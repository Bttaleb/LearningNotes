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
3. 4 OS structures with pros + cons