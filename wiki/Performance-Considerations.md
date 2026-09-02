# Performance Considerations

The core Unit model uses templates and compile-time physical context rather than virtual dispatch.

Runtime arithmetic and conversion are therefore lightweight, but template instantiation, formatting helpers, broad catalogue inclusion, and floating-point support can affect flash/RAM on very small targets.

## Practical guidance

- include only the context headers you need when code-size pressure matters;
- avoid formatting in hot paths unless required;
- choose numeric types appropriate to range and precision needs;
- use checked conversion at boundaries, but avoid redundant conversion churn internally;
- measure the target binary rather than assuming desktop compilation cost reflects embedded cost.

## Serialization

Do not include Serializable Unit variants unless serialized representation is actually needed. The optional dependency boundary exists specifically to prevent every Unit consumer from paying that cost.