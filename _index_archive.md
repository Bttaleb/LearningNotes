# Learning Notes Index

> **Last Updated:** 2026-02-01 (theory/dfa-implementation.md added)
> **Purpose:** Map concepts across all learning sources to build connected knowledge
> **See also:** [User Guide](_guide.md) — Full command reference and workflows

---

## How This System Works

### Folder Structure
Notes are organized by domain in subfolders:
```
LearningNotes/
├── _index.md          ← This file
├── _guide.md          ← User guide
├── arch/              ← Architecture/Design Patterns
├── os/                ← Operating Systems
├── swift/             ← Swift/iOS
└── [domain]/          ← Future domains
```

### Naming Convention
Files are named by **topic**, organized in domain folders:
```
[domain]/[topic].md
```

**Examples:**
- `os/memory.md` (not `2026-01-20-os-memory.md`)
- `os/execution-models.md` (not `cs340-lecture5.md`)

### Domains

| Domain | Folder | Covers |
|--------|--------|--------|
| Operating Systems | `os/` | Processes, memory, scheduling, filesystems |
| Swift/iOS | `swift/` | SwiftUI, UIKit, iOS APIs, AVKit, Xcode |
| Databases | `db/` | SQL, NoSQL, indexing, transactions, Supabase |
| Networking | `net/` | HTTP, TCP/IP, APIs, sockets |
| Architecture | `arch/` | Design patterns, system design, clean code |
| Algorithms | `algo/` | Data structures, complexity, problem-solving |
| Web | `web/` | HTML, CSS, JS, frontend frameworks |
| Tools | `tools/` | Git, CLI, debugging, IDEs |
| Theoretical CS | `theory/` | Automata, computability, complexity theory |

### Core Concepts (Cross-Domain Tags)

| Concept | Description | Appears In |
|---------|-------------|------------|
| `#state` | Managing and synchronizing state | swift-supabase-integration, os/process-management |
| `#concurrency` | Parallel execution, race conditions, synchronization | os/execution-models, os/clustered-systems, os/process-management |
| `#data-flow` | How data moves through a system | swift-supabase-integration, arch/data-vs-behavior |
| `#error-handling` | Catching, propagating, recovering from errors | swift-supabase-integration |
| `#crud` | Create, Read, Update, Delete patterns | swift-supabase-integration |
| `#ui-patterns` | Reusable interface patterns | swift-supabase-integration |
| `#debugging` | Finding and fixing issues | swift-supabase-integration |
| `#architecture` | System design, scaling, infrastructure | os/clustered-systems, arch/data-vs-behavior |
| `#performance` | Efficiency, utilization, optimization | os/execution-models |
| `#memory` | Memory management, allocation, protection | os/memory |
| `#security` | Protection, isolation, access control | os/memory, os/dual-mode |
| `#media` | Video, audio, image handling | swift/video-aspect-ratio |
| `#async` | Asynchronous operations, async/await | swift/video-aspect-ratio |
| `#automata` | Finite state machines, DFAs, NFAs, regex | theory/dfa, theory/dfa-implementation |
| `#computation` | Models of computation, decidability | theory/dfa, theory/dfa-implementation |

---

## File Registry

### os/clustered-systems.md
- **Concepts:** `#concurrency` `#architecture`
- **Topics:** Clustered vs distributed systems, asymmetric/symmetric clustering, shared resources, Distributed Lock Manager (DLM), high availability
- **Source:** OS Class (Jan 2026)

### os/execution-models.md
- **Concepts:** `#concurrency` `#performance`
- **Topics:** Batch → Multiprogramming → Time-sharing evolution, CPU utilization, I/O switching, time slices, preemption
- **Source:** OS Class (Jan 2026)
- **Merged from:** os-multiprogramming.md, os-time-sharing.md

### os/memory.md
- **Concepts:** `#memory` `#security` `#performance`
- **Topics:** Memory management activities, allocation/deallocation, protection, segmentation faults, locality of reference, caching, temporal/spatial locality
- **Source:** OS Class (Jan 2026)

### os/dual-mode.md
- **Concepts:** `#security` `#architecture`
- **Topics:** Kernel vs user mode, mode bit, status registers, timers, system calls, hardware-enforced protection
- **Source:** OS Class (Jan 2026)

### os/process-management.md
- **Concepts:** `#concurrency` `#state`
- **Topics:** Process vs program, threads, program counter, multiplexing, deadlock
- **Source:** OS Class (Jan 2026)

### swift/supabase-integration.md
- **Concepts:** `#state` `#data-flow` `#error-handling` `#crud` `#ui-patterns` `#debugging`
- **Topics:** Service architecture, navigation patterns, RLS, state management (@State/@Binding/@Observable), ViewModifiers, previews
- **Source:** saraBeauty1.0 project (Jan 2026)

### swift/video-aspect-ratio.md
- **Concepts:** `#media` `#async` `#ui-patterns`
- **Topics:** AVURLAsset, dynamic aspect ratio detection, preferredTransform, video metadata, SwiftUI video player
- **Source:** saraBeauty1.0 project (Jan 2026)

### swift/spritekit-swiftui-bridge.md
- **Concepts:** `#state` `#ui-patterns`
- **Topics:** SpriteKit vs SwiftUI paradigms, SKNode vs View, SKAction vs animation modifiers, imperative vs declarative, gesture handling differences
- **Source:** Chall4 project (Jan 2026)

### swift/weak-self-closures.md
- **Concepts:** `#memory` `#state`
- **Topics:** Weak self pattern, capture lists, reference cycles, memory leaks in closures, guard let unwrapping, class vs struct memory behavior
- **Source:** Chall4 SpriteKit project (Jan 2026)

### swift-spritekit-gestures.md
- **Concepts:** `#ui-patterns` `#state` `#data-flow`
- **Topics:** Touch lifecycle (touchesBegan/Moved/Ended), tap vs drag detection, tracking selected objects, drop zones (BattleSlot), collision detection with frame.intersects(), animated snapping
- **Source:** Chall4Game project (Jan 2026)

### arch/data-vs-behavior.md
- **Concepts:** `#architecture` `#data-flow` `#state`
- **Topics:** Separating data from behavior, struct vs class for game entities, Data → Factory → View pattern, Entity-Component pattern, when structs shouldn't have behavior
- **Source:** Chall4Game project (Jan 2026)

### theory/dfa.md
- **Concepts:** `#automata` `#computation` `#state`
- **Topics:** DFA definition (5-tuple), acceptance, start state as accepting, trap states, determinism, regular languages
- **Source:** Intro to Theoretical CS (Jan 2026)

### theory/dfa-implementation.md
- **Concepts:** `#automata` `#computation` `#state`
- **Topics:** DFA-to-code translation, 5-tuple → code mapping, transition table as 2D array, DFA simulator skeleton, C++ for Swift developers, ASCII char gotchas, boolean condition pitfalls
- **Source:** Intro to Theoretical CS — HW1 (Feb 2026)
- **See also:** theory/dfa.md

---

## Concept Map

### #concurrency
> Multiple things happening at once; coordination and safety

| File | What It Covers |
|------|----------------|
| os/clustered-systems.md | Distributed Lock Manager (DLM), shared resource coordination across nodes |
| os/execution-models.md | Job switching during I/O, time slices, preemption, CPU scheduling |
| os/process-management.md | Threads, program counter, multiplexing, deadlock |

**Future connections:**
- Swift: async/await, actors, Task groups
- Databases: Locks, isolation levels, race conditions

---

### #memory
> Memory management, allocation, and protection

| File | What It Covers |
|------|----------------|
| os/memory.md | Management, protection, segfaults, locality of reference, caching |
| swift/weak-self-closures.md | Reference cycles, weak captures, preventing memory leaks in closures |

---

### #security
> Protection, isolation, access control

| File | What It Covers |
|------|----------------|
| os/memory.md | Process isolation, segfaults |
| os/dual-mode.md | Kernel/user mode, hardware-enforced protection |

---

### #state
> How applications track and synchronize changing values

| File | What It Covers |
|------|----------------|
| swift/supabase-integration.md | @State vs @Binding vs @Observable |
| swift/spritekit-swiftui-bridge.md | SwiftUI @State (reactive) vs SpriteKit class properties (manual) |
| swift/weak-self-closures.md | Safely accessing state in delayed closures |
| swift-spritekit-gestures.md | Tracking selectedCard/dragStartPosition across touch lifecycle |
| os/process-management.md | Process states, program counter |
| theory/dfa.md | Finite states, state transitions, accepting states |
| arch/data-vs-behavior.md | Structs as immutable state containers vs classes as stateful actors |

---

### #performance
> Efficiency, utilization, optimization

| File | What It Covers |
|------|----------------|
| os/execution-models.md | CPU/IO utilization, avoiding idle time |
| os/memory.md | Cache efficiency through locality of reference |

---

### #data-flow
> How data moves from source to destination

| File | What It Covers |
|------|----------------|
| swift/supabase-integration.md | Service → View pattern, database triggers |
| swift-spritekit-gestures.md | Touch event → node lookup → state update → visual feedback |
| arch/data-vs-behavior.md | Data struct → Factory → View node pipeline |

---

### #architecture
> System design, design patterns, separation of concerns

| File | What It Covers |
|------|----------------|
| os/clustered-systems.md | Distributed system architecture, high availability |
| arch/data-vs-behavior.md | Data vs behavior separation, Entity-Component pattern, Factory pattern |

---

### #ui-patterns
> Reusable interface and interaction patterns

| File | What It Covers |
|------|----------------|
| swift/supabase-integration.md | Navigation patterns, ViewModifiers |
| swift-spritekit-gestures.md | Tap/drag detection, drop zones, animated snapping |

---

### #error-handling
> Detecting, communicating, and recovering from failures

| File | What It Covers |
|------|----------------|
| swift/supabase-integration.md | Supabase errors, decoding errors |

---

### #automata
> Finite state machines and formal language recognition

| File | What It Covers |
|------|----------------|
| theory/dfa.md | DFA definition, acceptance, determinism, regular languages |
| theory/dfa-implementation.md | DFA → code: transition table as 2D array, simulator loop, accept check |

**Future connections:**
- NFAs, regex equivalence
- Pumping lemma for regular languages

---

### #computation
> Models of computation and their power

| File | What It Covers |
|------|----------------|
| theory/dfa.md | DFAs as simplest computation model |
| theory/dfa-implementation.md | Translating computation models into executable code |

**Future connections:**
- PDAs, context-free languages
- Turing machines, decidability

---

## Quick Recall

**Common lookups:**
- Execution models → os/execution-models.md
- Memory → os/memory.md
- Deadlock → os/process-management.md
- State in SwiftUI → swift/supabase-integration.md §3
- Supabase errors → swift/supabase-integration.md §2.1
- DFA basics → theory/dfa.md
- DFA → code (C++) → theory/dfa-implementation.md
- Data vs behavior / component pattern → arch/data-vs-behavior.md

---

## Learning Queue

> Topics to explore that would strengthen existing knowledge

- [ ] Swift async/await deep dive → connects to `#concurrency`
- [ ] OS process states → connects to `#state`
- [ ] Database transactions/ACID → connects to `#state`, `#concurrency`
- [ ] System calls (how they work) → connects to os/dual-mode.md
- [ ] NFAs and DFA-NFA equivalence → connects to theory/dfa.md
- [ ] Regular expressions ↔ DFA conversion → connects to `#automata`
- [ ] Pumping lemma → connects to `#automata`
