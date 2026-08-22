# ESPressio Units

Strongly typed SI unit and physical-quantity components for the ESPressio Development Platform.

ESPressio Units makes physical meaning part of the C++ type system so APIs can distinguish seconds from milliseconds, distance from energy, and other otherwise-identical numeric values at compile time.

## Current Version — 0.2.3

Version 0.2.3 retains the comprehensive Units 0.2 API and validates optional Serializable Unit variants against ESPressio Serializable 0.10.2. Ordinary Unit types remain independent of Serializable.

# Why strongly typed Units?

A raw integer or floating-point value cannot tell the compiler whether it represents microseconds, metres, kilograms, ohms or degrees Celsius.

```cpp
uint64_t timeout = 500;
```

Is that 500 nanoseconds? microseconds? milliseconds? seconds?

A strongly typed value makes the contract explicit:

```cpp
ESPressio::Units::MilliSeconds<uint64_t> timeout(500);
```

This improves readability, makes APIs self-documenting and allows dimensionally invalid operations to be rejected before firmware runs.

# Compatibility

ESPressio Units contains no processor-specific implementation. It is designed for Arduino-compatible C++ targets that provide the required standard C++ facilities and Arduino `String` support used by formatting helpers.

Template instantiation, formatted conversion and floating-point use can still be significant on very small targets such as classic AVR; verify flash/RAM usage for the intended board/toolchain.

# ESPressio Development Platform

ESPressio libraries are designed to be light-weight, easy to use, object-oriented and explicit about SOLID dependency boundaries.

Project website: [espressio.org](https://espressio.org).

## License

Apache License 2.0. See [LICENSE](LICENSE).

# Namespace

```cpp
ESPressio::Units
```

Important public concepts include:

- `UnitOrderOfMagnitude`
- `UnitContext`
- `UnitRepresentation`
- `Unit<TValue, TBaseOrderOfMagnitude, TContext>`
- specialised context types such as `Time`, `Distance`, `Mass`, `Velocity`, `Energy`, etc.
- predefined time-magnitude types such as `NanoSeconds`, `MicroSeconds`, `MilliSeconds` and `Seconds`
- strongly typed conversion/formula helpers
- optional Serializable variants

# Dependencies

Required ESPressio dependencies: **none**.

Optional Serializable Unit variants:

```text
ESPressio Serializable >= 0.10.2 < 1.0.0
```

Ordinary Unit headers do not acquire Serializable. Serializable counterparts are exposed through separate `*_Serializable.hpp` headers and `ESPressio_SerializableUnits.hpp`.

See [ESPRESSIO_DEPENDENCY_CHART.md](ESPRESSIO_DEPENDENCY_CHART.md).

# Installation

Core Units:

```ini
lib_deps =
    espressio-development-platform/ESPressio-Units@^0.2.3
```

With optional Serializable Unit types:

```ini
lib_deps =
    espressio-development-platform/ESPressio-Units@^0.2.3
    espressio-development-platform/ESPressio-Serializable@^0.10.2
```

# `UnitOrderOfMagnitude`

`UnitOrderOfMagnitude` represents SI base-10 prefixes from quecto (10^-30) through quetta (10^30). `Base` represents the unprefixed 10^0 magnitude.

```cpp
#include <ESPressio_UnitEnums.hpp>

using namespace ESPressio::Units;

UnitOrderOfMagnitude sourceMagnitude = Milli; // 10^-3
UnitOrderOfMagnitude targetMagnitude = Kilo;  // 10^3
```

The complete prefix range is:

| Enumeration | Symbol | Magnitude |
| --- | ---: | ---: |
| `Quecto` | q | 10^-30 |
| `Ronto` | r | 10^-27 |
| `Yocto` | y | 10^-24 |
| `Zepto` | z | 10^-21 |
| `Atto` | a | 10^-18 |
| `Femto` | f | 10^-15 |
| `Pico` | p | 10^-12 |
| `Nano` | n | 10^-9 |
| `Micro` | μ | 10^-6 |
| `Milli` | m | 10^-3 |
| `Centi` | c | 10^-2 |
| `Deci` | d | 10^-1 |
| `Base` | — | 10^0 |
| `Deca` | da | 10^1 |
| `Hecto` | h | 10^2 |
| `Kilo` | k | 10^3 |
| `Mega` | M | 10^6 |
| `Giga` | G | 10^9 |
| `Tera` | T | 10^12 |
| `Peta` | P | 10^15 |
| `Exa` | E | 10^18 |
| `Zetta` | Z | 10^21 |
| `Yotta` | Y | 10^24 |
| `Ronna` | R | 10^27 |
| `Quetta` | Q | 10^30 |

Magnitude names/symbols can be queried using the shared representation selector:

```cpp
const char* microSymbol = GetUnitOrderOfMagnitudeSymbol(
    Micro,
    UnitRepresentation::Symbol
); // "μ"

const char* microName = GetUnitOrderOfMagnitudeSymbol(
    Micro,
    UnitRepresentation::Name
); // "micro"
```

`Base` intentionally has no prefix string.

# `UnitContext`

`UnitContext` describes **physical meaning** independently from numeric type and SI prefix.

This distinction matters because different quantities can share coherent SI dimensions while still expressing different application contracts. For example, work, heat and energy may all be measured in joules but need not be interchangeable in every API.

The library represents contexts covering:

- dimensionless ratios and angles;
- all seven SI base quantities;
- distance, area, volume, velocity and acceleration;
- force, pressure, torque, density and viscosity;
- energy, work, heat, power and thermal quantities;
- electrical and magnetic quantities;
- photometric quantities;
- decimal storage capacity;
- chemical quantities; and
- radiation quantities.

```cpp
#include <ESPressio_UnitEnums.hpp>

using namespace ESPressio::Units;

UnitContext distanceContext = UnitContext::Distance;

const char* symbol = GetUnitContextSymbol(
    distanceContext,
    UnitRepresentation::Symbol
); // "m"

const char* name = GetUnitContextSymbol(
    distanceContext,
    UnitRepresentation::Name
); // "metre"
```

Context symbols are magnitude-free so callers can compose them with the selected SI prefix.

`StorageCapacity` uses decimal SI magnitudes (`kB`, `MB`, etc.). IEC binary prefixes such as KiB/MiB are not represented by `UnitOrderOfMagnitude`.

# Generic `Unit<TValue, TBaseOrderOfMagnitude, TContext>`

`Unit` pairs:

- an arithmetic value;
- the instance's current magnitude;
- a compile-time canonical base magnitude; and
- a compile-time physical context.

It does this without virtual dispatch.

```cpp
#include <ESPressio_Unit.hpp>

using namespace ESPressio::Units;

Unit<int> distance(25, Centi);
Unit<unsigned long> timeout(500, Milli);
Unit<double> resistance(4.7, Kilo);
Unit<float> baseValue(12.5f);
```

`TValue` must be a non-boolean arithmetic type. Invalid representations fail at compile time.

A specialised type can define its canonical magnitude/context:

```cpp
template <typename TValue>
struct Metres : public Unit<TValue, Base, UnitContext::Distance> {
    using Unit<TValue, Base, UnitContext::Distance>::Unit;
};
```

# Specialised context types

Most users should consume the strongly named context headers rather than raw `Unit`:

```cpp
#include <ESPressio_Distance.hpp>
#include <ESPressio_Time.hpp>

using namespace ESPressio::Units;

Distance<float> distance(12.5f);
Time<unsigned long> timeout(500, Milli);
```

Or include the full catalogue:

```cpp
#include <ESPressio_Units.hpp>

Mass<double> mass(2.5);
ElectricResistance<float> resistance(4.7f);
StorageCapacity<unsigned long> size(2, Mega);
```

The filename/type convention is `ESPressio_<Context>.hpp` and `<Context><TValue>`.

# Time types for embedded APIs

Time is especially common in embedded code, so `ESPressio_Time.hpp` provides aliases whose type name carries the magnitude:

```cpp
Seconds<unsigned long> interval(5);
MilliSeconds<unsigned long> timeout(500);
MicroSeconds<unsigned long> sampleTime(250);
NanoSeconds<uint64_t> timestamp(123456789ULL);
```

`Time<TValue>` remains the base-seconds compatible form, and a magnitude can also be selected through the template parameter where appropriate.

These types make interfaces substantially clearer:

```cpp
void SetTimeout(
    ESPressio::Units::MilliSeconds<uint64_t> timeout
);
```

instead of:

```cpp
void SetTimeout(uint64_t timeout); // unit is undocumented at the type level
```

# Changing values and magnitudes

Construction without an explicit magnitude uses the specialised type's canonical base magnitude. `SetValue()` without an explicit magnitude preserves the instance's **current** magnitude.

```cpp
Time<unsigned long> elapsed(5); // 5 seconds

elapsed.SetValue(10);         // 10 seconds
elapsed.SetValue(250, Milli); // 250 milliseconds
elapsed.SetValue(500);        // 500 milliseconds; still Milli
```

That distinction is intentional and lets a value retain the representation chosen for that instance.

# Magnitude conversion

Convert a compatible quantity explicitly:

```cpp
Distance<double> distance(1250.0, Milli);
double metres = distance.ToMagnitude(Base);
```

Checked conversion paths protect finite/range behavior. Explicit unchecked conversion facilities remain available for code that has already established numeric safety.

The generated exhaustive conversion reference is available at:

```text
docs/UNIT_CONVERSIONS.md
```

# Strongly typed formulas

Compatible physical quantities can participate in formula helpers without losing dimensional meaning.

```cpp
Distance<double> distance(100.0, Base);
MilliSeconds<unsigned long> elapsed(500);

Velocity<double> velocity =
    Velocity<double>::From(distance, elapsed);
```

The elapsed value is normalized according to its magnitude; dimensionally invalid operands are rejected at compile time.

The same pattern is used across the formula relationships represented by the library.

# Formatting

Units can provide symbolic or human-readable formatting suitable for diagnostics and Arduino output.

The formatting layer composes:

```text
numeric value + magnitude prefix + context unit
```

so a distance might be represented in symbol form (`mm`) or full-name form (`millimetre`) according to the selected `UnitRepresentation`.

# Optional Serializable Unit variants

Serialization is deliberately not part of the core Unit abstraction.

```text
ordinary Unit
    -> Units only

Serializable Unit
    -> Units
    - - -> Serializable 0.10.x
```

This is particularly useful for ESPressio Timing: Timing can use ordinary time values without requiring Serializable, while an application that needs serialized timestamps can explicitly select a Serializable time type.

Representative includes are separate from the normal Unit headers, and the batch umbrella is:

```cpp
#include <ESPressio_SerializableUnits.hpp>
```

# Design goals

- Compile-time distinction between incompatible quantities.
- Self-documenting APIs.
- Explicit, predictable magnitude conversion.
- Dimensional correctness in formulas.
- Defined range/rounding behavior.
- Minimal runtime overhead.
- No mandatory dependency on Serializable.
- Portable use on suitable Arduino/C++ targets.

# Tests and generated reference

The host tests and generated conversion catalogue are the exhaustive behavioral reference:

```text
docs/UNIT_CONVERSIONS.md
tools/generate_conversion_assets.py
```

# Changelog

See [CHANGELOG.md](CHANGELOG.md) for release history and notable changes.
