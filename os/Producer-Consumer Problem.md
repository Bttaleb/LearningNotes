---
tags:
  - concurrency
  - data-flow
source: "OS Class (Jan 2026)"
description: "Classic IPC pattern solved with semaphores — bridges Ch 3 (IPC) and Ch 5 (Synchronization)"
date: 2026-03-24
---

# Producer-Consumer Problem

A producer writes data to a shared buffer. A consumer reads from it. The problem: how do you coordinate access so nothing gets corrupted or lost?

This pattern bridges [[IPC Models]] (Ch 3) and [[Synchronization]] (Ch 5). It's an IPC problem (two processes exchanging data) whose shared-memory solution requires synchronization tools.

---

## Solution with Semaphores

Three synchronization tools:
- `mutex` — initialized to 1. Protects the buffer ([[Mutex Locks]])
- `full` — [[Semaphores|counting semaphore]] initialized to 0. Tracks items in buffer
- `empty` — [[Semaphores|counting semaphore]] initialized to n. Tracks empty slots

```
// Producer                    // Consumer
wait(empty);                   wait(full);
wait(mutex);                   wait(mutex);
  // add item to buffer          // remove item from buffer
signal(mutex);                 signal(mutex);
signal(full);                  signal(empty);
```

---

## ORDER MATTERS — Exam Trap

If the producer swaps `wait(mutex)` before `wait(empty)`:
1. Producer grabs mutex (locks buffer)
2. Buffer is full → producer blocks on `wait(empty)`
3. Consumer needs mutex to consume → blocks on `wait(mutex)`
4. **[[process-management|Deadlock]]** — producer holds mutex waiting for empty, consumer needs mutex to free a slot

**Rule:** Always wait on the counting semaphore FIRST, then the mutex. The counting semaphore checks the *condition*, the mutex protects the *operation*.

---

## Connection to Buffering

The bounded buffer here maps to the bounded-capacity case in [[IPC Models|message passing buffering]]:
- In message passing → the OS manages the buffer and blocking
- In shared memory → **you** write the code (using [[Semaphores]]) to manage it

Same problem, different responsibility.
