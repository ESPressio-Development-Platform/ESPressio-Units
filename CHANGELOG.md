# Changelog

All notable changes to this project are documented in this file.

The structure follows the principles of [Keep a
Changelog](https://keepachangelog.com/en/1.1.0/) and [Semantic
Versioning](https://semver.org/).

> **Historical note:** This changelog was reconstructed retrospectively
> from published GitHub Releases, tags, release notes, repository
> history, and the documented public API. Where an historical release
> had little or no release-note detail, the entry is intentionally terse
> rather than inferring unsupported intent.

## [0.2.2] - 2026-08-20

### Changed

- Updated the optional ESPressio Serializable integration baseline from
  `>= 0.10.0 < 1.0.0` to `>= 0.10.1 < 1.0.0`.
- Updated PlatformIO examples and current dependency documentation to target
  ESPressio Serializable 0.10.1.
- Updated package metadata for ESPressio Units 0.2.2.

### Compatibility

- Ordinary Unit types remain dependency-free with respect to ESPressio
  Serializable.
- Serializable Unit variants remain opt-in and source-compatible.
- No Units runtime or public API behaviour changes are introduced by this
  dependency-maintenance release.

## [0.2.1] - 2026-08-19

### Changed

-   Updated the optional ESPressio Serializable compatibility guidance to
    target `>= 0.9.0 < 1.0.0`.
-   Replaced the narrower `^0.9.0` consumer guidance so Serializable Unit
    variants may consume later compatible 0.x minor and patch releases while
    remaining protected from a future 1.x breaking release.
-   Updated current dependency documentation and release metadata for the
    ESPressio dependency refresh.

## [0.2.0] - 2026-08-18

### Added

-   Added opt-in ESPressio Serializable integration across the Unit
    catalogue.
-   Added `SerializableUnit` and Serializable counterparts for concrete
    Unit families.
-   Added per-type `*_Serializable.hpp` headers.
-   Added `ESPressio_SerializableUnits.hpp` umbrella header.
-   Added Serializable time aliases across the supported SI magnitude
    range.
-   Added `MakeSerializableUnit()` promotion support.
-   Added serialization of runtime Unit state (`value` and
    `orderOfMagnitude`).

### Changed

-   Preserved the existing non-Serializable Unit hierarchy without
    adding virtual dispatch, serialization metadata, or mandatory
    serialization overhead.
-   Kept ESPressio Serializable as a pay-for-what-you-use dependency.

## [0.1.0] - 2026-08-11

### Added

-   Initial public pre-release of ESPressio Units.
-   Added the strongly typed `Unit` foundation, SI order-of-magnitude
    support, physical contexts, conversions, formatting, typed formula
    helpers, and concrete Unit families.
