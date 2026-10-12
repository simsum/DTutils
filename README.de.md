# DTutils

Kleine Arduino-Bibliothek ohne Abhängigkeiten für Datums- und Zeitberechnungen: Wochentag, Schaltjahr, mitteleuropäische Sommerzeit, Umrechnung von/nach Unix-Zeit und Zeitpunkt des Sonnenhöchststands.

🇬🇧 [English version](README.md)

## Installation

- **Arduino IDE:** *Sketch → Bibliothek einbinden → .ZIP-Bibliothek hinzufügen…* (ZIP dieses Repositorys: *Code → Download ZIP*).
- **Manuell:** Ordner nach `<Sketchbook>/libraries/DTutils` kopieren.

```cpp
#include <DTutils.h>
```

## Schnellstart

```cpp
dtElements dt = {2014, 6, 17, 14, 15, 16};   // Jahr, Monat, Tag, Stunde, Minute, Sekunde
uint32_t unixTime;

DTToInt(dt, unixTime);                        // 1403014516
IntToDT(unixTime, dt);                        // und zurück
Serial.println(DayOfWeek(2014, 6, 17));       // 2 = Dienstag
```

Ein vollständiges Beispiel: [`examples/DTutils`](examples/DTutils/DTutils.ino).

## Funktionen

| Funktion | Beschreibung |
|---|---|
| `int DayOfWeek(int Year, int Month, int Day)` | Wochentag: `1` = Montag … `7` = Sonntag. |
| `int DayOfYear(int Year, int Month, int Day)` | Tag im Jahr: 5.1. = 5 … 31.12. = 365 (366 im Schaltjahr). |
| `int LeapYear(int Year)` | `1` bei Schaltjahr, sonst `0`. |
| `int StartDateDaylightSaving(int Year)` | Tag im **März**, an dem die Sommerzeit beginnt (letzter Sonntag), z. B. `30` für 2014. |
| `int EndDateDaylightSaving(int Year)` | Tag im **Oktober**, an dem die Sommerzeit endet (letzter Sonntag), z. B. `26` für 2014. |
| `bool DaylightSaving(int Year, int Month, int Day, int Hour, int Minute)` | `true`, wenn mitteleuropäische Sommerzeit herrscht. Zeit als **UTC** übergeben; Umstellung um 01:00 UTC. |
| `void DTToInt(dtElements dt, uint32_t &Seconds)` | Datum/Zeit → Sekunden seit 01.01.1970 00:00 (Unix-Zeit). |
| `void IntToDT(uint32_t Seconds, dtElements &dt)` | Sekunden seit 1970 → Datum/Zeit. |
| `void LocalTimeToUTC(int8_t TimeZone, bool DLS, dtElements &in, dtElements &out)` | Ortszeit → UTC. `TimeZone` = Stunden Abweichung von UTC (MEZ = `+1`), `DLS` = `true` bei Sommerzeit (+1 h). |
| `float SunMiddayTimeUTC(float Lon, int Year, int Month, int Day)` | Tageszeit (UTC, Dezimalstunden), zu der die Sonne exakt im Süden steht. `Lon` = Längengrad, Ost positiv. Beispiel: `11.12` = 11:07 UTC. *Näherung, auf etwa eine Minute genau.* |

Hinweis: `makeTime`/`breakTime` der Time-Bibliothek arbeiten mit einem anderen Offset; `DTToInt`/`IntToDT` verwenden die Standard-Unix-Epoche (1970).

### Grenzen

- Sekunden als `uint32_t` laufen im Februar 2106 über.
- Die Sommerzeit folgt den **EU-Regeln** (letzter Sonntag im März/Oktober, 01:00 UTC).

## Tests

```bash
make -C test
```

Vergleicht gegen die C-Standardbibliothek für jeden Tag von 1970 bis 2099.
