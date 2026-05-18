---
type: chapter
chapter: "6"
title: Loops
book: K.N. King — C Programming, A Modern Approach
tags:
  - status/learning
  - topic/loops
  - chapter/6
related: []
---

# Chapter NN — Title

> Each `##` heading is a deep-link target. From any other note write `[[ChNN - Title#Section]]` to jump here. Add new terms to [[Glossary]] as you encounter them.

## TL;DR

One-paragraph mental model of the chapter. Link the key concepts inline so the TL;DR doubles as a table of contents:

> *Example pattern:* "C does X using [[#Concept A]] and [[#Concept B]], controlled by [[#Concept C]]. Watch out for the [[#gotcha name|named gotcha]]."

---

## Iteration Statements
- while -> loops whose controlling expression is tested **before** loop body is executed
- do -> if the expression is tested **after** the loop body is executed
- for -> loops that increment or decrement a counting variable

### *while* Statement

```c
while (expression) statement

while (i < n)     // controlling expression
	i = i * 2;    // loop body
	
//countdown
i = 10;
while (i > 0) {
	printf("T minus %d seconds and counting\n", i);
	i--;
}
```

Observations about the *while* statement:
- The controlling expression is **FALSE** when a while loop **terminates**
- Since controlling expression is tested **before** the loop is executed, body may not be executed at all
Cross-link related ideas inline: `[[Ch04 - Expressions#Operator precedence]]`.

## *do* Statement

Essentially same as the *while* statement, except controlling expression is tested **after** each execution of the loop body.
- handy for loops that must execute at least once

```c
do statement while (expression)

//countdown
i = 10;
do {
	printf("T minus %d seconds and counting", i) // loop body
	i--;
} while (i > 0); // controlling expression
```

- Loop body is executed first, then the controlling expression is evaluated
- If value of expression is nonzero -> loop body is executed again, expression evaluated once more
Do statement turns out to be more attractive, because every integer (even 0) has at least one integer

```c
//replacing the do loop by a similar while loop
while (n > 0) {  // if n is initally 0, loop doesn't execute at all
	n /= 10;
	digits++;
}
Output: The number has 0 digit(s)
```

## *for* Statement
Ideal for loops that have a **"counting" variable**

```c
for (expr1 ; expr2; expr3 ) statement
for (i = 10; i > 0; i--)
	printf("T minus %d and counting\n", i);
```
Variable *i* -> initialized to 10, then *i* is tested to see if it's greater than 0
Since it is -> "T minus 10 and counting" is printed
Then -> *i* is decremented

*for* is closely related to the *while*

```c
expr1; // initialization step performed before loop begins
while (expr2) { // controls loop termination (continues executing as long 
	statement    // as value of expr2 == nonzero)
	expr3; // operation to be performed at the end of each loop iteration
}

i = 10; //initialization
while (i > 0) { // loop termination
	printf("T minus %d and counting\n", i);
	i--; // operation to be performed at the end
}
```

### *for* statement idioms
- usually best choice for loops that "count up" (increment a variable) or "count down" (decrement a variable)
```c
// Counting UP from 0 TO n-1
for (i = 0; i < n; i++)
// Counting UP from 1 TO n
for (i = 1; i <= n; i++) 
// Counting DOWN from n-1 to 0
for (i = n - 1; i >= 0; i++)
// Counting DOWN from n to 1
for (i = n; i > 0; i--)
```
Some beginner errors:
 - Using `<` or `>` in the controlling expression
	 - Counting up -> `<` or `<=`
	 - Counting down -> `>` or `>=`
- Using == in controlling expression instead of `<`, `<=`, `>`, `>=`
	- Controlling expression BEGIN `true` -> LATER `false` so loop can terminate
- "Off-by-one" errors; `i <= n` instead of `i < n`
## Omitting Expressions in *for* statements

*for* statements are flexible
- If the first expression is omitted (*expr1*), no initialization is performed before execution

```c
i = 10; // omit the first expr1 (expr1)
for (; i > 0; i--)
	printf("T minus %d and counting. \n", i);
	
for (i = 10; i > 0;)
	printf("T minus %d and counting. \n", i--); // omit third (expr3) post decrement,
```

...


---

## Worked examples

```c
// worked example from the book, with your annotation
```

Read each line out loud — what is it doing, and why?

## Gotchas

- Subtle thing that bit you (or could)
- Mistake the book flagged

## Quick reference

| Thing | Meaning |
|---|---|
|   |   |

---

## Exercises

[[ChNN Exercises]]

## Connects to

- **Builds on:** [[Ch(NN-1) - PrevTitle]] — what idea this chapter extends
- **Forward:** [[Ch(NN+x) - LaterTitle]] — where this concept resurfaces

## Glossary feed

After finishing, add these terms to [[Glossary]] with `**term** — see [[ChNN - Title#Section]]`:

- term 1
- term 2
