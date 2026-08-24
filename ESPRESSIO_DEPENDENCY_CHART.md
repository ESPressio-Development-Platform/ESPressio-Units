# ESPressio Dependency Chart — Current Released Generation

![ESPressio Library Dependency Chart](ESPRESSIO_DEPENDENCY_CHART.svg)

This document records the completed Serializable 0.11.3 cascade and the current released ESPressio dependency generation. Arrows point from a consuming library to the library it consumes.

- **Required** — part of the normal/core package contract.
- **Opt-in** — introduced only when the corresponding integration/header is selected.

## Released generation

```text
Observable    3.0.2
Serializable  0.11.3
Units         0.2.7
Timing        2.2.8
Threads       3.1.7
Event         6.0.3
Command       1.0.3
Security      0.4.2
Persistence   0.3.2
Sockets       0.7.3
ESP-Now       0.8.3
WiFi          0.2.0
Serial        0.8.1
```

## Required dependency edges

```text
Observable 3.0.2
    -> none

Serializable 0.11.3
    -> none

Units 0.2.7
    -> none

Timing 2.2.8
    -> Units >= 0.2.7 < 1.0.0
    -> Observable >= 3.0.2 < 4.0.0

Threads 3.1.7
    -> Timing >= 2.2.8 < 3.0.0
    -> Observable >= 3.0.2 < 4.0.0

Event 6.0.3
    -> Threads >= 3.1.7 < 4.0.0
    -> Timing >= 2.2.8 < 3.0.0
    -> Observable >= 3.0.2 < 4.0.0

Command 1.0.3
    -> Observable >= 3.0.2 < 4.0.0

Security 0.4.2
    -> Observable >= 3.0.2 < 4.0.0

Persistence 0.3.2
    -> none

Sockets 0.7.3
    -> Observable >= 3.0.2 < 4.0.0

ESP-Now 0.8.3
    -> Timing >= 2.2.8 < 3.0.0
    -> Observable >= 3.0.2 < 4.0.0

WiFi 0.2.0
    -> Observable >= 3.0.2 < 4.0.0
    -> Serializable >= 0.11.3 < 1.0.0
    -> Threads >= 3.1.7 < 4.0.0

Serial 0.8.1
    -> none in the core package
```

## Opt-in integration edges

```text
Units
    - - -> Serializable >= 0.11.3 < 1.0.0

Threads
    - - -> Serializable representations transitively through Units

Event
    - - -> Serializable >= 0.11.3 < 1.0.0

Command
    - - -> Event >= 6.0.3 < 7.0.0

Security
    - - -> Event >= 6.0.3 < 7.0.0

Persistence
    - - -> Serializable >= 0.11.3 < 1.0.0
            protected persistence reaches Security through Serializable's protection API

Sockets
    - - -> Event >= 6.0.3 < 7.0.0
    - - -> Command >= 1.0.3 < 2.0.0
    - - -> Security >= 0.4.2 < 1.0.0
    - - -> Timing >= 2.2.8 < 3.0.0

ESP-Now
    - - -> Event >= 6.0.3 < 7.0.0
    - - -> Command >= 1.0.3 < 2.0.0
    - - -> Security >= 0.4.2 < 1.0.0

WiFi
    - - -> Persistence >= 0.3.2 < 1.0.0
    - - -> Security >= 0.4.2 < 1.0.0
    - - -> Event >= 6.0.3 < 7.0.0
    - - -> Command >= 1.0.3 < 2.0.0

Serial
    - - -> Serializable >= 0.11.3 < 1.0.0
    - - -> Timing >= 2.2.8 < 3.0.0
    - - -> Threads >= 3.1.7 < 4.0.0
    - - -> Event >= 6.0.3 < 7.0.0
    - - -> Command >= 1.0.3 < 2.0.0
    - - -> Security >= 0.4.2 < 1.0.0
    - - -> Sockets >= 0.7.3 < 1.0.0
    - - -> ESP-Now >= 0.8.3 < 1.0.0
    - - -> WiFi >= 0.2.0 < 1.0.0
```

## Completed cascade

```text
Serializable 0.11.3
    -> Units 0.2.7
    -> Timing 2.2.8
    -> Threads 3.1.7
    -> Event 6.0.3
    -> Command 1.0.3 / Security 0.4.2
    -> Persistence 0.3.2 / Sockets 0.7.3 / ESP-Now 0.8.3
    -> WiFi 0.2.0
    -> Serial 0.8.1
```

Event remains mechanism-only and has no reverse dependency on Command, Security, Sockets, ESP-Now or WiFi. Serial remains terminal/downstream. ESPressio Tree remains standalone and outside this cascade.
