---
tags:
  - 
source: ""
description: ""
date:
---
- Focus on strings that are IN the language and not strings OUTSIDE of the language
## Problem 1
[{ w | w begins with 1 and ends with 0 }]([[DFA1#^9aumb4rw]])
What do we know?
- a "1" must be accepted first
- if a "0" is accepted first it becomes "dead"
Questions:
- What happens to the state if a 1 is accepted after the 0?
- What happens to state if 0 is accepted first?
- What do we do with 1’s after the first?
![[DFA1]]


## Problem 2
