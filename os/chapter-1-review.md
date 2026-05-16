---
tags:
  - cache/caching
  - dual-mode
  - multiprocessor
source: OS Class (Jan 2026)
description: Chapter 1 study tips — memory hierarchy, multiprocessing, dual mode, caching, OS responsibilities, protection vs security
---

Operating System
 - A resource manager that manages ALL the resources in the system

# Chapter 1 Study Tips

## 1. Memory hierarchy (RCMSHOM)

Fastest to slowest (7):
1. Registers (CPU Registers || Volatile)
2. Cache (L1, L2, L3 || Volatile)
3. Main Memory (RAM , Fast || Volatile)
4. Solid State Disk (SSD, Fast || Non-Volatile)
5. Hard Disk Drive (HDD, large capacity || Non-Volatile)
6. Optical Disk (CD/DVD/Blu-ray || Non-Volatile)
7. Magnetic Tape (Used for backups/archives || Non-Volatile)

### Volatile vs Non-Volatile

- **Volatile** — Requires power to maintain it's data (RAM). Provides high speed, temporary storage for active tasks.
- **Non-Volatile** — Retains data without power. Slower, long-term storage. Cheaper per GB.

## 2. Benefits of multiprocessor systems (3)

- Increased Throughput -> more work in less time (run in parallel)
- Economy of Scale -> Cheaper than multiple, single-processor systems
- Increased Reliability -> Failure of one processor doesn't halt the system

Symmetric vs Asymmetric?
- Symmetric (SMP): Processors are peers, processors share memory and I/O, most modern
- Asymmetric: Master-slave relationship, simpler but less efficient

## 3. Multiprogramming vs Timesharing

- **Multiprogramming** — maximizing CPU utilization. Multiple programs loaded in memory simultaneously. CPU switches between to maximize utilization.
	- Background tasks
- **Timesharing** — minimizing response time. Logical extension of multiprogramming. CPU switches so frequently that the users interact with programs while they run.
	- User experience
	- Real-time feel

## 4. Dual mode operation

See [[dual-mode|dual-mode operation]] for the full write-up.

Needed to:
- Protect OS from malware
- Protect user programs from each other
- Prevent users from accessing hardware directly
- Ensure system stability || security

User -> Kernel: (SIE-0)
- System Call (user -> OS service)
- Interrupt (hardware -> CPU)
- Exception/Trap(error in user program)
- ==Mode bit = 0==

Kernel -> User: (OC-1)
- OS completes requested service
- Controls return to user program
- ==Mode bit = 1==

## 5. Caching

Temporarily copy data from slower to faster storage for later use.

How is it implemented?
- Check if data is in cache
- Yes? *hit* - use it
- No? *miss* - copy from slower storage to cache, use it (hold it)

## 6. 4 components of a computer system

1. Hardware -> CPU, memory, I/O devices
2. Operating System
3. Application Programs -> Defines how sys. resources are used to solve user's problems
4. Users -> People, machines, other computers

## 7. OS responsibilities

### [[memory]]
- which parts are used where
- decides which processes/data move in/out of mem.
- de-/allocate memory as needed
- manage mem. hierarchy
- implement VRAM (RAM appears larger)

### storage
- File management: CRUD
- dir management: organizing fies to dir structure
- mapping files to secondary storage
- track available disk space

### I/O
- Hide hardware details from user
- Manage I/O drivers
- Buffering - Store data temporarily while transferring
- Caching - Keep copies of frequently used data in faster storage
- Spooling - overlapping output of one job with input of another job

## 8. Protection vs Security

- **Protection**: ==internal access controls==
	- Only auth'd processes can access resources
	- Implements access controls (read/write/execute)
	- Uses dual mode
- **Security**: ==defensing against external threats==
	- User auth (passwords, biometrics)
	- Protection against DOS-attacks
	- Protection against worms, viruses, malware
	- Network security (firewalls, encryption)
