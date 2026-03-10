---
tags:
  - coupling
  - encapsulation
source: "SE Lab Week 8 (Mar 2026)"
description: "Encapsulation via private keyword, reducing coupling, constructors"
---
# Encapsulation

## What is encapsulation?
Controlling **what the outside world can access** on your class. You expose a clean interface (`public` methods) and hide the internals (`private` methods and attributes).

Related to [[Abstraction]] — abstraction hides *complexity*, encapsulation hides *access*.

## The Core Insights

### 1. `private` = boundaries, not secrecy
You're telling other code "this is internal, don't depend on it." The insides can change freely without breaking the outside.

### 2. Public methods = contract. Private methods = freedom.
- `public` says "I promise to support this"
- `private` says "I can change this anytime without breaking you"

### 3. Coupling isn't about *how much* you depend — it's about *what* you depend on
Depending on a class is fine. Depending on its **internals** is the problem.
- ✅ Main depends on `createAccount`, `printInvoice` → good (interface)
- ❌ Main depends on `calculateTuition`, `resetAccount` → bad (implementation details)

### 4. Accidental misuse
If it's visible, someone *will* call it for something it wasn't designed for. A developer sees `resetAccount` in the dot list, thinks "I can use that for re-enrollment" — not knowing it wipes payment history.

### 5. The snowball effect
One exposed internal method invites another. Over time Main becomes tangled with the service's guts. Every small change becomes a minefield.

| | Tight Coupling | Snowball Effect |
|---|---|---|
| **What** | One unnecessary dependency exists | Dependencies keep accumulating |
| **When** | Right now, in this code | Over time, as project grows |
| **Analogy** | You walked into the kitchen once | You now live in the kitchen |

Coupling is the disease. The snowball is what happens if you don't treat it.

### 6. The dot operator is your signal
IntelliJ's `object.` dropdown shows what you *should* call. `private` keeps that menu clean and intentional.

## The Pattern
```
Before: Main sees 4 methods → can misuse internals
After:  Main sees 2 methods → clean interface only

public  = Main can call (the "menu")
private = internal only (the "kitchen")
```

## Constructors

A **constructor** is a special method that:
- Has the **same name as the class**
- Has **no return type** (not `void`, not `int`, nothing)
- Runs **automatically** when you write `new ClassName()`

### Default constructor (no params)
```java
public WageCalc() {
    System.out.println("Welcome!");
}
```

### Parameterized constructor
```java
public WageCalc(String name, String role) {
    this.employeeName = name.toLowerCase();
    this.role = role.toLowerCase();
}
```

### Overloading
Two constructors, same name, different parameters. Java picks the right one based on what you pass in:
```java
new WageCalc();                      // calls default
new WageCalc("Alice", "Instructor"); // calls parameterized
```

A constructor only runs the one you call — not both.

## Cross-Language Note
| Concept | Java | Swift | Python |
|---------|------|-------|--------|
| Private method | `private void method()` | `private func method()` | `def _method()` (convention) |
| Constructor | `public ClassName()` | `init()` | `def __init__(self)` |
| Lowercase string | `.toLowerCase()` | `.lowercased()` | `.lower()` |

The keyword changes, the principle doesn't.
