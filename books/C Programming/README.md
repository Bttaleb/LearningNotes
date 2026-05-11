---
type: dashboard
book: C Programming - A Modern Approach (K.N. King)
tags: [moc, c-programming]
---

# C Programming — Vault Dashboard

Notes on K.N. King's *C Programming: A Modern Approach*. Built for Obsidian.

## How this is organized (deliberately small)

| File / folder | What it's for |
|---|---|
| `Chapters/` | One file per chapter. Each is heavily sectioned with `##` headings so you can deep-link to any concept. |
| `Exercises/` | One file per chapter's exercises. |
| `Glossary.md` | Every key term → links to the exact heading in the chapter where it lives. **This is your concept index.** |
| `Cheatsheets/` | Quick-reference tables. Add only when actually useful. |
| `_Templates/` | Templates for new chapter / exercise notes. |

**Connection-making without bloat:** because Obsidian supports `[[Ch07 - Basic Types#int conversions]]`, you can link to a *heading inside another file*. Backlinks and graph view still work. No need for a file per concept.

## Chapters

### Part I — Basic Features
- [[Ch01 - Introducing C]]
- [[Ch02 - C Fundamentals]]
- [[Ch03 - Formatted Input-Output]] ✅
- [[Ch04 - Expressions]]
- [[Ch05 - Selection Statements]]
- [[Ch06 - Loops]]
- [[Ch07 - Basic Types]]
- [[Ch08 - Arrays]]
- [[Ch09 - Functions]]
- [[Ch10 - Program Organization]]

### Part II — Advanced Features
- [[Ch11 - Pointers]] · [[Ch12 - Pointers and Arrays]] · [[Ch13 - Strings]] · [[Ch14 - The Preprocessor]] · [[Ch15 - Writing Large Programs]]
- [[Ch16 - Structures, Unions, and Enumerations]] · [[Ch17 - Advanced Uses of Pointers]] · [[Ch18 - Declarations]] · [[Ch19 - Program Design]] · [[Ch20 - Low-Level Programming]]

### Part III — Standard Library
- [[Ch21 - The Standard Library]] · [[Ch22 - Input-Output]] · [[Ch23 - Library Support for Numbers and Character Data]] · [[Ch24 - Error Handling]] · [[Ch25 - International Features]] · [[Ch26 - Miscellaneous Library Functions]]

> Chapter files are created on demand — only the chapters you've started exist as files. Wiki-links above will show as "unresolved" (faded) until you create them. That's fine and useful: the dashboard shows your reading progress at a glance.

## Tag taxonomy (use consistently in frontmatter)

- `chapter/3` — chapter number
- `topic/io`, `topic/pointers`, `topic/memory`, `topic/types`, `topic/preprocessor`, `topic/strings`, `topic/control-flow`
- `kind/chapter`, `kind/exercise`, `kind/cheatsheet`
- `status/learning`, `status/review`, `status/mastered`

## Workflow

1. **Reading** → open the chapter file. Add `##` sections as you go. Each named concept becomes a heading.
2. **Term shows up again later** → add it to [[Glossary]] as `**term** — see [[ChNN - Title#Section]]`.
3. **Related to an earlier idea** → drop a `[[Ch04 - Expressions#Operator precedence]]` link inline. Backlinks light up automatically.
4. **Practice** → log it under `Exercises/Ch## Exercises.md` with prediction → actual → reflection.
5. **Weekly** → open Graph View, scan for orphan notes (un-linked headings). Decide: link, fold into another section, or delete.
