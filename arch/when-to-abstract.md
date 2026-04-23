---
tags:
  - architecture
  - ui-patterns
source: "Couler project — FabricsLibView (Apr 2026)"
description: "Recognizing when repeated code is ready to become an abstraction vs. premature generalization"
---

# When to Abstract: The Rule of Three

## The Insight

There's a gap between **writing code that works** and **designing abstractions that eliminate repetition**. Recognizing that gap — and knowing when to cross it — is a fundamental skill.

---

## The Three Phases

### 1. Implementation Phase
You write each view with its own boilerplate: `.onDelete`, `.task`, `.sheet`, toolbar buttons. Every new "library" screen repeats the same structure. This is **correct** — it works and you understand every line.

### 2. Recognition Phase
You start feeling friction: "every library view does the same thing — load a list, delete from a list, show a detail sheet, add new items." That friction is the signal that an abstraction might exist.

### 3. Abstraction Phase
You can clearly answer two questions:
- **What varies?** (the model type, the card view, the detail sheet, the viewmodel)
- **What stays the same?** (List, ForEach, onDelete, task loading, toolbar, sheet presentation)

Once those buckets are clear, you can build a generic component that takes the varying parts as parameters and handles the shared parts internally.

---

## The Rule: Three Before You Abstract

Build the thing **three times** before generalizing:
1. First time — you're just learning the pattern
2. Second time — you notice the repetition
3. Third time — you know *exactly* what varies vs. what's shared

**If you abstract after one instance**, you'll guess wrong about what varies and build something rigid that fights you later.

**The repetition is teaching you the shape of the abstraction.**

---

## How to Evaluate Readiness

| Signal | Meaning |
|--------|---------|
| You copy-paste a view and change 3-4 things | The abstraction is becoming clear |
| You can list what varies vs. what's shared | You're ready |
| You're annoyed by the repetition | Good — but wait until you can name the variation points |
| You *think* it'll probably be the same | Not ready — "probably" means you're guessing |

---

## Connections

- [[data-vs-behavior]] — same principle at a different level: separate what changes from what doesn't
- **Swift Generics** — the language mechanism that makes this possible (`LibraryView<Item, CardView, DetailView>`)
- **DRY vs. premature abstraction** — DRY says don't repeat yourself, but premature abstraction says don't generalize until you understand the variation
