# Doppler Simulator

A small C + [raylib](https://www.raylib.com/) program that shows the Doppler effect. Move a "car" around with the arrow keys and watch the sound waves it emits bunch up in front of it and spread out behind it.

```bash
make run
```

Requires raylib installed via Homebrew (`/opt/homebrew`).

---

# Understanding Doppler

The rest of this README is a study guide for the project. It's organized as **layers**. Each layer depends on the one before it, so read them in order. Every layer ends with **Check Yourself** questions. Answer them from memory *before* you open the answers. If you can't explain a layer in your own words, don't move on yet.

| Layer | Topic | What you should be able to do after |
|---|---|---|
| 0 | The big idea (physics) | Explain the Doppler effect without code |
| 1 | Building & running | Explain what `make` does with `main.c` |
| 2 | Data: constants, structs, globals | Draw the program's memory on paper |
| 3 | The game loop | Trace one frame from start to finish |
| 4 | Functions, one by one | Explain every line of `main.c` |
| 5 | Analysis: bugs & design questions | Find what's wrong and argue for a fix |
| 6 | Extensions | Design new features yourself |

---

## Layer 0 — The Big Idea

**What the program does:** a white dot (the "car") moves around a black window. Four times a second it emits a sound wave, drawn as a circle. Each circle grows outward from **the spot where the car was when it emitted it**.

**Why that matters:** that's the whole Doppler effect.

- When the car is still, every circle shares a center, so the rings are evenly spaced.
- When the car moves, each new circle starts a bit further ahead. Rings bunch up **in front** of the car (higher pitch) and spread out **behind** it (lower pitch).

The program never computes "pitch." The effect comes from just two rules:
1. A wave's center is fixed at its birth position.
2. A wave's radius grows at a constant speed.

> Insight: A lot of simulation works this way. You encode simple local rules and the interesting behavior shows up without you programming it directly. The Doppler effect isn't written anywhere in `main.c`. It falls out of rules 1 and 2.

### Check Yourself
1. If wave centers followed the car instead of staying fixed, would you still see the Doppler effect? Why or why not?
2. What would you expect to see if the car moved *faster* than the waves?

<details><summary>Answers</summary>

1. No. Every ring would be centered on the car, so they'd stay concentric however the car moved. The effect depends on waves "remembering" where they were born.
2. The car would outrun its own waves. The circles would form a cone (a **Mach cone**, like a sonic boom) with the car at its tip.
</details>

---

## Layer 1 — Building & Running

**Files:**

| File | Role |
|---|---|
| [main.c](main.c) | All the program's source code (117 lines) |
| [Makefile](Makefile) | The recipe for turning `main.c` into the `doppler` executable |
| [compile_flags.txt](compile_flags.txt) | Tells your editor's language server (clangd) how to read `main.c`, so autocomplete and error squiggles work |
| `doppler` | The compiled program. Generated output, not source |

**The Makefile, decoded:**

```make
CC      = clang                                  # which compiler
CFLAGS  = -Wall -std=c99 -I/opt/homebrew/include # warnings on, C99 standard, where raylib.h lives
LDFLAGS = -L/opt/homebrew/lib -lraylib -framework ...  # where libraylib lives + macOS system frameworks

doppler: main.c          # "doppler" depends on main.c
	$(CC) $(CFLAGS) main.c -o doppler $(LDFLAGS)
```

The rule `doppler: main.c` means "rebuild `doppler` only if `main.c` is newer than it." That's the core idea behind `make`: **dependency tracking based on timestamps**.

Two separate steps happen here:
- **Compiling** (`-I` flag): `#include <raylib.h>` needs the *header*, which promises "these functions exist."
- **Linking** (`-L`, `-lraylib`): the final executable needs the *library*, which holds the actual function code.

> Insight: A header is a menu and a library is the kitchen. `-I` tells the compiler where the menu is, and `-l`/`-L` tell the linker where the kitchen is. If you see "undefined symbol" errors, that's a linking problem. "file not found" for a `.h` is a compiling problem.

**Commands:**
```bash
make run
```
```bash
make clean
```

### Check Yourself
1. You delete the `-lraylib` flag. Does the error appear while compiling or while linking? What would it say?
2. You run `make` twice in a row without editing anything. What happens the second time, and why?
3. Why is `.PHONY: run clean` there? (Hint: what if a file named `clean` existed?)

<details><summary>Answers</summary>

1. While linking. Compiling works because the header is still found, but the linker can't find `InitWindow`, `DrawCircle` and the rest, so it reports undefined symbols.
2. Nothing gets rebuilt ("`doppler` is up to date"). `doppler` is newer than `main.c`.
3. `.PHONY` tells make those targets are commands, not files. Without it, a file called `clean` would make `make clean` think the target is already up to date, and it would do nothing.
</details>

---

## Layer 2 — Data: What the Program Remembers

Before reading any logic, learn the **shape of the data**. Programs are easier to read once you know what they're storing.

### Constants (`#define`) — [main.c:6-11](main.c#L6)

| Name | Value | Meaning | Unit |
|---|---|---|---|
| `WIDTH`, `HEIGHT` | 900, 600 | Window size | pixels |
| `MAX_WAVES` | 50 | Capacity of the waves array | count |
| `WAVE_SPEED` | 50 | How fast a ring's radius grows | pixels / **second** |
| `CAR_SPEED` | 0.5f | How far the car moves per key press | pixels / **frame** ⚠️ |
| `WAVE_EMISSION_FREQUENCY` | 4 | Waves emitted per second | Hz |

`#define` does **text substitution** before compiling. Every `MAX_WAVES` becomes literally `50`. It isn't a variable and takes up no memory.

> Convention: In C, macro constants are written in `SCREAMING_SNAKE_CASE`, so you can tell at a glance that they're compile-time constants and not variables.

Look at the **Unit** column. One of those units doesn't match the others. Remember that for Layer 5.

### Structs — [main.c:16-24](main.c#L16)

```c
struct Car       { float x, y; };      // a position
struct SoundWave { float x, y, r; };   // a center + a radius = a circle
```

A struct groups related values under one name. A `SoundWave` is fully described by 3 floats, and that's all you need to draw a circle.

Why `float` and not `int`? Movement happens in fractional amounts (`0.5f` per frame, `50 * 0.016` per frame). With `int` those would be truncated to 0 and nothing would move.

### Globals — [main.c:14](main.c#L14), [27](main.c#L27), [30](main.c#L30)

```c
int current_waves = 0;              // how many slots of `waves` are in use
struct Car car;                     // the one car
struct SoundWave waves[MAX_WAVES];  // fixed-size storage for rings
```

**Draw it on paper.** `waves` is 50 boxes in a row, each holding `{x, y, r}`. `current_waves` is a separate counter saying how many of those boxes count as "live." The array always has 50 slots; the counter decides how many of them matter.

> Insight: "Fixed-capacity array + count" is one of the most common patterns in C. C arrays can't grow, so you allocate the maximum up front and track how much you're using. In Swift, `Array` hides this from you: it has a `count` and a hidden `capacity`, and it reallocates when full. Here you manage both by hand.

### Check Yourself
1. How many bytes does `waves` take up? (A `float` is 4 bytes.)
2. Why is `current_waves` needed at all? Couldn't `draw_waves` just loop to `MAX_WAVES`?
3. The comment on line 13 says `current_waves` is "unsigned." Is it? Does the comment match the code?

<details><summary>Answers</summary>

1. 50 waves × 3 floats × 4 bytes = **600 bytes**.
2. Globals start zeroed, so unused slots are `{0, 0, 0}`. Drawing them would draw radius-0 circles at the top-left corner (0, 0). The counter keeps you from processing slots that don't hold real data yet.
3. No. It's declared `int`, which is signed. The comment is out of date. Comments that don't match the code are worse than no comments, because they teach the reader something false.
</details>

---

## Layer 3 — The Game Loop

Every real-time graphics program has the same skeleton. Find it in `main()` ([main.c:75-117](main.c#L75)):

```
setup once
while window is open:
    1. INPUT    — read keys
    2. UPDATE   — change the data (move things, spawn things)
    3. DRAW     — render the data to the screen
cleanup
```

Mapped onto the actual code:

| Phase | Lines | What happens |
|---|---|---|
| Setup | 78-84 | Open window, put car in center, cap at 60 FPS, start emission timer at 0 |
| Input | 91-94 | Arrow keys nudge `car.x`/`car.y` |
| Update | 96-104 | Get `dt`, maybe emit a wave, grow every wave |
| Draw | 107-114 | Clear to black, draw car, draw waves |

### Delta time (`dt`) — the key concept

`GetFrameTime()` returns **how many seconds the last frame took** (about 0.0167 at 60 FPS). Multiplying a speed by `dt` turns "per second" into "per this frame":

```
pixels this frame = (pixels per second) × (seconds this frame)
```

This makes motion **frame-rate independent**. On a slow computer running at 30 FPS, `dt` doubles, so each frame moves twice as far, and the motion per second stays the same.

### The emission timer — [main.c:98-103](main.c#L98)

```c
interval += dt;                                   // accumulate elapsed time
if (interval > 1.0f / WAVE_EMISSION_FREQUENCY)    // 1/4 = 0.25 seconds passed?
{
    emit_new_wave();
    interval = 0;                                 // restart the stopwatch
}
```

This is an **accumulator timer**. You add elapsed time every frame and fire when it crosses a threshold. It's the standard way to do "every N seconds" inside a loop that runs every frame.

> Insight: Why `1.0f / WAVE_EMISSION_FREQUENCY` and not `1 / WAVE_EMISSION_FREQUENCY`? In C, `1 / 4` is **integer division** and gives `0`. The `1.0f` makes it floating-point division and gives `0.25`. This bug is easy to miss, and the `.0f` is the only thing preventing it.

### Check Yourself
1. Trace one frame by hand: the car is at (450, 300), the right arrow is held, `interval` is 0.24, and `dt` is 0.016. Write down every value that changes, in order.
2. Why must `ClearBackground` come *before* `draw_car`?
3. What would you see if `ClearBackground(BLACK)` were deleted?

<details><summary>Answers</summary>

1. `car.x` → 450.5. `interval` → 0.256, which is > 0.25, so `emit_new_wave()` runs (new wave at (450.5, 300), r = 0) and `interval` → 0. Then every live wave's `r` grows by 50 × 0.016 = 0.8 (the new wave too, so it ends at r = 0.8). Then the frame is drawn.
2. Drawing order is painting order. Clearing last would paint black over everything you just drew.
3. Every frame would draw on top of the previous ones, leaving smeared trails. The rings would turn into filled-looking blobs.
</details>

---

## Layer 4 — The Functions

| Function | Lines | Job | Reads | Writes |
|---|---|---|---|---|
| `draw_car()` | [33-36](main.c#L33) | Draw the car as a radius-10 circle | `car` | screen |
| `emit_new_wave()` | [39-57](main.c#L39) | Put a new wave at index 0, shift older ones back | `car`, `waves` | `waves`, `current_waves` |
| `draw_waves()` | [59-65](main.c#L59) | Outline every live wave | `waves`, `current_waves` | screen |
| `propagate_waves(dt)` | [67-73](main.c#L67) | Grow every live wave's radius | `dt`, `current_waves` | `waves` |
| `main()` | [75-117](main.c#L75) | Setup + game loop | everything | everything |

Notice the split: `draw_*` functions only **read** state, while `emit_*`/`propagate_*` only **change** state. That's the update/draw separation from Layer 3, applied at the function level.

### `emit_new_wave()` — the tricky one

Its intent is "the newest wave goes at the front, everything else slides back one slot, and the oldest falls off the end." Think of a queue at a counter where new people push in at the front.

It does this in two passes:
1. Copy all of `waves` into a temporary array `copy` (lines 42-46).
2. Write `copy[i]` into `waves[i+1]` for each `i` (lines 47-51), which moves everything one step back.
3. Put the new wave at `waves[0]` (line 53).
4. Increase the count, capped at `MAX_WAVES` (lines 54-55).

**Your task:** before reading Layer 5, trace step 2 on paper for the **last** iteration of the loop. What is `i`? What is `i+1`? Is `waves[i+1]` a real slot?

### Check Yourself
1. Why does `emit_new_wave` need `copy` at all? What goes wrong if you write `waves[i+1] = waves[i]` going *forward* (i = 0, 1, 2...) directly?
2. Why doesn't `propagate_waves` loop all the way to `MAX_WAVES`?
3. `draw_car` takes no parameters but reads `car`. What does it depend on that you can't see from its signature?

<details><summary>Answers</summary>

1. Going forward, `waves[1] = waves[0]`, then `waves[2] = waves[1]`, which is *already overwritten* with the old `waves[0]`. Every slot ends up as a copy of `waves[0]`. The copy avoids this. (A cheaper option exists. See Layer 5.)
2. Same reason as `draw_waves`: slots past `current_waves` aren't real waves yet.
3. The global `car`. Hidden dependencies on globals make functions harder to test and reuse. You can't call `draw_car` for a *second* car.
</details>

---

## Layer 5 — Analysis: What's Wrong & What Could Be Better

The program runs and looks right, but it has real problems. **The fixes aren't given here.** Each item gives you a clue and a question. Find the problem, explain it, then fix it yourself.

### 🐛 Bug 1 — Out-of-bounds write (serious)
**Where:** [main.c:47-51](main.c#L47)
**Clue:** Look at the last iteration of the loop. What's the largest valid index of `waves`? What index does the loop write to?
**Clue 2:** The `if (i < MAX_WAVES)` on line 48 is meant to guard against this. When is that condition ever false inside this loop?
**Why it's sneaky:** `clang -Wall` gives **no warning**, and the program usually seems fine. C doesn't check array bounds, so the write silently lands in whatever memory comes after `waves`. That's **undefined behavior**.
**Question:** Which index should the guard really be checking?

### 🐛 Bug 2 — Mixed units / frame-rate dependence
**Where:** [main.c:10](main.c#L10) and [main.c:91-94](main.c#L91)
**Clue:** Go back to the Unit column in Layer 2. Waves use `* dt`. Does the car?
**Question:** If someone runs this at 120 FPS, does the car get faster, slower, or stay the same? Do the waves? What happens to the Doppler picture?
**Follow-up:** At 60 FPS, what is the car's speed in pixels/second? What fraction of `WAVE_SPEED` is that? (This ratio is the car's "Mach number.")

### 🐛 Bug 3 — Diagonal movement is faster
**Where:** [main.c:91-94](main.c#L91)
**Clue:** Holding RIGHT + UP moves the car 0.5 in x *and* 0.5 in y. How far is that in a straight line? (Pythagoras.)

### 🧹 Stale comments
Find **three** comments that don't match the code (hint: lines 13, 32, 41). For each one, decide whether the code or the comment is wrong.

### 🤔 Design question — Is the copy necessary?
`emit_new_wave` copies 50 structs into a temp array, then copies 50 back, every time it runs.
- **Option A:** Shift in the *other direction* (start from the end) so you never overwrite something you still need. No `copy` array required.
- **Option B:** Don't shift at all. Keep a "next write index" that wraps around with `%` (a **ring buffer**).
- **Option C:** Store newest waves at the *end* instead of the front.

**Evaluate:** Which option does the least work per emission? Which is easiest to read? Does draw order (front-to-back) matter for this program?

> Insight: "Shift everything to insert at the front" costs O(n) per insert. A ring buffer does it in O(1). You'll see ring buffers in OS courses (keyboard buffers, pipes), in networking (packet queues), and in audio (sample buffers).

### Check Yourself
1. Explain undefined behavior in one sentence, in your own words.
2. Why didn't the compiler catch Bug 1?

---

## Layer 6 — Extensions (Design Practice)

Try these only after Layer 5's bugs are fixed. For each one, **write the plan in plain English first**: what new data you need, and which loop phase (input/update/draw) it touches.

1. **Fade old waves:** make rings get dimmer as `r` grows. (Look up raylib's `Fade()` or `ColorAlpha()`.)
2. **Remove off-screen waves:** once a ring's radius is larger than the window diagonal, it's invisible. Should it still use a slot?
3. **Speed control:** keys to raise and lower the car's speed. Can you get it to break the sound barrier and see the Mach cone from Layer 0?
4. **A listener:** place a fixed point on screen. Count how many rings pass it per second, show that number, and watch it change as the car approaches and leaves. *That's the Doppler shift, measured.*
5. **No more globals:** pass `car` and `waves` into the functions as parameters. What do the signatures look like? (Hint: you'll need pointers for the ones that modify data.)

---

## Progress Tracker

- [ ] Layer 0: can explain the Doppler effect from the two rules
- [ ] Layer 1: can explain compile vs. link
- [ ] Layer 2: drew the memory layout on paper
- [ ] Layer 3: traced one frame by hand
- [ ] Layer 4: traced the last iteration of `emit_new_wave`
- [ ] Layer 5: found & fixed Bug 1
- [ ] Layer 5: found & fixed Bug 2
- [ ] Layer 5: found & fixed Bug 3
- [ ] Layer 5: chose and defended a design for `emit_new_wave`
- [ ] Layer 6: built at least one extension
