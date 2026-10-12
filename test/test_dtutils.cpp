// Host-side tests. Build and run:  make -C test   (needs g++ on Linux/macOS)
#include <stdio.h>
#include <time.h>
#include "DTutils.h"

static int failures = 0;
#define CHECK(cond, ...) do { if (!(cond)) { failures++; printf("FAIL line %d: ", __LINE__); printf(__VA_ARGS__); printf("\n"); } } while (0)

static int lastSunday(int year, int month) {
    for (int d = 31; d > 0; d--)
        if (DayOfWeek(year, month, d) == 7) return d;
    return 0;
}

int main() {
    // Reference is the C library, checked for every day from 1970 to 2099
    for (int y = 1970; y <= 2099; y++) {
        CHECK(LeapYear(y) == (((y % 4 == 0) && (y % 100 != 0)) || y % 400 == 0), "LeapYear(%d)", y);
        CHECK(StartDateDaylightSaving(y) == lastSunday(y, 3), "DST start %d", y);
        CHECK(EndDateDaylightSaving(y) == lastSunday(y, 10), "DST end %d", y);

        for (int m = 1; m <= 12; m++) {
            for (int d = 1; d <= 31; d++) {
                struct tm t = {};
                t.tm_year = y - 1900; t.tm_mon = m - 1; t.tm_mday = d; t.tm_hour = 13; t.tm_min = 14; t.tm_sec = 15;
                time_t tt = timegm(&t);
                struct tm r;
                gmtime_r(&tt, &r);
                if (r.tm_mon != m - 1) continue;                       // day does not exist in this month

                CHECK(DayOfWeek(y, m, d) == (r.tm_wday == 0 ? 7 : r.tm_wday), "DayOfWeek(%d,%d,%d)", y, m, d);
                CHECK(DayOfYear(y, m, d) == r.tm_yday + 1, "DayOfYear(%d,%d,%d)", y, m, d);

                dtElements in = { (uint32_t)y, (uint8_t)m, (uint8_t)d, 13, 14, 15 }, out = {};
                uint32_t s = 0;
                DTToInt(in, s);
                CHECK(s == (uint32_t)tt, "DTToInt(%d-%d-%d): %lu != %lu", y, m, d, (unsigned long)s, (unsigned long)tt);

                IntToDT((uint32_t)tt, out);
                CHECK(out.Year == in.Year && out.Month == in.Month && out.Day == in.Day &&
                      out.Hour == 13 && out.Minute == 14 && out.Second == 15, "IntToDT(%d-%d-%d)", y, m, d);
            }
        }
    }

    // Known values
    dtElements dt = {};
    IntToDT(1403014516UL, dt);                                         // example from the sketch
    CHECK(dt.Year == 2014 && dt.Month == 6 && dt.Day == 17 && dt.Hour == 14 && dt.Minute == 15 && dt.Second == 16, "sketch value");
    IntToDT(1709164800UL, dt);                                         // 2024-02-29 (leap day)
    CHECK(dt.Year == 2024 && dt.Month == 2 && dt.Day == 29, "leap day 2024");

    // Daylight saving switches at 01:00 UTC (2014: 30 March and 26 October)
    CHECK(!DaylightSaving(2014, 3, 30, 0, 59), "before start");
    CHECK( DaylightSaving(2014, 3, 30, 1, 0),  "at start");
    CHECK( DaylightSaving(2014, 6, 17, 12, 0), "summer");
    CHECK( DaylightSaving(2014, 10, 26, 0, 59), "before end");
    CHECK(!DaylightSaving(2014, 10, 26, 1, 0), "at end");
    CHECK(!DaylightSaving(2014, 12, 24, 12, 0), "winter");
    CHECK( DaylightSaving(2014, 7, 31, 23, 59), "late July (needs long arithmetic on AVR)");

    // Local time -> UTC
    dtElements loc = { 2014, 1, 1, 0, 30, 0 }, utc = {};
    LocalTimeToUTC(1, false, loc, utc);
    CHECK(utc.Year == 2013 && utc.Month == 12 && utc.Day == 31 && utc.Hour == 23 && utc.Minute == 30, "CET -> UTC");
    loc = { 2014, 6, 17, 14, 0, 0 };
    LocalTimeToUTC(1, true, loc, utc);
    CHECK(utc.Year == 2014 && utc.Month == 6 && utc.Day == 17 && utc.Hour == 12, "CEST -> UTC");

    // Solar noon, Berlin (13.4 deg E), 17 June 2014: about 11:07 UTC
    float noon = SunMiddayTimeUTC(13.4f, 2014, 6, 17);
    CHECK(noon > 11.08f && noon < 11.16f, "solar noon Berlin: %f", noon);
    // 3 November: equation of time ~ +16 min, so the sun is south ~16 min early
    float nov = SunMiddayTimeUTC(0.0f, 2014, 11, 3);
    CHECK(nov > 11.65f && nov < 11.85f, "solar noon Greenwich 3 Nov: %f", nov);

    printf(failures ? "\n%d failure(s)\n" : "all tests passed\n", failures);
    return failures ? 1 : 0;
}
