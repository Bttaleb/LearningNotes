---
tags:
  - concurrency
  - performance
source: "OS Class (Jan 2026)"
description: "CPU scheduling algorithms, multiprocessor, realtime, and algorithm evaluation"
date: 2026-03-24
---

# CPU Scheduling

A process bounces between CPU bursts (executing) and I/O bursts (waiting). The scheduler decides **who gets the CPU next** when it's free.

---

## When Does Scheduling Happen?

Four situations:
1. Running → Waiting (I/O request)
2. Running → Ready (**preempted**)
3. Waiting → Ready (I/O complete)
4. Process terminates

**Non-preemptive:** Only at 1 and 4. Process keeps CPU until done or blocked.
**Preemptive:** All four. Scheduler can yank CPU away. Creates [[Synchronization]] issues — process might be mid-update on shared data.

Preemptive exists because you **can't trust every process to give up the CPU in time**. One long process would make the whole system unresponsive. That's why preemptive scheduling is why you need [[Synchronization Tools#Mutex Locks|mutex locks]] and [[Synchronization Tools#Semaphores|semaphores]].

---

## Five Criteria

- **CPU utilization** — keep CPU busy
- **Throughput** — processes completed per time unit
- **Turnaround time** = Completion − Arrival (total time in system)
- **Waiting time** = Turnaround − Burst (time doing nothing in ready queue)
- **Response time** = time until first response

---

## The Algorithm Ladder

Each fixes a problem the previous one created:

### FCFS (First Come First Served)
Non-preemptive. Run in arrival order. Simple but **convoy effect** — short jobs stuck behind long ones.

### SJF (Shortest Job First)
Non-preemptive. Pick shortest burst from ready queue. Optimal avg waiting for non-preemptive. Requires knowing burst time in advance.

### SRTF (Shortest Remaining Time First)
**Preemptive SJF.** At every new arrival, check: does new process have shorter remaining time than current? If yes, preempt. Optimal overall but causes **starvation** for long jobs.

**Tracking method for Gantt charts:** R(Pᵢ, T) = B(Pᵢ) − (time Pᵢ has spent on CPU). At each decision point, run `argmin{R}` among arrived, unfinished processes.

### Priority Scheduling
Each process gets a priority. Highest runs first. Risk: **starvation** — low priority never runs. Fix: **aging** (increase priority over time).

### Round Robin (RR)
Everyone gets a **time quantum**, rotate through ready queue. Fair — no starvation. Quantum too small = constant switching overhead. Too large = becomes FCFS.

Process finishes early? Releases CPU immediately. Quantum is a **maximum**, not fixed.

### Multilevel Queue (MLQ)
Multiple queues (e.g., interactive=RR, batch=FCFS). Process permanently assigned to one queue. Problem: **rigid** — can't adapt.

### Multilevel Feedback Queue (MLFQ)
Same as MLQ but processes **move between queues** based on behavior. Use full quantum → demoted (CPU-heavy). Give up CPU early → stay/promoted (interactive). Self-adjusting. Most flexible, most complex.

---

## Thread Scheduling

**PCS (Process Contention Scope)** — threads compete within the same process. User-level library decides. Kernel doesn't see individual threads. Used with [[Multithreaded Programming|user threads]].

**SCS (System Contention Scope)** — threads compete across ALL processes. Kernel schedules directly. Used with [[Multithreaded Programming|kernel threads]].

### pthread APIs
- `SCHED_FIFO` — realtime FCFS within same priority. No quantum. Runs until done/blocked/preempted by higher priority.
- `SCHED_RR` — realtime Round Robin within same priority. Time quantum for equal-priority threads.
- `SCHED_OTHER` — default non-realtime time-sharing.

Both realtime policies require SCS (`PTHREAD_SCOPE_SYSTEM`).

---

## Multiprocessor Scheduling

**Symmetric (SMP)** — all CPUs are equal, each can schedule independently. Modern standard.
**Asymmetric** — one boss CPU makes all decisions. Simple but bottleneck.

**Processor Affinity** — keep process on same CPU for cache benefits.
- Soft = OS tries but doesn't guarantee
- Hard = locked to specific CPU

**NUMA** — memory architecture where each CPU has fast local memory and slow remote memory. NOT a scheduling algorithm — it's the hardware reality. Affinity is the scheduling strategy to deal with it. Without affinity on NUMA, process bounces between CPUs but its data stays put → slow remote memory access on every operation.

**Load Balancing** — distribute work evenly across CPUs.
- Push migration: system task moves processes from overloaded CPU
- Pull migration: idle CPU grabs work from busy CPU
- Tension with affinity: balancing wants to move, affinity wants to stay

---

## Realtime Scheduling

**Soft real-time** — try to meet deadlines, degraded quality if missed (video streaming).
**Hard real-time** — deadlines are absolute, missing = catastrophic (pacemaker).

Periodic tasks: `0 ≤ t (burst) ≤ d (deadline) ≤ p (period)`

### Rate Monotonic (RM)
**Static** priority. Shorter period = higher priority (runs more often = more important). Never changes.
- Utilization bound: `n(2^(1/n) - 1)`. For 2 tasks ≈ 82.8%.
- Below bound = guaranteed. Above = might work, might not.

### Earliest Deadline First (EDF)
**Dynamic** priority. Closest deadline = highest priority. Changes constantly.
- Can handle up to **100%** utilization theoretically.
- **Optimal** — if any algorithm can meet all deadlines, EDF can.
- More complex to implement than RM.

### Gantt Chart Method (Exam)
Build a table at each decision point:

```
Time | Event            | Running | R(T1) | R(T2) | Deadline Check
```

List arrival times first (multiples of each period). At each row: who arrived/finished? Who has highest priority? Update remaining times. Draw Gantt from Running column.

---

## Algorithm Evaluation

Four methods, accuracy vs cost spectrum:

1. **Deterministic** — trace specific processes, compare results. Simple, exact, but only valid for that workload.
2. **Queuing Models** — mathematical formulas. Little's Law: **n = λ × W**. General but requires assumptions.
3. **Simulations** — computer model with random/trace data. Realistic but expensive to build.
4. **Implementation** — deploy in real OS. Most accurate but most expensive.
