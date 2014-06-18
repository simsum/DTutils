DTutils

Arduino Library mit Zeit und Datums Funktionen.

DayOfWeek

DayOfWeek gibt als Rückgabewert den Wochentag für das vorgegebene Datum zurück. 
siehe auch http://manfred.wilzeck.de/Datum_berechnen.html

Übergabewerte
int Year - Jahreszahl (4-stellig) z.b. 2014
int Month - Monat z.b. 6 für Juni
int Day - Tag z.b. 18

Rückgabewert
int DayOfWeek - Wochentag „1“ entspricht dem Montag, „2“ Dienstag usw.

StartDateDaylightSaving

StartDateDaylightSaving gibt als Rückgabewert den Tag im März, zu Beginn der Sommerzeit, für das angegeben Jahr zurück.
siehe auch http://manfred.wilzeck.de/Datum_berechnen.html

Übergabewerte
int Year - Jahreszahl (4-stellig) z.b. 2014

Rückgabewert
int StartDateDaylightSaving - Tag Beginn Sommerzeit z.b. 30 für den 30. März

EndDateDaylightSaving

EndDateDaylightSaving gibt als Rückgabewert den Tag im Oktober, zum Ende der Sommerzeit, für das angegeben Jahr zurück.
siehe auch http://manfred.wilzeck.de/Datum_berechnen.html

Übergabewerte
int Year - Jahreszahl (4-stellig) z.b. 2014

Rückgabewert
int EndDateDaylightSaving - Tag Ende Sommerzeit z.b. 26 für den 26. Oktober

DaylightSaving

Die Funktion DaylightSaving überprüft, ob im Augenblick Sommerzeit herrscht, oder nicht.

Übergabewerte
int Year - Jahreszahl (4-stellig) z.b. 2014
int Month - Monat z.b. 6 für Juni
int Day - Tag z.b. 18
int Hour - Stunde
int Minute - Minute

Rückgabewert
bool DaylightSaving - TRUE/HIGH wenn Sommerzeit


DayOfYear

Die Funktion DayOfYear berechnet den Tag des Jahres aus dem Eingangsdatum. Schaltjahre werden berücksichtigt.

Übergabewerte
int Year - Jahreszahl (4-stellig) z.b. 2014
int Month - Monat z.b. 6 für Juni
int Day - Tag z.b. 18

Rückgabewert
int DayOfYear - Tag im Jahr z.b. (05.01.2012 = 5 .... 31.12.2012 = 366)


LeapYear

Die Funktion LeapYear testet, ob das Eingangsjahr ein Schaltjahr ist und gibt gegebenenfalls TRUE bzw. "1" aus. Gültig für 1901 bis 2099.

Übergabewerte
int Year - Jahreszahl (4-stellig) z.b. 2014

Rückgabewert
int LeapYear - Schaltjahr aktiv (1 = Ja)

sunMiddayTimeUTC - noch beta

Die Funktion sunMiddayTimeUTC berechnet abhängig vom Tagesdatum zu welcher Tageszeit die Sonne exakt im Süden steht. Die Berechnung erfolgt in UTC (Weltzeit).

Übergabewerte
float Lon - Längengrad des Bezugsortes.
int Year - Jahreszahl (4-stellig) z.b. 2014
int Month - Monat z.b. 6 für Juni
int Day - Tag z.b. 18

Rückgabewert
float sunMiddayTimeUTC - Tageszeit, Sonne exakt im Süden. Die Uhrzeit wird als Float zurückgeben und muss noch umgerechnet werden.

DTToInt

Die Funktion DTToInt konvertiert das Datums- und Zeit-Format in Sekunden seit 1970 (Unix-Zeitformat) Hinweis: Bei der Funktion makeTime aus Time.h/.cpp fehlt der Offset von 1970.

Übergabewerte
dtElements dt - Datum und Uhrzeit als struct
	uint32_t Year	Jahreszahl (4-stellig)
    	uint8_t Month	Monat
    	uint8_t Day 	Tag
    	uint8_t Hour	Stunde
    	uint8_t Minute	Minute
    	uint8_t Second	Sekunde

Rückgabewert
unsigned long DTToInt - Sekunden seit 01.01.1970 00:00

IntToDT

Die Funktion IntToDT konvertiert Sekunden seit 1970 in Datum und Zeit.
Hinweis: Bei der Funktion breakTime aus Time.h/.cpp fehlt der Offset von 1970.

Übergabewerte
uint32_t - Seconds - Sekunden seit 01.01.1970 00:00

Übergabewerte bzw. Rückgabewert
dtElements dt - Datum und Uhrzeit als struct
	uint32_t Year	Jahreszahl (4-stellig)
    	uint8_t Month	Monat
    	uint8_t Day 	Tag
    	uint8_t Hour	Stunde
    	uint8_t Minute	Minute
    	uint8_t Second	Sekunde