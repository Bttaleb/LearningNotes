---
title: Integer Container (Practice Assessment)
platform: CodeSignal
type: assessment
language: C++
test-framework: Catch2
path:
course:
lesson: Filesystem with Unit Tests (practice task)
concepts:
  - "[[C++ Containers]]"
status: in-progress
levels-total:
levels-done: 0
score:
time-limit:
date: 2026-11-23
next-review:
tags:
  - codesignal
description: "Multi-level practice assessment: implement an integer container (Add, Delete, GetMedian) behind a C++ interface, graded by unit tests."
---
# Integer Container (Practice Assessment)

> Hub: [[CodeSignal Hub]] · Lesson it builds on: [[Understanding C++ Vectors and Strings]] · Concept: [[C++ Containers]]

---

## 0️⃣ How This Format Works
<!-- This is the shape of the real CodeSignal assessment. Learn the format once so it costs you no time on the real one. -->

**The rules (in my own words):**
- Levels unlock only after the current one passes:
- Score / time:
- Efficiency required?

**The files: what each one is for**

| File                                        | Editable? | What it holds              | Why it's split this way |
| ------------------------------------------- | --------- | -------------------------- | ----------------------- |
| `src/integer_container.hpp`                 | 🔒        | The interface (base class) |                         |
| `src/integer_container_impl.hpp`            | ✏️        | My class's declarations    |                         |
| `src/integer_container_impl.cpp`            | ✏️        | My method bodies           |                         |
| `tests/level_N_tests.cpp`                   | 🔒        | Graded tests               |                         |
| `tests/sandbox_tests.cpp`                   | ✏️        | My own tests (not scored)  |                         |
| `Makefile`, `main.sh`, `run_single_test.sh` | 🔒        | Build + run                |                         |

**How the pieces connect** (interface → impl header → impl source → tests):


**Run Tests: "In Terminal" vs "Structured":**


---

## 1️⃣ Level 1: Add / Delete

**Spec in my own words:**
- `int Add(int value)`:
- `bool Delete(int value)`:

**Trace of the given example:**

| Query        | Returns | State after |
| ------------ | ------- | ----------- |
| `Add(5)`     |         |             |
| `Add(10)`    |         |             |
| `Add(5)`     |         |             |
| `Delete(10)` |         |             |
| `Delete(1)`  |         |             |
| `Add(1)`     |         |             |

**Rules hidden in the example:**
1. Duplicates:
2. Delete removes how many copies:
3. 

**Container choice and why:**


**Design decisions:**
- Where the vector lives (member vs local), and why:
- Why `Delete` searches but `Add` doesn't:

**Final code:**
```cpp

```

**Bugs I hit:**

| Bug | Why it was wrong | Fix |
|---|---|---|
| `sizeof(nums)` for the count |  |  |
| `erase(value)` |  |  |
| Search + condition copied into `Add` |  |  |
| Missing `};` / missing `return` |  |  |
| Wrote my own `Container` class |  |  |

**Tests passed:** 

---

## 2️⃣ Level 2: GetMedian

**Spec in my own words:**
- Return type and what "empty" returns: null optional
- Odd count: the median
- Even count: the leftmost integer from the two middle integers

**Trace by hand:**

| State | Sorted | n | Index | Median |
|---|---|---|---|---|
|  |  |  |  |  |
|  |  |  |  |  |
| `[]` | `[]` | 0 | n/a |  |

**Index math: deriving one expression for both cases:**
- `n / 2` gives (odd / even):
- `n % 2` gives:
- `(n - 1) / 2` gives:
- Why integer division makes this work:

**Design decision: sort a copy vs. sort in place:**

| | Copy | In place |
|---|---|---|
| Memory |  |  |
| Side effects |  |  |
| Forced by a `const` signature? |  |  |

My choice and why:

**New C++ pieces this level used:**
- `std::optional<int>` / `std::nullopt`:
- `std::sort(first, last)`:
- `std::size(...)` vs `.size()`:

**Final code:**
```cpp
int IntegerContainerImpl::Add(int value) {
	nums.push_back(value);
	return nums.size();
}

bool IntegerContainerImpl::Delete(int value) {
	auto it = std::find(nums.begin(), nums.end(), value);
	if (it != nums.end()) {
		nums.erase(it);
		return true;
	}
	return false;
}

std::optional<int> IntegerContainerImpl::GetMedian() {
	std::vector<int> sorted_copy = nums;
	int n = nums.size();
	int median = (n - 1) / 2;
	sort(nums.begin(), nums.end());
	if (nums.size()) {
		return nums[median];
	}
	return std::nullopt;
}
```

**Bugs I hit:**
- 

**Tests passed:** 

---

## 3️⃣ Level 3:
<!-- Copy the level block above when it unlocks -->

---

## 🧱 C++ Concepts This Task Forced Me to Learn
<!-- One line each in my own words. If it's still true outside this task, promote it to a concept note and link it. -->

| Concept | In my words | Swift equivalent | Concept note |
|---|---|---|---|
| Header vs. source (`.hpp` / `.cpp`) |  |  | [[ ]] |
| Include guards (`#ifndef`/`#define`/`#endif`) |  |  | [[ ]] |
| Inheritance `: public Base` + `override` |  |  | [[ ]] |
| `ClassName::method` definitions |  |  | [[ ]] |
| Iterators: `begin()`, `end()`, `find`, `erase` |  |  | [[ ]] |
| Half-open ranges `[first, last)` |  |  | [[ ]] |
| `sizeof` vs `.size()` |  |  | [[ ]] |
| Copy semantics (eager copy vs. Swift COW) |  |  | [[ ]] |
| `std::optional` |  |  | [[ ]] |
| Integer division truncation |  |  | [[ ]] |

---

## 🎯 Assessment Strategy
<!-- What would I do differently with the clock running? -->
- First 2 minutes: 
- Before writing code for a level: 
- When a test fails: 
- Use the sandbox tests for: 

---

## 🔁 Review Log
| Date | Rebuilt from scratch? | Time | Notes |
|---|---|---|---|
| 2026-11-23 |  |  | First attempt |
