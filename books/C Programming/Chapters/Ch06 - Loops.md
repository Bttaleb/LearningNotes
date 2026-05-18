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

Essentially the *while* statement whose controlling expression is tested **after** each execution of the loop body

```c
do statement while (expression)

//countdown
i = 10;
do {
	printf("T minus %d seconds and counting", i) // loop body
	i--;
} while (i > 0); // controlling expression
```

Loop body is executed first, then the controlling expression is evaluated
If value of expression is nonzero -> loop body is executed again, expression evaluated once more

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
