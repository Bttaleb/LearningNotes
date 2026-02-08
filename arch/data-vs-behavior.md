---
tags:
  - architecture
  - data-flow
  - state
source: "Chall4Game project (Jan 2026)"
---

# Separating Data from Behavior


## The Problem

When a class holds both **data** (what something IS) and **behavior** (what it DOES visually), modifying one risks breaking the other. Adding new types means duplicating logic instead of just adding data.

**Example:** A `Card: SKSpriteNode` that stores attack/defense AND handles flip animations. To add a new card type, you're forced to touch the visual class.

---

## The Principle: Structs Hold Data, Classes Do Things

### Structs = Pure Data Containers (Value Types)
- Just properties — no methods that reach outside themselves
- No SpriteKit, no UIKit, no external dependencies
- **Rule of thumb:** If you could print it on a physical card, it's data
- Copied on assignment, so one card's data can't accidentally mutate another's

### Classes = Behavior + Identity (Reference Types)
- Handle rendering, animations, user interaction
- *Receive* data, don't own the definition of it
- Need identity because each instance is unique in the scene

### The Test
> If a struct needs to reach outside itself (modify game state, touch another object), that behavior doesn't belong in the struct.

---

## The Pattern: Data → Factory → View

| Layer | Role | Game Example |
|-------|------|-------------|
| **Data** (struct) | Defines what something IS | `CardData` — stats, abilities, image names |
| **Factory** (static methods) | Builds a view from data | `CardFactory.createCard(type: .knight)` |
| **View** (class/node) | Renders and animates | `Card: SKSpriteNode` — flip, float, drag |

### Mental Model: The Restaurant
- **Recipe** (data) — ingredients and quantities on paper
- **Chef** (factory) — reads recipe, assembles the plate
- **Plate** (view) — what the customer sees and interacts with

The recipe doesn't cook itself. The plate doesn't decide what food goes on it.

---

## When to Apply This

- You have **multiple types** of the same entity (card types, enemy types, weapon types)
- You want to **add new types without touching visual code**
- Your class init has **5+ parameters** that are all just raw values — that's a struct waiting to be extracted
- You're **hardcoding values** in the scene/controller instead of in a definition

---

## Connections

- **Entity-Component pattern** — game dev standard (Unity ECS, Godot). Same idea: entities are just IDs, components are data bags, systems provide behavior
- **Swift struct vs class** — value semantics prevent shared mutable state bugs
- **MVC / separation of concerns** — data layer shouldn't know about the view layer
