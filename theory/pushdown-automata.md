---
tags:
  - automata
  - computation
  - state
aliases:
  - PDA
  - PDAs
  - pushdown automaton
  - pushdown automata
  - DPDA
source: "Intro to Theoretical CS (Jan 2026)"
description: "A finite-state machine plus a stack: recognizes exactly the context-free languages"
---

# Pushdown Automata (PDA)

A [[dfa|finite automaton]] **plus a stack**.
	The states give it finite memory; the stack gives it unbounded memory with LIFO access.

Recognizes exactly the [[context-free-languages|context-free languages]].

---

## Definition

A PDA is a 6-tuple: **(Q, Σ, Γ, δ, q₀, F)**

| Symbol | Meaning |
|--------|---------|
| Q | Finite set of states |
| Σ | Input alphabet |
| Γ | Stack alphabet (what can be pushed; can differ from Σ) |
| δ | Transition function: Q × Σ_ε × Γ_ε → 𝒫(Q × Γ_ε) |
| q₀ | Start state (q₀ ∈ Q) |
| F | Set of accepting states (F ⊆ Q) |

Σ_ε = Σ ∪ {ε}, Γ_ε = Γ ∪ {ε}

**Reading a transition:** `a, b → c` means: read input `a`, pop `b` off the stack, push `c`.
- `a, ε → c`: push c without popping
- `a, b → ε`: pop b without pushing
- `ε, b → c`: change the stack without reading input

---

## What the machine sees at each step

Every move is decided by exactly two things:
1. the **current input symbol** (or ε)
2. the **top of the stack** (or ε)

That's why a PDA's transitions can be written as a case table: list every combination of (input, top), then merge the rows that act the same. Each row becomes one branch in code.

---

## Acceptance

Accept if, after reading all of the input, the machine is in an accepting state.
	Common variant: accept by **empty stack**. Both versions recognize the same class of languages.

Standard trick: push a bottom marker `$` first, so the machine can tell when the stack is empty.

---

## PDA vs. DFA

| | [[dfa\|DFA]] | PDA |
|---|---|---|
| Memory | finite states only | finite states + unbounded stack |
| Recognizes | regular languages | context-free languages |
| Can count without bound? | no | yes (push one symbol per unit) |
| Can match nested structure? | only to a fixed depth | yes, any depth |

---

## Deterministic vs. nondeterministic

By default a PDA is **nondeterministic** (δ returns a *set* of moves).

Unlike DFA vs. [[NFA]], the two are **not** equal in power:
- **NPDA** recognizes all context-free languages
- **DPDA** recognizes only the **deterministic CFLs**, a strict subset
	- Example that needs nondeterminism: even-length palindromes { wwᴿ }. The machine has to *guess* where the middle is.

Why deterministic matters in code: exactly one move per (input, top) means no guessing and no backtracking, so it's **one left-to-right pass, O(n) time**.

---

## Classic example: { 0ⁿ1ⁿ | n ≥ 0 }

Not regular (a DFA can't count n without bound), but a PDA can:
1. Push `$`
2. For each `0`: push `0`
3. For each `1`: pop a `0` (if there's no `0` to pop, reject)
4. At end of input: accept if the top is `$`

The stack works as an unbounded counter. With one symbol type, a plain integer counter would do the same job.

---

## In code

| PDA part            | Code                                                 |
| ------------------- | ---------------------------------------------------- |
| Stack               | array + `top` index (or pointer)                     |
| Push                | `stack[++top] = c`                                   |
| Pop                 | `stack[top--]`                                       |
| Empty stack         | `top == -1`                                          |
| Transition function | `if`/`else` branches, often driven by a lookup table |

## Where this shows up
- [[20. Valid Parentheses]]: the solution *is* a deterministic PDA; its case table is the transition function
- Parsers and compilers: recognizing nested syntax (blocks, expressions, delimiters)
- The call stack: recursion is a stack of pending work, the same LIFO idea
