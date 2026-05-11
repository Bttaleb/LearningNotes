---
type: exercise
chapter: 3
tags: [chapter/3, topic/io, kind/exercise, status/learning]
related: ["[[Ch03 - Formatted Input-Output]]"]
---

# Chapter 3 Exercises

Format: prediction → actual → reflection. Verify by compiling small `.c` programs.

---

## 1) Predict the printf output

### a) `printf("%6d,%4d", 86, 1040);`

- **Predict:** `␣␣␣␣86,1040`
- **Why:** `86` in 6-wide field (right-justified, 4 leading spaces); `1040` in 4-wide field (exactly fits).
- **Actual:** `␣␣␣␣86,1040` ✅

### b) `printf("%12.5e", 30.253);`

- **Predict:** `␣3.02530e+01`
- **Why:** 12 wide, 5 after decimal, exponential. `3.02530e+01` = 11 chars → 1 leading space.
- **Actual:** `␣3.02530e+01` ✅

### c) `printf("%.4f", 83.162);`

- **Predict:** `83.1620`
- **Why:** 4 digits after decimal, no minimum width. Trailing 0 added (unlike `%g`).
- **Actual:** `83.1620` ✅

### d) `printf("%-6.2g", .0000009979);`

- **Predict:** `1e-06␣`
- **Why:** [[Ch03 - Formatted Input-Output#%g — general float (smart)|%g]] picks exponential (exponent < −4). 2 sig figs → `1.0e-06`, trailing zero stripped → `1e-06` (5 chars), then 1 trailing space (left-justified, width 6).
- **Actual:** `1e-06␣` ✅

## 2) Write calls of printf that display a float variable x in the following formats

### a) `exponential notation; left-justified in a field of size 8; one digit after the decimal point`
- printf('%-8.1e')
### b) `exponential notation; right justified in a filed of size 10; six digits after the decimal point`
- printf('%10.6e')
### c) `fixed decimal notation; left justified in a field of size 8 three digits after the decimal point`
- printf("%-8.3f")
### d) `fixed decimal noation; right justified in a field of size 6; no digits after the decimal`
- printf("%6f")
## 3) For each of the following pairs of scanf format strings, indicate whether or not the two strings are equal, if not show how they can be distinguished
### a) "%d" versus "     %d"
- 
## Reflection

What I want to remember:
- [[Ch03 - Formatted Input-Output#%g — general float (smart)|%g strips trailing zeros]] (unlike `%f`).
- Counting exp notation: `m.dddde±NN` = `precision + 6` chars.
- Width is a **minimum** — never truncates.

Mistakes I made:
- *(log here as you do more exercises)*
