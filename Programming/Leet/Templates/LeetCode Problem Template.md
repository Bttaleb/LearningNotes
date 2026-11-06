---
title: <% tp.file.title %>
number:
link:
difficulty:
patterns: []
data-structures: []
model:
language:
status:
time-spent:
date: <% tp.date.now("YYYY-MM-DD") %>
next-review:
attempts: 1
tags:
  - leetcode
---

# <% tp.file.title %>

> **Pipeline:** Define → Classify → Choose model → Specify model → Pseudocode → Build → Reflect
> Do not move to the next stage until the current one holds up.

---

## 1️⃣ Define (Understand)
<!-- Restate it without copying the prompt. Turn every vague word ("valid", "correct order", "matching") into something a program can check. -->

**Problem in my own words:**


**Formal statement:**
- Input: 
- Output: 
- Kind of problem: decision (yes/no) | search (find one) | optimization (find best) | counting
<!-- For string problems: alphabet Σ = { }, language L = { w ∈ Σ* | ... }, question: is w ∈ L? -->

**Rules / properties a correct answer must satisfy:**
1. 
2. 
3. 

**Constraints that matter:**
- n ≤ 
- Values: 
- What the constraints change in practice (buffer sizes, which complexities pass): 

**Examples I traced by hand:**
<!-- Include at least one example per rule above that breaks only that rule -->
```
Input:
Output:
Why:
```

---

## 2️⃣ Classify
<!-- The class tells you the minimum machinery you need. -->

**Core question:** Can this be solved with a fixed amount of memory, no matter how large the input gets?
- As n grows, does what I need to remember grow without limit? → 

**For string / language problems (Chomsky hierarchy):**

| Class | Machine | In code |
|---|---|---|
| Regular | DFA / bounded counter | O(1) extra space, a few flags or a state enum |
| Context-free | PDA | a stack (O(n) space) |
| Beyond | TM | general data structures |

- Is L regular? → 
- How I know (build a DFA/regex to show yes, or Myhill–Nerode / pumping lemma to show no): 

**For other problems (problem family):**
- Family: search | optimization | graph | counting | simulation | parsing
- Structural property (optimal substructure, monotonic predicate, overlapping subproblems, ...): 

---

## 3️⃣ Choose the Model
**Model / data structure:** [[ ]]

**Why the classification forces this choice:**


**Signal(s) in the problem that pointed to it:**
- 

**Naive approach and why it's not enough:**
- Idea: 
- Complexity: Time O( ) · Space O( )

**Similar problems:** [[ ]], [[ ]]

---

## 4️⃣ Specify the Model (Case Table)
<!--
1. What does the algorithm look at to decide each step?
2. List the possible values of each.
3. Cross them, then merge the cases that behave the same way.
The table must be exhaustive (every situation covered) and mutually exclusive (each situation in exactly one row).
Each row (or merged group of rows) becomes one branch in the code.
-->

**What the machine sees at each step:** 

| Input | State / top | Action |
|---|---|---|
|  |  |  |
|  |  |  |

---

## 5️⃣ Pseudocode
<!-- Translate the case table directly. No real syntax yet. -->
```
```

**Invariant / why it's correct:**


**Complexity:** Time O( ) · Space O( )
<!-- Justify each factor: where does it come from? -->

---

## 6️⃣ Build (Code)
```c

```

**Line purposes:**
<!-- For each non-trivial line: what job it does and what breaks without it -->
- 

---

## 7️⃣ Reflect

### Edge cases
- [ ] Empty input
- [ ] Single element
- [ ] One example per rule from stage 1
- [ ] Max constraints (overflow, recursion depth)

**Bugs I hit:**
- 

**Could a weaker model have worked?** (e.g. a counter instead of a stack: if not, why not?)


### Coursework connections
<!-- Theory of Computation, Algorithm Design, OS, SWE -->
- [[ ]]: 

### Takeaways
**What I'd tell myself before attempting this again:**


**Mistake to never repeat:**


**Retrieval questions (answer at next review without looking):**
1. What class is this problem, and how do I know?
2. Which model does that class require, and why can't a weaker one work?
3. What are the rows of the case table?
4. What's the complexity, and where does each factor come from?

---

## 🔁 Review Log
| Date | Solved from scratch? | Time | Notes |
|---|---|---|---|
| <% tp.date.now("YYYY-MM-DD") %> |  |  | First attempt |
