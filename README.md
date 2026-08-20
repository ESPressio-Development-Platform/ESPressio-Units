# ESPressio Units

Strongly typed SI unit and physical-quantity components for the
Flowduino ESPressio Development Platform.

## Latest Stable Version

**0.2.1**

## ESPressio Development Platform

ESPressio is a collection of discrete, composable component libraries
built around a common development ethos:

-   **Light-weight** --- minimise memory consumption and runtime
    overhead without sacrificing correctness.
-   **Ease of use** --- provide strongly typed, developer-friendly
    abstractions over lower-level facilities.
-   **Object-oriented** --- a type for everything, and everything in a
    type.
-   **SOLID** --- favour focused responsibilities, extensibility,
    substitutable abstractions, narrow interfaces, and dependency
    inversion wherever practical on embedded C++ platforms.

## License

Licensed under the **Apache License 2.0**. See [LICENSE](LICENSE).

## ESPressio Library Dependencies

ESPressio is designed as a modular ecosystem of independently useful
libraries, with required dependencies kept explicit and optional
integrations introduced only when the corresponding functionality is
selected.

For a complete overview of required dependencies, opt-in dependencies,
and the overall hierarchy, see:

**[ESPressio Library Dependency Chart](ESPRESSIO_DEPENDENCY_CHART.md)**

-   **Solid relationships** represent required ESPressio dependencies.
-   **Dashed relationships** represent opt-in dependencies introduced
    only by the corresponding feature, integration, type, or header.

### Required ESPressio dependencies

None.

### Optional: ESPressio Serializable

Ordinary Unit types do **not** require Serializable. Serializable
counterparts are exposed through separate `*_Serializable.hpp` headers
and `ESPressio_SerializableUnits.hpp`; only applications selecting those
types acquire the dependency.

Serializable Unit variants target **ESPressio Serializable >= 0.10.0 < 1.0.0**,
allowing compatible later 0.x minor and patch releases while preventing an
automatic transition to a future 1.x breaking release.

## PlatformIO

Core Units usage:

```ini
lib_deps =
    https://github.com/flowduino/ESPressio-Units@^0.2.1
```

When using the optional Serializable Unit variants:

```ini
lib_deps =
    https://github.com/flowduino/ESPressio-Units@^0.2.1
    https://github.com/flowduino/ESPressio-Serializable@^0.10.0
```

## Namespace

``` cpp
ESPressio::Units
```

## Core model

`Unit<TValue, TBaseOrderOfMagnitude, TContext>` pairs an arithmetic
value with a compile-time canonical SI magnitude, a physical context,
and an instance magnitude. It provides explicit checked conversions
without virtual dispatch.

``` cpp
#include <ESPressio_Time.hpp>

using namespace ESPressio::Units;

Seconds<unsigned long> interval(5);
MilliSeconds<unsigned long> timeout(500);
MicroSeconds<unsigned long> sample(250);
```

`UnitOrderOfMagnitude` covers the SI prefix range from quecto through
quetta, with `Base` representing 10\^0.

## Physical contexts

`UnitContext` describes physical meaning independently of numeric
representation and magnitude. Specialised types cover time, distance,
mass, velocity, acceleration, force, pressure, energy, power, frequency,
electrical and magnetic quantities, photometric quantities, storage,
chemical quantities, radiation quantities, and the other contexts
represented by the library.

Include only what is required:

``` cpp
#include <ESPressio_Distance.hpp>
#include <ESPressio_Time.hpp>
```

or the full catalogue:

``` cpp
#include <ESPressio_Units.hpp>
```

## Magnitude conversion

``` cpp
Distance<double> distance(1250.0, Milli);
double metres = distance.ToMagnitude(Base);
```

Checked conversions protect finite/range behaviour. Explicit unchecked
paths remain available when the caller has already established numeric
safety.

## Strongly typed formulas

``` cpp
Distance<double> distance(100.0, Base);
MilliSeconds<unsigned long> elapsed(500);

Velocity<double> velocity =
    Velocity<double>::From(distance, elapsed);
```

Dimensionally invalid operands are rejected at compile time.

## Formatting

`AsString()` supports symbolic and full-name representations suitable
for Arduino output.

## Serializable Unit variants

Version 0.2.0 preserves ordinary types while adding opt-in Serializable
siblings:

``` text
ordinary Unit
    -> Units only

Serializable Unit
    -> Units
    -> Serializable
```

This is particularly important to Timing: Timing can use either ordinary
or Serializable time types without making Serializable mandatory.

## Design goals

-   Compile-time distinction between incompatible quantities.
-   Explicit predictable conversion.
-   Dimensional correctness.
-   Defined range/rounding behaviour.
-   Minimal runtime overhead.
-   Portable use on suitable Arduino/C++ targets.
-   Clean interoperability with the ESPressio ecosystem.

## Tests and generated reference

The repository's host tests and generated conversion catalogue remain
the authoritative exhaustive reference:

``` text
docs/UNIT_CONVERSIONS.md
tools/generate_conversion_assets.py
```
