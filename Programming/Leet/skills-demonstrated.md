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

### [[26. Remove Duplicated from Sorted Array]] — in-place two-pointer compaction
- **Technique:** **read/write two pointers** (fast scanner `i`, slow write slot `k`), compare only neighbours (`nums[i] != nums[i-1]`), overwrite in place and return the new length.
- **Signal:** *"I exploit sortedness — duplicates are adjacent, so I never need to remember seen values — and compact an array in place in O(n) time, O(1) space."*
- **Concepts:** structural property drives the model (sorted → adjacent duplicates → no hash set), prefix invariant (`nums[0..k-1]` holds the uniques seen so far).

### [[27. Remove Element]] — in-place filter
- **Technique:** the same **read/write two pointers**, with the keep-test swapped to `nums[i] != val`; `k` is both the write slot and the count.
- **Signal:** *"I recognise a filter as the same compaction pattern as dedupe: one pass, in place, the write index doubles as the answer."*
- **Concepts:** pattern reuse (26 and 27 differ only in the predicate), `k` equals `i` only by coincidence until the first removal.

### [[28. Find Index of First Occurrence in a String]] — brute-force substring search *(C build still empty in the note)*
- **Technique:** **two indices** (`i` = read position in haystack, `j` = chars of needle matched); on mismatch **backtrack** `i = i - j + 1`, `j = 0`; attempt start is derived as `i - j`, never stored.
- **Signal:** *"I can derive an algorithm's rules from hand traces, state its loop invariant precisely, and explain why a single `while` loop is still O(n·m) — the backward jump re-reads characters."*
- **Concepts:** invariant (`needle[0..j-1]` equals `haystack[i-j..i-1]`), derived vs stored state, work-nesting ≠ loop-nesting (multiply, not add), fixed-needle matching is a regular language ([[Chomsky hierarchy]]).

### [[35. Search Insert Position]] — binary search (lower bound)
- **Technique:** **half-open binary search** — `left = 0`, `right = numsSize`; `nums[mid] >= target` → `right = mid` (keep the middle), else `left = mid + 1` (discard it); return `left`. Overflow-safe `mid = left + (right - left) / 2`.
- **Signal:** *"I restate 'found or insert position' as one predicate — the first index where `nums[i] >= target` — so there are no special cases, and I can argue correctness with a loop invariant rather than by testing."*
- **Concepts:** unify cases through a precise output statement, invariant (answer always in `left..right`), Start / Keep / Stop + progress, search space halves each pass → O(log n).

## Cross-cutting meta-skills (the most valuable signal)

| Meta-skill | Where it showed up |
|---|---|
| Ordered guards / bounds-before-use | palindrome `-7` ordering · LCP check-ended-before-index · strStr `i < len(haystack) &&` checked before the read |
| Only stop-conditions `return`; success-exit lives *after* the loop | LCP `return strs[0]` · merge `return dummy.next` · search-insert `return left` · strStr's after-loop `return -1` (reaching it *is* the evidence of no match) |
| Separate auxiliary memory from output | O(1) space claims across all |
| Reason before coding (Define → Classify → Model → …) | the pipeline itself |
| Sentinel + two-cursor patterns ("one anchored, one roams") | merge's dummy/tail · 26/27 write slot `k` vs scanner `i` |
| Trace table → rule table → code (one row per decision; columns = what changes or gets checked) | strStr's four rules · search-insert's five rules, both read off hand traces |
| Pick trace inputs by "which event haven't I seen yet?"; re-test any rule on a second input | strStr `"aab"` / `"xxab"` / `"aa"` (two rules looked right by coincidence on one input) |
| Every branch must make progress toward stopping | strStr `i - j` → `i - j + 1` · search-insert `left = mid` → `left = mid + 1` (both found as a repeated trace row) |
| Loop invariant in the loop's own variables: Start / Keep / Stop | strStr matched-stretch invariant · search-insert `left..right` |
| A precise output statement removes special cases and gives the initial state | search-insert "first index where `nums[i] >= target`, or `numsSize`" → `right = numsSize` |

## Technique-coverage map

| Family | Covered by | Gap to target next |
|---|---|---|
| Arithmetic / digits | 9 | — |
| Array / string scan | 14 | sliding window |
| Two pointers on arrays (in place) | 26, 27 | opposite-ends two pointers (two-sum on sorted, reverse in place) |
| String matching | 28 (brute force) | linear-time matching that never moves `i` backwards (KMP) |
| Binary search | 35 (lower bound) | binary search on a rotated array, binary search on the answer |
| Linked list | 21 | reversal, cycle detection (slow/fast) |
| Mapping / lookup | 13 | hash-map frequency counting |
| Stack | 20 | monotonic stack |
| **Not yet covered** | — | **recursion/trees, hashing, DP, graphs/BFS-DFS** |

★ Before an interview: read the **Signal** line for each, not the code. Then name one *gap* family above and go solve one problem in it.
