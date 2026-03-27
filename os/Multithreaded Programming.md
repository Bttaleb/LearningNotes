---
tags:
  - concurrency
  - parallelism
  - threads
source: Chapter 4
description: ""
date: 2026-02-19
---
#Parallelism -> implies a system can perform more than one task SIMULTANEOUSLY
#Concurrency -> supports more than one task making progress

Types of Parallelism (Software)
	**Data**: ==distributes subsets of same data across multiple cores==, *same operation on each*
	**Task**: ==distributing threads across cores==, *threads perform unique operation*
As number of threads grows, architectural support for threading grows as well (Hardware)
	CPU’s have cores and hardware threads

#Amdahls-Law - What does it identify?
	Performance gains from adding additional cores to an application THAT HAS BOTH serial and parallel components
	S = serial portion
	N = processing cores
$$
Speedup <= 1 / (S+((1-S)/N)
$$

User Threads and Kernel Threads (kernel mode = unrestricted access)
#Thread-library -> provides programmer with API for creating and managing threads
#User-threads -> management done by user-level threads library
#Kernel-threads -> Supported by Kernel

- Threads do NOT have parent child processes
- Any system that support UNIX or LINUX, must support POSIX
- 
[3 Primary thread libraries]
	1. POSIX Pthreads (User and Kernel)
	2. Windows threads (Kernel)
	3. Java threads (User but depends on hosting OS)
<font color="#00b050">Advantages</font> of User-Threads:
- thread switching doesn’t require kernel mode
- User level thread can run on ANY OS
- Scheduling can be app specific in the user level thread
- User level thread are fast to create and manage
<font color="#ff0000">Disadvantages</font> of User-Threads:
- Most systems calls are blocking
- Multithreaded apps cannot use multiprocessing