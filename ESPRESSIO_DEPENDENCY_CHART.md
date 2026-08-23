# ESPressio Dependency Chart — Current Released Generation

![ESPressio Library Dependency Chart](ESPRESSIO_DEPENDENCY_CHART.svg)

This document is the canonical snapshot of the current released ESPressio dependency generation at the Units 0.2.6 cascade step. Arrows point from the consuming library to the library it consumes.

- **Required** — the dependency is part of the library's normal/core contract.
- **Opt-in** — the dependency is introduced only when the corresponding integration/header is selected.

## Released generation

```text
Observable    3.0.2
Serializable  0.11.2
Units         0.2.6 (release candidate)
Timing        2.2.6
Threads       3.1.5
Event         6.0.1
Command       1.0.1
Security      0.4.0
Persistence   0.3.0
Sockets       0.7.1
ESP-Now       0.8.1
WiFi          0.1.0
Serial        0.8.0
```

## Relevant dependency edges

```text
Units 0.2.6
    -> none required
    - - -> Serializable >= 0.11.2 < 1.0.0
            Serializable Unit variants

Timing 2.2.6
    -> Units >= 0.2.5 < 1.0.0
    -> Observable >= 3.0.2 < 4.0.0

Threads 3.1.5
    -> Timing >= 2.2.5 < 3.0.0
    -> Observable >= 3.0.2 < 4.0.0

Event 6.0.1
    -> Threads >= 3.1.5 < 4.0.0
    -> Timing >= 2.2.5 < 3.0.0
    -> Observable >= 3.0.2 < 4.0.0
    - - -> Serializable >= 0.10.3 < 1.0.0
```

Other current opt-in integrations remain as documented by their owning libraries; each is advanced only when its upstream release exists.

## Active Serializable 0.11.2 cascade

```text
Serializable 0.11.2
    -> Units 0.2.6
        -> Timing 2.2.7
            -> Threads 3.1.6
                -> Event 6.0.2
                    -> Command 1.0.2
                    -> Security 0.4.1
                        -> Persistence 0.3.1
                    -> Sockets 0.7.2
                    -> ESP-Now 0.8.2
                -> WiFi 0.2.0
                    -> Serial 0.8.1
```

Units 0.2.5 and Timing 2.2.6 were already released during the superseded 0.11.1 cascade. Therefore the corrected 0.11.2 train introduces Units 0.2.6 and Timing 2.2.7; unreleased downstream version numbers remain unchanged.

The cascade is released in dependency order. Future-version labels above describe planned release steps and are not claimed as released until their corresponding upstream releases are published.

## Dependency-direction invariants

Event owns the generic Event mechanism. Domain-specific Event types and bridges belong to the lowest-order library that owns the represented concept without introducing a reverse dependency.

Serial remains terminal/downstream. No upstream ESPressio library should depend on Serial.

ESPressio Tree remains standalone and is not part of this dependency cascade.
