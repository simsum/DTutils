//
//  DTutils.cpp
//  
//
//  Created by Sven Steinmeier on 15.06.14.
//  sven.steinmeier@gmail.com
//

#include "DTutils.h"
#include "Arduino.h"

//  --- intere Funktionen und Konstanten ---

//  Monatskennziffern für die Wochentagsberechnung (Sakamoto-Verfahren, 0 = Sonntag)

static const uint8_t MonthDigit[] = {0,3,2,5,0,3,5,1,4,6,2,4};  // API starts from 1, this array starts from 0!!!

//  Monatslänge festlegen

static const uint8_t MonthDays[]={31,28,31,30,31,30,31,31,30,31,30,31}; // API starts from 1, this array starts from 0!!!

// Osterkennzahl berechnen, wird für weitere Berechnungen benötigt
// gültig bis 2199
// siehe auch http://manfred.wilzeck.de/Datum_berechnen.html

static int EasterCode(int Year)
{
    int a;    //Hilfvariable
    int b;    //Hilfvariable
    int c;    //Hilfvariable
    int e;    //Osterkennzahl
    a = (Year % 19 * 19 + 24) % 30;
    b = 120 + a - (a / 27);
    c = (b + (Year * 5 / 4) - (Year / 2100)) % 7;
    e = b - c;
    return e;
}

//  --- Funktionen ---

//  Die Funktion DayOfWeek berechnet den Wochentag aus dem Eingangsdatum.
//  Gültig für den gesamten Gregorianischen Kalender.

int DayOfWeek(int Year, int Month, int Day)
{
    if (Month < 3) {
        Year -= 1;                                                      // Januar/Februar zählen zum Vorjahr
    }
    int WeDay = (Year + Year / 4 - Year / 100 + Year / 400 + MonthDigit[Month-1] + Day) % 7;  // 0=Son, 1=Mon, usw.
    return (WeDay == 0) ? 7 : WeDay;                                    // 1=Mon ... 7=Son
}


// Tag Start Sommerzeit (02:00 Uhr/März) - Schaltjahre werden berücksichtigt

int StartDateDaylightSaving(int Year)
{
    int e = EasterCode(Year);
    int Day;
    Day = 25 + (e + 2) % 7;
    return Day;
}

// Tag Ende Sommerzeit (03:00 Uhr/Oktober)

int EndDateDaylightSaving(int Year)
{
    int e = EasterCode(Year);
    int Day;
    Day = 25 + (e + 5) % 7;
    return Day;
}

//  Die Funktion DaylightSaving überprüft, ob zum angegebenen Zeitpunkt in Mitteleuropa Sommerzeit herrscht.
//  Eingabe ist UTC (Weltzeit): Die Umstellung erfolgt EU-weit am letzten Sonntag im März bzw. Oktober um 01:00 UTC.

bool DaylightSaving (int Year, int Month, int Day, int Hour, int Minute)                    // TRUE/HIGH wenn Sommerzeit
{
    // long-Arithmetik nötig: auf AVR ist int nur 16 Bit, 366 * 1440 passt nicht hinein
    long StartDSInM   = (long)DayOfYear(Year, 3, StartDateDaylightSaving(Year)) * 1440L + 60;   // Start Sommerzeit in Minuten
    long EndDSInM     = (long)DayOfYear(Year, 10, EndDateDaylightSaving(Year)) * 1440L + 60;    // Ende Sommerzeit in Minuten
    long NowInMinute  = (long)DayOfYear(Year, Month, Day) * 1440L + (long)Hour * 60 + Minute;   // aktuelle Minuten im Jahr

    return NowInMinute >= StartDSInM && NowInMinute < EndDSInM;                             // TRUE wenn Zeitraum innerhalb Sommerzeit
}

//  Die Funktion DAYOFYEAR berechnet den Tag des Jahres aus dem Eingangsdatum.

int DayOfYear (int Year, int Month, int Day)      // ( 05.01.2012 = 5 .... 31.12.2012 = 366)
{
    int sj = LeapYear(Year);
    int DayNbr = Day + 489 * Month / 16 - (7 + Month) / 10 * (2 - sj) -30 ;
    return DayNbr;
}


//  Die Funktion LEAPYEAR testet, ob das Eingangsjahr ein Schaltjahr ist und gibt gegebenenfalls TRUE bzw. "1" aus.
//  Gültig im gesamten Gregorianischen Kalender.

int LeapYear (int Year)                     // Schaltjahr aktiv (1 = Ja)
{
    int sj = (1/(1 + Year % 4)) - (1/(1 + Year % 100)) + (1/(1 + Year % 400));
    return sj;
}

//  Die Funktion SunMiddayTimeUTC berechnet abhängig vom Tagesdatum zu welcher Tageszeit die Sonne exakt im Süden steht.
//  Die Berechnung erfolgt in UTC (Weltzeit).
//  Lon = Längengrad des Bezugsortes.

float SunMiddayTimeUTC (float Lon, int Year, int Month, int Day)
{
    float T = DayOfYear(Year, Month, Day);
    float OFFSET = -0.1752 * sin(0.033430 * T + 0.5474) - 0.1340 * sin(0.018234 * T - 0.1939);
    float SunMidday = (12.0 - OFFSET - Lon * 0.0666666666666);
    return SunMidday;
}

//  Die Funktion DTToInt konvertiert das Datums- und Zeit-Format in Sekunden seit 1970.
//  (makeTime aus Time.h berechnet nicht das UNIX Format seit 1970)

void DTToInt(dtElements dtEl, uint32_t &Seconds)
{
    int i;
    Seconds = (dtEl.Year - 1970) * SECS_PER_YEAR;
    for (i = 0; i < (int)(dtEl.Year - 1970); i++) {
        if (LeapYear(i + 1970)>= 1) {
            Seconds+= SECS_PER_DAY;   // add extra days for leap years
        }
    }
    
    for (i = 1; i < dtEl.Month; i++) {
        if ( (i == 2) && LeapYear(dtEl.Year)) {
            Seconds += SECS_PER_DAY * 29;
        } else {
            Seconds += SECS_PER_DAY * MonthDays[i-1];  //monthDay array starts from 0
        }
    }
    Seconds+= (dtEl.Day-1) * SECS_PER_DAY;
    Seconds+= dtEl.Hour * SECS_PER_HOUR;
    Seconds+= dtEl.Minute * SECS_PER_MIN;
    Seconds+= dtEl.Second;
}

//  Die Funktion IntToDT konvertiert Sekunden seit 1970 in Datum und Zeit.
//  (breakTime aus Time.h berechnet nicht das UNIX Format Format seit 1970)

void IntToDT(uint32_t Seconds,dtElements &dtEl)
{
    uint32_t year;
    uint8_t month, monthLength;
    uint32_t time;
    unsigned long days;
    
    time = (uint32_t)Seconds;
    dtEl.Second = time % 60;
    time /= 60; // now it is minutes
    dtEl.Minute = time % 60;
    time /= 60; // now it is hours
    dtEl.Hour = time % 24;
    time /= 24; // now it is days
    
    year = 0;
    days = 0;
    while((days += (LeapYear(year + 1970) ? 366 : 365)) <= time) {
        year++;
    }
    dtEl.Year = year + 1970;
    
    days -= LeapYear(year + 1970) ? 366 : 365;
    time  -= days; // now it is days in this year, starting at 0
    
    days=0;
    month=0;
    monthLength=0;
    for (month=0; month<12; month++) {
        if (month==1) { // february
            if (LeapYear(year + 1970)) {
                monthLength=29;
            } else {
                monthLength=28;
            }
        } else {
            monthLength = MonthDays[month];
        }
        
        if (time >= monthLength) {
            time -= monthLength;
        } else {
            break;
        }
    }
    dtEl.Month = month + 1;  // jan is month 1
    dtEl.Day = time + 1;     // day of month
}

//  Die Funktion LocalTimeToUTC rechnet Ortszeit in UTC um.
//  TimeZone = Abweichung von UTC in Stunden (MEZ = +1), DLS = true wenn Sommerzeit (zusätzlich +1 h) gilt.

void LocalTimeToUTC(int8_t TimeZone, bool DLS, dtElements &dtInput, dtElements &dtOutput)
{
    uint32_t Seconds;
    DTToInt(dtInput, Seconds);
    Seconds -= (int32_t)TimeZone * (int32_t)SECS_PER_HOUR;
    if (DLS) {
        Seconds -= SECS_PER_HOUR;
    }
    IntToDT(Seconds, dtOutput);
}
