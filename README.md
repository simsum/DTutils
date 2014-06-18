DTutils
=======

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