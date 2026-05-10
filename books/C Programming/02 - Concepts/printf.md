---
type: concept
chapter: 3
tags: [chapter/3, topic/io, kind/concept, status/learning]
related: ["[[scanf]]", "[[Format string]]", "[[Conversion specification]]"]
---

# printf

Writes formatted output to stdout. Declared in `<stdio.h>`.

```c
printf(format_string, arg1, arg2, ...);
```

The first argument is a [[Format string]]. Every [[Conversion specification]] in it is replaced by the corresponding argument, formatted accordingly.

## Mental model

Think of `printf` as a tiny templating engine: literal text is copied through verbatim; `%`-specs get replaced by the next argument.

## Minimal example

```c
int n = 42;
printf("n = %d\n", n);   // prints: n = 42
```

## Watch out

- The number and types of arguments must match the format string. The compiler can warn (`-Wformat`) but won't always catch it.
- `\n` is not automatic — flushes happen on newline for line-buffered stdout.

## See also

- [[scanf]] — the input counterpart
- [[Format specifier - d (decimal integer)]], [[Format specifier - f (fixed decimal float)]], [[Format specifier - e (exponential float)]], [[Format specifier - g (general float)]]
- [[printf format reference card]] — quick lookup
