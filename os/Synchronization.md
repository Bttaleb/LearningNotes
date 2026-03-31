---
tags:
  - concurrency
  - state
source: "OS Class (Jan 2026)"
description: "Race conditions, critical sections, and solutions — the core of Ch 5"
date: 2026-01-20
---
## Shared Data
- Shared var
- Shared file
- DB table

Producer
```
while (true) {
/* produce an item in next produced */

	while (counter == BUFFER_SIZE);
	/* do nothing */
	buffer[in] = next_produced;
	in = (in + 1) % BUFFER_SIZE;
	counter++;
}
```

Consumer

A “counter” could be implemented as
```
Register1 = counter
Register1 = register1 + 1
Counter = register1
```

Critical Section
- General structure of process P<sub>i</sub>
```
do {
	[entry section]
		critical section
	[exit section]
		remainder section
} while (true);
```


# Solutions to Critical-Section Problem
1. <mark style="background:#b1ffff">Mutual Exclusion</mark> - process P<sub>i</sub> is executing in its critical section, NO OTHER PROCESSES can be executing in THEIR critical section
2. <mark style="background:#b1ffff">Progress</mark> - if NO process is in critical section, processes wishing to enter cannot be postponed indefinitely
3. <mark style="background:#b1ffff">Bounded Waiting</mark> - Must be strict limit on how many times other processes can enter critical sections after a process request(will/could one of the processes wait for an unlimited time?)

See [[Atomic Hardware Instructions]] for how test_and_set and compare_and_swap satisfy these, and the bounded-waiting solution that guarantees all three.

Higher-level tools built on these: [[Mutex Locks]], [[Semaphores]]
Classic problems using them: [[Producer-Consumer Problem]], [[Readers-Writers Problem]], [[Dining Philosophers]]

ANYTIME YOU ACCESS SHARED DATA, YOU MUST PUT IT IN A <mark style="background:rgba(240, 200, 0, 0.2)">CRITICAL SECTION</mark> (with entry and exit)
	- When you use the bathroom, you go inside (lock), use the bathroom, exit (unlock)

# Critical-Section Handling in OS 
	(is a solution a valid solution?)
2 approaches depending on if kernel is preemptive or non-preemptive
1. <mark style="background:#b1ffff">Preemptive</mark> - allows preemption of process when running in kernel mode
2. <mark style="background:#b1ffff">Non-preemptive</mark> - runs until exits kernel mode, blocks, or voluntarily yields CPU

**Atomic** - cannot be interrupted

### Peterson’s Solution
Requirements: 2 processes share 2 variables
- int turn;
- Boolean flag[2]
“Turn” indicates who’s turn to enter the **critical section**
	If (turn == i), then P<sub>i</sub> can enter critical section
“Flag” array indicates if process is READY to enter critical section
	Flag[i] = true -> P<sub>i</sub> is ready

### Algorithm for Process P<sub>i</sub>
```
do {
	flag[i] = true;
	turn = j;
	while (flag[j] && turn == j);
		[critical section]
	flag[i] = false;
		[remainder section]
} while (true);
```

1. Mutual exclusion - Satisfied
	P<sub>i</sub> enters **critical section** ONLY if
	- flag[j] = false 
		OR 
	- turn = i
2. Progress - Satisfied
3. Bounded Waiting requirement met