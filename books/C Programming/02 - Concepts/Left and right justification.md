---
type: concept
chapter: 3
tags: [chapter/3, topic/io, kind/concept]
related: ["[[Conversion specification]]", "[[Field width and precision]]"]
---

# Left and right justification

The `-` flag in a [[Conversion specification]] flips alignment.

| Spec | Output for value `50` | Justification |
|------|-----------------------|---------------|
| `%5d` | `␣␣␣50` | right (default) |
| `%-5d` | `50␣␣␣` | left |

Padding is always with **spaces** (use `0` flag for zero-padding numbers, e.g. `%05d` → `00050`).

## Mnemonic

The `-` "pulls the value to the left."
