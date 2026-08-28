# Conversion

Compatible quantities can be converted explicitly between SI magnitudes.

```cpp
Distance<double> distance(1250.0, Milli);
double metres = distance.ToMagnitude(Base);
```

## Checked conversion

The normal conversion path protects finite/range behaviour so narrowing or invalid numeric results are not silently accepted.

Explicit unchecked facilities remain available for code that has already established numeric safety, but checked conversion should be the default for API boundaries and externally sourced values.

## Canonical magnitude

Each specialised type has a compile-time canonical base magnitude while each instance can retain its current representation magnitude. Conversion changes representation without changing the physical quantity.

## Exhaustive reference

The repository generates an exhaustive conversion reference from the same supported magnitude/context model. Extension developers should keep generated assets in step with any new conversion-capable types; see [Generated Conversion Assets](Generated-Conversion-Assets).