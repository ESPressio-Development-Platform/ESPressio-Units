# Orders of Magnitude

`UnitOrderOfMagnitude` represents decimal SI prefixes from quecto (10^-30) through quetta (10^30). `Base` represents 10^0.

Common embedded magnitudes include:

| Enumeration | Symbol | Magnitude |
| --- | ---: | ---: |
| `Nano` | n | 10^-9 |
| `Micro` | μ | 10^-6 |
| `Milli` | m | 10^-3 |
| `Base` | — | 10^0 |
| `Kilo` | k | 10^3 |
| `Mega` | M | 10^6 |
| `Giga` | G | 10^9 |

The full enum covers all current SI decimal prefixes.

## Representation

Magnitude names and symbols can be requested through `UnitRepresentation`:

```cpp
const char* microSymbol = GetUnitOrderOfMagnitudeSymbol(
    Micro,
    UnitRepresentation::Symbol
);

const char* microName = GetUnitOrderOfMagnitudeSymbol(
    Micro,
    UnitRepresentation::Name
);
```

`Base` intentionally contributes no prefix string.