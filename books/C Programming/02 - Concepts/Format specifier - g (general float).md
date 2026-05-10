---
type: concept
chapter: 3
tags: [chapter/3, topic/io, kind/concept, specifier]
related: ["[[Format specifier - f (fixed decimal float)]]", "[[Format specifier - e (exponential float)]]"]
---

# Format specifier — `%g`

The "smart" floating-point specifier: picks **either** `%f` or `%e` based on the value's magnitude.

- Precision = **maximum significant digits** (default 6) — *not* digits after the decimal.
- Trailing zeros are **stripped** (unlike `%f`).
- Uses `%e` when the exponent is `< -4` or `≥ precision`; otherwise `%f`.

## Examples

```c
printf("|%g|",  839.21);        // |839.21|     ← fixed form
printf("|%g|",  0.0000009979);  // |9.979e-07|  ← exponential form
printf("|%-10.2g|", 0.0000009979); // |1e-06     |  ← 2 sig figs, left-justified
```

## Use when

- You don't know the magnitude in advance and want readable output either way.
- You want trailing zeros suppressed.

## See also

- [[Format specifier - f (fixed decimal float)]]
- [[Format specifier - e (exponential float)]]
