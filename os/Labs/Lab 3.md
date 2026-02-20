---
tags:
  - producer/consumer
  - sychronization
source: ""
description: ""
date: 2026-02-20
---


#Semaphore a counter with special rules
- holds an integer value
- can do 2 operations: wait & signal
	in pthreads: sem_wait, sem_post

sem_wait - "Can I go?"
1. counter > 0 -> decrements the counter, then proceed
2. counter = 0 -> thread blocks (sleeps), until raised
sem_post - "Im done, someone else can go"
-  increments counter by 1
- if ANY thread was sleeping waiting on it, wake one of them up

