---
tags:
  - architecture
  - data-flow
source: "Cross-domain reference"
description: "Maps abstract CS/OS concepts to real-world applications and coding patterns"
---

# Bridges — Theory to Practice

> Every concept you learn in class shows up somewhere in real software. This file collects those connections.

---

## Automata & Formal Languages

### DFA → Input Validation & UI State Machines
**Concept:** [[dfa]] — deterministic transitions, one path per input, accept/reject

**In practice:**
- **Regex engines** are DFAs under the hood. When you write `^\d{3}-\d{2}-\d{4}$` to validate an SSN, the regex compiler builds a DFA that walks through each character with deterministic transitions — exactly like the state diagrams you draw in class
- **UI navigation** — think of your SafeZone app's tab bar. Each screen is a state, each button tap is an input symbol. From the Dashboard (state), tapping "Tutors" (input) always takes you to TutorListView (next state). Deterministic, no ambiguity
- **Network protocols** — TCP connection states (LISTEN → SYN_RECEIVED → ESTABLISHED → CLOSE_WAIT) are a DFA. Each packet type is an input that moves the connection to exactly one next state

**Why it matters:** Anytime you have a fixed set of states and predictable transitions, you're implementing a DFA whether you know it or not.

---

### NFA → Pattern Matching & Backtracking
**Concept:** [[NFA]] — multiple possible transitions per input, nondeterministic

**In practice:**
- **Grep/search** — when you search for a pattern with wildcards, the engine explores multiple paths simultaneously (or backtracks), just like an NFA
- **Autocomplete** — as you type, the system considers multiple possible completions at each character. Each keystroke narrows the possibilities, like an NFA resolving paths

**Why it matters:** NFAs model problems where you have to explore multiple possibilities before knowing the answer — that's backtracking algorithms, search, and AI decision trees.

**Practice exercise:** `c_state_machines/01_dfa_validator/` — turn a DFA diagram directly into a transition table array and a switch statement.

---

### PDA → Stack-Based Parsing & Code Structure
**Concept:** Pushdown Automata — a DFA with a stack for memory

**In practice:**
- **Compilers and interpreters** — when your Java compiler checks that every `{` has a matching `}`, it's using a PDA. Push on open brace, pop on close. If the stack is empty at the end, it's valid
- **Undo/Redo** — every text editor uses a stack. Each action pushes onto the undo stack. Ctrl+Z pops it off and pushes onto the redo stack. That's a PDA managing nested state
- **Function call stack** — when `main()` calls `setName()` which calls `this.name = name`, each call pushes a frame. When each returns, it pops. Recursion is literally a PDA — and stack overflow means you pushed more than memory allows
- **HTML/XML parsing** — `<div><p></p></div>` is a context-free language. A PDA validates nesting by pushing open tags and popping matching close tags

**Why it matters:** Any time you see nested structure (brackets, function calls, undo history), there's a PDA concept underneath. If you can recognize "this is a stack problem," you jump straight to the right data structure.

**Practice exercises:** `c_state_machines/03_lexer/` (DFA tokenizer) and `c_state_machines/04_pda_bracket_checker/` (PDA with explicit stack).

---

## Operating Systems

### Mutex → Protecting Shared Resources
**Concept:** [[Synchronization Tools]] — mutual exclusion, one thread at a time

**In practice:**
- **Database row locks** — when two users try to edit the same record, the database uses a mutex. First transaction locks the row, second waits. Without this, you get corrupted data (same race condition as your `race_condition.c` exercise)
- **File systems** — when you save a file in two apps simultaneously, the OS locks the file. That's why you sometimes see "file is in use by another program"
- **Banking transactions** — withdrawing from an ATM while a deposit processes. The account balance is the shared variable, each transaction needs exclusive access. Exactly like your `bank_simulation.c`

**Why it matters:** Any shared resource that can't handle simultaneous writes needs a mutex. Databases, files, hardware — the pattern is identical to what you coded in C.

---

### Semaphore → Rate Limiting & Connection Pools
**Concept:** [[Synchronization Tools]] — counting semaphore, N threads at a time

**In practice:**
- **Database connection pools** — a server has 10 database connections. Each request takes one (sem_wait), uses it, returns it (sem_post). Request #11 waits. This is your parking lot exercise scaled up
- **API rate limiting** — "100 requests per minute" is a semaphore initialized to 100. Each request decrements, a timer resets it
- **Thread pools** — Java's `ExecutorService` with a fixed pool of 4 threads is a semaphore(4). Submit 10 tasks, 4 run, 6 wait

**Why it matters:** Semaphores appear whenever you have a limited resource shared among many consumers. Recognizing this pattern saves you from reinventing it.

---

### Page Tables → Memory Debugging & Virtual Memory
**Concept:** [[Chapter 8 Main Memory]] — virtual-to-physical address translation

**In practice:**
- **Segfault debugging** — a crash at address `0x00000008` means page 0, offset 8. Page 0 is unmapped → null pointer dereference. The address split tells you exactly what went wrong
- **Memory-mapped files** — when you open a large file, the OS doesn't load it all. It maps pages of the file to virtual addresses. Read page 5? The OS loads just that 4KB chunk from disk
- **Copy-on-write (fork)** — when a process forks, both share the same physical pages. Only when one writes does the OS copy that page. The page table tracks which pages are shared vs. private

**Why it matters:** Understanding the split between page number and offset turns memory errors from mysterious crashes into diagnosable problems.

---

### Process Scheduling → Task Queues & Load Balancing
**Concept:** [[Chapter 6 - CPU Scheduling]] — deciding which process runs next

**In practice:**
- **Web server request handling** — Nginx/Apache deciding which request to process next uses scheduling algorithms. Round Robin = each request gets equal time. Priority = premium users served first
- **Thread pools in your SafeZone app** — when multiple users book tutors simultaneously, the server queues requests. The scheduling algorithm decides order
- **CI/CD pipelines** — GitHub Actions has limited runners. Your build jobs queue up and get scheduled across available runners, just like processes competing for CPU

**Why it matters:** Every system that serves multiple users/tasks is running a scheduling algorithm. The tradeoffs you learn (throughput vs. latency, fairness vs. priority) apply everywhere.

---

### Producer-Consumer → Everywhere in Software
**Concept:** [[Classic Sync Problems]] — bounded buffer with mutex + semaphores

**In practice:**
- **Message queues (Kafka, RabbitMQ)** — producers publish events, consumers process them, the queue is the bounded buffer. If the queue fills up, producers block. If it's empty, consumers wait
- **Logging** — your app produces log entries, a background thread consumes and writes them to disk. This prevents logging from slowing down your main thread
- **Video streaming** — the network downloads chunks (producer), the video player consumes them (consumer). The buffer is why you can pause and still have video to play

**Why it matters:** This is the single most common concurrency pattern in professional software. If you understand `producer_consumer.c`, you understand Kafka.

---

## Software Engineering

### Encapsulation → API Design
**Concept:** Private fields + public methods (your Java assignment)

**In practice:**
- **REST APIs** — the database is "private," the API endpoints are "public methods." Users can't touch the database directly, they go through `/api/users` (the getter) and `/api/users` POST (the setter)
- **Your SafeZone Supabase setup** — the database tables are hidden behind `SupabaseAuthService` and `TutorService`. Views never query the database directly — they go through the service layer (the public methods)

**Why it matters:** The Student class pattern (private data, public getters/setters) scales to entire systems. It's the same principle whether it's a class, a module, or a microservice.

---

### Inheritance → Code Reuse Hierarchies
**Concept:** Person → Student/Teacher (your Java assignment)

**In practice:**
- **UI components** — in your SafeZone app, `WSUBadge`, `WSUHeader`, `WSUEmptyState` could all inherit from a base `WSUComponent` with shared styling. Each adds its own behavior
- **Error handling** — `IOException`, `FileNotFoundException`, `SocketException` all extend a base `Exception` class. You catch the parent to handle all of them, or the child to handle one specific type

**Why it matters:** Whenever you see "these things share some properties but differ in others," that's inheritance. Recognizing it saves you from duplicating code.
