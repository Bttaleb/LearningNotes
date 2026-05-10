---
type: concept
chapter: 3
tags: [chapter/3, topic/io, kind/concept, status/learning]
related: ["[[printf]]", "[[Format string]]", "[[scanf newline behavior]]"]
---

# scanf

Reads formatted input from stdin and stores results into the variables you point at. Declared in `<stdio.h>`.

```c
scanf(format_string, &var1, &var2, ...);
```

Every argument after the format string must be a **pointer** — `scanf` writes through it. Forgetting the `&` is the classic beginner bug.

## Example

```c
int i, j;
float x, y;
scanf("%d%d%f%f", &i, &j, &x, &y);
```

Input `1 -20 .3 -4.0e3` produces `i=1, j=-20, x=0.3, y=-4000.0`.

## Whitespace handling

- Most numeric specifiers (`%d`, `%f`, etc.) **skip leading whitespace** automatically — including spaces, tabs, and newlines.
- `%c` does **not** skip whitespace. Add a leading space (`" %c"`) if you want it to.

## Gotcha

[[scanf newline behavior]] — scanf "peeks" at the trailing newline without consuming it, so the next call sees it first.

## See also

- [[printf]]
- [[Conversion specification]]
