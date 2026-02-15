---
tags:
  - automata
  - computation
  - state
source: "Intro to Theoretical CS (Jan 2026)"
description: "Recognizing regular languages with finite states and deterministic transitions"
---

# Deterministic Finite Automata (DFA)

Takes in a string as an input
	For every symbol in the input, we always know where to go next
## Definition

A DFA is a 5-tuple: **(Q, Σ, δ, q₀, F)**

| Symbol | Meaning |
|--------|---------|
| Q | Finite set of states |
| Σ | Alphabet (input symbols) |
| δ | Transition function: Q × Σ → Q |
| q₀ | Start state (q₀ ∈ Q) |
| F | Set of accepting states (F ⊆ Q) |

**Deterministic** = exactly one transition per symbol from each state.

---

## Acceptance

A DFA **accepts** a string if:
1. Start at q₀
2. Read each symbol, follow transitions
3. After reading entire string, end in a state ∈ F

The **language** L(M) = all strings the DFA accepts.

---

## Key Insight: Start State as Accepting

If **q₀ ∈ F** (start state is accepting):
- The empty string ε is accepted
- Useful for languages that include ε

```
Example: L = {strings with even number of 1s}
         ε has zero 1s (even) → must accept
         → start state must be accepting
```

---

## Example: Strings Ending in 0

Language: All strings over {0,1} that end in 0

```
        0           0
    ┌───────┐   ┌───────┐
    ▼       │   ▼       │
→ (q₀) ────────→((q₁))
         0
    │               │
    └───────────────┘
            1
```

| State | 0 | 1 |
|-------|---|---|
| q₀ | q₁ | q₀ |
| q₁ (accept) | q₁ | q₀ |

- q₀: Haven't seen 0 as last symbol
- q₁: Last symbol was 0 → accept

**Pattern:** Stay in accepting state with 0s; any 1 returns to non-accepting, requiring another 0 to accept.

---

## Common Patterns

| Language | Start Accepting? | Key Insight |
|----------|-----------------|-------------|
| Ends in X | No | Accept only after seeing X |
| Contains X | No | Once X seen, stay accepting |
| Even count of X | Yes | Toggle on each X |
| Doesn't contain X | Yes | Trap state if X seen |

---

## Trap States

A **trap state** (dead state) is non-accepting with only self-loops.
- Once entered, no escape
- Used for "rejection" patterns

```
→ (q₀) ──[bad input]──→ (trap) ⟲
```

---

## Key Points

1. **Deterministic** — no ambiguity, exactly one path per input
2. **Acceptance = finishing state** — doesn't matter how you got there
3. **Every string has exactly one path** — either ends in F or doesn't
4. **DFAs recognize exactly the regular languages**
