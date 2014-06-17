//
//  DTutils.cpp
//  
//
//  Created by Sven Steinmeier on 15.06.14.
//  sven.steinmeier@gmail.com
//

#include "DTutils.h"
#include "Arduino.h"


// Monatskennziffer festlegen (wird u.a. zur Wochentagsberechnung benötigt)
// siehe auch http://manfred.wilzeck.de/Datum_berechnen.html

static const uint8_t MonthDigit[] = {23,7,8,20,0,12,20,4,16,24,8,16};// API starts from 1, this array starts from 0!!!

// Monatslänge festlegen

static const uint8_t MonthDays[]={31,28,31,30,31,30,31,31,30,31,30,31}; // API starts from 1, this array starts from 0!!!

//  Die Funktion DayOfWeek berechnet den Wochentag aus dem Eingangsdatum.
// siehe auch http://manfred.wilzeck.de/Datum_berechnen.html

int DayOfWeek(int Year, int Month, int Day)
{
    int WeDay;
    int Weekday;
    
    WeDay = (((5 * Year) + MonthDigit[Month-1] / 4) + Day - 1) % 7;     //Zwischenergabnis (0=Son, 1=Mon, usw.)
    if (WeDay < 1)                                                    //Endergebnis in der richtigen Folge (1=Mon, 2=Die,... 7=Son)
    {
        Weekday = 7;
    }
    else
    {
        Weekday = WeDay;
    }
    return Weekday;
}

// Osterkennzahl berechnen, wird für weitere Berechnungen benötigt
// siehe auch http://manfred.wilzeck.de/Datum_berechnen.html

int EasterCode(int Year)
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

//  Die Funktion DaylightSaving überprüft, ob im Augenblick Sommerzeit herrscht, oder nicht.
//  Sommerzeit wird aufgrund von UTC (Weltzeit) berechnet.

bool DaylightSaving (int Year, int Month, int Day, int Hour, int Minute)                    // TRUE/HIGH wenn Sommerzeit
{
    bool active;
    long StartDSInM   = (DayOfYear(Year, 3, StartDateDaylightSaving(Year)) *1440) + 120;    // Start Sommerzeit in Minuten
    long EndDSInM     = (DayOfYear(Year, 10, EndDateDaylightSaving(Year)) * 1440) + 180;    // Ende Sommerzeit in Minuten
    long NowInMinute  = (DayOfYear(Year, Month, Day) * 1440) + (Hour * 60) + Minute;        // aktuelle Minuten im Jahr
    
    active = NowInMinute >= StartDSInM && NowInMinute <= EndDSInM;                          // Ausgang TRUE wenn Zeitraum innerhalb Sommerzeit
    return active;
}

//  Die Funktion DAYOFYEAR berechnet den Tag des Jahres aus dem Eingangsdatum.

int DayOfYear (int Year, int Month, int Day)      // ( 05.01.2012 = 5 .... 31.12.2012 = 366)
{
    int sj = LeapYear (Year);
    int DayNbr = Day + 489 * Month / 16 - (7 + Month) / 10 * (2 - sj) -30 ;
    return DayNbr;
}


//  Die Funktion LEAPYEAR testet, ob das Eingangsjahr ein Schaltjahr ist und gibt gegebenenfalls TRUE bzw. "1" aus.

int LeapYear (int Year)                     // Schaltjahr aktiv (1 = Ja)
{
    int sj = (1/(1 + Year % 4)) - (1/(1 + Year % 100)) + (1/(1 + Year % 400));
    return sj;
}

//  Die Funktion sunMiddayTimeUTC berechnet abhängig vom Tagesdatum zu welcher Tageszeit die Sonne exakt im Süden steht.
//  Die Berechnung erfolgt in UTC (Weltzeit).
//  Lon = Längengrad des Bezugsortes.

float sunMiddayTimeUTC (float Lon, int Year, int Month, int Day)
{
    float T = DayOfYear(Year, Month, Day);
    float OFFSET = -0.1752 * sin(0.033430 * T + 0.5474) - 0.1340 * sin(0.018234 * T - 0.1939);
    float SunMidday = (12.0 - OFFSET - Lon * 0.0666666666666);
    return SunMidday;
    
}

//Die Funktion DTToInt konvertiert das Datums- und Zeit-Format in Sekunden seit 1970. (makeTime aus Time.h berechnet falsch)

unsigned long DTToInt(dtElements dt) //(int Year, int Month, int Day, int Hour, int Minute, int Second)
{
    
    int i;
    unsigned long seconds;
    seconds = (dt.Year - 1970) * SECS_PER_YEAR;
    for (i = 0; i < dt.Year - 1970; i++) {
        if (LeapYear(dt.Year)) {
            seconds +=  SECS_PER_DAY;   // add extra days for leap years
        }
    }
    return seconds;
}
