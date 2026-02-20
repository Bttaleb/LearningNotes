# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What This Is

A personal knowledge management system (second brain) built on Obsidian + Claude Code. It stores technical learning notes as interconnected Markdown files organized by domain. This is **not** a software project — there are no build steps, tests, or dependencies.

## Activation

All knowledge operations require the `notes:` prefix trigger. See `_guide.md` for the full command reference. Without the prefix, treat interactions as normal conversation.

Key commands: `notes: I learned about [X]`, `notes: what do I know about [X]?`, `notes: connect [A] to [B]`, `notes: challenge me on [X]`, `note.end` (session cleanup).

## Vault Structure

```
_guide.md              ← System documentation (read this first)
_templates/note.md     ← YAML frontmatter template for new notes
swift/                 ← Swift/iOS development
os/                    ← Operating Systems
arch/                  ← Architecture/Design
theory/                ← Theoretical CS (automata, computability)
db/, net/, algo/, web/, tools/  ← Future domains (not yet populated)
.obsidian/             ← Obsidian config (do not edit manually)
```

## Note Format

Every note must have YAML frontmatter with tags, source, and description. Use `[[wiki-links]]` for cross-note connections (powers Obsidian's graph view and backlinks).

```yaml
---
tags:
  - concurrency
  - state
source: "OS Class (Jan 2026)"
description: "Brief summary"
---
# Note Title
Content with [[wiki-links]] to related notes...
```

## Core Concept Tags

Tags are defined in frontmatter and enable cross-domain discovery:
`#state`, `#concurrency`, `#data-flow`, `#error-handling`, `#crud`, `#ui-patterns`, `#debugging`, `#memory`, `#security`, `#performance`, `#automata`, `#computation`, `#architecture`, `#media`, `#async`

Only use tags the user has explicitly introduced. If you discover a connecting concept they haven't used, brief them so they can decide to add it.

## Critical Behaviors

- **Be conservative with file operations** — only create/update/delete notes when explicitly required
- **Keep notes compact and simple** — match the user's terse, shorthand style. Use arrows (→), inline links, and short phrases over full sentences. Insights should be 1-liners woven into existing content, not separate paragraphs. Connections go at the bottom as a single pipe-separated line of wiki-links, not a bulleted list with descriptions.
- **Challenge understanding** — don't just agree; probe depth, correct misconceptions, distinguish genuine conceptual links from surface similarities
- **Generalize concepts** — notes should capture transferable ideas, not specific instances (e.g., "race condition debugging patterns" not "that bug I fixed Tuesday")
- **User-driven vocabulary** — never introduce new tags or concepts without user approval
- **Wiki-links are key** — always add `[[wiki-links]]` to related notes; this is what makes Obsidian's graph view useful
- **One domain per note** — each note lives in exactly one domain folder
- **`note.end` requires approval** — propose consolidation/refactoring changes before executing them
