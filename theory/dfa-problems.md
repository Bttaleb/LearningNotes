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
{ w | w contains >= 3 1’s }
What do we know
- State wont be accepting if it’s LESS THAN 3
- Doesn’t care about 0’s
![[DFA2]]

## Problem 3
{ w | w contains 0101 as a substring }
What we know
- string can start and end with anything
![[DFA3]]

Problem 4
DFA that accepts all strings over {0,1} of length 2
![[DFA4]]

Problem 5
Accepts any strings over {a,b} that DOES NOT contain the string ”aabb” in it