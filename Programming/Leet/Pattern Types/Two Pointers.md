---
title: two pointers
type: pattern
source: Grokking the Coding Interview (Design Gurus)
link:
status: learning
date:
next-review:
related-patterns: []
tags:
  - leetcode
  - pattern
---
# Two Pointers
---

## 0️⃣ The Hook Problem
<!-- The one small example that makes the pattern obvious. Solve it the slow way first, then the pattern way. -->

**Problem:** Given a sorted array and target sum, find two numbers that add to the target

**Brute force:**
- Idea: A *pointer* is an index that shows a position in an array or string
- Complexity: Time O(N^2) · Space O(1)
- What work is wasted? (which checks could never be the answer?)

**Pattern way:**
- Idea: 
- Complexity: Time O( ) · Space O( )

**Trace by hand:**
```
step | state of pointers / window / structure | decision
-----|----------------------------------------|---------
  1  |                                        |
  2  |                                        |
```

---

## 1️⃣ Core Idea
<!-- One or two sentences in my own words. No copying. -->


**The property of the input that makes it work:** (sorted? monotonic? bounded? contiguous?)


**What gets thrown away at each step, and why it's safe:**
<!-- This is the proof. If I can't say it, I don't understand the pattern yet. -->


---

## 2️⃣ How It Works
**Setup (where things start):**

**Each step (what moves, and by what rule):**
1. `left` pointer at first index
2. `right` pointer at last index
3. add `array[left]` and `array[right]`
4. if `sum` == `target`, return both indices
5. if `sum` < `target`, move `left` one step right (gives us a larger value)
6. if `sum` > `target`, move `right` one step left (gives us smaller value)

**Stop condition:**
`left` and `right` meet

**Invariant (true before every step):**


---

## 3️⃣ Recognize It When
<!-- The signals in a problem statement. Rank them strongest first. -->

**Use it when:**
- input is *sorted*
- problem asks for *pair* or *triplet* that meets condition
- change an array *in place*
- asked to use *constant extra space*

**Strongest signal:**
Nested loops

**The question to ask myself:**
> e.g. "Can one pointer replace the inner loop?"

**Don't use it when (and what to use instead):**

| Situation                                              | Use instead            |
| ------------------------------------------------------ | ---------------------- |
| unsorted array, return original indices                | hashmap                |
| contiguous part of array/string that grows and shrinks | sliding window         |
| find a cycle or midpoint in linked list                | fast and slow pointers |
| find one specific value in sorted array                | modified binary search |

---

## 4️⃣ The Template (Skeleton)
<!-- The loop shape that stays the same across problems. Write it from memory, then check. -->
```
function findPair(array, target):
	// setup
    left = 0
    right = length(array) - 1

    while (left < right):
        // test
		sum = array[left] + array[right]
		if sum == target
			return [left, right]
			
        // move rule
        if sum < target
	        left = left + 1
	    if sum > target
		    right = right - 1

    return []
```

**What changes between problems:**

| Part           | Stays the same | Changes per problem |
| -------------- | -------------- | ------------------- |
| Setup          |                |                     |
| Loop condition |                |                     |
| Test           |                |                     |
| Move rule      |                |                     |
| Return value   |                |                     |

---

## 5️⃣ Variants
<!-- One row per variant. The problems column links to my solved notes. -->
Two pointers do no always start at opposite ends, they can move in several ways

| Variant                 | How the pieces move                                          | Signal | Problems                                                                                                   |
| ----------------------- | ------------------------------------------------------------ | ------ | ---------------------------------------------------------------------------------------------------------- |
| Converging              | start @ opposite ends, move inward                           |        | [[pair with target sum]], [[squaring a sorted array]], [[minimum window sort]]                             |
| Same direction          | fast pointer reads, slow pointer writes                      |        | [[find non-duplicate number instances]]                                                                    |
| fixed value plus a pair | one loop fixes a value while two pointers find the remaining |        | [[triplet sum to zero]], [[triplet sum close to target]], [[triplets with smaller sum]], [[quadruple sum]] |
| partitioning            | pointers divide the array into different regions             |        | [[dutch national flag]]                                                                                    |
| one pointer per input   | one pointer moves through each input                         |        | [[comparing strings containing backspaces]]                                                                |

**Start with:**

---

## 6️⃣ Watch Out For
<!-- Mistakes the course warns about, plus ones I actually made. Mark mine with (me). -->
- **Moving the wrong pointer**
- **Moving both pointers after a failed comparison**
- **Using the wrong stopping condition** -> use `left < right` when one value cannot be used twice
- **Forgetting duplicate values** -> skip repeated values when a problem requires unique pairs or triplets
- **Sorting without checking output requirement** -> sorting changes original indices
- **Ignoring the cost of sorting** -> takes O(NlongN) time

---

## 7️⃣ Compare With Nearby Patterns
<!-- The point isn't to list them; it's to know the one difference that decides between them. -->

| Problem Needs:                      | Use:                   |
| ----------------------------------- | ---------------------- |
| pair or triplet in a sorted array   | two pointers           |
| contiguous range that grows/shrinks | sliding window         |
| cycle or midpoint in linked list    | fast and slow pointers |
| one specific value in sorted array  | modified binary search |

---

## 8️⃣ Complexity
- Typical time: O( ) because
- Typical space: O( ) because
- Hidden cost to remember (e.g. sorting first = O(N log N)):

---

## 9️⃣ Problems I've Solved With This
<!-- Pulls every problem note whose `patterns:` field links to this note. Put [[this note's name]] in that field. -->
```dataview
TABLE difficulty, status, next-review
FROM "Programming/Leet"
WHERE contains(patterns, this.file.link)
SORT date ASC
```

**Problems still to do:**
- [ ]
- [ ]

---

## 🔟 Takeaways
**The pattern in one line:**
- Pointer is an *index* that shows a position in an array or string
- Two pointers processes two positions at the same time
- Sorted order tells you which pointer to move
- Each move must safely remove values that cannot be part of the answer

**Connections to coursework:**
<!-- Algorithm Design, Theory of Computation, OS -->
- [[ ]]:

**Retrieval questions (answer at next review without looking):**
1. What property of the input makes this pattern correct?
2. What gets discarded on each step, and why is that safe?
3. Write the skeleton from memory.
4. Name the variants and one signal for each.
5. When does this pattern look right but isn't? What do I use instead?

---

## 🔁 Review Log
| Date | Skeleton from memory? | Signals recalled? | Notes |
|---|---|---|---|
|  |  |  |  |
