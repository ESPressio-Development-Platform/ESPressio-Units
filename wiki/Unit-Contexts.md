# Unit Contexts

`UnitContext` represents physical meaning independently from numeric representation and SI prefix.

This distinction matters because quantities can share dimensions or coherent SI units while still expressing different application contracts. Work, heat, and energy may all be measured in joules without necessarily being interchangeable in every API.

The library covers dimensionless quantities and angles; the seven SI base quantities; distance, area, volume, velocity and acceleration; mechanical, thermal, electrical, magnetic, photometric, chemical, storage, and radiation quantities.

## Symbols and names

```cpp
const char* symbol = GetUnitContextSymbol(
    UnitContext::Distance,
    UnitRepresentation::Symbol
); // "m"

const char* name = GetUnitContextSymbol(
    UnitContext::Distance,
    UnitRepresentation::Name
); // "metre"
```

Context symbols are magnitude-free so formatting can compose them with the selected SI prefix.

## Storage capacity

`StorageCapacity` uses decimal SI magnitudes (`kB`, `MB`, and so on). IEC binary prefixes such as KiB/MiB are not represented by `UnitOrderOfMagnitude`.