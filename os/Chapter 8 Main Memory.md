**Translation Look Aside Buffer (TLB)**
- Store Address-Space Identifiers (ASIDs)
	- To uniquely ID each process (pid??) -> provides address-space protection
	If not, you would need to flush at every context switch (unusable)
**Associative Memory**
- Compares input search data

First look to TLB (cache) for what you need (the address of the whole page)
- if HIT, add to *physical* address with displacement into *physical* memory
- if MISS, look in page table, add to *physical* address with displacement (d) into *physical* memory

**Finding Effective Access Time**
e = epsilon -> time for TLB search, "20 nanoseconds"
Hit ratio = a -> percentage of times a page # is found in associative registers, *a ratio related to number of associative registers*
Miss ratio = 1-a
Memory access time = m


EAT = a(e + m) + (1-a)(e + 2m) <- why hit twice? First time hit the cache, if it misses where have to check the page table

**Locality of Reference**
- 3 reasons as to why we have *LOR*
1. Your code runs sequentially (usually)
2. Loops (references array "A" over and over so it helps)
	- for (i=0; i < 100; i++)
			A[i] = 0;
3. functions/modules

**Memory Protection**
- Valid-Invalid bit attached to each entry in table 
	- if valid -> page is in process' logical address space (legal page)
	- if invalid -> page not in process' logical address space (segmentation fault)