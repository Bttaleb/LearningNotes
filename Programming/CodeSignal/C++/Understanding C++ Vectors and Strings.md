---
title: Understanding C++ Vectors and Strings
platform: CodeSignal
language: C++
path:
course:
lesson: Understanding C++ Vectors, and Strings
concepts:
  - "[[C++ Containers]]"
status: in-progress
practices-total: 6
practices-done: 0
date: 2026-11-23
next-review:
tags:
  - codesignal
description: ""
---
# Understanding C++ Vectors and Strings

> **Path** → **Course** → **Lesson** · Concept notes: [[C++ Containers]] · Hub: [[CodeSignal Hub]]

---

## 1️⃣ Lesson Reading (the concept)

**Lesson's claim:** C++ containers are *mutable*: you can change their contents after creating them.

**Lesson's example:**
```cpp
#include <vector>

int main() {
    std::vector<int> my_vector = {1, 2, 3, 4};
    my_vector[0] = 100;   // now {100, 2, 3, 4}
    return 0;
}
```

**In my own words:**
A container is a *data structure* that allows for grouping of multiple elements under a single entity.
Containers are **mutable**, meaning we can alter their contents after creation.

**What problem does this feature solve?** (why does it exist at all?)
Allows us to craft more complex operations

**Line by line — what each piece does:**
- `#include <vector>` → allows us to use vector type
- `std::` →look inside the standard libraries namespace
- `vector<int>` → declares our vector, made up of integers
- = `{1, 2, 3, 4}` → an initializer list, where the starting values are handed to the vector
- `my_vector[0] = 100` → overwrites the element at index 0 to 100

**Vectors** are dynamic arrays that also provide several built-in functions for managing the stored data
- `push_back()`
- `insert()`
- `erase()`
- `find()`

---

## 2️⃣ What's Happening in Memory
<!-- Where does the data live (stack/heap)? Who owns it? What happens on copy, on resize, at end of scope? -->


---

## 3️⃣ Swift ↔ C++ Bridge

| Idea | Swift | C++ | Difference that matters |
|---|---|---|---|
| Growable array |  | `std::vector<T>` |  |
| Text |  | `std::string` |  |
| Mutability |  |  |  |

---

## 4️⃣ Operations & Complexity
| Operation | Syntax | Time | Why that cost? |
|---|---|---|---|
|  |  |  |  |

---

## 5️⃣ Gotchas / Undefined Behavior
- 

---

## 6️⃣ Practices

| # | Type | Solved first try? | Concept tested |
|---|---|---|---|
| 1 |  |  |  |
| 2 |  |  |  |
| 3 |  |  |  |
| 4 |  |  |  |
| 5 |  |  |  |
| 6 |  |  |  |

> [!example]- Practice 1
> **Task (my words):**
>
> **Type:**
>
> **Approach before coding:**
>
> ```cpp
>
> ```
> **What it was really testing:**
>
> **Mistake / insight:**

> [!example]- Practice 2
> **Task (my words):**
>
> **Type:**
>
> **Approach before coding:**
>
> ```cpp
>
> ```
> **What it was really testing:**
>
> **Mistake / insight:**

> [!example]- Practice 3
> **Task (my words):**
>
> **Type:**
>
> **Approach before coding:**
>
> ```cpp
>
> ```
> **What it was really testing:**
>
> **Mistake / insight:**

> [!example]- Practice 4
> **Task (my words):**
>
> **Type:**
>
> **Approach before coding:**
>
> ```cpp
>
> ```
> **What it was really testing:**
>
> **Mistake / insight:**

> [!example]- Practice 5
> **Task (my words):**
>
> **Type:**
>
> **Approach before coding:**
>
> ```cpp
>
> ```
> **What it was really testing:**
>
> **Mistake / insight:**

> [!example]- Practice 6
> **Task (my words):**
>
> **Type:**
>
> **Approach before coding:**
>
> ```cpp
>
> ```
> **What it was really testing:**
>
> **Mistake / insight:**

---

## 7️⃣ Reflect

**Compiler errors I hit (and what they actually meant):**
- 

**Connections:**
- Concept note: [[C++ Containers]]
- LeetCode problem where this applies: [[ ]]
- Coursework (OS / Algorithms / Theory): [[ ]]

**Retrieval questions (answer at next review without looking):**
1. 
2. 
3. 

---

## 🔁 Review Log
| Date | Recalled without looking? | Notes |
|---|---|---|
| 2026-11-23 |  | First pass |
