---
type: Selection Statements
chapter: 5
title:
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
"Programmers are not to be measured by their ingenuity and their logic, but by the completeness of their case analysis"
Most of C's statements fall into three categories *depending on how they affect the order in which statements are executed*
**Selection Statements** -> the `if` and `switch` statements allow a program to select a particular execution path from a set of alternatives
**Iteration Statements** -> the `while`, `do`, and `for` statements support iteration (looping)
**Jump Statements** -> the `break`, `continue`, and `goto` statements case an unconditional jump to some other place in the program (return belongs here as well)

Before writing `if` statements, we need logical expressions; conditions that `if` statements can test

---

## 5.1 Logical Expressions

### Relational Operators
Can be used to compare integers and floating-point numbers with operands and mixed types allowed
Ex.
1 < 2.5 has the value 1
5.6 < 4 has the value 0

| Symbol              | Meaning                                                                        |
| ------------------- | ------------------------------------------------------------------------------ |
| <<br>> <br><=<br>>= | less than<br>greater than<br>less than or equal to<br>greater than or equal to |
Precedence of relational operators is lower than arithmetic and left associative 
`i + j < k - 1` means `(i + j) < (k - 1)`

### Equality Operators
Have lower precedence than relational operators
i < j == (j < k)
is equivalent to
(i < j) == (j < k)

| Symbol | Meaning      |
| ------ | ------------ |
| ==     | equal to     |
| !=     | not equal to |
Left associative, produce either 0 (false) or 1 (true)

### Logical Operators
Building more complicated logical expressions

| Symbol | Meaning          |
| ------ | ---------------- |
| !      | logical negation |
| &&     | logical *and*    |
| \|\|   | logical *or*     |
Prouce either 0 or 1 as their result and behave as follows;
- !expr has the value 1 if expr has the value 0
- `expr1 && expr2` has the value `1` if the values `expr1` and `expr2` are **both non-zero**
- expr1 || expr2 has the value 1 if either expr1 or expr2 (or both) has a non-zero value
Both && and || perform "short-circuit" evaluation of their operands. 
These operators evaluate the left operand, then the right
If the value of the expression can be deduced from the value of the left operand alone, then the right operand isn't evaluated

## 5.2 The *If* Statement
Allows for a program to choose between two alternatives by testing the value of an expression
Don't confuse == (equality) with = (assignment)
`if (i == 0)` -> tests whether i is equal to 0
`if (i = 0)` -> assigns 0 to i, then tests whether the result is non-zero
```c
// code
```

## Concept name 2

...

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
|---|---|
|   |   |

---

## Exercises

[[ChNN Exercises]]

## Connects to

- Builds on: [[ChNN - PrevTitle]]
- Forward: [[ChNN - LaterTitle]]
