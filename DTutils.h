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

#define SECS_PER_MIN  (60UL)
#define SECS_PER_HOUR (3600UL)
#define SECS_PER_DAY  (SECS_PER_HOUR * 24UL)
#define SECS_PER_YEAR (SECS_PER_DAY * 365UL)

typedef struct  {
    uint32_t Year;      //Year 4 Digit!!!
    uint8_t Month;
    uint8_t Day;
    uint8_t Hour;
    uint8_t Minute;
    uint8_t Second;
} 	dtElements;

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
void DTToInt(dtElements dtEl, uint32_t &Seconds);
void IntToDT(uint32_t Seconds, dtElements &dtEl);
void LocalTimeToUTC(int8_t TimeZone, bool DLS, dtElements &dtInput, dtElements &dtOutput);

#endif
