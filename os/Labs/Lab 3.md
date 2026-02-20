---
tags:
  - producer/consumer
  - sychronization
source: ""
description: ""
date: 2026-02-20
---


## Semaphore 
	a counter with special rules
- <font color="#00b0f0">holds an integer value</font>
- can do 2 operations: wait & signal
	in pthreads: sem_wait, sem_post

---

3 Types of semaphores
1. <font color="#00b050">full</font> -> how many items are in the buffer (consumer waits on this)
2. <font color="#ff0000">empty</font> -> how many empty slots remain? (producer waits on this)
3. <font color="#de7802">mutex</font> -> prevents two threads from touching buffer array at the same time

<mark style="background:#fff88f"> sem_wait </mark> - "Can I go?"
4. counter > 0 -> decrements the counter, then proceed
5. counter = 0 -> thread blocks (sleeps), until raised
<mark style="background:#fff88f"> sem_post </mark> - "Im done, someone else can go"
-  increments counter by 1
- if ANY thread was sleeping waiting on it, wake one of them up

