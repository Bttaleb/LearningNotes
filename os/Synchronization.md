---
tags:
source: Chapter 5
description: ""
date: January 20, 2026
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
<mark style="background:#b1ffff">Mutual Exclusion</mark> - process P<sub>i</sub> is executing in its critical section, NO OTHER PROCESSES can be executing in THEIR critical section
<mark style="background:#b1ffff">Progress</mark> - There is NOT a process executing in its critical section AND there exist some processes that wants to enter their critical section, THEN the selection of the processes that enter critical section next CANNOT be postponed indefinitely
<mark style="background:#b1ffff">Bounded Waiting</mark> - A bound MUST exist on the # of times other processes are allowed to enter their critical sections AFTER process makes request to enter critical section and BEFORE that request is granted

ANYTIME YOU ACCESS SHARED DATA, YOU MUST PUT IT IN A <mark style="background:rgba(240, 200, 0, 0.2)">CRITICAL SECTION</mark> (with entry and exit)
	- When you use the bathroom, you go inside (lock), use the bathroom, exit (unlock)

# Critical-Section Handling in OS
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