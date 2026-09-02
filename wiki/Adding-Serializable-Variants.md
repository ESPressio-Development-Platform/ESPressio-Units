# Adding Serializable Variants

Serializable Unit variants layer ESPressio Serializable behaviour over an already-defined Unit type without making serialization mandatory for ordinary consumers.

## Rules

1. Complete and test the ordinary Unit type first.
2. Place Serializable support in the corresponding separate `*_Serializable.hpp` surface.
3. Preserve ordinary value construction/copy/move/container semantics.
4. Register/describe only stable fields needed to reconstruct the quantity faithfully.
5. Expose the type through `ESPressio_SerializableUnits.hpp` where appropriate.
6. Test aggregate-member and standard-container composition.

## Dependency direction

The optional Serializable type may depend on ESPressio Serializable. The ordinary Unit type must not depend back on it.

## Compatibility

Serialized representation is a schema contract. Changes to field names/types or magnitude/context interpretation require the same migration/compatibility discipline as any other Serializable schema.