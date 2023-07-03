# Toybox
Toybox is a personal game engine project which act as a playground to learn and test concept for game engine.
This project is not intended to be a usable engine in any way.

# Coding style
## Typedef Primitives
Toybox redefine primitive names to shorter version and uses them throughout the codebase.
For example: `float` is redefined as `f32` and `long long` as `i64`. Integer primitives are redefined from the `stdint.h` library to ensure constant size. The reasoning is that short name such as `i64` are easier to read than `int64_t`. `types.h` imports `stdint.h` and `stdbool.h` therefor all types names are available but Toybox codebase will use the shorter names. 