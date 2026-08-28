# Adding a Unit Context

Add a new `UnitContext` when the library needs to represent a distinct physical/application meaning that is not already modelled accurately.

## Steps

1. Add the new context enumeration value.
2. Define its canonical symbol and human-readable name metadata.
3. Confirm the coherent SI unit and canonical base magnitude.
4. Add or update the specialised quantity header/type.
5. Add conversion/reference generation inputs where applicable.
6. Add formula relationships only when dimensionally valid.
7. Add exhaustive tests for construction, conversion, formatting, and invalid cross-context use.
8. Add a Serializable counterpart only if required; keep it optional.

## Context identity

Do not merge conceptually different quantities solely because their SI dimensions coincide. The type system is intended to communicate semantic contracts as well as dimensional arithmetic.

## Metadata stability

Symbols and names become part of formatting, generated references, and potentially serialized/user-visible output. Treat them as stable API vocabulary.