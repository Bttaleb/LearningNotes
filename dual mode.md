---
tags:
  - security
  - architecture
source: OS Class (Jan 2026)
description: Restricting user access to hardware via kernel/user modes
---

# Dual-Mode Operation


## The Problem

OS has full access to everything (memory, files, I/O devices). How do we prevent users from touching hardware directly?

---

## Solution: Dual Mode

| Mode | Access | When |
|------|--------|------|
| **Kernel (0)** | Full — all hardware, memory, devices | OS is running |
| **User (1)** | Limited — own memory, files only | User programs running |

### How It's Implemented

**Mode bit** — a single bit in the CPU's status register.

```
Status Register: [...other bits...][mode bit]
                                      0 = kernel
                                      1 = user
```

Hardware checks this bit before allowing privileged operations.

---

## Mode Transitions

```
User Mode ──[system call]──→ Kernel Mode
    ↑                            │
    └────[return from call]──────┘
```

- **System call** → triggers switch to kernel mode
- **Return from call** → resets back to user mode

*(System call mechanics covered separately)*

---

## Timers

Prevents processes from hogging CPU (infinite loops, etc.).

- OS sets a timer interrupt
- When timer fires → control returns to OS
- OS decides what runs next

Without timers, a buggy/malicious program could run forever.

---

## Key Point

Protection is enforced by **hardware** (mode bit, timers), not just software. User programs can't simply flip the mode bit — only the hardware can during interrupts/system calls.
