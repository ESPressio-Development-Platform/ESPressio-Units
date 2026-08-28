# Testing Unit Extensions

Unit tests should protect both numeric behaviour and compile-time dimensional behaviour.

## Construction and representation

Test canonical/default magnitude, explicit magnitude, `SetValue()` magnitude retention, formatting names/symbols, and numeric-type constraints.

## Conversion

Exercise representative source/target magnitude combinations, signed/unsigned/floating types, finite/range boundaries, and checked failure behaviour.

## Compile-time safety

Add negative compile-time assertions/fixtures where practical so dimensionally invalid relationships cannot accidentally become accepted.

## Formulas

Test each formula across multiple compatible magnitudes and verify both numeric result and result context/type.

## Serializable variants

When present, test round trips, schema behaviour, aggregate-member construction, and standard-container use independently of the ordinary Unit tests.

## Generated assets

Regenerate and review the exhaustive conversion reference whenever the supported matrix changes.