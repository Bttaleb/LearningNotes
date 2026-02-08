---
tags:
  - concurrency
  - architecture
source: "OS Class (Jan 2026)"
description: "Multiple computers (nodes) working together as a single system"
---

# Clustered Systems


## What It Is

- 2+ machines connected via LAN or faster interconnect
- Share storage and coordinate work
- Appear as one system to users/applications

## Why It Exists

| Goal | Description |
|------|-------------|
| **High availability** | If one node fails, others continue (fault tolerance) |
| **High performance** | Parallel processing across nodes |

---

## Types of Clustering

| Type | How It Works | Trade-off |
|------|--------------|-----------|
| **Asymmetric** | One node active, others on standby (hot-standby). Standby monitors active and takes over on failure. | Simpler, but standby resources are idle |
| **Symmetric** | All nodes run applications and monitor each other | Better utilization, more complex coordination |

---

## The Shared Resource Problem

When multiple nodes share storage, concurrent access creates conflicts.

**Core pattern (applies to all shared resources):**

| Resource Type | Same Problem |
|---------------|--------------|
| Memory | Multiple nodes accessing same memory region |
| Files | Multiple nodes writing to same file |
| Database records | Multiple nodes updating same row |

### Solution: Distributed Lock Manager (DLM)

- Grants locks across the entire cluster
- Ensures only one node modifies a resource at a time
- Prevents conflicting operations

**Same concept, different scope:**

| Scope | Mechanism |
|-------|-----------|
| Threads (single machine) | Mutex / Semaphore |
| Nodes (cluster) | Distributed Lock Manager |

---

## Cluster vs. Distributed System

| Aspect | Clustered | Distributed |
|--------|-----------|-------------|
| Coupling | Tightly coupled | Loosely coupled |
| Storage | Shared | Independent |
| Location | Same location / data center | Geographically spread |

---

## Key Insight

The concurrency pattern is universal:
- **Shared resource** (memory, files, DB rows)
- **Multiple actors** (threads, processes, nodes)
- **Coordination mechanism** (mutex, DLM, locks)

Understanding this at the OS level transfers directly to application-level concurrency (Swift actors, database transactions, etc.).
