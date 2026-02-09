---
tags:
  - cache/caching
  - dual-mode
  - multiprocessor
source:
description:
---
# {{Ch. 1 Study Tips}}
1. Memory hierarchy from fastest to slowest (RCMSHOM) (7)
	1. Registers (CPU Registers || [[Volatile]])
	2. Cache (L1, L2, L3 || Volatile)
	3. Main Memory (RAM , Fast || Volatile)
	4. Solid State Disk (SSD, Fast || [[Non-Volatile]])
	5. Hard Disk Drive (HDD, large capacity || Non-Volatile)
	6. Optical Disk (CD/DVD/Blu-ray || Non-Volatile)
	7. Magnetic Tape (Used for backups/archives || Non-Volatile)
2. What are the benefits of multiprocessor systems? (3)
	- Increased Throughput -> more work in less time (run in parallel)
	- Economy of Scale -> Cheaper than multiple, single-processor systems
	- Increased Reliability -> Failure of one processor doesn't halt the system
		
	Symmetric vs Asymmetric?
		Symmetric (SMP): Processors are peers, processors share memory and I/O, most modern
		Asymmetric: Master-slave relationship, simpler but less efficient
3. When do you use [[multiprogramming]] vs [[timesharing]]?
	Multiprogramming for maximizing CPU utilization
	- Background tasks
	Timesharing for minimizing response time
	- User experience
	- Real-time feel
4. Why is [[dual mode]] operation needed? How do transitions occur?
	Needed to:
	- Protect OS from malware
	- Protect user programs from each other
	- Prevent users from accessing hardware directly
	- Ensure system stability || security
	<font color="#00b050">User</font> -> <font color="#ff0000">Kernel</font>: (SIE-0)
	- System Call (user -> OS service)
	- Interrupt (hardware -> CPU)
	- Exception/Trap(error in user program)
	- <mark style="background:#40a9ff">Mode bit = 0   </mark>
	<font color="#ff0000">Kernel</font> -> <font color="#00b050">User</font>: (OC-1)
	- OS completes requested service
	- Controls return to user program
	- <mark style="background:#40a9ff">Mode bit = 1    </mark>
5.  What is caching? How is it implemented?
	- temporarily copy data from slower to faster storage for later use
	How is it implemented?
		- Check if data is in cache
		- Yes? *hit* - use it
		- No? *miss* - copy from slower storage to cache, use it (hold it)
6. What are the 4 components of a computer system?
	1. Hardware -> CPU, memory, I/O devices
	2. Operating System 
	3. Application Programs -> Defines how sys. resources are used to solve user's problems 
	4. Users -> People, machines, other computers
7.  OS responsibilities for:
	[[memory]]
		- which parts are used where
		- decides which processes/data move in/out of mem.
		- de-/allocate memory as needed
		- manage mem. hierarchy
		- implement VRAM (RAM appears larger)
	storage
		- File management: CRUD
		- dir management: organizing fies to dir structure
		- mapping files to secondary storage
		- track available disk space
	I/O:
		- Hide hardware details from user
		- Manage I/O drivers
		- Buffering - Store data temporarily while transferring
		- Caching - Keep copies of frequently used data in faster storage
		- Spooling - overlapping output of one job with input of another job
8. What is the difference between protection and security?
	Protection: <mark style="background:#d3f8b6"> internal access controls </mark> 
		- Only auth'd processes can access resources
		- Implements access controls (read/write/execute)
		- Uses dual mode
	Security: <mark style="background:#d3f8b6"> defensing against external threats </mark> 
		- User auth (passwords, biometrics)
		- Protection against DOS-attacks
		- Protection against worms, viruses, malware
		- Network security (firewalls, encryption)
	