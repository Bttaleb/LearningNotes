---
tags:
  - concurrency
  - performance
source: "OS Class (Jan 2026)"
description: "Evolution: Batch → Multiprogramming → Time-Sharing"
---

# Execution Models


## Multiprogramming (Batch Systems)

> Keep the CPU busy by switching jobs during I/O waits

### Why It Was Created

**Problem:** Early computers were expensive, but components sat idle most of the time.

**Solution:** Keep multiple jobs in memory, switch between them.

e### Program Execution Flow

```
Disk (exe file)
     ↓  [load]
Main Memory (program loaded)
     ↓  [execute]
CPU (one instruction at a time)
```

### The Key Innovation

| Without Multiprogramming | With Multiprogramming |
|--------------------------|----------------------|
| Job waits for I/O → CPU sits idle | Job waits for I/O → CPU switches to another job |
| One job at a time | Multiple jobs in memory |
| Low CPU utilization | High CPU utilization |

### Execution Pattern

```
Job A: [run]──[I/O wait]─────────────[run]──[done]
Job B:        [run]──[I/O wait]──[run]──[done]
Job C:               [run]──────────────[run]
       ─────────────────────────────────────────→ time
              CPU never idle if jobs available
```

**Goal:** Keep ALL components busy — CPU *and* I/O devices working in parallel.

---

## Time-Sharing

> Multiprogramming + fast response time for interactive use

### Batch vs Time-Sharing

| Aspect | Batch | Time-Sharing |
|--------|-------|--------------|
| Interaction | None — all inputs upfront | Interactive — user waits for response |
| Response time | Doesn't matter | < 1 second (ideally < 100ms) |
| Example | Midnight backup | Terminal session, text editor |

### What Time-Sharing Adds

1. **Response time goal** — user shouldn't notice delay
2. **Time slices** — each job gets a small window to run
3. **CPU scheduling** — decides which job runs next

### Execution Pattern

```
Job 1: [run]──[time up]
Job 2:        [run]──[time up]
Job 3:               [run]──[finishes early]
Job 1:                      [run]──[time up]
       ─────────────────────────────────────→ time
       Each job gets fair share of CPU
```

A job either:
- Finishes before time slice expires
- Gets preempted and waits for next turn

---

## Key Insight

The CPU is fast; I/O is slow. Instead of waiting, do something else.

This is the foundation of:
- Modern process scheduling
- Async programming patterns
