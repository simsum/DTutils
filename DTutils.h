//
//  DTutils.h
//  
//
//  Created by Sven Steinmeier on 15.06.14.
//  sven.steinmeier@gmail.com
//

#ifndef _DTutils_h
#define _DTutils_h

#include "Arduino.h"

class DTutils
{
public:
    
private:
    
};

int DayOfWeek (int Year, int Month, int Day);
int StartDateDaylightSaving (int Year);
int EndDateDaylightSaving (int Year);
bool DaylightSaving (int Year, int Month, int Day, int Hour, int Minute);
int DayOfYear(int Year, int Month, int Day);
int LeapYear (int Year);
float SunMiddayTimeUTC (float Lon, int Year, int Month, int Day);

#endif
