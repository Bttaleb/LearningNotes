---
tags:
  - computation
source: "Learning session — Levitin Ch02 thread (May 2026)"
description: "Math is a language. Equivalence is relative to a level of abstraction (problem / algorithm / code)."
---
# Levels of Equivalence

> Pivot from "math is a language" → formal language theory → syntax vs. semantics → extensional vs. intensional equivalence → the problem/algorithm/code hierarchy. The punchline: **"the same as" is meaningless without naming a level.**

## Math as a formal language

Mathematical notation is a formal language in the same sense your [[dfa|DFA]] notes describe. The same four-layer apparatus applies to *any* formal system — programming languages, math notation, logical formulas, DNA, chess notation.

| Layer       | What it is                                       | Math example                                      |
| ----------- | ------------------------------------------------ | ------------------------------------------------- |
| Alphabet Σ  | The raw allowed symbols                          | digits, variables, `+`, `×`, `=`, brackets, `Σ`   |
| Grammar     | Rules that decide which symbol arrangements are well-formed | precedence, bracket matching, scope of `Σ`'s `k` |
| Language    | The *set* of all well-formed strings the grammar produces | every valid formula you could write              |
| Semantics   | The mapping from string → meaning                | what the formula computes / denotes               |

**Grammar is not part of the language.** Formally, grammar is a *generator* that sits outside and produces the language. Two different grammars can generate the same language (equivalent grammars). The colloquial usage that conflates them is fine in everyday talk, breaks down in formal CS.

## Syntax vs. semantics — and the "math as language" video

The video Bass referenced distinguishes "math as a language" from "the application of math." That maps directly onto **syntax vs. semantics**:

- **Math as language** = the syntactic system. Alphabet, grammar, well-formed strings.
- **Application of math** = binding semantics to the world. The formula $F = ma$ becomes physics when you map $F$, $m$, $a$ to actual forces, masses, accelerations.

A formula sitting on a page is pure syntax. A formula *interpreted as a computation on real matrices* is semantics being applied.

## Two notions of "same" — extensional vs. intensional

When are two things "the same"? Formal systems give two distinct answers:

**Extensional equivalence** — same input/output behavior. Black-box view. Two functions are the same if they map every input to the same output, regardless of *how*.

**Intensional equivalence** — same *procedure*. White-box view. Two computations are the same only if they unfold step-for-step the same way.

Strassen's algorithm and standard matrix multiplication are **extensionally equivalent** (same outputs for any input pair of matrices) but **intensionally distinct** (different procedures, different operation counts, different complexities).

## The three-level hierarchy

This refines the slogan "algorithms are semantic objects; code is syntactic packaging" into something sharper:

```
PROBLEM       (extensional)   what function are we computing?         e.g. "sort a list"
   ↑
ALGORITHM     (intensional)   what procedure are we using?            e.g. bubble sort vs. quicksort
   ↑
CODE          (syntactic)     how is the procedure written down?      e.g. C vs. Python vs. pseudocode
```

- The **problem** is the input/output mapping. A function.
- The **algorithm** is a specific procedure that solves the problem. Many algorithms can solve the same problem.
- The **code** is a specific string that expresses the algorithm in some language. Many code-strings can express the same algorithm.

Each level "abstracts away" the level below it.

## Where complexity lives

Complexity analysis only makes sense at the **algorithm level**, not at the problem level.

- "Matrix multiplication is O(n³)" — sloppy. Means: "the standard *algorithm* for matrix multiplication is O(n³)."
- "Matrix multiplication has lower bound Ω(n²)" — precise. Means: "the *problem* has lower bound Ω(n²) just to write out n² output entries." This is the floor any algorithm has to clear.
- "Strassen's is O(n^2.807)" — a specific algorithm's complexity.

The problem has a lower bound (must do at least this much work). Each algorithm has its own complexity (this is how much *this procedure* does). The gap between them is where algorithm research happens — finding faster algorithms for the same problem.

This is why the [[ch02-fundamental-analysis-algo-efficiency#Measuring an inputs size|size metric]] question even makes sense: complexity is a property of *the procedure as a function of input size*. You can't ask it about a problem (problems don't have procedures) and you can't ask it about code (the syntax is irrelevant; same algorithm in two languages has the same complexity).

## Worked example — matrix multiplication, two languages, one algorithm

Concrete demonstration of the whole framework. The standard algorithm for multiplying two n×n matrices $C = A \times B$ can be expressed two ways.

**Math notation:**

$$C[i][j] = \sum_{k=0}^{n-1} A[i][k] \times B[k][j]$$

In English: each entry of C is the **dot product** of one row of A with one column of B. There are n² entries to fill; each entry requires summing n products.

**C code:**

```c
for (i = 0; i < n; i++)        // pick the row of C
    for (j = 0; j < n; j++)    // pick the column of C
        for (k = 0; k < n; k++) // accumulate the dot product
            C[i][j] += A[i][k] * B[k][j];
```

**Same algorithm at three layers:**

- **Problem (extensional):** compute the matrix product $C = AB$. Both expressions solve this.
- **Algorithm (intensional):** the procedure is identical — fill each of n² output cells by summing n products of corresponding entries from a row of A and a column of B. Same procedure.
- **Code (syntactic):** different strings. The math version uses $\sum$ notation; the C version uses an explicit `for k` loop. The `for i` and `for j` loops in C are *implicit* in the math version (left to the reader to range over all `i, j`). Same algorithm, two syntactic packagings.

**Where the n³ comes from:**

- n² output cells.
- n multiplications per cell (one for each k).
- Total: n² × n = **n³ basic operations**.

The complexity is a property of the *algorithm*, not of either notation. Whether you wrote it in $\Sigma$-form or for-loop form, it's still n³ multiplications. If you rewrote it in Python or assembly, still n³. Change the algorithm (to Strassen's), and the complexity changes — to O(n^2.807) — because you've changed the procedure, not just the syntax.

**Three-question checklist for this algorithm:**

- **Size metric?** n (the matrix dimension). Note the Gotcha from [[ch02-fundamental-analysis-algo-efficiency#Gotcha - Choice of parameter indicating an input size DOES matter|Ch02]]: you could argue the *input data* is n², but by convention n is the dimension.
- **Basic operation?** scalar multiplication (innermost loop).
- **Does the count vary for inputs of the same size?** **No.** Always exactly n³ multiplications regardless of matrix values. Deterministic operation count.

## The punchline

**Equivalence is always relative to a level.** "Same as" is meaningless until you name the level:

- Bubble sort and quicksort — *same problem*, different algorithms, different code.
- Strassen and standard mat-mul — *same problem*, different algorithms, different code.
- The math formula $C[i][j] = \sum_k A[i][k] B[k][j]$ and the C-loop version — *same algorithm*, different code.
- Two compilers' output for the same C program — *same algorithm* (mostly), different code.

Always ask: same *as what*?

## Connections

- [[ch02-fundamental-analysis-algo-efficiency#Measuring an inputs size|size metric]] — complexity needs the algorithm level to be a meaningful concept
- [[dfa]] — DFAs accept formal languages; same formal-language machinery used here
- The "math is a language" framing is the gateway in; the four-layer model (alphabet/grammar/language/semantics) is the formal version

## Tag candidates (not yet adopted)

Three concepts in this note don't have a tag in your current vocabulary. Flagging them for you to decide whether to add:

- `abstraction` — levels of abstraction is the central idea here and recurs across domains (OS, programming languages, theory).
- `semantics` — the syntax/semantics distinction will keep showing up (compilers, programming languages, logic).
- `formal-languages` — the alphabet/grammar/language stack appears in TOC, compilers, and PL theory.

If any feels worth adopting, add it to the frontmatter and mention it in `_guide.md` so future notes can reuse it.
