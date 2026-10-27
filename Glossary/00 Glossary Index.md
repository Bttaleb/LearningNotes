---
type: index
description: "Every definition in the vault, auto-listed by Dataview"
---
# Glossary Index

Every term you've defined. New pages in `Glossary/` appear here automatically.

```dataview
TABLE WITHOUT ID file.link AS "Term", description AS "In one line", source AS "Source"
FROM "Glossary"
WHERE type = "definition"
SORT file.name ASC
```

### Still empty
```dataview
LIST
FROM "Glossary"
WHERE type = "definition" AND (!description OR description = "")
```
