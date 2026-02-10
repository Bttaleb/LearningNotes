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
4. Understanding trade-offs: Performance vs. reliability/maintainability
5. Which languages are used for which parts of the OS
6. How are system calls implemented (steps)
7. Understand policy vs mechanism separation
8. Categories of system programs with examples
9. Microkernel vs Monolithic (key differences)