# Strongly Typed Formulas

Formula helpers preserve dimensional meaning across calculations.

```cpp
Distance<double> distance(100.0, Base);
MilliSeconds<unsigned long> elapsed(500);

Velocity<double> velocity =
    Velocity<double>::From(distance, elapsed);
```

The formula normalizes compatible operand magnitudes as required while preserving the target physical context.

## Compile-time safety

Dimensionally invalid operands are rejected at compile time rather than becoming incorrect runtime arithmetic.

## Design guidance

Use the library's typed formulas when a relationship is part of the supported physical model. Avoid extracting raw numeric values solely to perform arithmetic that the type system can express safely.

Extension developers adding relationships should continue with [Adding Formula Relationships](Adding-Formula-Relationships).