---
type: glossary
tags: [moc, glossary, os]
description: OS concept index — every key term mapped to the chapter/file where it lives
---

# OS Glossary

Every key term → the file or section where it's defined or discussed. **Concept index — search here, then jump.**

When you encounter a term in a new file, add it below the existing entry (`also: [[file#section]]`). Backlinks will surface every place it's mentioned.

## A–C

- **API** — see [[chapter-2-review#1. Sys. Calls vs API vs Sys. Programs]]
- **asymmetric processors** — see [[chapter-1-review#2. Benefits of multiprocessor systems (3)]]; clustered case in [[clustered-systems#Types of Clustering]]
- **atomic hardware instructions** (`test_and_set`, `compare_and_swap`) — see [[synchronization-tools#Atomic Hardware Instructions]]
- **blocking (IPC)** — see [[ipc-models#Synchronization in Message Passing]]
- **buffering** — see [[ipc-models#Buffering]]; also [[chapter-1-review#7. OS responsibilities]]
- **caching** — see [[chapter-1-review#5. Caching]]
- **classic sync problems** — see [[classic-sync-problems]]
- **clustered systems** — see [[clustered-systems]]
- **concurrency** — see [[process-management#Concurrency]]; also [[multithreaded-programming]]
- **critical section** — see [[synchronization]]
- **CPU scheduling** — see [[chapter-6-cpu-scheduling]]

## D–F

- **deadlock** — see [[process-management#Deadlock]]; lab work in [[lab-3#Deadlock can occur if the system is out of order]]
- **dining philosophers** — see [[classic-sync-problems#Dining Philosophers]]
- **distributed lock manager (DLM)** — see [[clustered-systems#The Shared Resource Problem]]
- **dual mode** — see [[dual-mode]]; quick recap in [[chapter-1-review#4. Dual mode operation]]
- **execution models** (batch / time-sharing) — see [[execution-models]]
- **file management** — see [[chapter-1-review#7. OS responsibilities]]

## G–I

- **I/O responsibilities** — see [[chapter-1-review#7. OS responsibilities]]
- **IPC (inter-process communication)** — see [[ipc-models]]; also [[communications-models]]

## J–L

- **kernel mode** — see [[dual-mode#Solution: Dual Mode]]
- **layered OS structure** — see [[chapter-2-review#3. ==OS structures== with pros + cons (4)]]

## M–P

- **memory hierarchy (RCMSHOM)** — see [[chapter-1-review#1. Memory hierarchy (RCMSHOM)]]
- **memory management** — see [[memory]]; deep dive in [[chapter-8-main-memory]]
- **message passing (IPC)** — see [[ipc-models#Message Passing]]
- **microkernel** — see [[chapter-2-review#3. ==OS structures== with pros + cons (4)]]
- **mode bit** — see [[dual-mode#Solution: Dual Mode]]; transitions in [[chapter-1-review#4. Dual mode operation]]
- **monolithic kernel** — see [[monolithic]]; trade-offs in [[chapter-2-review#3. ==OS structures== with pros + cons (4)]]
- **multicore programming** — see [[multicore-programming]]
- **multiprocessor systems** — see [[chapter-1-review#2. Benefits of multiprocessor systems (3)]]
- **multiprogramming** — see [[chapter-1-review#3. Multiprogramming vs Timesharing]]; also [[execution-models#Multiprogramming (Batch Systems)]]
- **mutex** — see [[synchronization-tools#Mutex Locks]]; lab in [[lab-3#Semaphore vs Mutex]]
- **named pipes** — see [[sockets]]; mechanism table in [[ipc-models#Mechanisms]]
- **Non-Volatile** — see [[chapter-1-review#Volatile vs Non-Volatile]]
- **ordinary pipes** — see [[ordinary-pipes]]; also [[sockets]] and [[ipc-models#Mechanisms]]
- **page table** — see [[chapter-8-main-memory#Page Table Structure]]
- **parallelism vs concurrency** — see [[multithreaded-programming]]
- **parameter passing (system calls)** — see [[chapter-2-review#2. 3 Methods of passing parameters (Advantages vs Disadvantages)]]
- **PCB (Process Control Block)** — see [[sockets]] (end of file)
- **pipes** — see [[ordinary-pipes]]; comparison in [[sockets]]
- **policy vs mechanism** — see [[chapter-2-review#7. ==policy== vs ==mechanism== separation]]
- **preemptive vs non-preemptive scheduling** — see [[chapter-6-cpu-scheduling#When Does Scheduling Happen?]]
- **process vs thread** — see [[process-management#Key Terms]]; also [[multithreaded-programming#Key Distinction]]
- **process management** — see [[process-management]]
- **producer-consumer problem** — see [[classic-sync-problems#Producer-Consumer Problem]]; bridge to industry in [[bridges#Producer-Consumer → Everywhere in Software]]
- **program counter** — see [[process-management#Program Counter]]
- **protection vs security** — see [[chapter-1-review#8. Protection vs Security]]; memory-level in [[memory#Protection]]

## Q–S

- **race condition** — see [[synchronization]]
- **readers-writers problem** — see [[classic-sync-problems#Readers-Writers Problem]]
- **realtime scheduling** — see [[chapter-6-cpu-scheduling#Realtime Scheduling]]
- **round robin** — see [[chapter-6-cpu-scheduling#The Algorithm Ladder]]; coding notes in [[os-round-robin-insights]]
- **scheduling criteria** — see [[chapter-6-cpu-scheduling#Five Criteria]]
- **semaphore** — see [[synchronization-tools#Semaphores]]; lab in [[lab-3#Semaphore]]
- **shared memory (IPC)** — see [[ipc-models#Shared Memory]]
- **sockets** — see [[sockets]]
- **spinlock** — see [[synchronization-tools#Spinlock Behavior]]
- **spooling** — see [[chapter-1-review#7. OS responsibilities]]
- **symmetric multiprocessing (SMP)** — see [[chapter-1-review#2. Benefits of multiprocessor systems (3)]]
- **synchronization** — see [[synchronization]]; tools in [[synchronization-tools]]; problems in [[classic-sync-problems]]
- **system calls** — see [[system-calls]]; implementation steps in [[chapter-2-review#6. How are system calls implemented? (8 steps)]]
- **system programs** — see [[chapter-2-review#8. Categories of system programs with examples (7)]]

## T–Z

- **thread** — see [[process-management#Key Terms]]; threading model in [[multithreaded-programming]]
- **thread scheduling (PCS / SCS)** — see [[chapter-6-cpu-scheduling#Thread Scheduling]]
- **time-sharing** — see [[chapter-1-review#3. Multiprogramming vs Timesharing]]; deeper in [[execution-models#Time-Sharing]]
- **timers (interrupt)** — see [[dual-mode#Timers]]
- **TLB (Translation Lookaside Buffer)** — see [[chapter-8-main-memory#Translation Lookaside Buffer (TLB)]]; EAT formula in [[chapter-8-main-memory#Effective Access Time (EAT)]]
- **translation lookaside buffer** → see **TLB**
- **UNIX OS structure** — see [[chapter-2-review#3. ==OS structures== with pros + cons (4)]]
- **user mode** — see [[dual-mode#Solution: Dual Mode]]
- **Volatile** — see [[chapter-1-review#Volatile vs Non-Volatile]]
