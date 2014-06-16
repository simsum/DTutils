//
//  DTutils.cpp
//  
//
//  Created by Sven Steinmeier on 15.06.14.
//
//

#include "DTutils.h"
#include "Arduino.h"

//Die Funktion DAYOFYEAR berechnet den Tag des Jahres aus dem Eingangsdatum.

int DayOfYear (int Year, int Month, int Day)      // ( 05.01.2012 = 5 .... 31.12.2012 = 366)
{
    int sj = LeapYear (Year);
    int DayNbr = Day + 489 * Month / 16 - (7 + Month) / 10 * (2 - sj) -30 ;
    return DayNbr;
}


//Die Funktion LEAPYEAR testet, ob das Eingangsjahr ein Schaltjahr ist und gibt gegebenenfalls TRUE bzw. "1" aus.

int LeapYear (int Year)                     // Schaltjahr aktiv (1 = Ja)
{
    int sj = (1/(1 + Year % 4)) - (1/(1 + Year % 100)) + (1/(1 + Year % 400));
    return sj;
}

// noch zu testende Funktionen !!!

//Die Funktion SUN_MIDDAY berechnet abhängig vom Tagesdatum zu welcher Tageszeit die Sonne exakt im Süden steht.
//Die Berechnung erfolgt in UTC (Weltzeit).
//Lon = Längengrad des Bezugsortes.

float sunMiddayTimeUTC (float Lon, int Year, int Month, int Day)
{
    float T = DayOfYear(Year, Month, Day);
    float OFFSET = -0.1752 * sin(0.033430 * T + 0.5474) - 0.1340 * sin(0.018234 * T - 0.1939);
    float SunMidday = (12.0 - OFFSET - Lon * 0.0666666666666);
    return SunMidday;
    
}