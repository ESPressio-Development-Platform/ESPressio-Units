# Generated Conversion Assets

The repository maintains generated conversion reference material so the supported Unit/magnitude matrix can be audited exhaustively rather than inferred from a handful of examples.

The current source tree includes:

```text
docs/UNIT_CONVERSIONS.md
tools/generate_conversion_assets.py
```

## Extension workflow

When adding or changing contexts, magnitudes, aliases, or conversion behaviour:

1. update the authoritative source definitions;
2. update the generator inputs/logic if required;
3. regenerate the conversion assets;
4. review the generated diff for unexpected relationships;
5. run the host test suite;
6. commit generated output together with the source change where repository policy requires it.

## Why generated reference matters

Unit conversion has a combinatorial surface. Generated documentation and exhaustive tests catch omissions and asymmetric conversions more reliably than manually maintained tables.