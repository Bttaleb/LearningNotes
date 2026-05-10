---
type: snippet
tags: [topic/io, kind/snippet, reference]
related: ["[[printf]]", "[[scanf]]", "[[Conversion specification]]"]
---

# printf / scanf — Reference Card

## Anatomy
```
%[flags][width][.precision][length]conversion
```

## Common conversions

| Spec | Type | Notes |
|------|------|-------|
| `%d` `%i` | `int` | decimal |
| `%u` | `unsigned` | decimal |
| `%o` | `unsigned` | octal |
| `%x` `%X` | `unsigned` | hex (lower / upper) |
| `%f` | `double` | fixed decimal |
| `%e` `%E` | `double` | scientific |
| `%g` `%G` | `double` | smart picks `%f` or `%e`, strips trailing 0s |
| `%c` | `int` (char) | single char |
| `%s` | `char *` | null-terminated string |
| `%p` | `void *` | pointer (impl-defined) |
| `%%` | — | literal `%` |

## Length modifiers (printf)

| Modifier | With `d/i/o/u/x` | With `f/e/g` |
|----------|------------------|--------------|
| `h` | `short` | — |
| `hh` | `signed/unsigned char` | — |
| `l` | `long` | — |
| `ll` | `long long` | — |
| `L` | — | `long double` |
| `z` | `size_t` | — |

## Flags

| Flag | Effect |
|------|--------|
| `-` | left-justify |
| `+` | always show sign |
| `␣` (space) | space before positive |
| `0` | zero-pad numbers |
| `#` | alternate form (`0x` for hex, etc.) |

## scanf-only quirks
- Pointer args required: `scanf("%d", &n);`
- Numeric specs skip whitespace; `%c` does **not** (use `" %c"`).
- See [[scanf newline behavior]].
