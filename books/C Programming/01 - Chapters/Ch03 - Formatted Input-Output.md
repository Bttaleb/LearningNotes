---
type: chapter
chapter: 3
title: Formatted Input/Output
book: K.N. King — C Programming, A Modern Approach
tags: [chapter/3, topic/io, status/learning]
related: ["[[Ch02 - C Fundamentals]]", "[[Ch07 - Basic Types]]", "[[Ch22 - Input-Output]]"]
---

# Chapter 3 — Formatted Input/Output

> Hub note. The chapter is decomposed into atomic concept notes below — Cmd+click any link to drill in.

## Key ideas (one-line each)

- C's two main I/O workhorses are [[printf]] (output) and [[scanf]] (input). Both are driven by a [[Format string]].
- A format string is a mix of literal text and [[Conversion specification]]s like `%d` or `%5.3f`.
- A conversion spec controls type, [[Field width and precision]], and [[Left and right justification]].
- [[scanf]] has subtle quirks — especially [[scanf newline behavior]] — that bite beginners.

## Concept atoms

### Functions
- [[printf]] — write formatted output to stdout
- [[scanf]] — read formatted input from stdin

### Format string anatomy
- [[Format string]] — literals + conversion specs
- [[Conversion specification]] — `%[flags][width][.precision]conversion`
- [[Field width and precision]] — what `5` and `.3` mean in `%5.3f`
- [[Left and right justification]] — the `-` flag

### Format specifiers (one note each — easy to compare)
- [[Format specifier - d (decimal integer)]]
- [[Format specifier - f (fixed decimal float)]]
- [[Format specifier - e (exponential float)]]
- [[Format specifier - g (general float)]]

### Gotchas
- [[scanf newline behavior]]

## Worked examples (from the book)

```c
int   i = 50;
float x = 839.21f;

printf("|%d|%5d|%-5d|%5.3d|\n", i, i, i, i);
printf("|%10.3f|%10.3e|%-10g|\n", x, x, x);
```

Output:
```
|50|   50|50   |  050|
|   839.210| 8.392e+02|839.21    |
```

Read each spec out loud:
- `%d` → "decimal, minimum width" → `50`
- `%5d` → "decimal, min 5 chars, right-justified" → `␣␣␣50`
- `%-5d` → "decimal, min 5 chars, left-justified" → `50␣␣␣`
- `%5.3d` → "decimal, 5 chars wide, at least 3 digits" → `␣␣050`
- `%10.3f` → "fixed float, 10 wide, 3 after decimal" → `␣␣␣839.210`
- `%10.3e` → "exponential, 10 wide, 3 after decimal" → `␣8.392e+02`
- `%-10g` → "general float, 10 wide, left-justified" → `839.21␣␣␣␣`

## scanf example

```c
int i, j;
float x, y;
scanf("%d%d%f%f", &i, &j, &x, &y);
```

Input: `1 -20 .3 -4.0e3` → `i=1, j=-20, x=0.3, y=-4000.0`

The trailing newline is **peeked at but not consumed** — it's the first character the next [[scanf]] sees. See [[scanf newline behavior]].

## Exercises

- [[Ch03 Ex - printf output prediction]]

## Cheat sheet

- [[printf format reference card]]

## Related chapters

- Builds on: [[Ch02 - C Fundamentals]] (basic syntax, `main`, headers)
- Connects forward to: [[Ch07 - Basic Types]] (which types each specifier matches), [[Ch22 - Input-Output]] (file I/O, full `printf`/`scanf` family)
