---
type: concept
chapter: 3
tags: [chapter/3, topic/io, kind/concept]
related: ["[[Conversion specification]]", "[[Left and right justification]]"]
---

# Field width and precision

In a [[Conversion specification]] like `%W.Pf`:

- **W (width)** — *minimum* total characters. If the value is shorter, it's padded with spaces. If longer, the field is **expanded**, never truncated (numbers are never silently chopped).
- **P (precision)** — meaning depends on the conversion:
  - `%d` (int) → minimum number of digits (zero-padded if needed)
  - `%f` (fixed float) → digits after the decimal point
  - `%e` (exp float) → digits after the decimal point
  - `%g` (general float) → maximum significant digits
  - `%s` (string) → maximum chars to print

## Worked

```c
printf("|%5.3d|", 50);     // |  050|   width 5, ≥3 digits → "050" padded
printf("|%10.3f|", 839.21f); // |   839.210|
printf("|%10.3e|", 839.21f); // | 8.392e+02|
```

## See also

- [[Left and right justification]] — controls *which side* gets the padding
