---
type: concept
chapter: 3
tags: [chapter/3, topic/io, kind/concept, specifier]
related: ["[[Format specifier - f (fixed decimal float)]]", "[[Format specifier - g (general float)]]"]
---

# Format specifier — `%e`

Displays a floating-point number in **exponential** (scientific) form.

- Output looks like `m.ddde±xx` — one digit before the decimal, then precision digits after, then `e±` and at least 2 exponent digits.
- Precision = digits after the decimal point. Default is 6.

## Examples

```c
float x = 839.21f;
printf("|%e|",     x);   // |8.392100e+02|
printf("|%.3e|",   x);   // |8.392e+02|
printf("|%10.3e|", x);   // | 8.392e+02|
```

## When to use

- Very large or very small numbers — fixed notation gets unreadable.
- Scientific output where magnitude matters more than absolute value.

## See also

- [[Format specifier - f (fixed decimal float)]]
- [[Format specifier - g (general float)]]
