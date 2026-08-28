# Getting Started

Include the full catalogue:

```cpp
#include <ESPressio_Units.hpp>
```

or include only the contexts you need:

```cpp
#include <ESPressio_Distance.hpp>
#include <ESPressio_Time.hpp>
```

Use strong quantity types rather than raw numeric values when a physical meaning exists:

```cpp
using namespace ESPressio::Units;

MilliSeconds<uint64_t> timeout(500);
Distance<float> distance(12.5f);
```

A typed API communicates its unit contract directly:

```cpp
void SetTimeout(MilliSeconds<uint64_t> timeout);
```

## Core concepts

A Unit combines an arithmetic value, a physical `UnitContext`, an SI order of magnitude, and a compile-time canonical base magnitude.

Most consumers should use specialised quantity types rather than the raw generic `Unit` template.

## Next steps

- [Unit Contexts](Unit-Contexts)
- [Orders of Magnitude](Orders-of-Magnitude)
- [Conversion](Conversion)
- [Strongly Typed Formulas](Strongly-Typed-Formulas)