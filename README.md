# DTutils

[![CI](https://github.com/simsum/DTutils/actions/workflows/ci.yml/badge.svg)](https://github.com/simsum/DTutils/actions/workflows/ci.yml)

Small, dependency-free Arduino library for date and time calculations: weekday, leap year, central European daylight saving time, conversion to and from Unix time, and the time of solar noon.

🇩🇪 [Deutsche Version](README.de.md)

## Installation

- **Arduino IDE:** *Sketch → Include Library → Add .ZIP Library…* and select the ZIP of this repository (*Code → Download ZIP*).
- **Manual:** copy the folder to `<Sketchbook>/libraries/DTutils`.

```cpp
#include <DTutils.h>
```

## Quick start

```cpp
dtElements dt = {2014, 6, 17, 14, 15, 16};   // Year, Month, Day, Hour, Minute, Second
uint32_t unixTime;

DTToInt(dt, unixTime);                        // 1403014516
IntToDT(unixTime, dt);                        // and back
Serial.println(DayOfWeek(2014, 6, 17));       // 2 = Tuesday
```

See [`examples/DTutils`](examples/DTutils/DTutils.ino) for a complete sketch.

## Data type

```cpp
typedef struct {
    uint32_t Year;     // 4 digits, e.g. 2014
    uint8_t  Month;    // 1..12
    uint8_t  Day;      // 1..31
    uint8_t  Hour;     // 0..23
    uint8_t  Minute;   // 0..59
    uint8_t  Second;   // 0..59
} dtElements;
```

## Function reference

| Function | Description |
|---|---|
| `int DayOfWeek(int Year, int Month, int Day)` | Weekday: `1` = Monday … `7` = Sunday. |
| `int DayOfYear(int Year, int Month, int Day)` | Day of the year: 5 Jan = 5 … 31 Dec = 365 (366 in leap years). |
| `int LeapYear(int Year)` | `1` if leap year, otherwise `0`. |
| `int StartDateDaylightSaving(int Year)` | Day in **March** on which daylight saving time starts (last Sunday), e.g. `30` for 2014. |
| `int EndDateDaylightSaving(int Year)` | Day in **October** on which daylight saving time ends (last Sunday), e.g. `26` for 2014. |
| `bool DaylightSaving(int Year, int Month, int Day, int Hour, int Minute)` | `true` if central European summer time (CEST) is active. Pass the time as **UTC**; the switch is at 01:00 UTC. |
| `void DTToInt(dtElements dt, uint32_t &Seconds)` | Date/time → seconds since 1970-01-01 00:00:00 (Unix time). |
| `void IntToDT(uint32_t Seconds, dtElements &dt)` | Seconds since 1970 → date/time. |
| `void LocalTimeToUTC(int8_t TimeZone, bool DLS, dtElements &in, dtElements &out)` | Local time → UTC. `TimeZone` = hours from UTC (CET = `+1`), `DLS` = `true` if daylight saving (+1 h) applies. |
| `float SunMiddayTimeUTC(float Lon, int Year, int Month, int Day)` | Time of day (UTC, decimal hours) at which the sun is exactly in the south. `Lon` = longitude in degrees, east positive. Example: `11.12` = 11:07 UTC. *Approximation, accurate to about a minute.* |

Note: the `makeTime`/`breakTime` functions of the Time library work with a different epoch offset; `DTToInt`/`IntToDT` use the standard Unix epoch (1970).

### Limits

- `uint32_t` seconds overflow in February 2106.
- Daylight saving rules are the **EU rules** (last Sunday of March/October, 01:00 UTC). Other regions are not supported.

## Tests

The library is tested on a PC against the C standard library for every day from 1970 to 2099:

```bash
make -C test
```

Continuous integration also compiles the example for Arduino Uno and Mega.

## Changelog

See [CHANGELOG.md](CHANGELOG.md).

## License

See [LICENSE](LICENSE).
