# Adding Formula Relationships

Formula helpers should encode a real dimensional relationship between supported quantity types.

## Requirements

A new formula must:

- accept only dimensionally appropriate operand types;
- normalize operand magnitudes correctly;
- choose a clear result context/type;
- preserve numeric range/precision semantics;
- reject invalid operand categories at compile time;
- include tests across representative magnitudes and numeric representations.

## Context versus dimension

When multiple contexts share the same SI dimension, select the result context according to the semantic relationship being represented rather than mechanically treating every dimensionally equivalent context as identical.

## Avoid raw escape hatches

Do not implement a formula by extracting raw numbers and returning another Unit if the template/type system can express the constraints directly. The purpose of the formula layer is to retain dimensional correctness throughout the operation.