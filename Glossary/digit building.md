---
type: definition
aliases:
  - digit building
  - build a number digit by digit
  - acc * base + digit
  - Horner's method
source: "Palindrome Number (LeetCode 9)"
description: "The idiom for assembling a number one digit at a time: acc = acc * base + nextDigit."
---
# digit building

**In one line:** build a number left-to-right by, for each new digit, shifting what you have one place up and dropping the digit into the empty slot — `acc = acc * base + nextDigit`.

## What it means
To append a digit to a number you're constructing, you multiply by the **base** (shifting every existing digit one position more significant, emptying the ones place) and add the new digit:

```
acc = acc * 10 + nextDigit      // base 10
```

The mirror operation **tears a number down** from the right:

```
nextDigit = x % 10              // read the ones digit
x         = x / 10              // discard it
```

- `* base` / `% base` are a pair: one shifts up, one reads the bottom.
- `+ digit` / `/ base` are a pair: one fills the slot, one drops it.

Because you read `x`'s digits least-significant-first and append them, the result comes out **reversed** — which is why half-reversal works in [[9. Palindrome Number]].

## Example
Reversing the tail of `1221`:
```
acc=0,  x=1221  →  acc = 0*10 + 1  = 1,   x = 122
acc=1,  x=122   →  acc = 1*10 + 2  = 12,  x = 12
```
`acc` goes `0 → 1 → 12`, the reverse of the digits `1, 2`.

Same idiom appears in: reversing an integer (LeetCode 7), string-to-number parsing (`atoi`), and evaluating a polynomial (**Horner's method**, `acc = acc*x + coeff`). All are "fold one symbol at a time into an accumulator" — uses only [[bounded memory]].

<!-- Notes that use this term show up in the Backlinks pane automatically -->
