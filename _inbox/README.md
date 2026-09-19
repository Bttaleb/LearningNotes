---
type: system
description: "The inbox — raw captures land here before being processed into organized notes"
---

# 📥 Inbox

The **capture zone**. Drop raw, unpolished notes here — ideas, projects, things
you just learned — without worrying about structure, tags, or where they "should"
go. The goal is zero friction: get it out of your head and into the vault. I turn
the dumps into organized notes later.

## How to use it

1. **Capture** — copy `_templates/capture.md` into this folder, rename it, and dump.
   Or just tell me `notes: capture [idea]` and I'll create the file for you.
2. **Let it sit** — captures stay here with `status: raw` until you're ready.
3. **Process** — say `notes: process inbox` (or name a file). I'll:
   - Identify the right domain(s)
   - Split one dump into several focused notes when it covers multiple ideas
   - Add YAML frontmatter, tags (with your approval), and `[[wiki-links]]`
   - Move the finished notes into their domain folders
   - Mark the capture `status: processed` (or archive it)

## Rules

- Nothing here is "final" — it's a staging area.
- One capture can become many notes. That's the point.
- I won't invent tags you haven't approved (see `CLAUDE.md`). Candidates get
  flagged in each capture's *Processing notes* section for you to accept or reject.

## Current captures

- [[rubiks-cube-solver]] — optimal Rubik's cube solver program *(raw)*
