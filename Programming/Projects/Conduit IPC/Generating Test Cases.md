---
tags:
  - debugging
  - error-handling
  - state
  - concurrency
type: IPC
source: "conduit-ipc Phase 1 — read_exact (Oct 2026)"
description: "Six repeatable generators for finding edge cases + spec holes, with a per-function template and practice routine"
date: 2026-10-17
---
### G1. **One per Outcome**: read the output contract
### G2. **Boundaries**: 0, 1, limit-1, limit, limit+1, max
### G3.  **Each Input**: empty / zero / one / huge / invalid / NULL
### G4. **Each dependency's returns**: every call made * everything it returns
### G5. **States * events**: grid; every cell is a case
### G6. **Time/order**: before / during / after / never / twice

Our procedure for every generator
1. Target -> What does this generator point at? (outputs, input, a dependency)
2. Ask -> Apply the generator's fixed questions to that target
3. Concrete -> Turn each answer into a specific input/scenario
4. Predict -> Use the contract to say what should happen
5. Locate -> Which line of code handles it?

### G1: One per Outcome
Target: the return contract (n, 0, -1)
Ask: What input produces each outcome?

| Outcome        | Concrete Scenario                         | Predict | Line (code) |
| -------------- | ----------------------------------------- | ------- | ----------- |
| n              | Child writes 10 bytes, parent asks for 10 | 10      | 37          |
| 0              | Child writes nothing, closes              | 0       | 30          |
| -1 (truncated) | Child writes 5, parent asks for 10        | -1      | 32          |
| -1 (error)     | Pass an fd that isnt open                 | -1      | 25          |

> 🚩 **If you can't do step 4 (Predict), the contract has a hole.** That's a design decision, not a test.

### G2: Boundaries
Target: every number — `n`, where EOF lands, how `read()` splits data
Ask: 0? 1? limit−1? limit?

| Number       | Boundary     | Scenario                       | Predict                          |
| ------------ | ------------ | ------------------------------ | -------------------------------- |
| `n`          | 0            | Ask for 0 bytes                | `0`, ambiguous with EOF ⚠️       |
| `n`          | 1            | Ask for 1 byte                 | `1`                              |
| EOF position | `got = 1`    | Child sends 1 byte, closes     | `-1` (truncated)                 |
| EOF position | `got = n−1`  | Child sends 9 of 10, closes    | `-1`, almost complete but fails  |
| Read splits  | 1 read       | All 10 arrive at once          | `10`, loop runs once             |
| Read splits  | n reads      | 1 byte per `write()` + sleeps  | `10`, loop runs 10 times         |

Boundaries aren't only *values*, they're also **loop iteration counts** (once vs. n times).

### G3: Each Input
Target: `fd`, `buf`, `n`
Ask: invalid? NULL? too small? huge?

| Input | Question  | Scenario                   | Predict                                  |
| ----- | --------- | -------------------------- | ---------------------------------------- |
| `fd`  | Invalid?  | `fd = -1`                  | `EBADF` → `-1` ✅                        |
| `fd`  | Wrong end | Pass the pipe's write end  | `EBADF` → `-1` ✅                        |
| `buf` | NULL?     | `buf = NULL, n = 10`       | ⚠️ not in contract → precondition        |
| `buf` | Too small | 4-byte buffer, `n = 10`    | ⚠️ silent memory corruption → precondition |
| `n`   | Huge?     | `n` > max `ssize_t`        | ⚠️ `return n` can't fit in `ssize_t`     |

⚠️ here are **preconditions** (the caller's job), not loop bugs → document them. AddressSanitizer catches "too small" in testing.

### G4: Each Dependency's Returns
Target: `read()`, the only function called
Ask: what can it return?

| `read()` returns       | Scenario             | Predict                  |
| ---------------------- | -------------------- | ------------------------ |
| == n − got (all of it) | Fast writer          | Loop exits on next check |
| `< n − got` (partial)  | Slow writer          | Loop continues           |
| `0`                    | Writer closed        | EOF branch               |
| `-1`, `EINTR`          | Signal while blocked | Retry                    |
| `-1`, other            | Bad fd               | `-1`                     |

**Answer key:** `man 2 read` → **ERRORS** section. The OS documents every failure case.

### G5: States × Events
Target: state = `got` (zero / nonzero), event = `r`
Ask: fill every cell

|                | `r > 0`  | `r == 0`         | `r < 0`, EINTR          | `r < 0`, other                 |
| -------------- | -------- | ---------------- | ----------------------- | ------------------------------ |
| **`got == 0`** | Progress | Clean EOF → `0`  | Retry                   | `-1`                           |
| **`got > 0`**  | Progress | Truncated → `-1` | Retry, **keeping `got`** | `-1`, **partial data is garbage** |

"Truncated" came out of this grid: same event (EOF), different meaning depending on state → [[dfa]]-style thinking.

### G6: Time & Order
Target: what the writer does, relative to the reader
Ask: before? during? after? never?

| Timing                                    | Predict                                              |
| ----------------------------------------- | ---------------------------------------------------- |
| Writer writes + closes **before** reader starts | `10`, EOF only appears *after* buffered data is drained ✅ |
| Writer closes **during** a blocked read   | Wakes with `0` → clean or truncated, depending on `got` |
| Signal **during** read                    | Retry                                                |
| Writer **never** writes, **never** closes | ⚠️ **blocks forever** (no timeout)                   |

That last row motivates Phase 2: one hung worker freezes the coordinator.

---

## What Came Out of It

**Tests** (merged duplicates):
1. 10 bytes in 3 chunks → `10`
2. 10 bytes, 1 per write → `10`
3. Nothing, then close → `0`
4. 5 of 10, then close → `-1`
5. 9 of 10, then close → `-1`
6. Child writes + exits *before* parent reads → `10`
7. Bad fd → `-1`

**Spec holes** (decisions, not tests):
- [ ] `n == 0` is ambiguous with EOF
- [ ] `buf` NULL / too small → document as a precondition
- [ ] Error with `got > 0` → partial data discarded → document it
- [ ] Silent peer blocks forever → document now, fix in Phase 2

**Key lesson:** G3, G5, G6 found **design** gaps, not code bugs. Run generators during **planning** (Polya Step 1), not only after coding.

---

## Which Generators to Prioritize
- **Systems / IPC / concurrency** → G4, G5, G6 (bugs live in failure paths + timing)
- **Algorithms / LeetCode** → G1, G2, G3 (empty, single, duplicates, sorted, max size)

---

## Template (copy for every function)

```
### Function: name(params)
Contract: returns ___ on ___, ___ on ___, ___ on ___

Tests
| # | Generator | Scenario | Expected |
|---|-----------|----------|----------|
| 1 |           |          |          |

Spec holes (decisions, not tests)
- [ ] ___ → decision: ___ → documented in contract?

Preconditions (caller's responsibility)
- ___
```

---

## Practice Routine

**Every function (apply)**
1. Before coding: G1 + the two generators that fit the domain → fill in the template
2. Resolve every spec hole *before* writing the body
3. After coding: run the rest → turn them into tests

**Weekly drill (~15 min, study)**
Run all six generators on a function you didn't write, then grade yourself against its man page ERRORS section.
Queue: `write` → `memcpy` → `strtol` → `malloc` → `fork` → `pipe` → `waitpid`

**Monthly review**
Which generator found the most issues? The one you skip most is your blind spot (usually G6).

---

## Revisit Cues
- (~3 days) Name all six generators from memory. Which matter most for IPC, and why?
- (~1 week) Run G5 on `write_all`. Which cell has no equivalent in `read_exact`?
- (~2 weeks) Run G1–G3 on binary search. Which boundary breaks most implementations?
- (~1 month) Pick a past bug of yours. Which generator would have caught it?

## Related Notes
- [[conduit-ipc (inter process communication)]] · [[protocol]] · [[ordinary-pipes]] · [[system-calls]]
- [[dfa]] · [[study-methodology]]
- Concepts to write up later: [[Design by Contract]] · [[Boundary Value Analysis]] · [[Equivalence Partitioning]] · [[Loop Invariants]]
