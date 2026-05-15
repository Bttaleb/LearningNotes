---
type: chapter
chapter: 4
title: Expressions
book: K.N. King — C Programming, A Modern Approach
tags: [chapter/4, topic/expressions, topic/operators, status/learning]
related: ["[[Ch03 - Formatted Input-Output]]", "[[Ch05 - Selection Statements]]", "[[Ch07 - Basic Types]]"]
---

# Chapter 4 — Expressions

> Each `##` heading is a deep-link target. From any other note write `[[Ch04 - Expressions#Operator precedence]]` to jump here. Add new terms to [[Glossary]].

## TL;DR

Expressions are formulas that show how to compute a value — rather than statements. The simplest forms of expressions are variables and constants. A `variable` represents a value to be computed as the program runs; a `constant` represents a value that doesn't change. C builds bigger expressions from [[#Types of operators|operators]] grouped by [[#Operator precedence|precedence and associativity]]. Assignment ([[#L-values|requires an l-value]]), [[#Compound assignment|compound assignment]], and [[#Increment and decrement|increment/decrement]] each have subtleties worth slowing down for.

---

## Types of operators

- **Arithmetic operators** → including addition, subtraction, multiplication, division
- **Relational operators** → to perform comparisons such as "i is greater than 0" (see [[Ch05 - Selection Statements#Relational operators]])
- **Logical operators** → to build conditions such as "*i* is greater than 0 AND *i* is less than 10" (see [[Ch05 - Selection Statements#Logical operators]])

### Arithmetic operators table

| Unary (one operand) | Binary (two operands) — Additive | Binary (two operands) — Multiplicative |
| --- | --- | --- |
| `+` Unary plus<br>`-` Unary minus | `+` Addition<br>`-` Subtraction | `*` Multiplication<br>`%` Remainder<br>`/` Division |

When an `int` and `float` operands are mixed, result has *type* `float`.

## Implementation-defined behavior

Parts of C language are unspecified — an "implementation" (software needed to compile, link, and execute programs) will fill in the details.

---

## Assignment operators

Once value of expression is computed, store it in a variable for later use.

### L-values

- An assignment operator **requires** an `l-value` as its left operand.
- Represents an object stored in computer's memory.
  - **NOT** a `constant` or `result` of a computation.
- Variables ARE l-values; expressions such as `10` or `2 * i` are not.

Wrong:

```c
12 = i;
i + j = 0;
-i = j;
```

### Compound assignment

Allows us to shorten statements which may look like

```c
i = i + 2;
```

which turns into

```c
i += 2;
```

- `v += e` — adds v to e, storing the result in v
- `v -= e` — subtracts e from v, storing the result in v
- `v *= e` — multiplies v by e, storing the result in v
- `v /= e` — divides v by e, storing the result in v
- `v %= e` — computes the remainder when v is divided by e, storing the result in v

Compound operators **do not** mean equivalence — because of [[#Operator precedence|operator precedence]]: `i *= j + k` isn't the same as `i = i * j + k`.

- `v += e` is **not** equivalent to `v = v + e`

Compound assignment operators have same properties as the '**=**' operator:

- `i += j += k;` means `i += (j += k);`

---

## Increment and decrement

Incrementing and decrementing allow us to condense the statements:

```c
i = i + 1;   // → i += 1
j = j - 1;   // → j -= 1
```

Shortened even further using `++` (increment) or `--` (decrement).

### Prefix: `++i` or `--j`

The increment/decrement happens *before* using i or j.

```c
i = 1;
printf("i is %d\n", ++i); /* prints "i is 2" */
printf("i is %d\n", i);   /* prints "i is 2" */
```

### Postfix: `i++` or `j--`

The increment/decrement happens *after* using i or j.

```c
i = 1;
printf("i is %d\n", i++); /* prints "i is 1" */
printf("i is %d\n", i);   /* prints "i is 2" */
```

---

## Operator precedence

C evaluates expressions in stages: highest precedence first, then ties broken by associativity.

| Precedence | Name | Symbol(s) | Associativity |
| --- | --- | --- | --- |
| 1 | increment (postfix)<br>decrement (postfix) | `++`<br>`--` | left |
| 2 | increment (prefix)<br>decrement (prefix)<br>unary plus<br>unary minus | `++`<br>`--`<br>`+`<br>`-` | right |
| 3 | multiplicative | `*` `/` `%` | left |
| 4 | additive | `+` `-` | left |
| 5 | assignment | `=` `*=` `/=` `%=` `+=` `-=` | right |

### Worked example — parsing a hairy expression

How would we understand an expression like

```c
a + b += c++ - d + --e / -f
```

Express using *subexpressions*:

1. Highest precedence is increment (postfix):
   `a + b += (c++) - d + --e / -f`
2. Then decrement (prefix) and unary minus operator (both precedence 2):
   `a + b += (c++) - d + (--e) / (-f)`
3. Multiplicative `/` operator:
   `a + b += ((c++) - d) + ((--e) / (-f))`
4. `-` and `+` additive operators:
   `a + b += (((c++) - d) + ((--e) / (-f)))`
5. `=` and `+=` assignment operators (group from right to left):
   `(a = b += (((c++) - d) + ((--e) / (-f))))`

---

## Gotchas

- `v += e` is **not** the same as `v = v + e` — precedence changes the parse.
- Prefix vs postfix changes when the value is read, not just the side effect.
- Assignment is **right-associative**: `a = b = c` reads as `a = (b = c)`.
- The left operand of '**=**' must be an [[#L-values|l-value]] — constants and computed expressions are not.

## Quick reference

| Category | Operators |
| --- | --- |
| Arithmetic (unary) | `+` `-` |
| Arithmetic (binary) | `+` `-` `*` `/` `%` |
| Assignment | `=` |
| Compound assignment | `+=` `-=` `*=` `/=` `%=` |
| Increment / decrement | `++` `--` (prefix and postfix) |

---

## Exercises

[[Ch04 Exercises]]

## Connects to

- **Builds on:** [[Ch03 - Formatted Input-Output]] — the values you print come from expressions
- **Forward:** [[Ch05 - Selection Statements]] — relational and logical operators extend this precedence table; [[Ch07 - Basic Types]] — type conversions inside mixed-type expressions

## Glossary feed

- expression, variable, constant
- l-value
- compound assignment
- prefix / postfix increment
- operator precedence, associativity
- implementation-defined behavior
