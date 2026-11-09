---
tags:
  - leetcode
  - index
description: "What each solved problem actually demonstrates — technique, recruiter framing, and vault links. Review before interviews."
---
# Skills Demonstrated — LeetCode

> Talk about the **technique**, not the puzzle. "I solved Merge Two Sorted Lists" is weak; "I'm comfortable with in-place pointer splicing and sentinel nodes" is the signal. The problem is just the evidence.

## Per-problem breakdown

### [[9. Palindrome Number]] — arithmetic / digit manipulation
- **Technique:** reverse a number by pure arithmetic (`%10` reads a digit, `/10` drops one); **half-reversal** to avoid overflow.
- **Signal:** *"I manipulate numbers at the digit level, reason about integer overflow, and hit O(1) space instead of converting to a string."*
- **Concepts:** [[bounded memory]], [[word-RAM model]], [[digit building]], regular-vs-context-free (bounded input → finite → regular), [[pumping lemma]].

### [[Longest Common Prefix]] (14) — multi-string array scan
- **Technique:** **vertical scanning** (compare column `j` across all strings), **monotonic early-stop**, **bounds-check-before-access**; build/return a substring in C via the null terminator.
- **Signal:** *"I reason over many inputs at once, handle the 'for all' quantifier, and guard array bounds before indexing (no segfault on a short string)."*
- **Concepts:** optimization over a set (not a language problem), two size dimensions (`O(n·m)`, not `n²`), *"for-all → the most restrictive element wins"* (shortest string caps the answer), [[Chomsky hierarchy]].

### [[21. Merge Two Sorted Lists]] — linked-list pointer work
- **Technique:** **pointer splicing** (relink `.next`, never copy values), **dummy-head sentinel**, **two-pointer merge**, attach-remainder in one assignment.
- **Signal:** *"I manipulate pointer structures cleanly, use sentinels to erase edge cases, and I know the merge subroutine behind merge sort — in O(1) space."*
- **Concepts:** [[Linked List]], construction/simulation family, merge invariant (consumed ≤ both remaining heads), linked-list-vs-array-vs-graph.

### [[13. Roman to Integer]] — mapping + local lookahead *(verify against your note)*
- **Technique:** symbol→value lookup table; subtract when a smaller symbol precedes a larger one (lookahead).
- **Signal:** *"I design clean mappings and handle local context / one-step lookahead."*

### [[20. Valid Parentheses]] — stack for nesting *(verify against your note)*
- **Technique:** a **stack** to match unbounded nested brackets.
- **Signal:** *"I recognize when O(1) won't work and a stack (context-free) is required."* — the mirror of the others, and a strong signal on its own.

## Cross-cutting meta-skills (the most valuable signal)

| Meta-skill | Where it showed up |
|---|---|
| Ordered guards / bounds-before-use | palindrome `-7` ordering · LCP check-ended-before-index |
| Only stop-conditions `return`; success-exit lives *after* the loop | LCP `return strs[0]` · merge `return dummy.next` |
| Separate auxiliary memory from output | O(1) space claims across all |
| Reason before coding (Define → Classify → Model → …) | the pipeline itself |
| Sentinel + two-cursor patterns ("one anchored, one roams") | merge's dummy/tail |

## Technique-coverage map

| Family | Covered by | Gap to target next |
|---|---|---|
| Arithmetic / digits | 9 | — |
| Array / string scan | 14 | sliding window, two-pointer on arrays |
| Linked list | 21 | reversal, cycle detection (slow/fast) |
| Mapping / lookup | 13 | hash-map frequency counting |
| Stack | 20 | monotonic stack |
| **Not yet covered** | — | **recursion/trees, binary search, hashing, DP, graphs/BFS-DFS** |

★ Before an interview: read the **Signal** line for each, not the code. Then name one *gap* family above and go solve one problem in it.
