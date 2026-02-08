---
tags:
  - ui-patterns
  - state
  - data-flow
---

# SpriteKit Touch Handling & Drop Zones


## Core Concept: Touch Lifecycle

SpriteKit uses three methods in `SKScene` to handle touches:

```
touchesBegan  →  touchesMoved (repeats)  →  touchesEnded
     ↓                  ↓                        ↓
Finger lands      Finger slides           Finger lifts
```

**Key insight**: These are the building blocks for ALL gestures. Tap, drag, swipe - they're all just different patterns of this lifecycle.

---

## Tap vs Drag Detection

The same lifecycle serves both - the difference is **distance traveled**.

```swift
// In touchesEnded:
let distance = sqrt(dx*dx + dy*dy)  // Pythagorean theorem

if distance < 10 {
    // Tap — barely moved
} else {
    // Drag — moved significantly
}
```

**Why this matters**: You can't know it's a tap until `touchesEnded`. The user might start touching (tap?) then move (now it's a drag).

---

## Pattern: Tracking Selected Objects

**Problem**: `touchesMoved` fires many times, but you need to know WHICH node to move.

**Solution**: Store a reference when touch begins.

```swift
class GameScene: SKScene {
    var selectedCard: Card?           // What we're dragging
    var dragStartPosition: CGPoint?   // Where it started (for tap detection + return)
}
```

**Why optional?**: `nil` means "nothing selected" — cleaner than a boolean flag.

---

## Step-by-Step: touchesBegan

**Goal**: Find what's under the finger, store it.

```swift
override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
    guard let touch = touches.first else { return }
    let location = touch.location(in: self)

    // nodes(at:) returns ALL nodes at that point, sorted by zPosition
    let touchedNodes = nodes(at: location)

    for node in touchedNodes {
        if let card = node as? Card {    // Safe cast — is it a Card?
            selectedCard = card
            dragStartPosition = card.position
            card.zPosition = 100          // Bring to front while dragging
            break                         // Only select one
        }
    }
}
```

**Concept — Safe Casting (`as?`)**: Returns `nil` if the cast fails, avoiding crashes. The `if let` unwraps it only if successful.

---

## Step-by-Step: touchesMoved

**Goal**: Make the card follow the finger.

```swift
override func touchesMoved(_ touches: Set<UITouch>, with event: UIEvent?) {
    guard let touch = touches.first,
          let card = selectedCard else { return }

    let location = touch.location(in: self)
    card.position = location
}
```

**Concept — Guard with Multiple Conditions**: Both must pass, or we exit early. Keeps code flat instead of nested `if` statements.

---

## Step-by-Step: touchesEnded

**Goal**: Decide if it was a tap or drag, then respond.

```swift
override func touchesEnded(_ touches: Set<UITouch>, with event: UIEvent?) {
    guard let card = selectedCard,
          let startPos = dragStartPosition else { return }

    // Calculate distance traveled
    let dx = card.position.x - startPos.x
    let dy = card.position.y - startPos.y
    let distance = sqrt(dx*dx + dy*dy)

    if distance < 10 {
        // TAP — flip the card
        card.flip()
    } else {
        // DRAG — check if over a drop zone
        if let slot = battleSlotUnderCard(card) {
            snapToSlot(card: card, slot: slot)
        } else {
            returnToStart(card: card, position: startPos)
        }
    }

    // Cleanup
    card.zPosition = 0
    selectedCard = nil
    dragStartPosition = nil
}
```

---

## Pattern: Drop Zones (Battle Slots)

**Problem**: Need visual areas where dragged items can be "dropped."

**Solution**: Use `SKShapeNode` for simple rectangles.

```swift
class BattleSlot: SKShapeNode {
    var isOccupied: Bool = false
    var slotOwner: Player

    init(size: CGSize, owner: Player) {
        self.slotOwner = owner
        super.init()

        // Create centered rectangle
        let rect = CGRect(
            x: -size.width/2,
            y: -size.height/2,
            width: size.width,
            height: size.height
        )
        self.path = CGPath(roundedRect: rect, cornerWidth: 10, cornerHeight: 10, transform: nil)

        // Visual styling
        self.strokeColor = owner == .player1 ? .blue : .red
        self.lineWidth = 3
        self.fillColor = .clear
    }

    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}
```

**Why negative x/y in rect?**: SpriteKit positions nodes by CENTER. To draw a rectangle centered on the node's position, offset by half width/height.

---

## Pattern: Collision Detection for Drop Zones

**Goal**: Check if card overlaps a slot.

```swift
func battleSlotUnderCard(_ card: Card) -> BattleSlot? {
    // frame.intersects() checks rectangle overlap
    if player1Slot.frame.intersects(card.frame) && !player1Slot.isOccupied {
        return player1Slot
    }
    if player2Slot.frame.intersects(card.frame) && !player2Slot.isOccupied {
        return player2Slot
    }
    return nil
}
```

**Why return the slot?**: Caller needs it to snap the card to `slot.position`.

---

## Pattern: Animated Snap

**Goal**: Card smoothly animates to slot center.

```swift
func snapToSlot(card: Card, slot: BattleSlot) {
    let snapAction = SKAction.move(to: slot.position, duration: 0.15)
    snapAction.timingMode = .easeOut  // Fast start, slow end — feels natural
    card.run(snapAction)

    slot.isOccupied = true
    slot.fillColor = UIColor.gray.withAlphaComponent(0.3)  // Visual feedback
}

func returnToStart(card: Card, position: CGPoint) {
    let returnAction = SKAction.move(to: position, duration: 0.15)
    card.run(returnAction)
}
```

---

## Setup: Creating Slots in Scene

```swift
class GameScene: SKScene {
    var player1Slot: BattleSlot!
    var player2Slot: BattleSlot!

    override func didMove(to view: SKView) {
        let slotSize = CGSize(width: 120, height: 180)

        player1Slot = BattleSlot(size: slotSize, owner: .player1)
        player1Slot.position = CGPoint(x: gameArea.midX, y: gameArea.height * 0.25)
        addChild(player1Slot)

        player2Slot = BattleSlot(size: slotSize, owner: .player2)
        player2Slot.position = CGPoint(x: gameArea.midX, y: gameArea.height * 0.75)
        addChild(player2Slot)
    }
}
```

---

## Data Flow Summary

```
┌──────────────────────────────────────────────────────┐
│ touchesBegan                                         │
│   • Find node at touch location                      │
│   • Store reference (selectedCard)                   │
│   • Store starting position (dragStartPosition)      │
└──────────────────────────────────────────────────────┘
                          ↓
┌──────────────────────────────────────────────────────┐
│ touchesMoved (repeats)                               │
│   • Update card.position to follow finger            │
└──────────────────────────────────────────────────────┘
                          ↓
┌──────────────────────────────────────────────────────┐
│ touchesEnded                                         │
│   • Calculate distance from start                    │
│   • distance < 10? → TAP → flip()                    │
│   • distance >= 10? → DRAG → check slots             │
│       • Over slot? → snap to slot                    │
│       • Not over slot? → return to start             │
│   • Clear selectedCard and dragStartPosition         │
└──────────────────────────────────────────────────────┘
```

---

## Common Bugs

| Bug | Cause | Fix |
|-----|-------|-----|
| Card doesn't move | `selectedCard` is nil | Check `nodes(at:)` is finding the card |
| Card stays on top | Forgot to reset `zPosition` | Set `card.zPosition = 0` in touchesEnded |
| Tap always triggers | Distance threshold too high | Lower the `< 10` check |
| Slot detection fails | `frame.intersects` typo | It's `intersects`, not `interesects` |
| Slot detection fails | Slot not added to scene | Call `addChild(slot)` |

---

## Connections

- **SKAction sequences** → Used for flip animation, snap animation
- **Optional chaining** → Safe handling of selectedCard
- **Guard statements** → Early exit pattern keeps code flat
- **Value vs Reference types** → Card is a class (reference), position is a struct (value)
