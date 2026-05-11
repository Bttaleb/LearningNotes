---
type: chapter
chapter: 3
title: Formatted Input/Output
book: K.N. King — C Programming, A Modern Approach
tags: [chapter/3, topic/io, status/learning]
related: ["[[Ch02 - C Fundamentals]]", "[[Ch07 - Basic Types]]", "[[Ch22 - Input-Output]]"]
---

# Chapter 3 — Formatted Input/Output

> Each `##` heading below is a deep-link target. From any other note write `[[Ch03 - Formatted Input-Output#printf]]` to jump straight here. Add new terms to [[Glossary]] as you encounter them again later.

## TL;DR

C's two main I/O functions are [[#printf]] and [[#scanf]]. Both take a [[#Format strings|format string]] whose `%`-tokens are [[#Anatomy of a conversion specification|conversion specifications]]. The same machinery formats integers (`%d`), floats in three flavors (`%f`/`%e`/`%g`), and more — controlled by [[#Field width and precision|width/precision]] and [[#Justification|justification]] flags. Watch out for the [[#scanf gotcha — the trailing newline|scanf newline gotcha]].

---

## printf

Writes formatted output to stdout. From `<stdio.h>`.

```c
printf(format_string, arg1, arg2, ...);
```

Literal text is copied through; each `%`-spec is replaced by the next argument, formatted accordingly. Argument count and types must match the format string (`-Wformat` will warn).

## scanf

Reads formatted input from stdin into the variables you point at. From `<stdio.h>`.

```c
scanf(format_string, &var1, &var2, ...);
```

Every argument after the format string must be a **pointer** — `scanf` writes through it. Forgetting `&` is the classic beginner bug.

```c
int i, j;
float x, y;
scanf("%d%d%f%f", &i, &j, &x, &y);
// input:  1 -20 .3 -4.0e3
// result: i=1, j=-20, x=0.3, y=-4000.0
```

Numeric specs (`%d`, `%f`, `%i`, `%u`, `%x`) skip leading whitespace automatically. `%c` does **not** — see the gotcha below.

---

## Format strings

The first argument to [[#printf]] / [[#scanf]] — a mix of:

1. **Literal text** — copied verbatim.
2. **Conversion specifications** — `%`-prefixed tokens that consume one argument each.

```c
printf("Hello %s, you are %d years old\n", name, age);
//      ─────  ──   ──────────────  ──
//       lit  spec      lit         spec
```

## Anatomy of a conversion specification

```
%[flags][width][.precision][length]conversion
```

| Part | Example | Meaning |
|------|---------|---------|
| flag | `-` | left-justify (see [[#Justification]]) |
| width | `5` | minimum total characters (see [[#Field width and precision]]) |
| `.precision` | `.3` | digits after decimal / max chars / min digits — depends on type |
| length | `l`, `ll`, `h`, `z` | size modifier (e.g. `%ld` for `long`) |
| conversion | `d`, `f`, `e`, `g`, `s`, `c`, `x` | the actual type |

## Field width and precision

In `%W.Pf`:
- **W (width)** — *minimum* total characters. Shorter values are space-padded; longer values **expand the field** (numbers are never truncated).
- **P (precision)** — meaning depends on the conversion:
  - `%d` → minimum digits (zero-padded)
  - `%f` / `%e` → digits after the decimal point
  - `%g` → maximum significant digits
  - `%s` → max chars to print

```c
printf("|%5.3d|", 50);       // |  050|
printf("|%10.3f|", 839.21f); // |   839.210|
printf("|%10.3e|", 839.21f); // | 8.392e+02|
```

## Justification

The `-` flag flips alignment.

| Spec | Output for `50` | Justification |
|------|-----------------|---------------|
| `%5d`  | `␣␣␣50` | right (default) |
| `%-5d` | `50␣␣␣` | left |

Padding is spaces. Use `0` for zero-padding numbers (`%05d` → `00050`). Mnemonic: `-` "pulls the value to the left."

---

## The four numeric specifiers

### `%d` — decimal integer

For `int`. `%Nd` = min N chars wide; `%.Pd` = min P digits zero-padded.

```c
int i = 50;
printf("|%d|",   i);   // |50|
printf("|%5d|",  i);   // |   50|
printf("|%-5d|", i);   // |50   |
printf("|%5.3d|",i);   // |  050|
```

Related: `%i` (same in printf), `%u` (unsigned), `%o` (octal), `%x`/`%X` (hex), `%ld`/`%lld` (long, long long).

### `%f` — fixed decimal float

For `double`. Precision = digits after the decimal. Default precision is 6.

```c
float x = 839.21f;
printf("|%f|",      x);   // |839.210000|
printf("|%.3f|",    x);   // |839.210|
printf("|%10.3f|",  x);   // |   839.210|
printf("|%-10.3f|", x);   // |839.210   |
```

### `%e` — exponential float

Output looks like `m.ddde±xx`. Precision = digits after the decimal. Default 6.

```c
float x = 839.21f;
printf("|%e|",     x);   // |8.392100e+02|
printf("|%.3e|",   x);   // |8.392e+02|
printf("|%10.3e|", x);   // | 8.392e+02|
```

Use when magnitude varies wildly.

### `%g` — general float (smart)

Picks `%f` or `%e` based on the value:
- Uses `%e` when the exponent is `< -4` or `≥ precision`; otherwise `%f`.
- Precision = **maximum significant digits** (default 6) — *not* digits after the decimal.
- **Strips trailing zeros** (unlike `%f`).

```c
printf("|%g|", 839.21);          // |839.21|     ← fixed form
printf("|%g|", 0.0000009979);    // |9.979e-07|  ← exponential
printf("|%-10.2g|", 0.0000009979); // |1e-06     |
```

Use when you don't know the magnitude in advance.

---

## Worked example (the canonical one from the book)

```c
int   i = 50;
float x = 839.21f;

printf("|%d|%5d|%-5d|%5.3d|\n", i, i, i, i);
printf("|%10.3f|%10.3e|%-10g|\n", x, x, x);
```

```
|50|   50|50   |  050|
|   839.210| 8.392e+02|839.21    |
```

Read each spec out loud:
- `%d` → "decimal, minimum width" → `50`
- `%5d` → "decimal, min 5 chars, right-justified" → `␣␣␣50`
- `%-5d` → "decimal, min 5 chars, left-justified" → `50␣␣␣`
- `%5.3d` → "decimal, 5 wide, ≥3 digits" → `␣␣050`
- `%10.3f` → "fixed float, 10 wide, 3 after decimal" → `␣␣␣839.210`
- `%10.3e` → "exponential, 10 wide, 3 after decimal" → `␣8.392e+02`
- `%-10g` → "general float, 10 wide, left-justified" → `839.21␣␣␣␣`

---

## scanf gotcha — the trailing newline

When [[#scanf]] finishes reading a value, it **peeks at** the trailing `\n` but doesn't consume it. The next `scanf` sees that newline first.

```c
int n;
char c;
scanf("%d", &n);   // user types "42⏎" → n=42, '\n' stays in buffer
scanf("%c", &c);   // immediately reads '\n' — c is '\n', not the next char!
```

**Fixes:**
- Add a leading space to skip whitespace including `\n`: `scanf(" %c", &c);`
- Or call `getchar()` to drain the newline.

Doesn't bite numeric specs (`%d`/`%f`/...) because they skip leading whitespace automatically.

---

## Quick reference

| Spec | Type | Notes |
|------|------|-------|
| `%d` `%i` | `int` | decimal |
| `%u` | `unsigned` | decimal |
| `%o` | `unsigned` | octal |
| `%x` `%X` | `unsigned` | hex |
| `%f` | `double` | fixed decimal |
| `%e` `%E` | `double` | scientific |
| `%g` `%G` | `double` | smart, strips trailing 0s |
| `%c` | char | watch the [[#scanf gotcha — the trailing newline\|newline gotcha]] |
| `%s` | `char *` | null-terminated string |
| `%p` | `void *` | pointer (impl-defined) |
| `%%` | — | literal `%` |

Length modifiers (printf): `h` short, `hh` char, `l` long, `ll` long long, `L` long double, `z` size_t.

Flags: `-` left-justify, `+` always show sign, `␣` space before positive, `0` zero-pad, `#` alternate form (`0x` for hex).

---

## Exercises

[[Ch03 Exercises]]

## Connects to

- Builds on: [[Ch02 - C Fundamentals]]
- Forward: [[Ch07 - Basic Types]] (which type each specifier matches), [[Ch22 - Input-Output]] (file I/O, full `printf`/`scanf` family)
