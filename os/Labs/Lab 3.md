---
tags:
  - producer/consumer
  - sychronization
source: OS Class (Jan 2026)
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

Real World Analogy
- Every car entering (wait) reduced the sign by 1
- Ever car leaving (post) increases the sign by 1
- IF sign reads 0, cars have to wait in line until someone leave

## Semaphore vs Mutex
- Semaphore allows multiple threads through
- Mutex allows one at a time (bathroom lock)

Producer MUST do three things (<font color="#d83931">Does order matter?</font>)
1. <mark style="background:#fff88f"> Wait on empty </mark> semaphore
2. <mark style="background:#ff4d4f"> Lock the mutex </mark>
3. <mark style="background:rgba(205, 244, 105, 0.55)"> Insert the item, unlock mutex, signal full </mark>
<font color="#d83931">ABSOLUTELY</font>

## Deadlock can occur if the system is out of order
1. Buffer <font color="#00b050">FULL</font> (5 slots taken)
2. Producer <font color="#ff0000">LOCKS MUTEX</font>
3. Producer calls <mark style="background:#fff88f"> sem_wait </mark> (empty) -> but empty = 0, producer goes to sleep while holding mutex
4. Consumer wants to remove (must lock mutex to remove item) but producer is holding it and sleeping!
5. Consumer can never remove an item -> empty never gets signaled -> producer never wakes up

# GOLDEN RULE
ALWAYS wait on the semaphore before grabbing mutex (why?)
- You never hold the mutex while sleeping

```
sem_wait(&full);              // 1. Wait — is there an item to take?
pthread_mutex_lock(&mutex);    // 2. Lock — I need exclusive access
// remove item from buffer        // 3. Do the work
pthread_mutex_unlock(&mutex);  // 4. Unlock — others can access now
sem_post(&empty);              // 5. Signal — I freed up a slot
```

| buffer | [____] | [____] | [____] | [____] | [____] | [____] |
| ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| index  | 0      | 1      | 2      | 3      | 4      | 5      |

What is the index of "in" and "out" if a producer inserts 3 items and a consumer removes 1?
Index of "in" is 3
Index of "out" is 1

**Two Variables**
1. <font color="#00b050">In</font> (points to where NEXT item is INSERTED)
2. <font color="#d83931">Out</font> (points to where NEXT item gets REMOVED)
```
PRODUCER:
buffer[in] = item;
in = (in + 1) % BUFFER_SIZE

CONSUMER:
*item = buffer[out];
out = (out + 1) % BUFFER_SIZE
```
