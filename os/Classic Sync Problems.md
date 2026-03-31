---
tags:
  - concurrency
  - data-flow
source: "OS Class (Jan 2026)"
description: "Producer-Consumer, Readers-Writers, Dining Philosophers — classic semaphore problems"
date: 2026-03-24
---

# Classic Synchronization Problems

Three classic problems that apply [[Synchronization Tools#Semaphores|semaphores]] to real coordination scenarios.

---

## Producer-Consumer Problem

A producer writes data to a shared buffer. A consumer reads from it. The problem: how do you coordinate access so nothing gets corrupted or lost?

This pattern bridges [[IPC Models]] (Ch 3) and [[Synchronization]] (Ch 5). It's an IPC problem (two processes exchanging data) whose shared-memory solution requires synchronization tools.

### Solution with Semaphores

Three synchronization tools:
- `mutex` — initialized to 1. Protects the buffer
- `full` — counting semaphore initialized to 0. Tracks items in buffer
- `empty` — counting semaphore initialized to n. Tracks empty slots

```
// Producer                    // Consumer
wait(empty);                   wait(full);
wait(mutex);                   wait(mutex);
  // add item to buffer          // remove item from buffer
signal(mutex);                 signal(mutex);
signal(full);                  signal(empty);
```

### ORDER MATTERS — Exam Trap

If the producer swaps `wait(mutex)` before `wait(empty)`:
1. Producer grabs mutex (locks buffer)
2. Buffer is full → producer blocks on `wait(empty)`
3. Consumer needs mutex to consume → blocks on `wait(mutex)`
4. **[[process-management|Deadlock]]** — producer holds mutex waiting for empty, consumer needs mutex to free a slot

**Rule:** Always wait on the counting semaphore FIRST, then the mutex. The counting semaphore checks the *condition*, the mutex protects the *operation*.

### Connection to Buffering

The bounded buffer here maps to the bounded-capacity case in [[IPC Models|message passing buffering]]:
- In message passing → the OS manages the buffer and blocking
- In shared memory → **you** write the code (using semaphores) to manage it

Same problem, different responsibility.

---

## Readers-Writers Problem

Shared database. Multiple readers can read simultaneously (no conflict). Writers need **exclusive access**.

Uses: `rw_mutex` (sem, init 1), `mutex` (sem, init 1), `read_count` (int, init 0)

```
// Writer                      // Reader
wait(rw_mutex);                wait(mutex);
  // write                       read_count++;
signal(rw_mutex);                if (read_count == 1)
                                   wait(rw_mutex);     // FIRST reader locks writers out
                               signal(mutex);
                                 // read
                               wait(mutex);
                                 read_count--;
                                 if (read_count == 0)
                                   signal(rw_mutex);   // LAST reader lets writers in
                               signal(mutex);
```

**Key insight:** Only **first** reader grabs `rw_mutex`, only **last** reader releases it. Middle readers just bump the count. `mutex` protects `read_count` itself.

If every reader called `wait(rw_mutex)`, only one could read at a time — defeats the purpose.

---

## Dining Philosophers

5 philosophers, 5 chopsticks. Need **both** left and right to eat.

Naive solution: everyone grabs left, then right → if all grab left simultaneously → **circular wait → [[process-management|deadlock]]**.

Fixes: allow max 4 at table, pick up both atomically, or break symmetry (one philosopher grabs right first).
