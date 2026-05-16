---
tags:
  - concurrency
  - data-flow
  - memory
source: "OS Class (Jan 2026)"
description: "Two IPC models — shared memory vs message passing — and when to use each"
date: 2026-03-24
---

# IPC Models

Processes are isolated by design — the OS gives each its own address space. When cooperating processes need to communicate, they need IPC (Inter-Process Communication).

Two fundamental models, each with a core trade-off: **speed vs safety**.

---

## Shared Memory

A region of memory that both processes can read/write directly.

- Kernel involved **once at setup** (`shm_open()` system call), then **no kernel involvement** for data exchange
- Fast — just regular memory reads/writes
- Dangerous — if both processes access at the same time, [[Synchronization|race conditions]] occur
- This is why the [[Classic Sync Problems|Producer-Consumer Problem]] needs [[Synchronization Tools#Mutex Locks|mutex locks]] and [[Synchronization Tools#Semaphores|semaphores]]

**Analogy:** Two coworkers sharing a whiteboard. Fast to use, but if both write at the same time, you get a mess.

---

## Message Passing

Processes send/receive discrete messages through the kernel.

- **Every** `send()` and `receive()` is a system call — kernel copies data between address spaces
- Slower — two system calls and two memory copies per message
- Safer — no shared state to corrupt
- Works **across networks** (processes don't need to be on the same machine)

**Analogy:** Mailing letters. Every letter goes through the post office (kernel).

---

## Comparison (Exam-Ready)

| | Shared Memory | Message Passing |
|--|---------------|-----------------|
| Speed | Fast (no kernel per exchange) | Slower (kernel on every send/receive) |
| Safety | Must handle [[Synchronization]] yourself | OS handles data transfer, no shared state |
| Kernel calls | Once at setup | Every message |
| Network | Same machine only | Works across machines |

---

## Synchronization in Message Passing

Blocking vs Non-blocking determines how send/receive behave:
- **Blocking send** — sender waits until message is received
- **Blocking receive** — receiver waits until message is available
- If BOTH are blocking → **rendezvous** (both must be present for hand-off)

Rendezvous is NOT [[process-management|deadlock]] — it's **intentional** and **resolves itself** when both sides show up. Deadlock is circular and permanent.

---

## Buffering

Queue of messages attached to a link. Three capacities:
1. **Zero** — no buffer, sender always waits → rendezvous
2. **Bounded** — finite queue of n messages, sender waits when full
3. **Unbounded** — infinite queue, sender never waits

Pattern: as buffer size increases, sender gets more freedom.

Connects to: [[Producer-Consumer Problem]] uses the same bounded buffer concept, but in shared memory **you** manage the buffer logic instead of the kernel.

---

## Mechanisms

- [[Sockets]] — for communication across networks (IP + port)
- [[ordinary-pipes|Ordinary Pipes]] — local, unidirectional, requires parent-child relationship, disappear when processes terminate
- Named Pipes — local, bidirectional, no parent-child needed, persist after processes finish

**When to use pipes vs sockets:** Pipes for local related processes. Sockets when processes are on different machines.
