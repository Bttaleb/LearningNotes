---
type: chapter
chapter: 5
title: Selection Statements
book: K.N. King — C Programming, A Modern Approach
tags: [chapter/5, topic/control-flow, status/learning]
related: ["[[Ch04 - Expressions]]", "[[Ch06 - Loops]]", "[[Ch09 - Functions]]"]
---

# Chapter 5 — Selection Statements

> Each `##` heading is a deep-link target. From any other note write `[[Ch05 - Selection Statements#If statement]]` to jump here. Add new terms to [[Glossary]].

## TL;DR

"Programmers are not to be measured by their ingenuity and their logic, but by the completeness of their case analysis."

Most of C's statements fall into three categories *depending on how they affect the order in which statements are executed*:

- **Selection statements** — the [[#If statement|`if`]] and `switch` statements allow a program to select a particular execution path from a set of alternatives.
- **Iteration statements** — the `while`, `do`, and `for` statements support iteration (looping). See [[Ch06 - Loops]].
- **Jump statements** — the `break`, `continue`, and `goto` statements cause an unconditional jump to some other place in the program (`return` belongs here as well).

Before writing `if` statements, we need [[#Logical expressions|logical expressions]] — conditions that `if` statements can test.

---

## Logical expressions

### Relational operators

Can be used to compare integers and floating-point numbers with operands and mixed types allowed.

```c
1 < 2.5   // has the value 1
5.6 < 4   // has the value 0
```

| Symbol | Meaning |
| --- | --- |
| `<` | less than |
| `>` | greater than |
| `<=` | less than or equal to |
| `>=` | greater than or equal to |

Precedence of relational operators is lower than arithmetic and left associative.

`i + j < k - 1` means `(i + j) < (k - 1)` (see [[Ch04 - Expressions#Operator precedence]]).

### Equality operators

Have lower precedence than [[#Relational operators]].

`i < j == (j < k)` is equivalent to `(i < j) == (j < k)`.

| Symbol | Meaning      |
| ------ | ------------ |
| **=**  | equal to     |
| `!=`   | not equal to |

Left associative, produce either `0` (false) or `1` (true).

### Logical operators

Building more complicated logical expressions.

| Symbol | Meaning          |
| ------ | ---------------- |
| `!`    | logical negation |
| `&&`   | logical *and*    |
| \|\|** | logical *or*     |

Produce either `0` or `1` as their result and behave as follows:

- `!expr` has the value `1` if `expr` has the value `0`
- `expr1 && expr2` has the value `1` if the values `expr1` and `expr2` are **both non-zero**
- `expr1 || expr2` has the value `1` if either `expr1` or `expr2` (or both) has a non-zero value

### Short-circuit evaluation

Both `&&` and `||` perform "short-circuit" evaluation of their operands.

These operators evaluate the left operand, then the right. If the value of the expression can be deduced from the value of the left operand alone, then the right operand isn't evaluated.

---

## If statement

Allows a program to choose between two alternatives by testing the value of an expression. Has the form:

```c
if (expression) statement
```

Don't confuse *== (equality)* with **= (assignment)**:

```c
if (i == 0)   // tests whether i is equal to 0
if (i = 0)    // assigns 0 to i, then tests whether the result is non-zero
```

```c
// if we wanted to test whether a variable falls within a range of values (0 <= i <= n), we'd write
if (0 <= && i < n)

// to test the opposite condition (i is outside the range)
if (i <  0 || i >= n)
```

## Compound statements

If we want an *if* statement to control two or more statements. Has the form:

```c
{ statements }
```

```c
{ line_num = 0; page_num++; }
```

Compound statement when used inside an `if` statement:

```c
if (line_num == MAX_LINES) {
    line_num = 0;
    page_num++;
}
```

### The *else* clause

```c
if (expression) statement else statement
```

The statement that follows `else` is executed if the expression in the parenthesis has the value `0`.

Example:

```c
if (i > j)
    max = i;
else
    max = j;
```

The following program uses *if* statements to find the largest of the numbers stored in `i`, `j`, and `k` and stores that value in `max`:

```c
if (i > j) {            // is i greater than j? if true, move on
    if (i > k) {        // is i greater than k? if true, i is bigger than both
        max = i;        // set max to the value of i
    } else {            // i is greater than j but less than k
        max = k;        // so set max to the value of k
    }
} else {                // i is less than j, check j
    if (j > k) {        // is j greater than k?
        max = j;        // set max to the value of j
    } else {            // j is less than the value of k
        max = k;        // set max to the value of j
    }
}
```

### Cascaded *if* statements

To test a series of conditions, stopping as soon as one of them is true. The following tests whether `n` is less than `0`, equal to `0`, or greater than `0`:

```c
if (n < 0)
    printf("n is less than 0\n");
else
    if (n == 0)
        printf("n is equal to 0\n");
    else
        printf("n is greater than 0\n");
```

### Dangling else

When `if` statements are nested, watch out for the following:

```c
if (y != 0)
    if (x != 0)
        result = x / y;
else // C follows the rule that an "else" belongs to the nearest "if"
    printf("Error: y is equal to 0\n");
```

Which looks like the following:

```c
if (y != 0)
    if (x != 0)
        result = x / y;
    else
        printf("Error: y is equal to 0\n");
```

If you want the `else` to be paired with the outer `if`:

```c
if (y != 0) {
    if (x != 0)       // enclose the inner "if" with braces
        result = x / y;
} else
        printf("Error: y is equal to 0\n");
```

---

## Conditional expressions

**Conditional operator** — an operator that allows an expression to produce one of two values depending on the value of a condition.

- Consists of 2 symbols (`?` and `:`)
- `expr1 ? expr2 : expr3` — read: "`if` expr1 **then** expr2 *else* expr3"

Considered a `ternary` operator instead of `conditional expression` as it requires **3 operands** instead of 1 or 2.

Expressions are evaluated in stages:

- `expr1` is evaluated first; if value (of `expr1`) `!= 0` (or true) → then `expr2` is evaluated, and its value is the value of the entire conditional expression
- If value of `expr1 == 0` (false), then value of `expr3` is the value of the conditional

```c
int i, j, k;
i = 1;
j = 2;
k = i > j ? i : j;         /* k is now 2 */
k = (i >= 0 ? i : 0) + j;  /* k is now 3 */
```

- Since `i = 1` and `j = 2`, the comparison (*i > j*) fails. The value of the conditional (*2*) is then assigned to `k`.
- In the second assignment, we'll say "if `i` is greater than or equal to 0, then `i`, else 0". This results in the value of 1 being added to j, equaling 3.

Conditionals can be shortened, such as `return` statements:

```c
if (i < j)
    return i;
else
    return j;
// can be shortened to
return i < j ? i : j;
```

`printf` calls can also benefit from conditional expressions:

```c
if (i > j)
    printf("%d\n", i);
else
    printf("%d\n", j);
// turns into
printf("%d\n", i > j ? i : j);
```

---

## Boolean values

### C89

Declare an `int` variable and assign it to either `0` or `1`:

```c
int flag;
flag = 0;
flag = 1;
```

**Problem:** It's not obvious that `flag` is to be assigned only Boolean values and that `0` and `1` represent false and true. Instead, define *macros* such as:

```c
#define TRUE 1
#define FALSE 0
```

Now, assignments to *flag(s)* are more natural:

```c
flag = FALSE;
flag = TRUE;
```

To test whether a *flag* is `TRUE`, we can write:

```c
if (flag == TRUE)     // or     if (flag == FALSE)
```

or

```c
if (flag)             // or     if (!flag)   ← better, more concise
```

Carrying over, we can assign *macros* that can be used as a *type*:

```c
#define BOOL int      // BOOL can take int's place
BOOL flag;            // makes it clear that flag isn't an ordinary int variable,
                      // but represents a BOOL condition
```

### C99

Provides the `_Bool` type. Can be declared by writing:

```c
_Bool flag;
```

- An integer type (more precisely, an **unsigned** integer type)
- Can only be assigned `0` or `1`
- Attempting to store a nonzero will cause the variable to be assigned `1`

```c
flag = 5;   // flag is assigned 1
```

---

## Gotchas

- `if (i = 0)` silently assigns instead of comparing — use **==
- The [[#Dangling else|dangling else]] always pairs with the nearest `if`.
- `&&` and `||` short-circuit — relied-upon side effects on the right operand may not run.
- C89 has no Boolean type; C99 introduces `_Bool` (and `<stdbool.h>` gives you `bool` / `true` / `false`).

## Quick reference

| Operator          | Meaning                     | Precedence vs         |
| ----------------- | --------------------------- | --------------------- |
| `<` `>` `<=` `>=` | relational                  | lower than arithmetic |
| **==**<br>**!=**  | equality                    | lower than relational |
| `!`               | logical NOT (unary)         | high                  |
| `&&`              | logical AND, short-circuits | lower than **==**     |
| `\|\|`            | logical OR, short-circuits  | lower than `&&`       |
| `? :`             | ternary conditional         | low                   |

---

## Exercises

[[Ch05 Exercises]]

## Connects to

- **Builds on:** [[Ch04 - Expressions]] — relational and logical operators extend the [[Ch04 - Expressions#Operator precedence|precedence table]]
- **Forward:** [[Ch06 - Loops]] — same logical conditions, used to control iteration; [[Ch09 - Functions]] — `return` plus ternary

## Glossary feed

- selection statement, iteration statement, jump statement
- relational operators, equality operators, logical operators
- short-circuit evaluation
- `if` statement, compound statement, `else` clause, cascaded `if`, dangling else
- conditional / ternary operator
- `_Bool`, `BOOL` macro
