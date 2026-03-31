---
tags:
  - concurrency
source: "OS Class (Jan 2026)"
description: "Deadlock illustration — 5 philosophers, 5 chopsticks"
date: 2026-03-24
---

# Dining Philosophers

5 philosophers, 5 chopsticks. Need **both** left and right to eat.

Naive solution: everyone grabs left, then right → if all grab left simultaneously → **circular wait → [[process-management|deadlock]]**.

Fixes: allow max 4 at table, pick up both atomically, or break symmetry (one philosopher grabs right first).

Connects to: [[Semaphores]], [[Readers-Writers Problem]], [[Producer-Consumer Problem]]
