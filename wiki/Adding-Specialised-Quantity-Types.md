# Adding Specialised Quantity Types

A specialised quantity type binds the generic `Unit` template to a physical context and canonical magnitude.

Typical pattern:

```cpp
template <typename TValue>
struct MyQuantity : public Unit<
    TValue,
    Base,
    UnitContext::MyContext
> {
    using Unit<
        TValue,
        Base,
        UnitContext::MyContext
    >::Unit;
};
```

## Requirements

Choose the canonical magnitude deliberately, inherit the existing constructors/value semantics, follow the repository's header/type naming convention, and expose the type through the appropriate catalogue umbrella when complete.

## Numeric type

`TValue` remains a non-boolean arithmetic type. Do not introduce a specialised quantity whose representation bypasses the generic Unit safety rules.

## Aliases

Magnitude-specific aliases are useful where the magnitude itself is central to API readability, as with `MilliSeconds` and `MicroSeconds`. Add them selectively rather than producing unnecessary alias proliferation.