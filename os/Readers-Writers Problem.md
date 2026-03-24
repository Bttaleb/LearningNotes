---
tags:
  - concurrency
source: "OS Class (Jan 2026)"
description: "Multiple readers OR one writer — classic sync problem"
date: 2026-03-24
---

# Readers-Writers Problem

Shared database. Multiple readers can read simultaneously (no conflict). Writers need **exclusive access**.

Uses: `rw_mutex` (sem, init 1), `mutex` (sem, init 1), `read_count` (int, init 0)

```
// Writer                      // Reader
wait(rw_mutex);                wait(mutex);
  // write                       read_count++;
signal(rw_mutex);                if (read_count == 1)
                                   wait(rw_mutex);     // FIRST reader locks writers out
                               signal(mutex);
                                 // read
                               wait(mutex);
                                 read_count--;
                                 if (read_count == 0)
                                   signal(rw_mutex);   // LAST reader lets writers in
                               signal(mutex);
```

**Key insight:** Only **first** reader grabs `rw_mutex`, only **last** reader releases it. Middle readers just bump the count. `mutex` protects `read_count` itself.

If every reader called `wait(rw_mutex)`, only one could read at a time — defeats the purpose.

Connects to: [[Semaphores]], [[Producer-Consumer Problem]], [[Dining Philosophers]]
