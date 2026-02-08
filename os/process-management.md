---
tags:
  - concurrency
  - state
source: "OS Class (Jan 2026)"
description: "OS manages processes and threads executing on the system"
---

# Process Management


## Key Terms

| Term | Definition |
|------|------------|
| **Program** | Passive entity — code sitting on disk |
| **Process** | Active entity — program in execution, unit of work |
| **Thread** | Execution path within a process |

A process has at least one thread. Multiple threads share the same process memory.

---

## Program Counter

Each thread has a **program counter (PC)** — points to the next instruction to execute.

```
Thread A: PC → instruction 42
Thread B: PC → instruction 17
```

---

## Concurrency

System runs many processes (user + OS) concurrently across one or more CPUs.

**How:** Multiplexing — rapidly switching CPU among processes/threads (see [[os-time-sharing]]).

---

## Deadlock

When two or more processes are waiting for resources held by each other — nobody can proceed.

**Example:**
```
2 people, 1 pencil, 1 paper
"On count of 3, grab resources and write"

Person A grabs paper
Person B grabs pencil

→ Deadlock: neither can write
```

Both hold one resource, need the other, won't release what they have.
