---
tags:
  - memory
  - processes
  - buffering
source: OS Class (Jan 2026)
description: ""
date: 2026-02-12
---

Message passing
Shared memory

Interprocess Communication

### Synchronization
	Blocking <—> Non-blocking
Blocking: Synchronous
	- Blocking send — sender is blocked until message is received
	- Blocking receive — receiver is blocked until message is available (NOT SENT!)
Non-blocking: Asynchronous
	- Non-blocking send — sender sends message and continue
	- Non-blocking receive — receiver receives :
						- Valid message
						- Null message

Different combinations are made possible with <mark style="background:#fff88f">synchronization</mark>, if both send AND receive are blocking, we have a #rendezvous

### Buffering
- Queue of messages attached to a link
- 3 ways of implementation
	1. Zero - capacity — <font color="#ff0000">no</font> messages are queued on a link (sender must wait for receiver #rendezvous )
	2. Bounded-capacity — <font color="#ffc000">FINITE</font> length of ***n*** messages (sender must wait if link == full)
	3. Unbounded-capacity — <font color="#00b050">INFINITE</font> length (sender never waits)

### IPC Systems - POSIX
POSIX Shared Memory
Shared memory segment is created first

shm_fd = shm_open(name, O_CREATE | O_RDWR, 0666);
