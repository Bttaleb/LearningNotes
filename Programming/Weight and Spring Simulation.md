---
tags:
  - state
  - debugging
source: "PhysicsSim project, C + raylib (Oct 2026)"
description: "Real-time spring/string weight simulation in C with raylib: design decisions, physics model, and bugs that taught something"
---

# Weight and Spring Simulation

### What Is It?
- A real-time physics sim, written in **C** and drawn with **raylib**
- The user picks **spring** or **string**, and picks the **mass** of the weight
- Drop the weight:
	- **Spring** → bounces
	- **String** → holds, or **snaps** under a heavy enough load
- Code: `~/Desktop/Projects/PhysicsSim/PhysicsSim.c`

### Roadmap
| Part | Goal                                 | Status                            |
| ---- | ------------------------------------ | --------------------------------- |
| A    | Weight falls under gravity           | ✅ Done                            |
| B    | Weight hangs on a spring and bounces | 🟡 Bounces. Damping not added yet |
| C    | String: holds or snaps               | ⬜                                 |
| D    | UI to pick spring/string + mass      | ⬜                                 |

---

## The Big Idea: The Game Loop Is the Clock
- A simulation has no single answer to compute. **Every frame**: move the world forward a tiny bit of time, then draw it
- The `while (!WindowShouldClose())` loop **is** the simulation clock. One pass = one frame = one time step
	- Don't add another loop inside it to "run the physics". Wrapping the update in a 60x `for` loop would simulate a full second every frame (60x speed)
- Each frame has two phases, kept separate: **1. update the world → 2. draw it**
	- Physics doesn't belong between `BeginDrawing()` / `EndDrawing()`. When something looks wrong, you know which phase to check

---

## Storing Data: State vs. Parameters vs. Constants
**Test:** *"If there were two weights on screen, would each one need its own copy?"*
- Yes → **field** in a struct
- No, it's shared by everything → **constant** (`#define`)

| Value | Kind | Changes per frame? | Where it lives |
| ----- | ---- | ------------------ | -------------- |
| position | **state** | yes | `Ball` field (`Vector2`) |
| velocity | **state** | yes | `Ball` field (`Vector2`) |
| mass, radius | parameter | no | `Ball` field (`float`) |
| anchor | parameter | no | `Spring` field (`Vector2`, it's a **place**) |
| restLength, stiffness | parameter | no | `Spring` field (`float`, a **distance** / a number) |
| gravity, time step, scale | world constant | no | `#define` |

- **State** = exactly what must be carried from one frame to the next. Freeze the sim, keep only the state, and you can continue it exactly
	- Position alone is **not enough**: a ball at y=300 just dropped vs. flying upward after a bounce look identical. **Velocity** (speed + direction) tells them apart
- "Never changes" ≠ "shared by everything". Mass never changes, but it's still per-weight
- **The spring has no velocity or position of its own.** It's pinned to the anchor at the top and to the weight at the bottom, so its shape is fully set by those. Things that **move** have state, and things that **push** only produce forces

### Struct type vs. variable
- `typedef struct { ... } Ball;` = the **blueprint**: lists what every ball *has*. **No values go in here**
- `Ball weight = { .position = {...}, ... };` = one **actual** ball with values
- Type rule: has an x **and** y → `Vector2`. A single number → `float`
	- **Place vs. distance:** a position is a place (`Vector2`). A rest length is *how far* (`float`), used only in the math and never drawn

---

## Decisions & Why

| Decision | Options | Chose | Why |
| -------- | ------- | ----- | --- |
| Language | C, C++, Python bindings… | **C** | raylib is written in C, so the docs and examples match 1:1 |
| Time step | real frame time (`GetFrameTime()`) vs. **fixed** | **Fixed** `1/60 s` | A lag spike with real time = one giant step that can launch the weight past where the spring should've stopped it. Fixed = same result on every machine |
| Update order | position first vs. **velocity first** | **Velocity first** | *Semi-implicit Euler*: compute how fast you should be going now, *then* move at that speed. Stable for springs |
| Units | pixels vs. meters | **1 m = 100 px** | 9.8 px/s² is invisibly slow on a 600 px screen. Keep the real 9.8 and convert |
| Spring direction | 2D vs. **y-only** | **Anchor directly above** | The weight only moves vertically, so stretch is just a difference of y values |
| Anchor type | `float anchorY` vs. **`Vector2 anchor`** | **Vector2** | Drawing needs a `Vector2`, and the string may swing sideways later |

### Constants are *derived*, not hand-typed
```c
#define PIXELS_PER_METER 100.0f
#define GRAVITY (9.8f * PIXELS_PER_METER)   // real-world value, converted
#define FRAMES 60.0f
#define TIME_STEP (1.0f / FRAMES)           // always agrees with FRAMES
```
- Typing `0.016f` by hand was slightly wrong (1/60 = 0.01666…) and **silently** breaks if `FRAMES` changes
- One name = one idea. The scale is a fact about the **screen**, and gravity is a fact about **physics**. They meet in a calculation
- Wrap `#define` expressions in **parentheses**. `#define` is text copy-paste, so `10.0f / HALF` with `HALF` = `1.0f / 2.0f` becomes `10 / 1 / 2`

---

## The Physics Model

### The one equation (Euler integration)
`quantity = quantity + rateOfChange × timeStep`
- Rate of change of **position** = **velocity**
- Rate of change of **velocity** = **acceleration**
- **Forces → acceleration → velocity → position**
- The `quantity +` part is the sim's **memory**. `velocity = gravity * dt` (no `velocity +`) would give constant speed, not acceleration

### Gravity
- Pulls only **down** → only `velocity.y` gets it. Nothing changes `velocity.x`
- **Mass cancels for gravity:** heavier objects get pulled harder *but* are harder to speed up, so every mass falls the same. That's why Part A never used `mass`

### Spring: Hooke's Law
Derived from a no-gravity thought experiment (spring clipped to a wall in space):

| Spring length vs. natural | Force |
| ------------------------- | ----- |
| equal | none |
| 1 cm longer | pulls back |
| 2 cm longer | pulls back **twice as hard** |
| shorter | pushes out |

- Force depends on **one thing only: stretch**, how far it is from natural length. The spring doesn't know gravity exists
- `springForce = -k × stretch`
	- **k (stiffness):** bigger k → faster, shallower bounce
	- **Minus sign:** force points **opposite** the stretch, *back toward rest*. Without it, a stretched spring would pull the weight further away and the sim would explode

### The full chain (what `update_ball` does each frame)
```c
float stretch     = (weight.position.y - light.anchor.y) - light.restLength;
float springForce = -light.stiffness * stretch;
float springAccel = springForce / weight.mass;   // F = ma  →  a = F / m
float totalAccel  = GRAVITY + springAccel;       // forces just add (signs = direction)

weight.velocity.y = weight.velocity.y + totalAccel * TIME_STEP;
weight.position.y = weight.position.y + weight.velocity.y * TIME_STEP;
```
- **Superposition:** forces from different sources add up. Adding a new force later = one more term, nothing else changes
- The spring makes **mass matter**: its force does *not* scale with mass, so `÷ mass` doesn't cancel. Heavier weight → hangs lower
- Stretch is grouped as `(current length) - restLength` so the reasoning shows in the code

### Observed behavior
- Bounces **forever**. Nothing in the chain removes energy (real springs lose it to friction, air, and heat)
- **Speed ≠ frequency.** A heavier weight *moves* through more pixels per bounce, but does it complete more bounces per second? Measure, don't eyeball

---

## Coordinate System Gotcha (hit it 3 times)
- raylib: **(0, 0) = top-left, y grows DOWN**
- So **down = positive y, up = negative y**
	- Gravity is **positive**
	- A stretched spring's pull (up) is **negative**
- **Fix that worked:** draw it and plug in real numbers. "Down is negative" from math class is a coordinate *choice*, not a law

```
y = 100   ●  anchor
          │  restLength = 200
y = 300   ┼  natural end
y = 350   ○  ball → spring is 250 long → stretch = +50 (stretched)
```
- Test formulas on **both sides of zero**. A formula that passes the zero case can still have the wrong sign

---

## Bugs That Taught Something

| Symptom | Cause | Lesson |
| ------- | ----- | ------ |
| Ball doesn't move at all | `#define TIME_STEP (1 / FRAMES)` → **integer division** → `0` | `int / int` throws the decimal away *during* the division. Make one side a float: `1.0f` |
| Ball "falls at constant speed" | `printf` showed velocity **was** increasing. Gravity 9.8 *px*/s² is just too slow to see | When eyes and data disagree, **trust the data**, then ask why your eyes were fooled (units) |
| Blank window / no window | Empty loop, so `EndDrawing()` never ran. Also ran an **old binary** | `EndDrawing()` also polls window events. `./sim` runs the *last compiled* version, so compile and run together |
| Function written but nothing happens | `draw_ball()` / `update_ball()` defined but never **called** | A definition only describes. Nothing happens until something calls it |
| Red squiggles on raylib calls | Editor's language server (clangd) can't find `raylib.h` | Editor ≠ compiler. Fix with `compile_flags.txt` → `-I/opt/homebrew/include` |
| Window wrong shape | `InitWindow(HEIGHT, WIDTH, …)` | Read the signature. The compiler can't catch swapped arguments of the same type |
| `DrawCircle` arg error | Takes `int x, int y`; passed a `Vector2` | Read the signature in the error. `…V` = takes a Vector2 |
| Comment said "under gravity" after adding the spring | Code changed, comment didn't | **Comment drift.** Comments explain *why*. Names and small functions tell the *what* |

### Debugging habit
- When it runs but behaves wrong, the compiler can't help → **`printf` the values you *think* you know**
- Fix compiler errors **top to bottom**, one at a time. The first error often causes the rest

---

## Build & Run
```bash
cd ~/Desktop/Projects/PhysicsSim
cc PhysicsSim.c -o sim $(pkg-config --libs --cflags raylib) && ./sim
```
- `pkg-config` fills in where raylib's headers/libs live (`brew install raylib pkg-config`)
- `&&` = only run if the compile succeeded

---

## Open Questions / Next
- [ ] **Equilibrium:** set `totalAccel = 0` and solve for stretch. Predict where the weight settles, then check on screen
- [ ] **Frequency:** count bounces in 10 s for mass 5 vs. 20. Does heavier bounce faster or slower, and why?
- [ ] **Damping:** add a force that takes energy out so the bouncing dies down
- [ ] **What if** velocity and position were updated in the *other* order? (Try it once the spring works)
- [ ] `radius` field (3) vs. hard-coded `10` in `DrawCircleV`: make drawing use the field
- [ ] Start the weight at `anchor + restLength` (C rule: a **global**'s initial value can't depend on another variable)
- [ ] **Part C — String:** a string **pulls but never pushes**. Closer than its length → **slack**, zero force. It's a one-sided rule, not a stiff spring
- [ ] **Snapping:** compare **tension** against a **breaking strength**, not mass. Light weight dropped from high vs. heavy weight lowered gently: which spikes tension more?

---

## Connections
- [[The Doppler Effect]]: same per-frame position update `x = x + v·Δt`. Both sims are the same game loop moving entities by velocity each step
