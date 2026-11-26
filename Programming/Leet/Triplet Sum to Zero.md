---
title: triplet sum to zero
number: 15
link: https://leetcode.com/problems/3sum
difficulty: Medium
patterns:
  - "[[Two Pointers]]"
data-structures: []
model: fixed value plus a pair
language: C++
status: in-progress
time-spent:
date: 2026-11-25
next-review:
attempts: 1
tags:
  - leetcode
---

---

## 1️⃣ Define (Understand)

**Problem in my own words:**
Given an unsorted array of integers, find every **unique** triplet `[a, b, c]` where `a + b + c == 0`.

**Formal statement:**
- Input: array `arr` of integers (may contain duplicates, may be unsorted)
- Output: list of triplets `[[a, b, c], ...]`, each summing to 0, no repeats
- Kind of problem: decision | **search (find all)** | optimization | counting

**Rules / properties a correct answer must satisfy:**
1. every triplet sums to 0
2. no triplet appears twice (`[-1, 0, 1]` only once, even if the input has two `-1`s)
3. one array position can't be used twice in the same triplet

**Examples I traced by hand:**
```
Input:  [-1, -1, 0, 1]      (sorted)
Naive:  [-1, 0, 1] found at anchor i=0 AND i=1   ← breaks rule 2
Fix:    skip anchor i=1 because arr[1] == arr[0]

Input:  [-3, -1, 0, 1, 2, 3], anchor -3 → target 3
Pairs:  (0, 3) AND (1, 2)   ← one anchor can have MANY pairs, so don't stop at the first match

Input:  [-2, 0, 0, 2, 2], anchor -2 → target 2
Naive:  [-2, 0, 2] recorded twice (left lands on another 0)   ← skip duplicate left/right values too
```

---

## 2️⃣ Classify

**Core question:** Fixed memory? → Yes (apart from the output): an anchor index plus two pointers. Sorting happens in place.

**Problem family:** search
- Structural property: **after sorting, the array is monotonic** (non-decreasing), so moving a pointer always moves the sum in a known direction. Also, **equal values end up adjacent**, which makes duplicates easy to spot.

---

## 3️⃣ Choose the Model
**Model:** [[Two Pointers]], *fixed value plus a pair* variant

**Why:** **Problem reduction**: fix one number `a`, and the question becomes "find `b + c = -a`". That's the sorted pair-sum problem, already solved with converging pointers.

**Signals:** "triplet", "sum to target", "unique" → sort, then use two pointers.

**Naive approach:** three nested loops, plus a set to remove duplicates → Time O(n³). Too slow.

**Similar problems:** [[26. Remove Duplicated from Sorted Array]] (same "duplicates are adjacent, compare to the previous element" trick), [[triplet sum close to target]], [[quadruple sum]]

---

## 4️⃣ Specify the Model (Case Table)

**Outer loop:** what the anchor `i` sees

| Condition | Action |
|---|---|
| `i > 0 && arr[i] == arr[i-1]` | skip: this value was already tried as an anchor |
| otherwise | search for pairs with target `-arr[i]`, starting at `left = i + 1` |

**Inner loop (`searchPair`):** `sum = arr[left] + arr[right]`

| sum vs target | Action                                                                                                                          |
| ------------- | ------------------------------------------------------------------------------------------------------------------------------- |
| ==            | record `[-target, arr[left], arr[right]]`, move **both** pointers, skip duplicate `left` and `right` values, **keep searching** |
| `<`           | `left++` (need a bigger value)                                                                                                  |
| `>`           | `right--` (need a smaller value)                                                                                                |

---

## 5️⃣ Pseudocode
```
searchTriplets(arr):
    sort arr
    for each anchor i (at least 2 elements must remain after it):
        if i > 0 and arr[i] == arr[i-1]: skip
        searchPair(arr, target = -arr[i], left = i + 1)

searchPair(arr, target, left):
    right = last index
    while left < right:
        sum = arr[left] + arr[right]
        if sum == target:
            record [-target, arr[left], arr[right]]
            left++, right--
            while left < right and arr[left]  == arr[left-1]:  left++
            while left < right and arr[right] == arr[right+1]: right--
        else if sum < target: left++
        else: right--
```

**Invariant / why it's correct:** see [[Invariant]]. Everything left of `left` and right of `right` can't pair with the current values to reach the target. Because the array is sorted, each move discards only values that can't be part of an answer.

**Complexity:** Time O(n²) · Space O(1) extra (ignoring output and sort)
- sort = O(n log n)
- n anchors × O(n) two-pointer scan each = O(n²), which dominates

---

## 6️⃣ Build (Code)

> Status: the logic is done. Next step: write the full `searchPair` and the `searchTriplets` body myself.

**Pieces I've derived so far:**
```cpp
// anchor duplicate skip (outer loop)
if (i > 0 && arr[i] == arr[i - 1]) continue;

// inside the match branch, AFTER left++ and right--
while (left < right && arr[left] == arr[left - 1]) { left++; }
while (left < right && arr[right] == arr[right + 1]) { right--; }
```

**Skeleton to fill in:**
```cpp
class Solution {
public:
  static vector<vector<int>> searchTriplets(vector<int> &arr) {
  vector<vector<int>> triplets;
    // sort, result container, anchor loop (safe bound!), return
    sort(arr.begin(), arr.end());
    vector<int> result;
    for (int i = 0; i < arr.size() - 2; i++) {
	    if (i > 0 && arr[i] == arr[i - 1]) {
		    continue;
	    }
	    searchPair(arr, )
    }
  }

private:
  static void searchPair(const vector<int> &arr, int targetSum, int left,
                         vector<vector<int>> &triplets) {
    // declare right
    // while pointers haven't crossed:
    //   sum; match → record, move both, skip loops; too small; too big
  }
};
```

**Line purposes:**
- `i > 0 &&`: guard. At `i = 0` there's no previous element, so `arr[-1]` would be out of bounds.
- `arr[i] == arr[i-1]`: rule. This anchor value was already tried.
- `left < right &&`: guard. Stops the skip loop from running past `right` or off the end of the array.
- skip loops use `while`, not `if`: there can be any number of duplicates in a row.

---

## 7️⃣ Reflect

### Edge cases
- [ ] Empty input / fewer than 3 elements → loop bound must not underflow
- [ ] All zeros `[0, 0, 0, 0]` → exactly one triplet `[0, 0, 0]`
- [ ] Many duplicates `[-2, 0, 0, 0, 2]`
- [ ] Multiple pairs per anchor `[-3, -1, 0, 1, 2, 3]`

### C++ syntax learned (Swift → C++)

| C++ | Swift | Note |
|---|---|---|
| `public:` / `private:` | `public func` / `private func` | C++ uses **section labels** (a colon, then everything below), not a keyword on each function |
| `static` member function | `static func` | a static function can only call other static functions directly (there's no object) |
| `vector<int>` / `vector<vector<int>>` | `[Int]` / `[[Int]]` | |
| `vector<int> &arr` | `inout [Int]` | shared, not copied, can modify |
| `const vector<int> &arr` | a normal parameter | shared, read-only, no copy |
| `triplets.push_back(x)` | `triplets.append(x)` | |
| `void` + `&triplets` param | `inout` result | adds to the caller's container instead of returning new vectors |

### Bounds guards: the recipe
1. Write the rule in English.
2. Translate it to code literally.
3. **Check every index** in the expression: can it go out of bounds?
   - `arr[x - k]` needs `x >= k` → e.g. `i > 0`
   - `arr[x + k]` needs `x + k < arr.size()`
4. Put the guard **first**: `guard && risky access`. `&&` short-circuits, so the risky side only runs if the guard passed. **Order matters in code**, even though `A && B == B && A` in math.
5. Trace the smallest input by hand.

### Gotchas
- **`arr.size()` is unsigned.** `arr.size() - 2` on a 1-element array wraps to a huge number. **Add on the index side** (`i + 2 < arr.size()`) instead of subtracting from the size.
- **Out-of-bounds in C++ is undefined behavior**: it silently reads garbage. Swift would crash instead.
- **`while` conditions mean "keep going while…"**, not "stop when…". I first wrote `!=` when I meant ==

**Bugs I hit:**
- wrote `private void f()` (Java/Swift style) instead of a `private:` section with `static void f()`
- put the duplicate skip loops at the top of `searchPair`. They belong **inside the match branch**. At the top, `arr[left-1]` is the anchor.
- thought I could stop after the first match. One anchor can have several pairs.

### Coursework connections
- Theory of Computation: **reduction**. 3Sum reduces to 2Sum, the same move used to prove undecidability (reduce a known problem to the new one).
- [[Invariant]]: the two-pointer discard argument.

### Takeaways
**What I'd tell myself before attempting this again:**
Fix one, solve the pair. Sort first so duplicates sit next to each other, and compare to the neighbor you came from (`left - 1`, `right + 1`, `i - 1`).

**Mistake to never repeat:**
Never access `arr[i ± k]` without asking "can this index go out of bounds?", and put that guard on the **left** of `&&`.

**Retrieval questions (answer at next review without looking):**
1. What does fixing `a` reduce the problem to, and what's the new target?
2. Why does sorting make two pointers correct? Use the word *monotonic*.
3. Name the three duplicate checks, and which neighbor each one compares to.
4. Why `while` and not `if` for the skip loops?
5. Why must `i > 0` come *before* `arr[i] == arr[i-1]`?
6. Why is `i + 2 < arr.size()` safe but `i < arr.size() - 2` isn't?
7. Complexity, and where each factor comes from?

---

## 🔁 Review Log
| Date | Solved from scratch? | Time | Notes |
|---|---|---|---|
| 2026-11-25 | No (guided, `teach:`) |  | Logic derived; C++ `searchPair` still to write |
