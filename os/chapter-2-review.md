---
tags:
  - os-structures
  - system-calls
source: OS Class (Jan 2026)
description: Chapter 2 study tips — system calls, parameter passing, OS structures, policy vs mechanism, system programs
---

# Chapter 2 Review

## 1. Sys. Calls vs API vs Sys. Programs

| | ==Sys. Calls== | ==API== | ==Sys. Programs== |
|---|---|---|---|
| What is it? | OS interface | Programming interface | Utility Program |
| Can User See? | No | No | Yes |
| Examples | `open()` | `fopen()` in C library | `ls` command |

## 2. 3 Methods of passing parameters (Advantages vs Disadvantages)

1. Registers (CPU) -- Fastest, but limited
2. Block/Table in memo. -- No limit, but slower
3. Stack -- no limit, most flexible, but slower + a lot of overhead

## 3. ==OS structures== with pros + cons (4)

1. ==Simple== ([[monolithic|Monolithic]])
	- Pros: Fast, efficient
	- Cons: Difficult to maintain/extend, no isolation, poor security
2. ==UNIX== (Layered-ish Monolithic)
	- Pros: Better structure, efficient, separation between kernel and user programs
	- Cons: Kernel monolithic (limited modularity), difficult to maintain, limited protection
3. ==Layered Approach==
	- Pros: Modularity (easy debugging), info. hidings, maintainability, good for teaching + understanding
	- Cons: Difficult to define layers, less efficient, rigid struct. (hard to change layer dependency)
4. ==Microkernel==
	- Pros: Easy to extend, reliable/secure, better fault isolation
	- Cons: Slower, more user-kernel mode switches, complex inter-service comm., not as efficient as monolithic FOR GENERAL-PURPOSE SYSTEMS

## 4. Trade-off Comparison between OS structures

| | Simple | UNIX | Layered | Microkernel |
|---|---|---|---|---|
| Performance | Fastest | Fast | Slower | Slowest |
| Reliability | Poor | Medium | Good | Best |
| Maintainability | Hard | Medium | Easy | Easiest |
| Modularity | None | Limited | Good | Best |

## 5. Which languages are used for which parts of the OS

- Assembly: Low level hardware-specific code, max. performance, direct HW access
- C: Most OS kernel, balance of performance and portability (low-level access)
- C++: modern OS components, object oriented
- High-Level: System utilities, python/java/C#, easier development + maintainability

## 6. How are [[system-calls|system calls]] implemented? (8 steps)

1. User invokes API function
2. API sets up parameters -> executes trap/software interrupt
3. Mode switches FROM User TO Kernel
4. CPU jumps to system call handler in OS
5. OS looks up system call # in system call table
6. OS executes corresponding kernel function
7. Result returned to user program
8. Mode switches BACK FROM Kernel TO User

## 7. Understand ==policy== vs ==mechanism== separation

- ==Policy==: What will be done
- ==Mechanism==: How to do it

Separation allows flexibility - can change policy without changing mechanism.

## 8. Categories of system programs with examples (7)

1. File Management (create, delete, copy, rename, print; cp, rm, ls)
2. Status Info (Date, time, memory usage, disk space; date, ps, top, df)
3. File Modification (Text editors, search tools; vi, emacs, grep)
4. Programming Lang. support (compilers, assemblers, debuggers, interpreters; gcc, gdb)
5. Program Loading and Execution (Loaders, linkers, debuggers)
6. Communications (email, web browsers, remote login; ssh, ftp)
7. Background Services (Daemons, continuously running services)

## 9. Microkernel vs Monolithic (key differences)
