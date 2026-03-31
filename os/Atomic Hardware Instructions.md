---
tags:
  - concurrency
  - state
source: "OS Class (Jan 2026)"
description: "test_and_set, compare_and_swap, and bounded-waiting solution"
date: 2026-03-24
---

# Atomic Hardware Instructions

Low-level building blocks for [[Synchronization]]. "Atomic" = executes as one indivisible unit, cannot be interrupted.

---

## test_and_set()

```
boolean test_and_set(boolean *target) {
    boolean rv = *target;
    *target = true;
    return rv;      // returns OLD value
}
```

Read, set to true, return old value — all atomic. If it returns false, you got the lock.

## compare_and_swap()

```
int compare_and_swap(int *value, int expected, int new_value) {
    int temp = *value;
    if (*value == expected)
        *value = new_value;
    return temp;     // returns OLD value
}
```

More flexible — only swaps **if value matches expected**. Enables lock-free algorithms.

## Both Satisfy

- Mutual exclusion ✓
- Progress ✓
- **NOT bounded waiting** — a thread could spin forever while others keep winning

---

## Bounded-Waiting Solution (test_and_set)

Adds `waiting[n]` array + circular scan to guarantee fairness.

**Entry:** Two ways in — either `test_and_set` returns false (lock was free), OR the exiting process sets your `waiting[i] = false`.

**Exit:** Don't release lock to a free-for-all. Scan forward circularly: `j = (i+1) % n`. Find first `waiting[j] == true`, set `waiting[j] = false` — **hand the lock directly to them**.

If nobody waiting → `lock = false`.

**Why it works:** Circular scan checks processes in order. Every process is at most **n-1 turns** away from getting the lock. That's bounded waiting.

**The insight:** Exiting process acts as a **gatekeeper** — picks the next one in line instead of releasing to everyone.
