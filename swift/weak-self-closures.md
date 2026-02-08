---
tags:
  - memory
  - state
source: "Chall4 SpriteKit project (Jan 2026)"
context: "Needed when writing animation closures in SpriteKit/UIKit"
---

# Weak Self in Closures


## The Problem

Closures **capture** variables they reference. When a closure captures `self` (a class instance), it keeps that object alive — even if it should be deallocated.

```swift
// BAD: Strong capture
let action = SKAction.run {
    self.isFaceUp.toggle()  // closure owns 'self' strongly
}
```

**Scenario:**
1. Card starts flip animation
2. Card gets removed from scene mid-animation
3. Closure still holds reference → card can't deallocate → **memory leak**

---

## The Solution

```swift
// GOOD: Weak capture + guard
let action = SKAction.run { [weak self] in
    guard let self = self else { return }
    self.isFaceUp.toggle()
}
```

---

## Breaking It Down

### `[weak self]` — Capture List

```swift
{ [weak self] in
```

- Goes before `in`
- Tells Swift: "Don't keep `self` alive — if it deallocates, set reference to `nil`"
- Makes `self` optional (`GameCard?`) inside the closure

### `guard let self = self` — Safe Unwrap

```swift
guard let self = self else { return }
```

| Condition | Result |
|-----------|--------|
| Object still exists | Unwraps, code continues |
| Object was deallocated | `self` is `nil`, exits early |

---

## When You Need This

| Situation | Need `[weak self]`? |
|-----------|---------------------|
| Closure runs **later** (animations, timers, async) | ✅ Yes |
| Closure **stored** as a property | ✅ Yes |
| Closure runs immediately, not stored | ❌ No |

**Rule of thumb:** If there's a delay between creating and running the closure, use `[weak self]`.

---

## Why This Matters

**Without weak self:**
```
Card → holds → Closure → holds → Card
         (reference cycle = memory leak)
```

**With weak self:**
```
Card → holds → Closure - - -> Card (weak, can break)
         (no cycle, safe to deallocate)
```

---

## SwiftUI vs SpriteKit/UIKit

| Framework | View Type | Need `[weak self]`? |
|-----------|-----------|---------------------|
| SwiftUI | `struct` (value type) | Rarely — structs are copied |
| SpriteKit/UIKit | `class` (reference type) | Often — classes are referenced |

This is why you see this pattern constantly in game dev and UIKit, but less in SwiftUI.

---

## Quick Reference

```swift
// Template for any delayed closure in a class:
someAsyncThing { [weak self] in
    guard let self = self else { return }
    // safe to use self here
}
```
