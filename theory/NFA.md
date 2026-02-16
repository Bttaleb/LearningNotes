---
tags:
  - automata
  - computation
  - state
source: "Intro to Theoretical CS (Feb 2026)"
description: "Nondeterministic Finite Automata — how they differ from DFAs and why they matter"
date: 2026-02-15
---

# NFA

Unlike [[dfa|DFA's]], for every symbol in the input, the next state is <font color="#ff0000">undetermined</font> — meaning a single state can have **multiple transitions** on the same symbol, or even transitions on **no input at all** (ε-transitions).

## How It Differs from a DFA

- **DFA**: one state + one symbol → exactly **one** next state
- **NFA**: one state + one symbol → a **set** of possible next states (zero, one, or many)
- **ε-transitions**: an NFA can jump to another state without consuming any input — a DFA can never do this

## Acceptance

An NFA **accepts** a string if **at least one** path through all the branching possibilities ends in an accept state. It doesn't matter if most paths die — one successful path is enough.

## Real-World Analogies

- **GPS with multiple routes** — a DFA gives you one route, an NFA explores every possible route simultaneously and succeeds if any of them arrive
- **Searching for a word on a page** — every time you spot a promising first letter, your attention forks off to check the rest; most forks fizzle, but one match is all you need
- **Detective following leads** — clues branch into multiple suspects, teams investigate all of them in parallel; ε-transitions are tips that appear without new evidence

## Diagrams

DFA:
![[DFAvsNFA|DFAvsNFA]]
NFA:
