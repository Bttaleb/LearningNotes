---
tags:
  - 
source: OS Class (Jan 2026)
description: ""
---

# {{Chapter 2}}

1. <mark style="background:#affad1">Sys. Calls</mark> vs <mark style="background:#fdbfff">API</mark> vs <mark style="background:#40a9ff">Sys. Programs</mark>
	What is it?
		<mark style="background:#affad1">OS interface</mark> || <mark style="background:#fdbfff">Programming interface</mark> || <mark style="background:#40a9ff">Utility Program</mark>
	Can User See? 
		<mark style="background:#affad1">No</mark> || <mark style="background:#fdbfff">No</mark> || <mark style="background:#40a9ff">Yes</mark>
	Examples
		<mark style="background:#affad1">open()</mark> || <mark style="background:#fdbfff">fopen() in C library</mark> || <mark style="background:#40a9ff">ls command</mark>
2. 3 Methods of passing parameters (Advantages vs Disadvantages)
	1. Registers (CPU) -- Fastest, but limited
	2. Block/Table in memo. -- No limit, but slower
	3. Stack -- no limit, most flexible, but slower + a lot of overhead
3. <mark style="background:rgba(5, 117, 197, 0.2)">OS structures</mark> with pros + cons (4)
	1. <mark style="background:rgba(5, 117, 197, 0.2)">Simple</mark> ([[Monolithic]])
		<font color="#00b050">Pros</font>: Fast, efficient
		<font color="#ff0000">Cons</font>: Difficult to maintain/extend, no isolation, poor security
	2. <mark style="background:rgba(5, 117, 197, 0.2)">UNIX</mark> (Layered-ish Monolithic)
		<font color="#00b050">Pros</font>: Better structure, efficient, separation between kernel and user programs
		<font color="#ff0000">Cons</font>: Kernel monolithic (limited modularity), difficult to maintain, limited protection
	3. <mark style="background:rgba(5, 117, 197, 0.2)">Layered Approach</mark>
		<font color="#00b050">Pros</font>: Modularity (easy debugging), info. hidings, maintainability, good for teaching + understanding
		<font color="#ff0000">Cons</font>: Difficult to define layers, less efficient, rigid struct. (hard to change layer dependency)
	4. <mark style="background:rgba(5, 117, 197, 0.2)">Microkernel</mark>
		<font color="#00b050">Pros</font>: Easy to extend, reliable/secure, better fault isolation
		<font color="#ff0000">Cons</font>: Slower, more user-kernel mode switches, complex inter-service comm., not as efficient as monolithic FOR GENERAL-PURPOSE SYSTEMS
4. Trade-off Comparison between OS structures
			Simple || UNIX || Layered || Microkernel
		Performance
			<font color="#00b050">Fastest</font> || <font color="#ffff00">Fast</font> || <font color="#de7802">Slower</font> || <font color="#ff0000">Slowest</font>
		Reliability
			<font color="#ff0000">Poor</font> || <font color="#de7802">Medium</font> || <font color="#ffff00">Good</font> || <font color="#00b050">Best</font>
		Maintainability
			<font color="#ff0000">Hard</font> || <font color="#de7802">Medium</font> || <font color="#ffff00">Easy</font> || <font color="#00b050">Easiest</font>
		Modularity
			<font color="#ff0000">None</font> || <font color="#de7802">Limited</font> || <font color="#ffff00">Good</font> || <font color="#00b050">Best</font>
5. Which languages are used for which parts of the OS
		Assembly: Low level hardware-specific code, max. performance, direct HW access
		C: Most OS kernel, balance of performance and portability (low-level access)
		C++: modern OS components, object oriented
		High-Level: System utilities, python/java/C#, easier development + maintainability
6. How are [[system calls]] implemented? (8 steps)
	1. User invokes API function
	2. API sets up parameters -> executes trap/software interrupt
	3. Mode switches FROM User TO Kernel
	4. CPU jumps to system call handler in OS
	5. OS looks up system call # in system call table
	6. OS executes corresponding kernel function
	7. Result returned to user program
	8. Mode switches BACK FROM Kernel TO User
7. Understand <font color="#ffff00">policy</font> vs <font color="#de7802">mechanism</font> separation
	<font color="#ffff00">Policy</font>: What will be done
	<font color="#de7802">Mechanism</font>: How to do it
	Separation allows flexibility - can change policy without changing mechanism
8. Categories of system programs with examples (7)
	1. File Management (create, delete, copy, rename, print; cp, rm, ls)
	2. Status Info (Date, time, memory usage, disk space; date, ps, top, df)
	3. File Modification (Text editors, search tools; vi, emacs, grep)
	4. Programming Lang. support (compilers, assemblers, debuggers, interpreters; gcc, gdb)
	5. Program Loading and Execution (Loaders, linkers, debuggers)
	6. Communications (email, web browsers, remote login; ssh, ftp)
	7. Background Services (Daemons, continuously running services)
9. Microkernel vs Monolithic (key differences)