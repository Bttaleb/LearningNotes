---
tags:
  - concurrency
  - performance
source: "OS Class (Jan 2026)"
description: "Spinlock vs Blocking — the two ways semaphores wait"
date: 2026-03-24
---

# Semaphore Implementations

Two ways a [[Semaphores|semaphore]] handles waiting. Likely exam question: "discuss the two implementations, advantages/disadvantages, when to use each."

---

## Spinlock (Busy Waiting)

Process loops checking: `while (S <= 0);`

- **Pro:** No context switch overhead — faster if wait is short
- **Con:** Wastes CPU cycles spinning
- **Use on:** Multiprocessor systems, short expected waits

## Blocking (Sleep/Wakeup)

Process calls `block()` and joins a waiting queue. `signal()` calls `wakeup()`.

- **Pro:** Zero CPU waste while waiting
- **Con:** Context switch cost (save/restore registers, switch address space)
- **Use on:** Single-processor systems, long expected waits

## Key Insight

On a **single core**, spinning is pointless — the process holding the lock can't run while you're spinning. You'll spin until preempted. Always block on single core.

On **multi core**, spinning can be faster — one core spins briefly while another core runs the process that will release the lock.
