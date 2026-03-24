---
tags:
  - concurrency
  - state
source: "OS Class (Jan 2026)"
description: "Simplest synchronization tool — built on hardware instructions, used everywhere"
date: 2026-03-24
---

# Mutex Locks

The simplest high-level [[Synchronization]] tool. Two operations:

```
acquire(lock);    // grab lock, wait if taken
    // critical section
release(lock);    // give up lock
```

Only one thread can hold the lock at a time → **mutual exclusion** guaranteed.

---

## Relationship to Hardware

[[Atomic Hardware Instructions]] (test_and_set, compare_and_swap) are the **building blocks**. A mutex is the **tool built from them**.

```
test_and_set / compare_and_swap → used to IMPLEMENT → mutex locks → which you USE in code
```

You don't write raw hardware instructions in application code. You use mutexes.

---

## Mutex vs Semaphore

A mutex is essentially a **binary** [[Semaphores|semaphore]] — locked (0) or unlocked (1). One resource, one thread.

A counting semaphore manages **multiple instances** of a resource. Different tool for a different problem.

| | Mutex | Counting Semaphore |
|--|-------|-------------------|
| Values | 0 or 1 | 0 to n |
| Controls | One resource | Multiple resources |
| Use case | Critical section | Resource pool (e.g., 5 printers) |

---

## Spinlock Behavior

A basic mutex implementation **spins** (busy waits) when the lock is taken:

```
while (test_and_set(&lock));  // keep checking: free yet? free yet?
```

This wastes CPU. See [[Semaphore Implementations]] for the alternative (blocking/sleeping).
