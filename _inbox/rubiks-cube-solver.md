---
type: capture
status: raw
tags: []
created: 2026-09-19
description: "Program that computes the shortest (optimal) solution to a Rubik's cube from a scramble or entered permutation"
---

# Rubik's Cube Solver

> **Raw capture.** Dump freely below. When ready, say `notes: process inbox`
> and I'll break this into organized notes (algorithms, theory, project design).

## What is it?
A program that takes a scrambled 3x3 Rubik's cube — either a sequence of moves
(a scramble) or a directly entered cube permutation — and returns the **shortest
possible solution** (optimal, minimum move count), not just *a* solution.

## Why it matters / why I care
- It's a real search / optimization problem with a huge but finite state space.
- "Optimal" is the hard, interesting part — a working solver is easy; a
  *shortest* solver forces real algorithm + heuristic design.
- Ties together things I'm already studying: search algorithms, complexity,
  state machines, and low-level performance.

## Brain dump
<!-- Add your own thoughts here — anything below the line is my seed material. -->
Building in stages
- Stage 1 
	- Cube data model
	- legal-move function
	- apply/undo
	- is-solved check
	- scrambler
- Stage 2
	- Wire dumb layer-method or BFS
	- The point is to scramble-in -> moves-out loop (test correctness against)
- Stage 3
	- Build Korf or Kociemba
- Stage 4
	- Interactive/animation layer


### What's the right unit to use for the data model?
What's the smallest thing that moves? (atomicity)
WRONG: The stickers (54)
- cause overhead -> comparing a single move like R leaves most of the cube alone
What are our rigid bodies?
- 3-sticker corner pieces -> 8
- 2-sticker edge pieces -> 12
- 1-sticker center pieces (fixed frames of reference) == NOT variables
This makes it so we have 20 moving pieces instead of 54 stickers

Permutation - where is it? (which of the 8 corner/12 edge slots is this piece sitting in)
Orientation - which way is it twisted/flipped?

In this manner, a cube state is now four small arrays (coordinates for Kociemba's algorithm)
1. corner position
2. corner orientation
3. edge position
4. edge orientation

How do we validate user's input?
- Decompose the entered corner and edge permutation into swaps, count them, add
- Odd total -> reject: "this isn't a real cube"
### Permutation Parity
"Permutation" -> A rule that sends each position to another position
"Parity" -> a relation between a pair of integers:
- if both are odd or both are even, they have the same parity
- if one is even and the other is odd they have different parity
Ex. 4 chairs
- person in chair 1 -> chair 2
- person in chair 2 -> chair 3
- person in chair 3 -> chair 4
- person in chair 4 -> chair 1

This gives us 4 cycles
A 3 cycle looks like
(1 2 3) = "1->2, 2->3, 3->1" = (3, 1, 2)
- swap 1 and 2
- swap 2 and 3
**2 transpositions**
The pattern generalizes to:
- 2 cycle = 1 swap
- 3 cycle = 2 swaps
- 4 cycle = 3 swaps
- k cycle = k-1 swaps

Q1. A U turn's *corner* cycle is 3 swaps (odd). It's *edge* cycle is 4 (3 swaps, also odd). Even or odd overall?
A1. One quarter turn changes total parity by odd + odd (3+3) = 6, even

Walking the chain:
- start solved, total parity = even (zero swaps)
- each quarter turn adds an even amount (Q1)
- even + even + even + ... **is always even**
- so every reachable state has an even total permutation parity
### Law of the Cube
1. Total permutation of corners and edges together is always even = 2
2. Corner Orientation = 3
3. Edge Orientation = 2
2 x 3 x 2 = 12

| Law                | Conserved Quantity       | Last Piece Forced  | Divides By |
| ------------------ | ------------------------ | ------------------ | ---------- |
| Permutation Parity | total swaps even         | last swap's parity | 2          |
| Corner Orientation | sum of twists ≡ 0(mod 3) | 8th corner's twist | 3          |
| Edge Orientation   | sum of flips ≡ 0(mod 2)  | 12th edge's flip   | 2          |
Every row is a validation gate where:
sum of twists mod 3, reject if its a nonzero
sum of flips mod 2, reject if its a nonzero
permutation parity, reject if its an odd




## What I already know
<!-- Fill in your current understanding so I can pitch the notes at the right level. -->
-

## Open questions / what I need to figure out
- Which cube **representation**? (facelet colors vs. cubie permutation+orientation)
- Which **move metric** defines "shortest"? (HTM — half-turn, vs. QTM — quarter-turn)
- **True optimal** (Korf-style IDA* + pattern databases) or **near-optimal but fast**
  (Kociemba two-phase)? Different projects, different difficulty.
- What language? (C for speed + ties to my C course, or Swift for a UI later?)
- How does the user **input** a cube — type a scramble, enter colors, camera later?
- How big do the **pruning/pattern-database tables** get, and can I hold them in memory?

## Sources / links
-

---
<!-- ↓ Claude's processing notes — my read on how this becomes vault notes ↓ -->
### Processing notes (Claude)

**Candidate domain(s):**
- `algorithms and design/` — the search + heuristics core (your strongest fit)
- `theory/` — state space size, group structure, why it's finite
- a new `projects/` domain (or `books/`-style project folder) for the build itself

**Candidate tags (need your OK — none of these are in your approved list yet):**
- `#search` — IDA*, BFS, pruning
- `#optimization` — minimizing move count
- `#group-theory` — the cube as a permutation group
- `#data-structures` — pattern databases, encoding cube states compactly
- (already-approved tags that apply: `#performance`, `#computation`)

**Notes this capture would likely spawn:**
1. **Cube state representation** (`algorithms and design/`) — facelet vs. cubie
   model; encoding a state as permutation + orientation; why the choice drives
   everything else.
2. **The state space** (`theory/`) — ~4.3x10^19 reachable states; God's Number
   (20 HTM / 26 QTM); why brute-force BFS is impossible and what that implies.
3. **IDA\* + pattern databases** (`algorithms and design/`) — iterative-deepening
   A\*, admissible heuristics from precomputed pattern DBs (Korf 1997). This is
   the heart of an *optimal* solver.
4. **Two-phase algorithm** (`algorithms and design/`) — Kociemba's method:
   fast, near-optimal, the practical alternative. Good compare/contrast with #3.
5. **Project design note** (`projects/`) — input format, module layout, memory
   budget for tables, milestones.

**Connections to existing vault:**
- [[Greedy Technique]] and Branch & Bound (you have `Excalidraw-Branch&Bound`) —
  IDA\* is the systematic-search cousin; good "why greedy fails here" contrast.
- [[Cyclic vs Acyclic Graph]] / Graph Traversal — the cube is a giant graph;
  solving = shortest path. BFS/DFS trade-offs connect directly.
- `theory/dfa.md` — both are finite state systems; useful analogy, with the
  caveat that the cube graph is astronomically larger.
- Your C Programming book notes — a natural language choice for the performance-
  critical table generation.

*(When you say `notes: process inbox`, I'll confirm tags with you first, then
create these as real notes with frontmatter and wiki-links.)*
