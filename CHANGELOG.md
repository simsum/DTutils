# Changelog

## 1.1.0

### Fixed
- **Link error (#1):** the header declared `SunMiddayTimeUTC`, the implementation was named `sunMiddayTimeUTC`. Both are now `SunMiddayTimeUTC`. Added tests for its result.
- `IntToDT`: leap years were evaluated on the offset from 1970 instead of the real year, so dates such as 29 Feb 2024 came out one day off.
- `DayOfWeek`: wrong for most dates (only coincidentally right for some years such as 2014). Now uses a verified algorithm.
- `DaylightSaving`: switch times were 02:00/03:00 instead of 01:00 UTC; the end instant was inclusive. The minute calculation overflowed the 16-bit `int` on AVR boards.
- `LocalTimeToUTC`: the `DLS` parameter was ignored.

### Added
- Host unit tests (`make -C test`) and GitHub Actions CI.
- `library.properties`, `keywords.txt`, Doxygen comments, English and German README.

### Removed
- Empty `DTutils` class and the unused `Time.h` include in the example.
