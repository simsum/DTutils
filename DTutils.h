//
//  DTutils.h
//  Date and time helper functions for Arduino
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

/// Date and time as separate elements.
typedef struct  {
    uint32_t Year;      ///< Year, 4 digits (e.g. 2014)
    uint8_t Month;      ///< Month, 1..12
    uint8_t Day;        ///< Day of month, 1..31
    uint8_t Hour;       ///< Hour, 0..23
    uint8_t Minute;     ///< Minute, 0..59
    uint8_t Second;     ///< Second, 0..59
} 	dtElements;

/// Day of week for a date. Returns 1 = Monday ... 7 = Sunday.
int DayOfWeek (int Year, int Month, int Day);

/// Day in March on which daylight saving time (CEST) starts, e.g. 30 for 30 March.
int StartDateDaylightSaving (int Year);

/// Day in October on which daylight saving time (CEST) ends, e.g. 26 for 26 October.
int EndDateDaylightSaving (int Year);

/// True if central European daylight saving time is active.
/// The given time must be UTC; the switch happens at 01:00 UTC.
bool DaylightSaving (int Year, int Month, int Day, int Hour, int Minute);

/// Day of the year, 1 = 1 January ... 365/366 = 31 December. Leap years are handled.
int DayOfYear(int Year, int Month, int Day);

/// 1 if Year is a leap year, otherwise 0.
int LeapYear (int Year);

/// Time of day (UTC, in hours as float) at which the sun is exactly in the south.
/// Lon = longitude in degrees, east positive. Example: 11.12 means 11:07 UTC.
float SunMiddayTimeUTC (float Lon, int Year, int Month, int Day);

/// Converts date/time to seconds since 1970-01-01 00:00:00 (Unix time).
void DTToInt(dtElements dtEl, uint32_t &Seconds);

/// Converts seconds since 1970-01-01 00:00:00 (Unix time) to date/time.
void IntToDT(uint32_t Seconds, dtElements &dtEl);

/// Converts local time to UTC.
/// TimeZone = offset from UTC in hours (CET = +1), DLS = true if daylight saving time (+1 h) applies.
void LocalTimeToUTC(int8_t TimeZone, bool DLS, dtElements &dtInput, dtElements &dtOutput);

#endif
