---
tags:
  - memory
  - paging
  - tlb
source: OS Class (Jan 2026)
description: Page tables, address translation, TLB caching, locality, memory protection
---

# Chapter 8 — Main Memory

## Translation Lookaside Buffer (TLB)

A small, fast **associative cache inside the MMU** that stores recent page-number → frame-number translations. Without it, every memory access would require walking the page table — doubling the work for every load/store.

- Stores Address-Space Identifiers (ASIDs)
	- To uniquely ID each process (pid??) -> provides address-space protection
	- If not, you would need to flush at every context switch (unusable)

### Associative Memory
- Compares input search data in parallel against all entries (single clock cycle)

### Lookup flow

First look to TLB (cache) for what you need (the address of the whole page):
- if HIT, add to *physical* address with displacement into *physical* memory
- if MISS, look in page table, add to *physical* address with displacement (d) into *physical* memory

### Effective Access Time (EAT)

- e = epsilon -> time for TLB search, "20 nanoseconds"
- Hit ratio = a -> percentage of times a page # is found in associative registers, *a ratio related to number of associative registers*
- Miss ratio = 1-a
- Memory access time = m

`EAT = a(e + m) + (1-a)(e + 2m)` ← why hit twice? First time hit the cache, if it misses we have to check the page table

## Locality of Reference

3 reasons as to why we have *LOR*:
1. Your code runs sequentially (usually)
2. Loops (references array "A" over and over so it helps)
	- `for (i=0; i < 100; i++) A[i] = 0;`
3. functions/modules

## Memory Protection

- Valid-Invalid bit attached to each entry in table
	- if valid -> page is in process' logical address space (legal page)
	- if invalid -> page not in process' logical address space (segmentation fault)

## Shared Code

*(notes pending)*

---

## Page Table Structure

### The Core Idea

A virtual address is split into two parts:

```
|---- page number ----|---- offset ----|
```

- **Page number** → index into the page table → gives you the **frame number** (physical)
- **Offset** → stays the same — it's the position within the page

### How to Calculate the Split

**Formula:** offset bits = log₂(page size in bytes)

| Page Size | In Bytes | Offset Bits | Remaining (32-bit) |
|-----------|----------|-------------|-------------------|
| 4 KB      | 4096     | 12          | 20 bits for page# |
| 8 KB      | 8192     | 13          | 19 bits for page# |
| 16 KB     | 16384    | 14          | 18 bits for page# |

### Worked Example

**Given:** 32-bit address space, 4 KB page size

**Step 1: Get the offset bits**
```
4 KB = 4096 bytes = 2^12  →  12 offset bits
```

**Step 2: Get the page number bits**
```
32 - 12 = 20 bits for page number
```

**Step 3: Split an address**

Virtual address: `0x00003A7F` → in binary:
```
  0000 0000 0000 0000 0011 1010 0111 1111
|-------- 20 bits --------|--  12 bits --|
     page number = 3         offset = A7F
```

Page number = `0x00003` = 3
Offset = `0xA7F` = 2687 (A7F converted to hexadecimal)

**Step 4: Look up page table**

```
Page Table
+---------+----------+
| Page #  | Frame #  |
+---------+----------+
|   0     |   5      |
|   1     |   2      |
|   2     |   8      |
|   3     |   6      |  ← page 3 maps to frame 6
|   ...   |   ...    |
+---------+----------+
```

**Step 5: Build the physical address**

Replace page number with frame number, keep offset:
```
Frame 6 = 0x00006 (20 bits) + offset 0xA7F (12 bits)
Physical address = 0x00006A7F
```

### The Full Translation

```
Virtual:  [page# = 3 ][offset = A7F]
               |
          page table
               |
               v
Physical: [frame# = 6][offset = A7F]
                        ↑ stays the same
```

### Why the Offset Stays the Same

Pages and frames are the same size (4 KB). The offset is your position within that chunk. Translating just swaps WHICH chunk you're in (page → frame), not WHERE inside it.

### Quick Reference

```
offset bits     = log₂(page size)
page number bits = address bits - offset bits
total pages      = 2^(page number bits)
total frames     = physical memory size / page size
```


## Two level Paging (forward mapped page table)

Logical address -> divided into
1. page number of 22 bits
2. page offset consisting of 10 bits (2^10 bits = 1024 bits or 1k)

Since page table is paged, page number further divided into:
- 12 bit page number
- 10 bit page offset
