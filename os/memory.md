---
tags:
  - memory
  - security
  - performance
  - concurrency
source: "OS Class (Jan 2026)"
description: "OS controls what's in memory, where, and who can access it"
---

# Memory
## Requirements

To execute a program:
- All or part of **instructions** must be in memory
- All or part of **data** must be in memory

---

## Management Activities

| Activity | Description |
|----------|-------------|
| **Track usage** | Know which parts of memory are in use and by whom |
| **Decide movement** | Which processes/data to move in/out of memory |
| **Allocate/Deallocate** | Assign memory space when needed, reclaim when done |

---

## Protection

Multiple jobs in memory → need isolation.

Without protection:
- Job A could read/write Job B's data
- Malicious or buggy code could corrupt other processes

### Segmentation Fault

OS kills a process when it tries to access memory it doesn't own.

**Common causes:**
- Array out of bounds
- Dereferencing null/invalid pointer
- Accessing freed memory

```c
int arr[5];
arr[10] = 1;  // segfault — out of bounds
```

### Key Point

Memory protection is the **OS's responsibility**, not the application's. The OS enforces boundaries; violations terminate the process.

---

## Storage

### Locality of Reference

Programs don't access memory randomly — they follow predictable patterns. Caches exploit this by storing "chunks" of recently/nearby accessed data.

**Why locality exists:**
1. **Sequential execution** — instructions run one after another
2. **Loops** — same code/data accessed repeatedly
3. **Functions** — localized block of code + local variables

| Type | Pattern | Cache Strategy |
|------|---------|----------------|
| **Temporal** | Same data accessed again soon | Keep recently used items |
| **Spatial** | Nearby data accessed soon | Fetch chunks, not single bytes |

### Buffering vs Caching

| Concept | Purpose | Location |
|---------|---------|----------|
| **Buffering** | Temp storage *during transfer* | Main memory |
| **Caching** | Copy of data for faster access | Cache (hardware) |

**Key distinction:** Caching = one *instance* of the data copied to faster storage. Not the same as "a cache" (the storage itself).

### Cache Coherence (Multi-CPU)

In systems with multiple CPUs, each has its own cache. Problem: if CPU A modifies a cached value, CPU B's cache becomes stale.

**Hardware must keep caches coherent** — when one cache changes, others must update or invalidate their copy.

Without coherence → CPUs see different values for same memory location → bugs.
