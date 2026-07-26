# Cycle Detection in a Directed Graph — Presentation Script

**Target time:** ~5 minutes spoken (≈700 words of delivery). Timing markers in each section.
**Delivery cues** are in `[brackets]` — don't read them aloud.

---

## 0. Opening — the problem (≈ 0:30)

> "Our task was: given a directed graph, decide whether it contains a **cycle**, and if it does, return the actual cycle — not just true/false. A cycle means you can start at some vertex, follow the edges, and get back to where you started.
>
> Our input is a set of vertices and an **adjacency list** — for each vertex, the list of vertices it points to. Our output is the sequence of vertices that form a cycle, or nothing if the graph is acyclic."

`[Point at the example graph if you have it on a slide/board: A→B,C,E; B→D; C→B; D→E; E→C. The cycle is C→B→D→E→C.]`

---

## 1. Strategy / approach (≈ 1:15)

> "Our strategy is **depth-first search with the three-color method**. This is the standard way to catch a cycle *while* you traverse, instead of doing extra passes.
>
> Every vertex is one of three colors:
> - **White** — not visited yet.
> - **Gray** — visited and currently **on the active search path** — meaning it's an ancestor in the recursion we're still exploring.
> - **Black** — fully explored, we're completely done with it and everything it reaches.
>
> The key insight is what gray means. If, while exploring, we hit a neighbor that's already **gray**, that neighbor is an ancestor on our current path — so we've found an edge pointing *back up* the path. That's a **back edge**, and a back edge is the definition of a cycle in a directed graph.
>
> Why three colors and not just visited/unvisited? Because *visited* alone can't tell the difference between 'this node is on my current path' — a real cycle — and 'this node I already finished exploring on a totally separate branch' — which is **not** a cycle. Gray versus black draws exactly that line."

`[This is the conceptual heart of the talk. Slow down here.]`

---

## 2. The algorithm in pseudocode (≈ 1:30)

> "Here's the algorithm in pseudocode."

`[Show the pseudocode. Walk the three regions: entry, the neighbor loop, exit.]`

```
FUNCTION findCycle(vertices, adjacency):
    color[v] ← WHITE  for every vertex v
    path    ← empty list          // the current DFS path (our "gray" stack)

    FUNCTION dfs(v):
        color[v] ← GRAY           // ENTRY: v is now on the active path
        path.push(v)

        FOR each neighbor u of v:
            IF color[u] = GRAY:            // back edge → cycle found
                RETURN the slice of path from u to the end
            IF color[u] = WHITE:           // unexplored neighbor
                result ← dfs(u)            // recurse deeper
                IF result ≠ null:
                    RETURN result          // bubble the cycle up

        color[v] ← BLACK          // EXIT: v fully explored
        path.pop()                // step off the path
        RETURN null

    FOR each vertex v:            // start DFS from every unvisited vertex
        IF color[v] = WHITE:
            result ← dfs(v)
            IF result ≠ null:
                RETURN result
    RETURN null                   // no cycle anywhere
```

> "Reading it: when we **enter** a vertex we paint it gray and push it onto the path. We scan its neighbors — if one is gray, we've closed a loop, and we return the portion of the path from that vertex to the end, which *is* the cycle. If a neighbor is white, we recurse. When we've exhausted a vertex's neighbors with no cycle, we paint it **black** and pop it off the path.
>
> The outer loop restarts DFS from every still-white vertex, so we cover **disconnected** graphs too, not just whatever's reachable from one start."

`[If asked why the outer loop matters: a graph can be in several disconnected pieces; a single DFS only reaches one piece.]`

---

## 3. Order of growth (≈ 1:15)

> "For complexity, let **V** be the number of vertices and **E** the number of edges. Our running time is **O(V + E)**.
>
> Here's why. The three-color marking guarantees each vertex is entered by DFS **exactly once** — that's the O(V) term. Inside each vertex we loop over its neighbors; a single vertex could have many neighbors, so it's tempting to say V times V. But that over-counts. Summed across the *whole* run, the neighbor loops touch each edge exactly once — the total is the sum of all the out-degrees, which is exactly **E**. That's the O(E) term.
>
> So it's O(V + E), **not** O(V²) — and that relies on two assumptions: the graph is stored as an **adjacency list** so we only look at edges that exist, and the color lookups are **O(1)** on average.
>
> The one non-obvious cost is extracting the cycle from the path when we find it — that's a linear O(V) operation, but it runs **at most once**, right before we return, so it's absorbed into O(V + E) and doesn't change the bound.
>
> Space is **O(V)**: the color map, the path list, and the recursion stack each grow with the number of vertices."

`[If you want one number to leave them with: "Linear in the size of the graph."]`

---

## 4. Close (≈ 0:15)

> "So, to summarize: three-color DFS detects a cycle in a single linear-time pass by treating a back edge to a gray ancestor as the signal, and it reconstructs the cycle straight from the current path. Happy to take questions."

---

# Q&A Preparation Bank
*(Not part of the 5 minutes — this is for the questions portion.)*

**Q: Why three colors instead of a simple visited/unvisited flag?**
A visited flag can't distinguish a node on the *current* path (gray = real cycle) from a node already fully explored on a *different* branch (black = not a cycle). In a directed graph, revisiting a black node is legal and common; revisiting a gray node is a cycle. Two states can't tell them apart.

**Q: Why is a gray neighbor exactly a cycle?**
Gray means the node is an ancestor still on the recursion stack — there's already a path from it down to the current vertex. An edge from the current vertex back to it closes that path into a loop. That edge is a "back edge," and in a directed graph a back edge ⇔ a cycle.

**Q: Does this work on undirected graphs?**
Not as-is. In an undirected graph the edge you just came in on looks like a back edge to your own parent and gives a false positive. Undirected cycle detection either skips the parent edge or uses union-find. Our method is specifically for **directed** graphs.

**Q: Why O(V + E) and not O(V²)?**
Aggregate analysis. Each vertex is entered once (V). The neighbor loops, summed over all vertices, visit each edge once — total E, not V per vertex. You only hit O(V²) if you use an adjacency *matrix*, where finding neighbors costs O(V) per vertex regardless of how many edges exist.

**Q: What if there are multiple cycles?**
It returns the **first** one it finds, in DFS order. It's a detector, not an enumerator. Finding *all* cycles is a harder problem.

**Q: Could deep recursion overflow the stack?**
Yes — worst-case recursion depth is O(V), so a long chain could overflow on very large graphs. You can convert it to an **iterative** DFS with an explicit stack to avoid that. Same complexity.

**Q: How does this compare to Kahn's algorithm / topological sort?**
Topological sort (Kahn's, using in-degrees and a queue) also detects cycles — if you can't order all vertices, there's a cycle. It's also O(V + E). Advantage of our DFS version: it hands back the **actual cycle vertices**, whereas Kahn's just tells you one exists.

**Q: How do you know it terminates?**
Every vertex is painted gray at most once and never re-entered while gray or black, so DFS makes finitely many calls — bounded by V — and each call does finite work. It must terminate.

**Q: What's the best case vs worst case?**
Best case: a cycle is found almost immediately (e.g., an early self-loop) and we return fast. Worst case — reported as O(V + E) — is an acyclic graph, where we're forced to explore every vertex and every edge before concluding "no cycle."
