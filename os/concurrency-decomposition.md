---
tags:
  - concurrency
  - async
  - data-flow
  - architecture
source: "Claude code-learn session (Oct 2026)"
description: "Using threads, IPC, and producer-consumer as design questions for breaking down any system"
---

# Decomposing Problems with Concurrency Thinking

> OS concepts aren't just kernel mechanisms. Each one answers a design question you can ask about any system.

## The Four Design Questions
1. **What are the independent units of work?** → threads / processes ([[process-management]])
2. **What do they share, or what do they pass?** → shared memory vs IPC
3. **Who waits on whom?** → blocking, deadlock when the waiting is circular
4. **What must happen in a specific order?** → synchronization

## Threads on a Single Core → "Where does my program wait?"
- One core can't run two things at once, so threads there **overlap waiting**, not computing
- Same idea as [[multiprogramming]]: switch work during I/O waits ([[execution-models]])
- Concurrency = structuring work as independent tasks. Parallelism = actually running simultaneously
- I/O-bound steps benefit from concurrency even on one core. CPU-bound steps don't
- Swift `async/await`: a suspended task yields the thread while it waits

## IPC → "Where are my boundaries, and what crosses them?"
- Processes don't share memory, so they must communicate explicitly (pipes, sockets, queues, messages)
- That constraint forces clear components with clear interfaces
- Shows up as: client/server, Unix pipelines (`cat | grep | sort`), Swift actors

## Worked Example: Chat App (network → database → UI)

### 1. Units of work are the verbs, not the data
- Receive, save, update UI
- A message is **data**. It flows *between* workers, like a message through a pipe
- Echoes [[data-vs-behavior]]: separate what moves from what acts on it

### 2. Producer–Consumer
- Receiver = producer, saver = consumer, **queue** = buffer between them
- The queue decouples a fast producer (network) from a slow consumer (disk)
- **Signaling**: the consumer sleeps until notified, instead of busy-waiting (semaphore / condition variable; `AsyncStream` in Swift)
- **Bounded buffer**: an unbounded queue eventually runs out of memory. When full, choose:
	- Backpressure: make the producer wait
	- Drop: bad for chat, fine for live sensor data
	- Batch: one DB transaction for many messages makes the consumer faster

### 3. Race Conditions and Critical Sections
- The queue is shared, so simultaneous access can corrupt it (lost update: both read `count = 5`, one writes 6, the other writes 4)
- Fix: mutual exclusion, but **lock only the critical section**
	- Receiver: lock → append → unlock
	- Saver: lock → remove → unlock → *then* write to DB
- Locking until the saver finishes saving re-couples the workers and defeats the queue
- Rule: keep critical sections tiny and never do I/O while holding a lock
- Swift `actor` gives mutual exclusion built into the type system

```swift
actor MessageQueue {
    private var items: [Message] = []
    func push(_ m: Message) { items.append(m) }   // critical section
    func pop() -> Message? { items.isEmpty ? nil : items.removeFirst() }
}
// saver: let m = await queue.pop() → write to DB outside the actor
```

### 4. Ordering: Save-then-Show vs Show-then-Save
| Choice | Protects | Costs |
|---|---|---|
| Save → show | Consistency, durability (UI never shows unsaved data) | Latency under bursts |
| Show → save (optimistic UI) | Responsiveness | Must reconcile failures ("sending…", retry) |

- Save-first is the same principle as write-ahead logging: make it durable, then announce it
- Neither is right in general. The skill is naming the tradeoff

## Key Takeaways
- Look for the hidden queue. Most systems have one
- Same pattern at every level: multiple actors + a coordination mechanism ([[clustered-systems]])

## Revisit Cues
- ~3 days: Why does threading help a network-bound task on one core but not an image resize?
- ~1 week: Write the lost-update race on a shared `count` and explain how a lock prevents it
- ~2 weeks: Build an image pipeline (fetch 20 URLs → resize → save) sequential, then concurrent, then producer–consumer. Time each
