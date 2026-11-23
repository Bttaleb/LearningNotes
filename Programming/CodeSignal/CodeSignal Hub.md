---
tags:
  - codesignal
  - index
description: "Map of CodeSignal Learn progress: how the platform is organized, how to take notes on it, and a live table of lessons."
---
# CodeSignal Hub

## How the platform is organized
```
Path            (e.g. a full interview-prep track)
 └─ Course      (a topic: data structures, strings, ...)
     └─ Lesson  (1 reading panel + N practice tasks)
         └─ Practice  (run · fix the bug · fill the blank · modify · write from scratch)
```
**One lesson = one note.** Practices live inside the lesson note (callouts), not as separate files.

## Where things go
| What | Where | Why |
|---|---|---|
| Lesson notes | `CodeSignal/<Language>/` | One file per lesson, course stored in frontmatter |
| Template | `CodeSignal/Templates/` | Same shape every lesson, so reviews are comparable |
| Transferable concepts (e.g. containers) | `Programming/Languages/` | Outlives the course; lessons link *to* it |
| Problems solved with it later | `Programming/Leet/` | Proof you can apply it |

## Workflow per lesson
1. Read the panel → fill **1️⃣–5️⃣** *before* touching practices.
2. Each practice: write the approach **before** coding, then the code, then what it tested.
3. Anything that would still be true outside CodeSignal → put it in the concept note, link from here.
4. Set `next-review`, bump `practices-done`, flip `status` to `done`.

## Lessons
```dataview
TABLE WITHOUT ID
  file.link AS Lesson,
  course AS Course,
  status AS Status,
  practices-done + "/" + practices-total AS Practices,
  next-review AS "Next review"
FROM "Programming/CodeSignal"
WHERE platform = "CodeSignal" AND file.name != "CodeSignal Lesson Template"
SORT date ASC
```

## Due for review
```dataview
LIST
FROM "Programming/CodeSignal"
WHERE next-review AND date(next-review) <= date(today)
```
