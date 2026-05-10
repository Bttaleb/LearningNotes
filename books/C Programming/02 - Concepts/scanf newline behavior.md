---
type: concept
chapter: 3
tags: [chapter/3, topic/io, kind/concept, gotcha]
related: ["[[scanf]]"]
---

# scanf newline behavior

When [[scanf]] finishes reading a value, it **peeks at** the trailing newline (`\n`) but does **not consume** it. That newline is the first character the *next* `scanf` call sees.

## Why it bites you

```c
int n;
char c;
scanf("%d", &n);   // user types "42\n" → n=42, '\n' stays in buffer
scanf("%c", &c);   // immediately reads '\n' — c is '\n', not the next char!
```

## Fixes

- Add a leading space in the format string — `" %c"` — to skip whitespace including `\n`:
  ```c
  scanf(" %c", &c);
  ```
- Or use `getchar()` to explicitly drain the newline.

## Doesn't affect

- Numeric specs like `%d`, `%f`, `%i`, `%u`, `%x` — they all skip leading whitespace automatically. The trap is specifically `%c` (and to some extent `%[...]` and `fgets` after a `scanf`).
