---
tags:
  - concurrency
  - state
source: "OS Class (Jan 2026)"
description: "General synchronization tool — binary and counting types, used in all classic problems"
date: 2026-03-24
---

# Semaphores

An integer variable accessed through two atomic operations:
- `wait(S)` (P) — if S > 0, decrement and proceed. If S == 0, block.
- `signal(S)` (V) — increment S, potentially waking a blocked process.

---

## Two Types

**Binary semaphore** — value is 0 or 1. Behaves like a [[Mutex Locks|mutex]].

**Counting semaphore** — value can be any non-negative integer. Controls access to a resource with **multiple instances**.

**Analogy:** A parking garage counter. `wait()` = car enters, counter goes down. `signal()` = car leaves, counter goes up. Counter hits zero = garage full, you wait.

---

## Two Implementations

See [[Semaphore Implementations]] for the full comparison. Summary:
- **Spinlock** — process loops checking the value. Wastes CPU but no context switch overhead.
- **Blocking** — process goes to sleep, gets woken up by signal. Saves CPU but has context switch cost.

---

## Used In Classic Problems

- [[Producer-Consumer Problem]] — `empty`, `full` (counting) + `mutex` (binary)
- [[Readers-Writers Problem]] — `rw_mutex` + `mutex` + `read_count`
- [[Dining Philosophers]] — `chopstick[5]` semaphores

---

## Negative Values = Queue Length

In the blocking implementation, S can go **negative**. The absolute value of S tells you how many processes are blocked waiting. If S = -3, three processes are in the waiting queue.
