---
type: definition
aliases:
  - word-RAM model
  - word RAM
  - RAM model
  - unit-cost model
source: "Algorithm Design / Palindrome Number (LeetCode 9)"
description: "The standard cost model where any integer fitting in a machine word is one O(1) cell and arithmetic on it is one O(1) step."
---
# word-RAM model

**In one line:** the default assumption behind Big-O analysis — a value that fits in a machine word counts as **one unit of space**, and a basic operation on it (`+`, `*`, `%`, `/`, compare) counts as **one unit of time**, regardless of the value's magnitude.

## What it means
When we say an algorithm is "O(1) space" or an addition is "O(1) time," we're implicitly working in the **word-RAM (unit-cost) model**:
- Memory is an array of **words**, each a fixed number of bits (e.g. 32 or 64).
- Any integer that fits in a word is **one cell** — a 2-digit number and a 10-digit number cost the same.
- Each arithmetic op on word-sized values is **one step**.

This is a *convention*, and it quietly ignores the bit-level truth: a `d`-digit number really needs ~`log₁₀(x)` bits, so under the stricter **bit-cost model** storing it is O(log x) bits and multiplying two big numbers isn't constant. We use word-RAM anyway because it matches real hardware (fixed-width registers) and keeps analysis clean — as long as the numbers fit in a word.

**The caveat that matters:** the model only holds while values fit in a word. For bignum / arbitrary-precision arithmetic (numbers that outgrow a register), you must drop back to the bit-cost model and count the digits.

## Example
In [[9. Palindrome Number]], `x`, `reverted`, and `nextDigit` each hold values bounded by `2^31`, so each fits in one 32-bit word → the solution is **O(1) space** and the loop body is **O(1) time** *under word-RAM*. Strictly, `reverted` holds a `log₁₀(x)`-digit value, but since the input is bounded, word-RAM applies cleanly. This is the same bounded-vs-unbounded tension as [[bounded memory]]: "constant" is honest here only because `x` can't outgrow a register.

<!-- Notes that use this term show up in the Backlinks pane automatically -->
