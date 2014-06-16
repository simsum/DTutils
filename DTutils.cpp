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

int DAYOFYEAR (int Year, int Month, int Day)      // ( 05.01.2012 = 5 .... 31.12.2012 = 366)
{
    int sj = LEAPYEAR (Year);
    int DayNbr = Day + 489 * Month / 16 - (7 + Month) / 10 * (2 - 0 /*sj*/) -30 ;
    return DayNbr;
}


//Die Funktion LEAPYEAR testet, ob das Eingangsjahr ein Schaltjahr ist und gibt gegebenenfalls TRUE aus.

int LEAPYEAR (int Year)                     // Schaltjahr aktiv (1 = Ja)
{
    int sj = (1/(1 + Year % 4)) - (1/(1 + Year % 100)) + (1/(1 + Year % 400));
    return sj;
}