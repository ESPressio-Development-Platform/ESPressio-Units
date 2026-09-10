# ESPressio Dependency Chart — Current Released Generation

![ESPressio Library Dependency Chart](ESPRESSIO_DEPENDENCY_CHART.svg)

This document records the completed Serializable cascade and the current released ESPressio dependency generation. Arrows point from a consuming library to the library it consumes.

- **Required** — part of the normal/core package contract.
- **Opt-in** — introduced only when the corresponding integration/header is selected.

## Released generation

```text
Observable
Serializable
Units
Timing
Threads
Event
Command
Security
Persistence
Sockets
ESP-Now
WiFi
Serial
```

## Required dependency edges

```text
Observable
    -> none

Serializable
    -> none

Units
    -> none

Timing
    -> Units main
    -> Observable main

Threads
    -> Timing main
    -> Observable main

Event
    -> Threads main
    -> Timing main
    -> Observable main

Command
    -> Observable main

Security
    -> Observable main

Persistence
    -> none

Sockets
    -> Observable main

ESP-Now
    -> Timing main
    -> Observable main

WiFi
    -> Observable main
    -> Serializable main
    -> Threads main

Serial
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
Serializable
    -> Units
    -> Timing
    -> Threads
    -> Event
    -> Command / Security
    -> Persistence / Sockets / ESP-Now
    -> WiFi
    -> Serial
```

Event remains mechanism-only and has no reverse dependency on Command, Security, Sockets, ESP-Now or WiFi. Serial remains terminal/downstream. ESPressio Tree remains standalone and outside this cascade.
