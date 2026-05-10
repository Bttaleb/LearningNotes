---
type: exercise
chapter: 3
tags: [chapter/3, topic/io, kind/exercise, status/learning]
related: ["[[Ch03 - Formatted Input-Output]]", "[[Conversion specification]]"]
---

# Ch3 Exercise — Predict the printf output

Predict the output of each call below, then verify by compiling. Track mistakes in the **Reflection** section.

## Problems

### a) `printf("%6d,%4d", 86, 1040);`

- My prediction: `␣␣␣␣86,1040`
- Why: `86` in 6-wide field (right-justified, 4 leading spaces); `1040` in 4-wide field (exactly fits).
- Actual: `␣␣␣␣86,1040` ✅

### b) `printf("%12.5e", 30.253);`

- My prediction: `␣␣3.02530e+01`
- Why: 12 chars wide, 5 digits after decimal, exponential form. `3.02530e+01` is 11 chars → 1 leading space.
- Actual: `␣3.02530e+01` ✅
- ⚠️ Note from earlier: I said "12 characters wide with 5 digits after the decimal point" — correct. Be careful counting padding.

### c) `printf("%.4f", 83.162);`

- My prediction: `83.1620`
- Why: 4 digits after the decimal point, no minimum width. Original had 3 digits after, so trailing 0 added.
- Actual: `83.1620` ✅

### d) `printf("%-6.2g", .0000009979);`

- My prediction: `1e-06␣` (6 wide, left-justified, 2 sig figs → rounds to 1e-06)
- Why: `%g` chose exponential because exponent < −4. 2 sig figs → `1.0e-06`, but trailing zero stripped → `1e-06` (5 chars), then 1 trailing space for left-justify in width 6.
- Actual: `1e-06␣` ✅
- ⚠️ My earlier note "1e-0.6" — that's a typo, watch transcription.

## Reflection

What I got wrong / want to remember:
- [[Format specifier - g (general float)]] **strips trailing zeros**, unlike `%f`.
- Counting exponential notation chars: `m.dddde±NN` has 1+1+precision+1+1+2 chars = `precision + 6`.
- Width is a **minimum**, never truncates.
