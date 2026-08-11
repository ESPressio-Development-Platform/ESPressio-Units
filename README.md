# ESPressio Units
Strongly-Typed SI Unit Components of the Flowduino ESPressio Development Platform.

Light-weight, expressive, and type-safe physical quantities for microcontroller development, with particular emphasis on reliable time representation and conversion.

## Latest Stable Version

ESPressio Units is currently under development and has not yet received its first stable release.

## ESPressio Development Platform

The **ESPressio** Development Platform is a collection of discrete (sometimes intra-connected) Component Libraries developed with a particular development ethos in mind.

The key objectives of the ESPressio Development Platform are:

- **Light-weight** - The Components should always strive to optimize memory consumption and operational overhead as much as possible, but not to the detriment of...
- **Ease of Use** - Many of our components serve as Developer-Friendly Abstractions of existing procedural code libraries.
- **Object-Oriented** - A `type` for everything, and everything in a `type`!
- **SOLID**:
  - > **S**ingle Responsibility Principle (SRP)  
    Break your code into smaller, focused components.
  - > **O**pen/Closed Principle (OCP)  
    Be open for extension but closed for modification.
  - > **L**iskov Substitution Principle (LSP)  
    Be substitutable for the base type without altering correctness.
  - > **I**nterface Segregation Principle (ISP)  
    Break interfaces into specific, client-focused ones.
  - > **D**ependency Inversion Principle (DIP)  
    Be dependent on abstractions, not concretions.

To the maximum extent possible within the limitations, restrictions, and constraints of the C++ language, the Arduino platform, and Microcontroller Programming itself, all Component Libraries of the **ESPressio** Development Platform must strive to honour the **SOLID** principles.

## License

ESPressio (and its component libraries, including this one) are subject to the *Apache License 2.0*.
Please see the [![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](LICENSE) accompanying this library for full details.

## Namespace

Every type, variable, constant, and function related to *ESPressio Units* will be located within the `Units` sub-namespace of the `ESPressio` parent namespace:

```cpp
namespace ESPressio::Units {
    // Unit types and supporting components
}
```

The namespace currently provides the following (*click the declaration to navigate to more information*):

- [`ESPressio::Units::UnitOrderOfMagnitude`](#unitorderofmagnitude)
- [`ESPressio::Units::UnitContext`](#unitcontext)
- `ESPressio::Units::UnitRepresentation`
- [`ESPressio::Units::Unit<TValue, TBaseOrderOfMagnitude, TContext>`](#unittvalue)

## Platformio.ini

Until the first stable release is published, the development sources can be included directly from GitHub:

```ini
lib_deps =
    https://github.com/Flowduino/ESPressio-Units.git
```

Please note that this uses the latest development commit, so the API may change without notice before the first stable release.

## Understanding Units

Values representing physical quantities should communicate more than their underlying numeric representation. An unqualified integer or floating-point value cannot, by itself, tell the compiler whether it represents microseconds, metres, ohms, degrees Celsius, or something else entirely.

ESPressio Units will provide specialised types for physical quantities and their units. These types are intended to make APIs self-documenting, prevent accidental operations between incompatible quantities, and provide explicit, reliable conversions between compatible units.

Time is the library's most immediately relevant quantity because it appears throughout embedded development in delays, timeouts, intervals, scheduling, sampling, and performance measurement. The library is nevertheless intended to cover the wider International System of Units (SI), including both base and derived quantities.

## `UnitOrderOfMagnitude`

`UnitOrderOfMagnitude` represents every base-10 order of magnitude assigned an SI prefix, from `Quecto` (10⁻³⁰) through `Quetta` (10³⁰). `Base` represents the unprefixed magnitude 10⁰.

Each enumeration value is the corresponding base-10 exponent, allowing conversion code to use the value directly when calculating the scale between compatible units:

```cpp
#include <ESPressio_UnitEnums.hpp>

using namespace ESPressio::Units;

UnitOrderOfMagnitude sourceMagnitude = Milli; // 10^-3
UnitOrderOfMagnitude targetMagnitude = Kilo;  // 10^3
```

The complete mapping is:

| Enumeration | SI prefix symbol | Base-10 magnitude |
|---|---:|---:|
| `Quecto` | `q` | 10⁻³⁰ |
| `Ronto` | `r` | 10⁻²⁷ |
| `Yocto` | `y` | 10⁻²⁴ |
| `Zepto` | `z` | 10⁻²¹ |
| `Atto` | `a` | 10⁻¹⁸ |
| `Femto` | `f` | 10⁻¹⁵ |
| `Pico` | `p` | 10⁻¹² |
| `Nano` | `n` | 10⁻⁹ |
| `Micro` | `μ` | 10⁻⁶ |
| `Milli` | `m` | 10⁻³ |
| `Centi` | `c` | 10⁻² |
| `Deci` | `d` | 10⁻¹ |
| `Base` | — | 10⁰ |
| `Deca` | `da` | 10¹ |
| `Hecto` | `h` | 10² |
| `Kilo` | `k` | 10³ |
| `Mega` | `M` | 10⁶ |
| `Giga` | `G` | 10⁹ |
| `Tera` | `T` | 10¹² |
| `Peta` | `P` | 10¹⁵ |
| `Exa` | `E` | 10¹⁸ |
| `Zetta` | `Z` | 10²¹ |
| `Yotta` | `Y` | 10²⁴ |
| `Ronna` | `R` | 10²⁷ |
| `Quetta` | `Q` | 10³⁰ |

`GetUnitOrderOfMagnitudeSymbol()` returns either the official SI prefix symbol or its full name using the shared `UnitRepresentation` selector:

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

`Base` returns an empty string for both representations because it means that no magnitude prefix is present. This allows either representation to be concatenated directly with its corresponding magnitude-free unit context.

## `UnitContext`

`UnitContext` identifies the physical meaning of a value independently of its numeric representation, magnitude, or unit symbol. This distinction matters because different physical quantities can have identical SI dimensions: energy, work, and heat are all expressed coherently in joules, while speed and velocity are both expressed in metres per second, but their contexts are not interchangeable in every API.

The enumeration covers:

- Quantities with the unit one, including ratios and plane and solid angles.
- All seven SI base quantities.
- Spatial and kinematic quantities such as distance, area, volume, velocity, acceleration, and frequency.
- Mechanical quantities such as force, pressure, torque, density, surface tension, and viscosity.
- Energy and thermal quantities such as work, heat, power, temperature, entropy, and thermal conductivity.
- Electrical and magnetic quantities such as charge, potential, resistance, capacitance, magnetic flux, and inductance.
- Photometric quantities such as luminous flux, illuminance, and luminance.
- Digital information quantities such as storage capacity expressed in bytes.
- Chemical quantities such as concentration, molar energy, and catalytic activity.
- Ionizing-radiation quantities such as radioactivity, absorbed dose, kerma, and dose equivalent.

```cpp
#include <ESPressio_UnitEnums.hpp>

using namespace ESPressio::Units;

UnitContext distanceContext = UnitContext::Distance;
UnitContext velocityContext = UnitContext::Velocity;
UnitContext resistanceContext = UnitContext::ElectricResistance;

const char* distanceSymbol = GetUnitContextSymbol(
    distanceContext,
    UnitRepresentation::Symbol
); // "m"

const char* distanceName = GetUnitContextSymbol(
    distanceContext,
    UnitRepresentation::Name
); // "metre"

const char* storageSymbol = GetUnitContextSymbol(
    UnitContext::StorageCapacity,
    UnitRepresentation::Symbol
); // "B"
```

`GetUnitContextSymbol()` returns the requested immutable, magnitude-free representation as a `const char*`. Pass `UnitRepresentation::Symbol` for the abbreviated symbol or `UnitRepresentation::Name` for the singular full unit name. The lookup performs no allocation and deliberately excludes SI prefixes so magnitude formatting can be handled separately. For example, `UnitContext::Mass` maps to `"g"` or `"gram"`; a separate magnitude mapping can therefore format `Base` as `g`/`gram`, `Micro` as `μg`/`microgram`, or `Kilo` as `kg`/`kilogram`.

The scoped enumeration prevents context names such as `Time`, `Distance`, and `Energy` from colliding with specialised unit type names. The SI also permits an unlimited number of derived quantities: `UnitContext::Other` provides an explicit context for a valid specialised quantity not yet represented by a named enumerator, while `UnitContext::Unknown` represents a context that has not been established. Both fallback contexts return an empty symbol because their representation must be supplied by the specialised implementation.

`StorageCapacity` uses decimal SI magnitudes: `Kilo` + `B` represents `kB` (1,000 bytes), while `Mega` + `B` represents `MB` (1,000,000 bytes). Binary IEC prefixes such as `KiB` and `MiB` are not SI magnitudes and are not represented by `UnitOrderOfMagnitude`.

## `Unit<TValue>`

`Unit<TValue, TBaseOrderOfMagnitude, TContext>` is the common value representation from which specialised physical unit types are derived. It pairs a numeric `value` with its current `UnitOrderOfMagnitude` and exposes both its canonical base magnitude and physical context at compile time, without introducing virtual dispatch or dynamic allocation.

`TValue` may be any non-boolean arithmetic type, including signed and unsigned integer types and floating-point types. Attempting to instantiate `Unit<TValue>` with a non-numeric type or `bool` produces a compile-time error.

`TBaseOrderOfMagnitude` defines the canonical magnitude of a specialised unit type at compile time and defaults to `Base`. `TContext` defines its `UnitContext` and defaults to `UnitContext::Unknown`. They are exposed through the static `baseOrderOfMagnitude` and `context` members. Each instance still retains its own `orderOfMagnitude`, allowing a value to be expressed at a different magnitude while preserving knowledge of the type's canonical base.

```cpp
#include <ESPressio_Unit.hpp>

using namespace ESPressio::Units;

Unit<int> distance(25, Centi);          // 25 × 10^-2
Unit<unsigned long> timeout(500, Milli); // 500 × 10^-3
Unit<double> resistance(4.7, Kilo);      // 4.7 × 10^3
Unit<float> baseValue(12.5f);            // 12.5 × 10^0
```

Derived types explicitly select their canonical base magnitude and context through the second and third template arguments:

```cpp
template <typename TValue>
struct Metres : public Unit<TValue, Base, UnitContext::Distance> {
    using Unit<TValue, Base, UnitContext::Distance>::Unit;
};

template <typename TValue>
struct Calories : public Unit<TValue, Kilo, UnitContext::Energy> {
    using Unit<TValue, Kilo, UnitContext::Energy>::Unit;
};

Metres<float> distance(12.5f); // Defaults to Base: metres
Calories<float> energy(2.0f);  // Defaults to Kilo: kilocalories
```

The default constructor value-initialises `value` and assigns the type's declared base magnitude. The explicit value constructor does the same when no instance magnitude is supplied, while preventing a raw number from being converted implicitly into a `Unit<TValue, TBaseOrderOfMagnitude, TContext>`.

The value constructor also accepts an optional instance magnitude which overrides the specialised type's canonical default:

```cpp
Time<unsigned long> seconds(5);          // 5 seconds (Base)
Time<unsigned long> milliseconds(500, Milli); // 500 milliseconds
```

`SetValue()` can subsequently replace either the numeric value alone or both the value and the magnitude it represents:

```cpp
Time<unsigned long> elapsed(5); // 5 seconds

elapsed.SetValue(10);           // 10 seconds; preserves Base
elapsed.SetValue(250, Milli);   // 250 milliseconds
elapsed.SetValue(500);          // 500 milliseconds; preserves Milli
```

Omitting the magnitude from `SetValue()` preserves the instance's current `orderOfMagnitude`. This differs deliberately from construction, where an omitted magnitude uses the specialised type's compile-time `baseOrderOfMagnitude`.

### Specialised Context Types

Every quantifiable `UnitContext` has a correspondingly named templated type and header. Include only the context required by an implementation:

```cpp
#include <ESPressio_Distance.hpp>
#include <ESPressio_Time.hpp>

Distance<float> distance(12.5f);
Time<unsigned long> timeout(500, Milli);
```

Alternatively, include the complete public context catalogue:

```cpp
#include <ESPressio_Units.hpp>

Mass<double> mass(2.5);                    // Defaults to Kilo: kilograms
ElectricResistance<float> resistance(4.7f); // Defaults to Base: ohms
StorageCapacity<unsigned long> size(2, Mega); // Two megabytes
```

The filename and type naming convention is `ESPressio_<Context>.hpp` and `<Context><TValue>`. `UnitContext::Unknown` and `UnitContext::Other` intentionally have no specialised types because neither identifies a concrete physical quantity.

Most specialised types use `Base` as their canonical magnitude. Contexts canonically expressed using kilograms use the following magnitudes relative to the library's magnitude-free gram symbol:

| Canonical magnitude | Specialised context types |
|---|---|
| `Kilo` | `Mass`, `Density`, `MassDensity`, `SurfaceDensity`, `MassConcentration` |
| `Milli` | `SpecificVolume`, `SpecificEnergy`, `SpecificHeatCapacity`, `SpecificEntropy`, `Exposure` |

Inverse-mass contexts use `Milli` because, for example, one joule per kilogram is 10⁻³ joules per gram.

### Magnitude Conversion

`ToMagnitude()` converts the stored value from its current `orderOfMagnitude` to another magnitude. The conversion multiplier is calculated at runtime from the difference between the two base-10 exponents, avoiding the memory cost of a 25 × 25 lookup table.

Calling `ToMagnitude()` without a result template argument returns `double` by default:

```cpp
Unit<int> metres(1, Base);
double decametres = metres.ToMagnitude(Deca); // 0.1

Unit<double> petametres(1.0, Peta);
double femtometres = petametres.ToMagnitude(Femto); // 1.0e30
```

The result type can be selected explicitly when another arithmetic representation is required:

```cpp
double asDouble = metres.ToMagnitude(Deca);
float asFloat = metres.ToMagnitude<float>(Deca);
long double asLongDouble = metres.ToMagnitude<long double>(Deca);
int asInteger = metres.ToMagnitude<int>(Deca);
```

Floating-point results retain the precision supported by the requested type. Integral results use nearest-integer rounding, with halfway values rounded away from zero: `1.4` becomes `1`, `1.5` becomes `2`, and `-1.5` becomes `-2`.

`bool` and non-numeric result types are rejected at compile time. A conversion which exceeds the range of the requested numeric result type throws `std::overflow_error` rather than performing an unsafe or undefined conversion.

### String Representation

`AsString()` returns an Arduino `String` containing the value, its current magnitude, and its context. Symbolic output is used by default, allowing the result to be passed directly to `Serial.println()` or incorporated into an embedded webpage:

```cpp
Time<unsigned long> elapsed(500, Milli);
Serial.println(elapsed.AsString()); // "500 ms"
```

Pass `UnitRepresentation::Name` to use full magnitude and context names:

```cpp
Serial.println(
    elapsed.AsString(UnitRepresentation::Name)
); // "500 millisecond"

Mass<double> mass(2.5); // Mass defaults to Kilo
String displayValue = mass.AsString(
    UnitRepresentation::Name
); // "2.5 kilogram"
```

Full unit names remain singular in accordance with SI unit-name convention. Numeric formatting uses sufficient significant digits to preserve the stored numeric representation without introducing a fixed number of trailing decimal places. Generic units whose context is `UnitContext::Unknown` or `UnitContext::Other` output only their numeric value because those contexts have no defined unit representation.

## Planned Unit Coverage

The initial design will consider the following quantity families:

| Quantity | SI unit | Symbol | Example scaled units |
|---|---|---:|---|
| Time | second | `s` | nanoseconds, microseconds, milliseconds, minutes, hours |
| Length | metre | `m` | millimetres, centimetres, kilometres |
| Mass | kilogram | `kg` | micrograms, milligrams, grams |
| Electric current | ampere | `A` | microamperes, milliamperes |
| Thermodynamic temperature | kelvin | `K` | degrees Celsius |
| Amount of substance | mole | `mol` | millimoles, micromoles |
| Luminous intensity | candela | `cd` | millicandelas |
| Electrical resistance | ohm | `Ω` | milliohms, kiloohms, megaohms |
| Electric potential | volt | `V` | millivolts, kilovolts |
| Power | watt | `W` | milliwatts, kilowatts |
| Frequency | hertz | `Hz` | kilohertz, megahertz, gigahertz |
| Storage capacity | byte | `B` | kilobytes, megabytes, gigabytes |

This list is an initial roadmap rather than a limitation on the eventual library scope.

## Design Goals

ESPressio Units is intended to provide:

- Compile-time distinction between incompatible physical quantities.
- Explicit and predictable conversion between compatible units and scales.
- Arithmetic and comparison operations that preserve dimensional correctness.
- Clear handling of representation range, precision, rounding, and overflow.
- Minimal runtime and memory overhead suitable for resource-constrained devices.
- APIs that remain useful across Arduino, ESP32, and conventional C++ environments.
- Straightforward interoperability with the other ESPressio component libraries.

## Basic Usage

Include a specialised context header, select the numeric representation, and optionally supply an instance magnitude:

```cpp
#include <ESPressio_Distance.hpp>

using namespace ESPressio::Units;

Distance<double> distance(1250.0, Milli);
double metres = distance.ToMagnitude(Base); // 1.25
```

## Tests

The host-based test suite applies the same behavioral contract to every specialised context type. Each of the 83 types receives 16 positive and 10 negative checks covering construction, compile-time metadata, setters, magnitude conversion, numeric result types, rounding, overflow handling, negative values, and both string representations. Additional checks cover every SI magnitude prefix and the fallback contexts.

Run the suite with CMake and CTest:

```sh
cmake -S tests -B build/tests
cmake --build build/tests
ctest --test-dir build/tests --output-on-failure
```

Optional coverage and sanitizer instrumentation can be enabled during configuration:

```sh
cmake -S tests -B build/tests \
    -DESPRESSIO_ENABLE_COVERAGE=ON \
    -DESPRESSIO_ENABLE_SANITIZERS=ON
```

The tests use a minimal host-side Arduino `String` stub and require no embedded hardware or external test framework.

## Development Status

This repository is in its initial scaffolding phase. Planned next steps include defining:

1. The common quantity and unit type model.
2. Numeric representation and conversion policies.
3. Time types and their supported scales.
4. Dimensional arithmetic and comparison rules.
5. Remaining SI base and derived quantity families.
6. Host-based tests covering conversions, boundaries, precision, and invalid operations.

Contributions and design discussion are welcome while these contracts are being established.
