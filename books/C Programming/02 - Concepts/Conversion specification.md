---
type: concept
chapter: 3
tags: [chapter/3, topic/io, kind/concept]
related: ["[[Format string]]", "[[Field width and precision]]", "[[Left and right justification]]"]
---

# Conversion specification

A `%`-prefixed token inside a [[Format string]] that controls how one argument is formatted.

## Anatomy

```
%[flags][width][.precision][length]conversion
```

| Part | Example | Meaning |
|------|---------|---------|
| flag | `-` | left-justify (see [[Left and right justification]]) |
| width | `5` | minimum total characters (see [[Field width and precision]]) |
| .precision | `.3` | digits after decimal / max chars / min digits (depends on type) |
| length | `l`, `ll`, `h` | size modifier (e.g. `%ld` for `long`) |
| conversion | `d`, `f`, `e`, `g`, `s`, `c`, `x` | the actual type |

## Examples decoded

- `%d` — decimal int, default width
- `%5d` — decimal int, min 5 chars wide, right-justified
- `%-5d` — same, left-justified
- `%5.3d` — at least 5 chars total, at least 3 digits (zero-padded)
- `%10.3f` — float, 10 wide, 3 after decimal
- `%-10g` — general float, 10 wide, left-justified

## See also

- Per-conversion notes: [[Format specifier - d (decimal integer)]] · [[Format specifier - f (fixed decimal float)]] · [[Format specifier - e (exponential float)]] · [[Format specifier - g (general float)]]
