---
source: OS Class (Jan 2026)
date: 2026-03-03
---


**Overarching Concept**
CPU Scheduling
- traffic control system (juggling multiple tasks)

Problems
- limited processing power
- decide what gets your attention and when

A process's <font color="#00b050">life</font> inside a computer is **essentially** bouncing back and forth between 2 distinct states (<font color="#92cddc">CPU I/O Burst Cycle</font>)
	1. Process is executing on CPU (CPU Burst)
	2. Waiting for some input/output (I/O Burst) 

POV: you're in a kitchen
CPU Burst - Period where the chef is actively chopping vegetables, searing meat, and plating a dish (Undivided attention, processing power)
I/O Burst - Pot of stock on the back burner, waiting 3 hours for it to simmer (not actively doing anything to the stock)

First-Come, First-Served (FCFS) Scheduling

Process  |   Burst Time
P<sub>1</sub>                   24
P<sub>2</sub>                   3
P<sub>3</sub>                   3

Suppose processes arrive in order:  P<sub>1</sub> , P<sub>2</sub> , P<sub>3</sub> 
Gantt Chart for schedule is
[                 P<sub>1</sub>                         |       P<sub>2</sub>      |     P<sub>3</sub>    ]
0					                         24              27          30

![[Symmetric-Asymmetric Processes]]

For real-time scheduling, scheduler MUST be
1. Preemptive
2. Priority based

Hard real-time processes MUST be able to meet deadlines
 
 0 <= t (time) <= d (deadline) < = p (period)
 Rate of periodic task = 1/p

Rate Monotonic Schedulling
Longer period - short priority
Short period - longer 