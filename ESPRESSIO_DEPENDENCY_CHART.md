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
    -> Units main
    -> Observable main

Threads 3.1.7
    -> Timing main
    -> Observable main

Event 6.0.3
    -> Threads main
    -> Timing main
    -> Observable main

Command 1.0.3
    -> Observable main

Security 0.4.2
    -> Observable main

Persistence 0.3.2
    -> none

Sockets 0.7.3
    -> Observable main

ESP-Now 0.8.3
    -> Timing main
    -> Observable main

WiFi 0.2.0
    -> Observable main
    -> Serializable main
    -> Threads main

Serial 0.8.1
    -> none in the core package
```

## Opt-in integration edges

```text
Units
    - - -> Serializable main

Threads
    - - -> Serializable representations transitively through Units

Event
    - - -> Serializable main

Command
    - - -> Event main

Security
    - - -> Event main

Persistence
    - - -> Serializable main
            protected persistence reaches Security through Serializable's protection API

Sockets
    - - -> Event main
    - - -> Command main
    - - -> Security main
    - - -> Timing main

ESP-Now
    - - -> Event main
    - - -> Command main
    - - -> Security main

WiFi
    - - -> Persistence main
    - - -> Security main
    - - -> Event main
    - - -> Command main

Serial
    - - -> Serializable main
    - - -> Timing main
    - - -> Threads main
    - - -> Event main
    - - -> Command main
    - - -> Security main
    - - -> Sockets main
    - - -> ESP-Now main
    - - -> WiFi main
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
