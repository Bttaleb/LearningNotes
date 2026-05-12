---
type: chapter
chapter: 4
title: Expressions
book: K.N. King — C Programming, A Modern Approach
tags:
  - chapter/
  - topic/
  - status/learning
related: []
---

# Chapter N — Title

> Each `##` heading is a deep-link target. From any other note: `[[ChNN - Title#Section]]`. Add new terms to [[Glossary]].

## TL;DR

Expressions are formulas that show how to compute a value-rather than statements. The simplest forms of expressions are variables and constants. `variable` represents a value to be computed as the program runs; a `constant` represents a value that doesn't change.

---

## Types of operators
a) **Arithmetic operators** -> including addition, subtraction, multiplication, division
b) **Relational operators** -> to perform comparisons such as "i is greater than 0"
c) **Logical operators** -> to build conditions such as "*i* is greater than 0 AND *i* is less than 10"

Definition. Mental model. Minimal example.

```c
// code
```

## Implementation-Defined Behavior
Parts of C language are unspecified, an "implementation" (software needed to compile, link, and execute programs) will fill in the details

| Unary (one operand) | Binary (two operands) | Binary           |     |
| ------------------- | --------------------- | ---------------- | --- |
|                     | `Additive`            | `Multiplicative` |     |
| +Unary plus         | + Addition            | * Multiplication |     |
| - Unary minus       | - Subtraction         | % Remainder      |     |
|                     |                       | / Division       |     |
When an `int` and `float` operands are mixed, result has *type* `float`

## 4.2 Assignment Operators
Once value of expression is computed, store it in a variable for later use
### L-Values
- an assignment operator REQUIRES an 'l-value' as its left operand
- represents an object stored in computer's memory
	- **NOT** a `constant` or  `result` of a computation
- variables ARE L-Values; expressions such as `10` or `2 * i`are not
WRONG:
12 = i;
i + j = 0;
-i = j;
### Compound Assignment
Allows us to shorted statements which may look like
i = i + 2;
which turns into
i += 2;
- `v += e`, adds v to e, storing the result in v
- `v -= e`, subtracts e from v, storing the result in v
- `v *=  e` multiplies b by e, storing the result in v
- `v /= e` divided v by e, storing the result in v
- `v %= e` computes the remainder when v is divided by e, storing the result in v
Compound operators DO NOT mean equivalence -> because of *operator precedence*: `i *= j + k` isn't the same as `i = i * j + k`
- v += e **is NOT** equivalent to v = v + e

Compound assignment operators have same properties as ` =` operator
- i += j += k; means i += (j += k);

## 4.3 Increment and Decrement Operators
Incrementing and Decrementing
Allow us to condense the statements;
i = i + 1 to i += 1
j = j - 1 to j -= 1
Shortened even further using `++ (increment)` or `-- (decrement)`
### Prefix: `++i or --j`
- the increment/decrement happens *before* using i or j

```
i = 1;
printf("i is %d\n", ++i); /* prints "i is 2" */
printf("i is %d\n", i); /* prints "i is 2" */
```

### Postfix: `i++ or j--`
- the increment/decrement happens *after* using i or j

```
i = 1;
printf("i is %d\n", i++); /* prints "i is 1" */
printf("i is %d\n", i); /* prints "i is 2" */
```

## 4.3
---

## Worked examples

```c
// from the book
```

## Gotchas

- Subtle thing 1
- Subtle thing 2

## Quick reference

| Thing | Meaning |
| ----- | ------- |
|       |         |

---

## Exercises

[[ChNN Exercises]]

## Connects to

- Builds on: [[ChNN - PrevTitle]]
- Forward: [[ChNN - LaterTitle]]
