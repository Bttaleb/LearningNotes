---
type: concept
chapter: 3
tags: [chapter/3, topic/io, kind/concept, specifier]
related: ["[[Format specifier - e (exponential float)]]", "[[Format specifier - g (general float)]]"]
---

# Format specifier — `%f`

Displays a floating-point number in **fixed decimal** form (no exponent).

- Precision = digits after the decimal point. Default is 6.

## Examples

```c
float x = 839.21f;
printf("|%f|",     x);   // |839.210000|
printf("|%.3f|",   x);   // |839.210|
printf("|%10.3f|", x);   // |   839.210|
printf("|%-10.3f|",x);   // |839.210   |
```

## See also

- [[Format specifier - e (exponential float)]] — same data, scientific notation
- [[Format specifier - g (general float)]] — picks `%f` or `%e` automatically
