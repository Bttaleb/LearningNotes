---
type: definition
aliases:
  - pumping lemma
  - pumping lemma for regular languages
source: "Theory of Computation"
description: "A property every regular language must have; used to prove a language is NOT regular."
---
# pumping lemma

**In one line:** every regular language has a length `p` beyond which any string can be split so that a middle chunk repeats any number of times and stays in the language — if no such split exists, the language isn't regular.

## What it means
If `L` is **regular**, there is a **pumping length** `p` such that every `w ∈ L` with `|w| ≥ p` can be written as `w = xyz` where:
1. `|y| ≥ 1` — the pumped part is non-empty
2. `|xy| ≤ p` — it sits within the first `p` symbols
3. `xyᶦz ∈ L` for **every** `i ≥ 0` — pumping `y` up or down never leaves the language

Intuition: a DFA has only finitely many states, so reading a long enough string must **revisit a state** — that revisited loop is `y`, and you can traverse it any number of times.

The lemma is used by its **contrapositive**: to prove `L` is *not* regular, assume a `p` exists, pick an adversarial `w ∈ L`, and show *some* split is forced that breaks when pumped. It only has teeth on **infinite** languages — it can never prove a finite language non-regular (finite ⇒ regular). See [[bounded memory]] and the [[Chomsky hierarchy]].

## Example
Palindromes `L = { w | w = reverse(w) }` are **not** regular. Take `w = aᵖ b aᵖ` (a palindrome, length `≥ p`). By rule 2, `xy` lies in the leading `a`'s, so `y` is all `a`'s. Pumping to `xy²z` adds `a`'s on the **left only** → the two `a`-runs no longer match → not a palindrome → contradiction.

This is exactly why abstract palindromes need a stack, while [[9. Palindrome Number]] escapes the result: bounding `x` to 32 bits makes its input set **finite**, so the pumping lemma doesn't apply and [[bounded memory]] suffices.

<!-- Notes that use this term show up in the Backlinks pane automatically -->
