---
tags:
  - automata
  - computation
  - state
source: "Intro to Theoretical CS — HW1 (Feb 2026)"
description: "A DFA diagram is already an algorithm — code it with a 2D array and a loop."
---

# Implementing a DFA in Code

## How It Works

A state machine in code is three things:

1. **A variable** tracking which state you're in
2. **A table** that says: "given this state + this input → go to that state"
3. **A loop** that reads input one character at a time and follows the table

After the loop, check if you landed on an accepting state. That's it.

```
currentState = startState
for each character:
    currentState = table[currentState][character]
if currentState is accepting → ACCEPT, else → REJECT
```

This works for ANY DFA. Only the table changes.

---

## The Odd-Parity DFA in C++

States track parity of 1's and 0's (e = even, o = odd):
- **ee** (0) — start. Even 1's, even 0's
- **oe** (1) — **accept.** Odd 1's, even 0's
- **oo** (2) — **accept.** Odd 1's, odd 0's
- **eo** (3) — Even 1's, odd 0's

Reading a `1` flips the first letter. Reading a `0` flips the second.

### Transition Table

|  | Input `0` | Input `1` |
|--|-----------|-----------|
| ee (0) | eo (3) | oe (1) |
| oe (1) | oo (2) | ee (0) |
| oo (2) | oe (1) | eo (3) |
| eo (3) | ee (0) | oo (2) |

### Full C++ Code

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    // States: ee=0, oe=1, oo=2, eo=3
    int ee = 0, oe = 1, oo = 2, eo = 3;

    // The transition table — this IS the DFA
    // arr[currentState][input] = nextState
    int arr[4][2] = {
        {3, 1},  // ee: 0→eo, 1→oe
        {2, 0},  // oe: 0→oo, 1→ee
        {1, 3},  // oo: 0→oe, 1→eo
        {0, 2}   // eo: 0→ee, 1→oo
    };

    // Read input from user
    string myString;
    cout << "Enter binary string: ";
    cin >> myString;

    // Run the DFA — start at ee (0)
    int currentState = 0;
    for (int i = 0; i < myString.length(); i++) {
        int input = myString[i] - '0';       // char → int
        currentState = arr[currentState][input]; // follow one arrow
    }

    // Check if we landed on an accepting state
    if (currentState == 1 || currentState == 2) {
        cout << "Accepted" << endl;
    } else {
        cout << "Rejected" << endl;
    }

    return 0;
}
```

The line `currentState = arr[currentState][input]` is the entire DFA running — one arrow followed per character.

---

## Swift → C++ Quick Reference

Same concepts, different punctuation:

| Swift | C++ |
|-------|-----|
| `print("hello")` | `cout << "hello" << endl;` |
| `var x = 5` | `int x = 5;` |
| `readLine()` | `cin >> myString;` |
| `for char in str { }` | `for (int i = 0; i < str.length(); i++) { }` |
| `if x == 0 { }` | `if (x == 0) { }` |
| `[[1,2],[3,4]]` | `int arr[2][2] = {{1,2},{3,4}};` |
| `import SpriteKit` | `#include <iostream>` |
| App starts at `AppDelegate` | App starts at `int main()` |

---

## Two Bugs to Remember

**1. Chars aren't ints in C++**
`myString[i]` gives `'0'` (ASCII 48) or `'1'` (ASCII 49). Using that directly as an array index goes way out of bounds. Fix: `myString[i] - '0'` converts to 0 or 1. Swift won't let you make this mistake — its `Character` type can't be used as a number.

**2. `||` doesn't work like English**
`if (x == 1 || 2)` is always true — C++ reads it as `(x == 1) || (true)` because any non-zero number is truthy. Fix: `if (x == 1 || x == 2)`. Swift catches this at compile time.

---

**See also:** [[theory/dfa|DFA Theory]]
