# Specialised Quantity Types

Most application code should use strongly named quantity types rather than raw `Unit`.

```cpp
#include <ESPressio_Distance.hpp>
#include <ESPressio_Time.hpp>

using namespace ESPressio::Units;

Distance<float> distance(12.5f);
Time<unsigned long> timeout(500, Milli);
```

The full catalogue is available through:

```cpp
#include <ESPressio_Units.hpp>
```

Examples include `Mass`, `Velocity`, `Acceleration`, `Force`, `Pressure`, `Energy`, `Power`, `ElectricResistance`, `StorageCapacity`, and many others.

## Why specialised types

A specialised type fixes the physical context and canonical base magnitude at compile time, improving readability and dimensional safety while retaining the generic conversion/formula machinery.

## Generic Unit

The underlying pattern is:

```cpp
template <typename TValue>
struct Metres : public Unit<TValue, Base, UnitContext::Distance> {
    using Unit<TValue, Base, UnitContext::Distance>::Unit;
};
```

Consumers normally do not need to define this themselves unless extending the library.