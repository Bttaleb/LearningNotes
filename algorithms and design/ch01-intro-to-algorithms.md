---
type: chapter
chapter: 1
title: Introduction to Algorithm Design and Analysis
source: Anany Levitin — Introduction to the Design and Analysis of Algorithms
class: Algorithms and Design (active class)
tags: [chapter/1, topic/algorithms, topic/algorithm-design, status/learning]
related: []
---

# Chapter 1 — Introduction to Algorithm Design and Analysis

> Each `##` heading is a deep-link target. From any other note write `[[ch01-intro-to-algorithms#Section name]]` to jump here.

## TL;DR

An **algorithm** is a sequence of unambiguous instructions for solving a problem in a finite amount of time. The same problem can have multiple algorithms with very different speeds — illustrated by three methods for computing [[#Three methods for computing GCD|GCD]] (Euclid's, consecutive-integer checking, middle-school). Designing an algorithm is a multi-step process: [[#Understanding the problem|understand the problem]] → pick [[#Decide on computational means|computational means]] → choose [[#Exact vs approximation|exact or approximate]] → apply a [[#Algorithm design techniques|design technique]] → pick the right [[#Designing the algorithm and data structures|data structures]] → [[#Methods of specifying an algorithm|specify it]] → [[#Proving correctness|prove correctness]] → [[#Analyzing the algorithm|analyze]] → [[#Coding the algorithm|code]]. The chapter closes with the seven [[#Important problem types|important problem types]] in algorithmics.

---

## Why study algorithms?

1. **Practical standpoint** → you have to know a standard set of important algorithms from different areas of computing. You should also be able to design new algorithms and analyze their efficiency.
2. **Theoretical standpoint** → *Algorithmics* (the study of algorithms) is recognized as the cornerstone of CS. More than a branch of CS — it is the core of computer science. Computer programs would not exist without algorithms.

## What is an algorithm?

An algorithm is a **sequence of unambiguous instructions for solving a problem** — i.e., for obtaining a required output for any legitimate input in a finite amount of time.

Key points illustrated by the three GCD methods:
- The non-ambiguity requirement for each step cannot be compromised.
- The range of inputs an algorithm works for must be specified carefully.
- The same algorithm can be represented in several different ways.
- Several algorithms can solve the same problem.
- Algorithms for the same problem can be based on very different ideas and solve the problem with dramatically different speeds.

---

## Three methods for computing GCD

**Greatest common divisor** of two nonnegative, not-both-zero integers `m` and `n` (denoted `gcd(m, n)`) is the largest integer that divides both `m` and `n` evenly (remainder of zero).

### 1. Euclid's algorithm

Based on repeated application of the equality:

```
gcd(m, n) = gcd(n, m mod n)
```

Happens until the second number becomes 0 (which makes the problem trivial). The last value of `m` is also the gcd of the initial `m` and `n`.

Example: `gcd(60, 24) = gcd(24, 12) = gcd(12, 0) = 12`

**Steps:**
- **Step 1:** If `n = 0`, return the value of `m` as the answer and stop; otherwise, proceed to Step 2.
- **Step 2:** Divide `m` by `n` and assign the value of the remainder to `r`.
- **Step 3:** Assign the value of `n` to `m` and the value of `r` to `n`. Go to Step 1.

**How do we know it comes to a stop?**
The second integer of the pair gets smaller with each iteration and cannot become negative — the new value of `n` is `m mod n`, which is always smaller than `n`. So the second integer eventually becomes 0 and the algorithm stops.

### 2. Consecutive integer checking algorithm

- **Step 1:** Assign the value of `min{m, n}` to `t`.
- **Step 2:** Divide `m` by `t`. If remainder = 0 → Step 3; otherwise → Step 4.
- **Step 3:** Divide `n` by `t`. If remainder = 0 → return `t`, stop; otherwise → Step 4.
- **Step 4:** Decrease `t` by 1 → Step 2.

Starts by checking whether `t` divides both `m` and `n`: if it does, `t` is the answer; if not, decrease `t` by 1 and try again.

**Gotcha:** Doesn't work correctly when one of its inputs is 0 — illustrates why specifying the set of legitimate inputs explicitly matters.

### 3. Middle-school procedure

- **Step 1:** Find prime factorization of `m`.
- **Step 2:** Find prime factorization of `n`.
- **Step 3:** Find all common prime factors.
- **Step 4:** Compute product of all common prime factors and return as `gcd(m, n)`.

Example:
```
gcd(60, 24)
  60 = 2 · 2 · 3 · 5
  24 = 2 · 2 · 2 · 3
  gcd(60, 24) = 2 · 2 · 3 = 12
```

**Why doesn't this pass as a legitimate algorithm in its current form?**
- Prime factorization steps are not defined unambiguously — they require a list of prime numbers.
- Step 3 is not defined clearly enough.
- Much more complex and slower than Euclid's algorithm.

---

Algorithms are considered to be **procedural solutions** to problems. These "solutions" are NOT answers — they are specific instructions for getting answers. This emphasis on precisely defined constructive procedures is what distinguishes computer science from disciplines like theoretical mathematics, where it's enough to prove that a solution *exists*.

---

## Algorithm design and analysis process

### Understanding the problem

Before designing an algorithm, completely understand the problem:
- Read the problem's description carefully and ask questions if you have doubts.
- Do a few small examples by hand, think about special cases.
- Consider using a known algorithm — understand its strengths and weaknesses, especially when choosing among alternatives.
- Specify exactly the set of instances the algorithm needs to handle.

### Decide on computational means

The vast majority of algorithms today are written for a computer closely resembling the **von Neumann machine** — captured by the **random-access machine (RAM)** model.

- **Sequential algorithm** → Instructions executed one after another, one operation at a time (RAM model).
- **Parallel algorithm** → Operations executed concurrently. The central RAM assumption doesn't hold for newer computers that execute operations in parallel.

Studying classic techniques under the RAM model remains the cornerstone of algorithmics for the foreseeable future.

### Exact vs approximation

Choose between solving the problem **exactly** (exact algorithm) or **approximately** (approximation algorithm).

**Why opt for an approximation algorithm?**
1. Important problems that simply cannot be solved exactly for most of their instances.
	- Example: extracting square roots.
2. Available exact algorithms can be unacceptably slow due to the problem's intrinsic complexity.
	- Common with problems involving a very large number of choices.
3. An approximation algorithm can be a part of a more sophisticated algorithm that solves the problem exactly.

### Algorithm design techniques

An **algorithm design technique** (also "strategy" or "paradigm") is a general approach to solving problems algorithmically — applicable to a variety of problems from different areas of computing.

General techniques:
- Brute Force and Exhaustive Search
- Decrease-and-Conquer
- Divide-and-Conquer
- Transform-and-Conquer
- Space and Time Trade-Offs
- Dynamic Programming
- Greedy Technique
- Iterative Improvement

### Designing the algorithm and data structures

Some design techniques can be inapplicable to the problem; sometimes several techniques need to be combined. Even when one applies, getting the algorithm often requires nontrivial ingenuity.

**Data structure choice matters.** Example: binary search on a sorted list is O(log n) with an array (constant-time middle access) but O(n log n) with a linked list (linear-time middle access).

### Methods of specifying an algorithm

- **Natural language** — obvious appeal, but inherent ambiguity makes succinct/clear descriptions surprisingly hard. Still worth practicing.
- **Pseudocode** — mixture of natural language and programming-language constructs. More precise, yields more succinct descriptions. No single agreed-upon form.
- **Flowchart** — historically dominant, now mostly found in old algorithm books. Inconvenient for all but very simple algorithms.

### Proving correctness

Prove that the algorithm yields a required result for every legitimate input in a finite amount of time.

Example: Euclid's algorithm's correctness comes from
- the equality `gcd(m, n) = gcd(n, m mod n)`,
- the observation that the second integer gets smaller every iteration,
- the algorithm stops when the second integer becomes 0.

### Analyzing the algorithm

Desirable qualities (in priority order):
- **Time efficiency** → how fast it runs.
- **Space efficiency** → how much extra memory it uses.
- **Simplicity** → easier to understand and program → fewer bugs.
- **Generality** → solves a class of similar problems, accepts a broad set of inputs.

If you're unsatisfied with efficiency, simplicity, or generality, return to the drawing board.

### Coding the algorithm

Programming an algorithm presents both a `peril` and an `opportunity`:
- **Peril** — making the transition from algorithm to program either incorrectly or very inefficiently.

Even with code-optimizing compilers, be aware of standard tricks:
- Compute a loop's invariant outside the loop.
- Collect common subexpressions.
- Replace expensive operations with cheap ones.

Test and debug thoroughly. Provide verification of the algorithm's inputs (real applications shouldn't assume inputs are pre-validated).

---

## Important problem types

Seven areas that attract particular attention from researchers — driven by practical importance or by being interesting research subjects.

### Sorting

Rearrange items of a given list in nondecreasing order. The list items must allow a total ordering (numbers, characters, strings, records).

For records, a **key** is the specially chosen piece of information used to guide the sort (e.g., student records by name, ID, or GPA).

**Why sort?**
- Required output of a task (e.g., ranking students by GPA).
- Makes many questions about the list easier to answer (dictionaries, class lists).
- Auxiliary step in other algorithms (e.g., the Greedy approach often requires sorted input).

No single algorithm is best in all situations — trade-offs between simplicity vs speed, random vs almost-sorted input, memory-resident vs disk-resident data.

**Two special properties:**
- **Stable** → preserves relative order of any two equal elements. If input has equal elements at positions `i < j`, the sorted output has them at `i' < j'`.
	- Before sort = 1, 2, 5, 3<sub>a</sub>, 4, 3<sub>b</sub>
	- Stable algorithm MUST preserve order of `a` and `b` after the sort:
	- After sort = 1, 2, 3<sub>a</sub>, 3<sub>b</sub>, 4, 5
	- Useful when secondary sort criteria matter (e.g., students sorted alphabetically *then* by GPA stay alphabetical within GPA groups).
	- Algorithms that exchange keys located far apart are usually unstable but faster.
- **In-place** → does NOT require extra memory (beyond a few units / no extra array for the sort).

### Searching

Find a given value, called a **search key**, in a given set (or multiset).

Range: from straightforward sequential search to spectacularly efficient but limited binary search, to algorithms based on representing the set in a form more conducive to searching. The latter are indispensable for storing and retrieving information from large databases.

### String processing

A **string** is a sequence of characters from an alphabet. Notable kinds:
- **Text strings** — letters, numbers, special characters.
- **Bit strings** — zeros and ones.
- **Gene sequences** — strings over `{A, C, G, T}`.

**String matching** — searching for a given word in a text — has attracted special attention.

### Graph problems

A **graph** is a collection of points (**vertices**), some of which are connected by line segments (**edges**). Used to model transportation, communication, social/economic networks, project scheduling, games, etc.

Two famously hard graph problems:
- **Traveling salesman problem (TSP)** — find the shortest tour through `n` cities that visits every city exactly once. Applications: route planning.
- **Graph-coloring problem** — assign the smallest number of colors to vertices so that no two adjacent vertices share a color. Applications: event scheduling.

### Combinatorial problems

Problems that (explicitly or implicitly) ask to find a combinatorial object — permutation, combination, subset — satisfying certain constraints.

The most difficult problems in computing, both theoretically and practically:
- The number of combinatorial objects grows extremely fast with problem size — reaching unimaginable magnitudes even for moderate sizes.
- No known algorithms can solve most such problems exactly in acceptable time (and most CS researchers believe such algorithms don't exist).

A few efficient exceptions exist — e.g., the **shortest-path problem**.

### Geometric problems

Deal with geometric objects (points, lines, polygons). Two classic problems:
- **Closest-pair problem** — given `n` points in the plane, find the closest pair.
- **Convex-hull problem** — find the smallest convex polygon containing all points of a given set.

### Numerical problems

Involve mathematical objects of continuous nature: solving equations and systems of equations, evaluating functions, etc.

---

## Linear data structures

*(class lecture material — populate as covered)*

### Array

### Linked list

### Stack

### Queue

---

## Graphs

A collection of points in a plane (**vertices / nodes**) — some connected by line segments (**edges**).

A **graph** `G = ⟨V, E⟩` is defined by a pair of two sets:
1. Finite non-empty set `V` of items (**vertices**).
2. Set `E` of pairs of these items (**edges**).

Graphs can be **undirected** or **directed** (digraph — edges have a from-to direction).

A graph `G` is:
- **Complete** if every pair of its vertices is connected by an edge.
- **Dense** if relatively few possible edges are missing.
- **Sparse** if few edges are present relative to the number of vertices.

### Representations

A graph can be represented in 2 ways:

#### Adjacency matrix (best for dense graphs)

An `n × n` Boolean matrix with 1 row and 1 column for each of the `n` vertices. Element in `i`th row and `j`th column:
- `1`, if there exists an edge from `i`th vertex to `j`th vertex
- `0`, if there is no such edge

For **directed graphs**, cell `(row, column) = 1` only if there's an edge **from row → to column**. The matrix is **not symmetric** in general (unlike undirected graphs, where it always is).

For **weighted graphs**, store the edge weight in the cell instead of 1; use a sentinel value (e.g., ∞ or `-999`) for missing edges.

#### Adjacency lists (best for sparse graphs)

*(populate as covered)*

### Weighted graphs

*(populate as covered)*

### Paths

A **simple path** from vertex `u` to vertex `v` is a sequence of edges that doesn't repeat any vertex. The **cost** of a path in a weighted graph is the sum of its edge weights.

### Cycles

*(populate as covered)*

---

## Trees

*(class lecture material — populate as covered)*

### Binary trees

A tree where each node has at most two children. Key vocabulary:
- **Root** — the only node with no parent (no incoming edge).
- **Child node** — any non-root node (has a parent).
- **Leaf** — a node with no children (no outgoing edges).
- **Parent** — the node directly above a child.

---

## Sets

*(populate as covered)*

---

## Gotchas

- The **middle-school GCD procedure** is NOT a legitimate algorithm in its presented form — prime factorization is ambiguous and step 3 is under-defined.
- **Consecutive integer checking** fails when one input is 0 — specify legitimate inputs explicitly.
- **Approximation ≠ wrong** — for some problems (square roots, NP-hard cases), it's the only practical option.
- In a **directed adjacency matrix**, `(u, v) = 1` does NOT imply `(v, u) = 1`. Symmetry only holds for undirected graphs.
- **Weighted matrix** missing edges aren't `0` (which would mean "free to traverse") — use `∞` or a sentinel.

## Quick reference

| Concept | One-line take |
| --- | --- |
| Algorithm | Unambiguous finite sequence of steps solving a problem |
| RAM model | Sequential execution, one operation at a time |
| Stable sort | Preserves relative order of equal elements |
| In-place | No extra memory beyond a constant |
| Adjacency matrix | `n × n`, good for dense graphs |
| Adjacency list | One list per vertex, good for sparse graphs |
| Simple path | No repeated vertices |
| Tree root | The only node with no parent |
| Tree leaf | A node with no children |

---

## Connects to

- **Forward:** future chapters cover specific [[#Algorithm design techniques|design techniques]] (brute force, divide-and-conquer, dynamic programming, greedy, etc.) applied to the [[#Important problem types|problem types]] above.
- **Cross-domain:** [[bridges]] connects algorithmic concepts to real-world software patterns.

## Glossary feed

*(seed for when you build the algorithms-and-design glossary later)*

- algorithm, algorithmics
- GCD, Euclid's algorithm, consecutive integer checking, middle-school procedure
- RAM model, sequential, parallel
- exact vs approximation algorithm
- algorithm design technique (brute force, divide-and-conquer, etc.)
- pseudocode, flowchart
- time efficiency, space efficiency, simplicity, generality
- sorting, stable, in-place, key
- searching, search key
- string, string matching
- graph, vertex, edge, undirected, directed, complete, dense, sparse
- adjacency matrix, adjacency list
- TSP, graph coloring
- combinatorial problem, geometric problem, numerical problem
- closest-pair, convex hull
- tree, root, child, leaf, binary tree
