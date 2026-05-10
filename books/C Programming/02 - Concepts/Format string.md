---
type: concept
chapter: 3
tags: [chapter/3, topic/io, kind/concept]
related: ["[[printf]]", "[[scanf]]", "[[Conversion specification]]"]
---

# Format string

The first argument to [[printf]] and [[scanf]]. A blend of:

1. **Literal text** — copied to output (printf) or expected verbatim in input (scanf).
2. **[[Conversion specification]]s** — `%`-prefixed tokens that consume one argument each.

## Example

```c
printf("Hello %s, you are %d years old\n", name, age);
//      ─────  ──   ─────────────  ──
//       lit  spec      lit       spec
```

## See also

- [[Conversion specification]] — the structure of a single `%` token
- [[Field width and precision]] — fine-grained control
