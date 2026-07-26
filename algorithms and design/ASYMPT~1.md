# Asymptotic Analysis — The Three-Layer Basis
**Date:** 2026-07-26
**Session focus:** What an asymptotic bound actually rests on, worked through the O(V+E) analysis of three-color DFS cycle detection.
**Course connections:** [[Algorithm Design]], [[Theoretical Computer Science]], [[Operating Systems]]

## Problem Statement
Derive — and *justify* — the running time of a directed-graph cycle detector implemented as three-color DFS. The real goal wasn't the number O(V+E); it was learning the reasoning an asymptotic claim stands on, so I can reconstruct it on any algorithm.

## The Big Idea
An asymptotic bound is meaningless until you state **what you're counting and under what assumptions.** Every complexity claim silently rests on three layers. When an analysis feels hand-wavy, it's almost always because one of these went unstated:

1. **RAM model** — decides what counts as *one step*. Every primitive operation (arithmetic, comparison, assignment, memory access, pointer follow) is O(1), independent of input size. Total time = number of primitives. Deliberately abstracts away caches, word size, memory hierarchy — that's what keeps the analysis about the *algorithm*, not the machine. ([[Operating Systems]] is where the abstracted-away details, locality and cache misses, come back to bite.)
2. **Cost assignment** — *prices* each operation. The model grants O(1) only to genuine primitives; composite ops need a stated cost, and honesty lives here. A line is O(1) *only* if it decomposes into constantly many primitives.
3. **Case** — picks *which input* you price on: best / worst / average. Distinct from the *bound type* (O / Θ / Ω). People constantly conflate "worst case" with "big-O" — the case is the input, big-O is the growth bound.

## The Reusable Move: every derivation step cashes all three layers
| Derivation step | RAM model | Cost assignment | Case (worst) |
|---|---|---|---|
| **Name V, E** | demands a size parameter to count against | adjacency list is *why* E is a separate term (matrix → O(V²), E vanishes) | scopes bound to largest input |
| **Aggregate loop** (why not V²) | lets you count iterations — loop body is O(1) | O(1) neighbor-step **+ O(1) dict guard** make Σ deg(v) = E | E realized only on the no-prune worst input |
| **Suspicious lines** (`index`, slice) | forces expanding non-primitives → exposes hidden O(V) | `index`=O(len), slice=O(len), len ≤ V | O(V)/call × **1 call** = absorbed; move it inside the loop → O(V·E) |

## Worked Example — three-color DFS cycle detection
- **Pattern:** [[Depth-First Search]] / [[Graph Traversal]], cycle detection via **back edge to a GRAY ancestor**.
- **Three colors:** white = unvisited, gray = on the *current* recursion path, black = fully explored. A gray neighbor = back edge = cycle. Two states (visited/unvisited) can't distinguish "on my path" (cycle) from "finished on another branch" (not a cycle).
- **Data structures:** [[Hash Map]] (color), list as the path/gray-[[Stack]], [[Adjacency List]].

## Complexity
- **Time: O(V + E)** — each vertex entered once (V); neighbor loops summed over all calls touch each edge once via [[Aggregate Analysis]] (Σ deg(v) = E), *not* V×V. Cycle extraction (`path.index` + slice) is O(V) but runs at most once, so it's absorbed.
- **Space: O(V)** — color map + path list + recursion stack each grow with V.
- **Caveats baked in:** adjacency-list representation, average-case O(1) hashing. Change either and the number changes (matrix → O(V²); non-O(1) guard → extra factor across all E iterations).

## Key Code Snippet
```
FUNCTION dfs(v):
    color[v] ← GRAY            // ENTRY: on the active path
    path.push(v)
    FOR each neighbor u of v:
        IF color[u] = GRAY:    RETURN path[u ... end]   // back edge = cycle
        IF color[u] = WHITE:   result ← dfs(u); IF result ≠ null: RETURN result
    color[v] ← BLACK           // EXIT: fully explored
    path.pop(); RETURN null
```

## What Clicked
"Why is it not O(V²)?" is **aggregate analysis**: bound the *total* work across all calls (Σ deg = E), don't multiply a per-call worst case by the number of calls. And the reason `path.index` doesn't wreck the bound is a **worst-case invocation-count** argument (cost per call × number of calls), not a property of the line itself — proven by the counterfactual: move it inside the edge loop and it becomes O(V·E).

## Connections to Coursework
- [[Algorithm Design]]: aggregate/amortized-style reasoning; representation choice (list vs matrix) drives the bound.
- [[Theoretical Computer Science]]: the RAM model as the formal cost model underneath big-O.
- [[Operating Systems]]: the RAM model abstracts away exactly the cache/locality effects OS teaches matter in practice.

## Revisit Cues (Spaced Repetition)
- **~3 days:** State the three layers from memory and, for each, name what it decides (one step / price / which input).
- **~1 week:** Why is the neighbor loop O(E) total and not O(V²)? What one assumption makes that true?
- **~2 weeks:** Redo the analysis assuming an **adjacency matrix** and a **balanced-BST-backed** color map. What changes and why?

## Related Notes
- [[Aggregate Analysis]]
- [[RAM Model]]
- [[Big-O vs Theta vs Omega]]
- [[Depth-First Search]]
- [[Graph Traversal]]
- [[Adjacency List]]

## Next Steps
Attempt the same cycle detection with **Kahn's algorithm** (topological sort via in-degrees) and analyze *its* O(V+E) with the three-layer lens — compare where each layer shows up differently from the DFS version.
