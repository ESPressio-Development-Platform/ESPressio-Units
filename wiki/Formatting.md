# Formatting

Units can be formatted for diagnostics and Arduino-facing output by composing the numeric value, SI magnitude prefix, and context unit.

`UnitRepresentation::Symbol` selects compact symbolic output, while `UnitRepresentation::Name` selects human-readable names.

Conceptually:

```text
value + magnitude + context
12.5 + milli + metre
12.5 mm
```

## Separation of metadata

Magnitude metadata and context metadata remain separate. This allows the same context symbol/name to be reused correctly across all supported SI prefixes.

## Embedded cost

Formatting introduces code and temporary-string cost that pure typed arithmetic does not. On small targets, measure flash/RAM impact and avoid formatting in hot paths unless needed.