---
type: concept
chapter: 3
tags: [chapter/3, topic/io, kind/concept, specifier]
related: ["[[printf]]", "[[scanf]]", "[[Conversion specification]]"]
---

# Format specifier — `%d`

Displays an integer in decimal (base 10).

- **printf**: prints an `int` in decimal.
- **scanf**: reads an `int` in decimal.

## Width & precision

- `%Nd` → minimum N characters wide (space-padded)
- `%.Pd` → minimum P digits (zero-padded)
- `%N.Pd` → both: at least N wide, at least P digits

## Examples

```c
int i = 50;
printf("|%d|",   i);   // |50|
printf("|%5d|",  i);   // |   50|
printf("|%-5d|", i);   // |50   |
printf("|%5.3d|",i);   // |  050|
```

## Related specifiers

- `%i` — same as `%d` in printf; in scanf accepts decimal/octal/hex
- `%u` — unsigned decimal
- `%o` — octal
- `%x`, `%X` — hex (lower/upper)
- `%ld`, `%lld` — long, long long
