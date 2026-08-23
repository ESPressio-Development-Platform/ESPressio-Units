# ESPressio Dependency Chart — Current Released Generation

![ESPressio Library Dependency Chart](ESPRESSIO_DEPENDENCY_CHART.svg)

This document is the canonical snapshot of the current released ESPressio dependency generation at the Units 0.2.7 cascade step. Arrows point from the consuming library to the library it consumes.

- **Required** — the dependency is part of the library's normal/core contract.
- **Opt-in** — the dependency is introduced only when the corresponding integration/header is selected.

## Released generation

```text
Observable    3.0.2
Serializable  0.11.3
Units         0.2.7 (release candidate)
Timing        2.2.7
Threads       3.1.6
Event         6.0.2
Command       1.0.2
Security      0.4.1
Persistence   0.3.1
Sockets       0.7.2
ESP-Now       0.8.2
WiFi          0.2.0 (merged, not yet released)
Serial        0.8.0
```

## Relevant dependency edges

```text
Units 0.2.7
    -> none required
    - - -> Serializable >= 0.11.3 < 1.0.0
            Serializable Unit variants

Timing 2.2.7
    -> Units >= 0.2.6 < 1.0.0
    -> Observable >= 3.0.2 < 4.0.0

Threads 3.1.6
    -> Timing >= 2.2.7 < 3.0.0
    -> Observable >= 3.0.2 < 4.0.0

Event 6.0.2
    -> Threads >= 3.1.6 < 4.0.0
    -> Timing >= 2.2.7 < 3.0.0
    -> Observable >= 3.0.2 < 4.0.0
```

Other current opt-in integrations remain as documented by their owning libraries; each is advanced only when its upstream release exists.

## Active Serializable 0.11.3 cascade

```text
Serializable 0.11.3
    -> Units 0.2.7
        -> Timing 2.2.8
            -> Threads 3.1.7
                -> Event 6.0.3
                    -> Command 1.0.3
                    -> Security 0.4.2
                        -> Persistence 0.3.2
                    -> Sockets 0.7.3
                    -> ESP-Now 0.8.3
                -> WiFi 0.2.0 release validation
                    -> Serial next patch release
```

The cascade is released in dependency order. Future-version labels above describe planned release steps and are not claimed as released until their corresponding upstream releases are published.

## Dependency-direction invariants

Event owns the generic Event mechanism. Domain-specific Event types and bridges belong to the lowest-order library that owns the represented concept without introducing a reverse dependency.

Serial remains terminal/downstream. No upstream ESPressio library should depend on Serial.

ESPressio Tree remains standalone and is not part of this dependency cascade.
