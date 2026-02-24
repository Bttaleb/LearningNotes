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


# Definitions
<mark style="background:#b1ffff">Mutual Exclusion</mark> - process P<sub>i</sub> is executing in its critical section, NO OTHER PROCESSES can be executing in THEIR critical section
<mark style="background:#b1ffff">Progress</mark> - There is NOT a process executing in its critical section AND there exist some processes that wants to enter their critical section, THEN the selection of the processes that enter critical section next CANNOT be postponed indefinitely
<mark style="background:#b1ffff">Bounded Waiting</mark> - A bound MUST exist on the # of times other processes are allowed t