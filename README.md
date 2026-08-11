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

The concrete public type catalogue will be documented here as the API is introduced.

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

The public API is still being designed. Concrete examples will be added here once the first unit types and their conversion and arithmetic contracts have been implemented.

## Development Status

This repository is in its initial scaffolding phase. Planned next steps include defining:

1. The common quantity and unit type model.
2. Numeric representation and conversion policies.
3. Time types and their supported scales.
4. Dimensional arithmetic and comparison rules.
5. Remaining SI base and derived quantity families.
6. Host-based tests covering conversions, boundaries, precision, and invalid operations.

Contributions and design discussion are welcome while these contracts are being established.
