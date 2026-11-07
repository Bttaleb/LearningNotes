---
type: definition
aliases:
  - bounded memory
  - fixed memory
  - constant memory
  - O(1) space
source: "Palindrome Number (LeetCode 9)"
description: "Extra memory whose size stays constant no matter how large the input grows."
---
# bounded memory

**In one line:** extra memory that does *not* grow with the input — a fixed number of variables whether the input has 1 element or a billion.

## What it means
A solution uses **bounded memory** when the amount of working storage it needs is capped by a constant, independent of input size (O(1) extra space). This is the dividing line in the [[Chomsky hierarchy]] that separates a **DFA** (fixed states, no extra storage) from machines that need a stack (PDA, O(n)) or unbounded tape (TM).

Key point: "bounded" means *doesn't grow with n*, **not** "zero." A couple of counters or a reversed-so-far value still count as bounded.

A language is recognizable with bounded memory exactly when it is **regular** — and every **finite** language is regular, since a bounded machine can account for all its (finitely many) strings.

## Example
In [[9. Palindrome Number]], reversing the integer with arithmetic keeps only a constant handful of `int`s regardless of how many digits `x` has → **bounded**. Converting `x` to a string and comparing ends stores all the digits → grows with digit count → **not** bounded (O(n)).

The abstract palindrome language `{ w | w = reverse(w) }` is *not* regular and needs a stack — but bounding `x` to 32 bits makes the input set finite, hence regular, hence solvable in bounded memory.

<!-- Notes that use this term show up in the Backlinks pane automatically -->
