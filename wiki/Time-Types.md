# Time Types

Time is particularly common in embedded APIs, so ESPressio Units provides aliases whose type names carry the magnitude:

```cpp
Seconds<unsigned long> interval(5);
MilliSeconds<unsigned long> timeout(500);
MicroSeconds<unsigned long> sampleTime(250);
NanoSeconds<uint64_t> timestamp(123456789ULL);
```

`Time<TValue>` remains the base-seconds compatible form.

## API design

Prefer:

```cpp
void SetTimeout(MilliSeconds<uint64_t> timeout);
```

over a raw numeric parameter whose unit exists only in a comment.

## Current magnitude

`SetValue()` without an explicit magnitude preserves the instance's current magnitude:

```cpp
Time<unsigned long> elapsed(5); // seconds
elapsed.SetValue(250, Milli);   // milliseconds
elapsed.SetValue(500);          // still milliseconds
```

This lets a value retain its chosen representation while remaining a strongly typed Time quantity.