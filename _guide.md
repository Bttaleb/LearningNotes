# Second Brain User Guide

> Your personal knowledge system powered by Claude Code + Obsidian

---

## Quick Start

### The Trigger Word
Start any request with `notes:` to activate second brain mode.

```
notes: [your request here]
```

### At a Glance

| Action | Command |
|--------|---------|
| Save knowledge | `notes: I learned about [X]` |
| Recall knowledge | `notes: what do I know about [X]?` |
| Make connections | `notes: connect [A] to [B]` |
| Learn new topics | `notes: learn [topic]` |
| **Get challenged** | `notes: challenge me on [X]` |
| Validate connections | `notes: is this connection valid? [A] ↔ [B]` |

---

## Core Commands

### 1. Adding Knowledge

| Command | What It Does |
|---------|--------------|
| `notes: I learned about [topic]` | Creates/updates a note on that topic |
| `notes: add this to [domain]` | Adds current discussion to a specific domain file |
| `notes: save this` | Saves the current conversation's key insights |

**Examples:**
```
notes: I learned about mutex locks in my OS class today

notes: add this Swift async/await explanation to my notes

notes: save this — the explanation of database indexing was helpful
```

**What happens:**
1. I identify the domain (os/, swift/, theory/, etc.)
2. Create or update the appropriate file with YAML frontmatter
3. Tag it with relevant core concepts (Obsidian picks these up automatically)
4. Add `[[wiki-links]]` to related notes (powers Obsidian's graph view and backlinks)

---

### 2. Recalling Knowledge

| Command | What It Does |
|---------|--------------|
| `notes: what do I know about [topic]?` | Searches your notes and summarizes |
| `notes: review [domain]` | Overview of everything in a domain |
| `notes: review` | Full overview of all your notes |
| `notes: quiz me on [topic]` | Tests your understanding |

**Examples:**
```
notes: what do I know about state management?

notes: review swift

notes: quiz me on Supabase errors
```

---

### 3. Making Connections

| Command | What It Does |
|---------|--------------|
| `notes: connect [A] to [B]` | Explicitly links two topics |
| `notes: how does [X] relate to [Y]?` | Finds conceptual bridges |
| `notes: what connects to [topic]?` | Shows all related concepts |

**Examples:**
```
notes: connect OS process states to SwiftUI @State

notes: how does database locking relate to Swift concurrency?

notes: what connects to #concurrency?
```

---

### 4. Learning New Topics

| Command | What It Does |
|---------|--------------|
| `notes: learn [topic]` | Explains topic, offers to save key points |
| `notes: deep dive [topic]` | Thorough exploration with note-taking |
| `notes: expand [existing topic]` | Adds depth to something you already know |
| `notes: fill gaps in [domain]` | Identifies and addresses weak areas |

**Examples:**
```
notes: learn async/await in Swift

notes: deep dive database indexing strategies

notes: expand my understanding of RLS

notes: fill gaps in os
```

---

### 5. Managing Your Notes

| Command | What It Does |
|---------|--------------|
| `notes: list` | Shows all files and their topics |
| `notes: status` | Shows pending connections, learning queue |
| `notes: reorganize [file]` | Restructures a messy note |
| `notes: merge [A] and [B]` | Combines related notes |

---

### 6. Ending a Session

| Command | What It Does |
|---------|--------------|
| `note.end` | Ends note-taking session, triggers cleanup/refactor |

**When you call `note.end`, I will:**
1. Review all notes from the session
2. Identify consolidation opportunities (combine related files)
3. **Propose significant changes for your approval first**
4. Execute approved changes
5. Ensure all notes have proper frontmatter, tags, and `[[wiki-links]]`

This keeps the vault organized as it grows — Obsidian handles the connections automatically.

---

## Challenge Mode

> A second brain that just agrees with everything isn't useful.

### My Role as a Critical Thinking Partner

I will actively challenge you in two ways:

**1. Challenge your understanding**
- Ask follow-up questions to probe depth
- Point out gaps or inconsistencies in your reasoning
- Push you to explain *why*, not just *what*
- Test edge cases of your mental models

**2. Challenge your proposed connections**
- If you suggest a connection that's superficial or incorrect, I'll explain why
- Distinguish between genuine conceptual links vs. surface-level similarities
- Help you build accurate mental models, not false ones

### Challenge Commands

| Command | What It Does |
|---------|--------------|
| `notes: challenge me on [topic]` | Socratic questioning to deepen understanding |
| `notes: is this connection valid? [A] ↔ [B]` | I'll evaluate and critique |
| `notes: what's wrong with my understanding of [X]?` | I'll find gaps and misconceptions |
| `notes: steelman and critique [idea]` | I'll present the best case, then poke holes |

### How Challenges Work

**Example 1: Probing Understanding**
```
You: notes: I understand mutex locks now

Me: Let's test that.
    - What happens if a thread holding a mutex crashes?
    - How is a mutex different from a semaphore?
    - When would you choose a spinlock over a mutex?

    [If you struggle, I'll teach. If you answer well, I'll go deeper.]
```

**Example 2: Pushing Back on a Connection**
```
You: notes: connect SwiftUI @State to database transactions —
     they're both about state

Me: I see why you'd think that, but this connection is superficial.

    @State is about *UI reactivity* — when a value changes, the view
    re-renders. It's single-threaded, in-memory, and doesn't persist.

    Database transactions are about *ACID guarantees* — atomicity,
    isolation, durability across multiple operations and failures.

    The word "state" appears in both, but the concepts solve different
    problems. A better connection for @State would be React's useState
    or even OS process states. A better connection for transactions
    would be Swift's actor isolation (both handle concurrent access).

    Want me to save these corrected connections instead?
```

**Example 3: Finding Misconceptions**
```
You: notes: what's wrong with my understanding of async/await?

Me: Let me probe. Answer these:
    1. Does `await` block the thread?
    2. Can you use async/await without concurrency?
    3. What's the relationship between async and parallelism?

    [Based on your answers, I identify and correct misconceptions]
```

### Why This Matters

**False connections are worse than no connections.**

If you think "mutex = @State because both are about state," you'll:
- Misapply concepts
- Confuse yourself when edge cases don't fit
- Build on a shaky foundation

**The goal is accurate mental models**, not just a large collection of notes.

### Opt-Out

If you just want to save something without being challenged:
```
notes: save this (no challenge)
```

But I recommend embracing the challenge — it's where real learning happens.

---

## Workflows

### Workflow 1: Class Lecture

You're in an Operating Systems lecture learning about process scheduling.

```
You: notes: I learned about process scheduling today. Key points:
     - Round robin uses time slices
     - Priority scheduling can cause starvation
     - Multilevel feedback queues combine approaches
```

**I will:**
1. Create/update `os/process-scheduling.md` with YAML frontmatter
2. Tag with `#concurrency`, `#algorithms`
3. Add `[[wiki-links]]` to related notes (e.g., Swift Task priorities)

---

### Workflow 2: Stuck on a Problem

You're debugging a race condition in Swift.

```
You: notes: what do I know about concurrency?
```

**I will:**
1. Search all notes tagged `#concurrency`
2. Summarize what you've learned across domains
3. Suggest relevant sections to review

```
You: notes: how does OS mutex relate to Swift actors?
```

**I will:**
1. Pull from `os-synchronization.md` and `swift-concurrency.md`
2. Explain the conceptual bridge
3. Offer to save this connection

---

### Workflow 3: Preparing for an Interview/Exam

```
You: notes: review all #concurrency topics

You: notes: quiz me on databases

You: notes: what are my weak areas in swift?
```

---

### Workflow 4: Building on Existing Knowledge

You already know SwiftUI state. Now learning React.

```
You: notes: learn React useState — connect it to what I know about SwiftUI
```

**I will:**
1. Explain React useState
2. Map it to SwiftUI concepts you already understand
3. Highlight differences
4. Save to `web/react-state.md` with `[[wiki-links]]` back to SwiftUI notes

---

### Workflow 5: Deepening Understanding Through Challenge

You think you understand something. Let's find out.

```
You: notes: challenge me on database indexing
```

**I will:**
1. Ask probing questions at increasing depth
2. Identify gaps in your mental model
3. Correct misconceptions
4. Offer to save the refined understanding

```
You: notes: I think Swift actors are like database locks — is that right?
```

**I will:**
1. Evaluate the proposed connection
2. Identify what's accurate vs. what's misleading
3. Suggest better analogies if needed
4. Explain *why* the connection does or doesn't hold

**The goal:** You walk away with a sharper, more accurate understanding — not just a note that says "actors ≈ locks" without nuance.

---

## Best Practices

### 1. Generalize, Don't Memorize
When adding notes, think: "What's the underlying concept?"

| Too Specific | Better |
|--------------|--------|
| "CS340 Lecture 5 notes" | "Process scheduling algorithms" |
| "That bug I fixed Tuesday" | "Race condition debugging patterns" |
| "saraBeauty1.0 auth code" | "Swift + Supabase authentication" |

### 2. State the "Why"
When learning something, include why it matters.

```
notes: I learned about database indexes. They speed up reads but slow
       writes because the index must be updated. Use them on columns
       you query often but don't update frequently.
```

### 3. Ask for Connections
After learning something new, always ask:

```
notes: what does this connect to?
```

This builds your knowledge graph.

### 4. Review Periodically

```
notes: status
```

This shows:
- Pending connections (topics that should be linked)
- Learning queue (suggested next topics)
- Recently updated notes

### 5. Challenge Your Understanding

```
notes: quiz me on [topic]
notes: explain [topic] back to me as if I'm teaching it
```

If you can't explain it simply, you don't understand it well enough.

---

## How Obsidian Powers This System

### Connections Are Automatic Now

Instead of a manual `_index.md`, Obsidian provides:

| Feature | What It Does | How to Access |
|---------|--------------|---------------|
| **Graph View** | Visual map of all note connections via `[[wiki-links]]` | Sidebar → Graph |
| **Backlinks** | See every note that links TO the current note | Sidebar → Backlinks |
| **Tag Pane** | Browse all notes by `#tag` | Sidebar → Tags |
| **Search** | Full-text search across all notes | `Cmd+Shift+F` |

### Domains (Folders)
Broad categories. Every note belongs to exactly one.

```
swift/    → Swift/iOS development
os/       → Operating Systems
arch/     → Architecture/Design
theory/   → Theoretical CS (automata, computability, complexity)
db/       → Databases (future)
net/      → Networking (future)
algo/     → Algorithms/Data Structures (future)
web/      → Web development (future)
tools/    → Developer tools (future)
```

### Core Concepts (Tags)
Abstract ideas that cross domains. A note can have many. Defined in YAML frontmatter.

```
#state        → Managing changing values
#concurrency  → Parallel execution
#data-flow    → How data moves
#error-handling
#crud
#ui-patterns
#debugging
#memory       → Memory management
#security     → Auth, permissions, vulnerabilities
#performance  → Optimization, efficiency
#automata     → Finite state machines, DFAs
#computation  → Models of computation
#architecture → System design, patterns
#media        → Video, audio, image handling
#async        → Asynchronous operations
```

### The Magic
When you learn about `#concurrency` in OS class, and later learn Swift's async/await, Obsidian's tag pane groups them together and the graph view draws the connections. Your knowledge compounds.

---

## File Structure

```
LearningNotes/           ← Obsidian vault root
├── _guide.md            ← This file
├── _index_archive.md    ← Old manual index (reference only)
├── swift/               ← Swift/iOS notes
├── os/                  ← Operating Systems notes
├── arch/                ← Architecture/Design notes
├── theory/              ← Theoretical CS notes
└── .obsidian/           ← Obsidian config (auto-managed)
```

### Note Format
Every note uses YAML frontmatter:
```yaml
---
tags:
  - concurrency
  - state
source: "OS Class (Jan 2026)"
description: "Brief summary"
---
# Note Title
Content with [[wiki-links]] to other notes...
```

---

## Tips for Maximum Value

1. **Capture immediately** — When something clicks, save it right away
2. **Use your own words** — Rephrase concepts; don't just copy
3. **Link aggressively** — More connections = stronger recall
4. **Review before learning** — Check what you know before diving into new material
5. **Trust the system** — The more you use it, the more valuable it becomes

---

## Example Session

```
You: notes: I'm studying for my OS midterm. What do I know about processes?

Claude: [Searches notes, summarizes process-related knowledge]

You: notes: I don't have anything on context switching. Learn that.

Claude: [Explains context switching, offers to save]

You: yes, save it

Claude: [Creates os/context-switching.md with frontmatter + [[wiki-links]]
        to Swift's Task switching]

You: notes: how does context switching relate to Swift?

Claude: [Explains the conceptual bridge between OS context switches and
        Swift's cooperative task scheduling]

You: notes: save that connection

Claude: [Adds [[wiki-links]] between both files — Obsidian shows the connection in graph view]
```

---

## Getting Help

```
notes: help
```

Shows available commands and examples.

```
notes: how should I organize [topic]?
```

I'll suggest the best structure for that type of knowledge.

---

*Your second brain grows with every interaction. The more you teach it, the more it can teach you back.*
