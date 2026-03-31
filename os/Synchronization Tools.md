---
tags:
  - concurrency
  - state
  - performance
source: "OS Class (Jan 2026)"
description: "Hardware instructions → mutex locks → semaphores — the sync tool hierarchy"
date: 2026-03-24
---

# Synchronization Tools

The building blocks for solving [[Synchronization|critical section problems]], from low-level hardware up to high-level tools.

---

## Atomic Hardware Instructions

Low-level building blocks. "Atomic" = executes as one indivisible unit, cannot be interrupted.

### test_and_set()

```
boolean test_and_set(boolean *target) {
    boolean rv = *target;
    *target = true;
    return rv;      // returns OLD value
}
```

Read, set to true, return old value — all atomic. If it returns false, you got the lock.

### compare_and_swap()

```
int compare_and_swap(int *value, int expected, int new_value) {
    int temp = *value;
    if (*value == expected)
        *value = new_value;
    return temp;     // returns OLD value
}
```

More flexible — only swaps **if value matches expected**. Enables lock-free algorithms.

### Both Satisfy

- Mutual exclusion ✓
- Progress ✓
- **NOT bounded waiting** — a thread could spin forever while others keep winning

### Bounded-Waiting Solution (test_and_set)

Adds `waiting[n]` array + circular scan to guarantee fairness.

**Entry:** Two ways in — either `test_and_set` returns false (lock was free), OR the exiting process sets your `waiting[i] = false`.

**Exit:** Don't release lock to a free-for-all. Scan forward circularly: `j = (i+1) % n`. Find first `waiting[j] == true`, set `waiting[j] = false` — **hand the lock directly to them**.

If nobody waiting → `lock = false`.

**Why it works:** Circular scan checks processes in order. Every process is at most **n-1 turns** away from getting the lock. That's bounded waiting.

**The insight:** Exiting process acts as a **gatekeeper** — picks the next one in line instead of releasing to everyone.

---

## Mutex Locks

The simplest high-level [[Synchronization]] tool. Two operations:

```
acquire(lock);    // grab lock, wait if taken
    // critical section
release(lock);    // give up lock
```

Only one thread can hold the lock at a time → **mutual exclusion** guaranteed.

### Relationship to Hardware

Atomic hardware instructions (test_and_set, compare_and_swap) are the **building blocks**. A mutex is the **tool built from them**.

```
test_and_set / compare_and_swap → used to IMPLEMENT → mutex locks → which you USE in code
```

You don't write raw hardware instructions in application code. You use mutexes.

### Spinlock Behavior

A basic mutex implementation **spins** (busy waits) when the lock is taken:

```
while (test_and_set(&lock));  // keep checking: free yet? free yet?
```

This wastes CPU. See the semaphore implementations section below for the alternative (blocking/sleeping).

---

## Semaphores

An integer variable accessed through two atomic operations:
- `wait(S)` (P) — if S > 0, decrement and proceed. If S == 0, block.
- `signal(S)` (V) — increment S, potentially waking a blocked process.

### Two Types

**Binary semaphore** — value is 0 or 1. Behaves like a mutex.

**Counting semaphore** — value can be any non-negative integer. Controls access to a resource with **multiple instances**.

**Analogy:** A parking garage counter. `wait()` = car enters, counter goes down. `signal()` = car leaves, counter goes up. Counter hits zero = garage full, you wait.

### Mutex vs Semaphore

| | Mutex | Counting Semaphore |
|--|-------|-------------------|
| Values | 0 or 1 | 0 to n |
| Controls | One resource | Multiple resources |
| Use case | Critical section | Resource pool (e.g., 5 printers) |

### Negative Values = Queue Length

In the blocking implementation, S can go **negative**. The absolute value of S tells you how many processes are blocked waiting. If S = -3, three processes are in the waiting queue.

### Used In Classic Problems

See [[Classic Sync Problems]] — Producer-Consumer, Readers-Writers, Dining Philosophers.

---

## Semaphore Implementations

Two ways a semaphore handles waiting. Likely exam question: "discuss the two implementations, advantages/disadvantages, when to use each."

### Spinlock (Busy Waiting)

Process loops checking: `while (S <= 0);`

- **Pro:** No context switch overhead — faster if wait is short
- **Con:** Wastes CPU cycles spinning
- **Use on:** Multiprocessor systems, short expected waits

### Blocking (Sleep/Wakeup)

Process calls `block()` and joins a waiting queue. `signal()` calls `wakeup()`.

- **Pro:** Zero CPU waste while waiting
- **Con:** Context switch cost (save/restore registers, switch address space)
- **Use on:** Single-processor systems, long expected waits

### Key Insight

On a **single core**, spinning is pointless — the process holding the lock can't run while you're spinning. You'll spin until preempted. Always block on single core.

On **multi core**, spinning can be faster — one core spins briefly while another core runs the process that will release the lock.
