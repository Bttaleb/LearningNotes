# Cyclic vs Acyclic Graph

An **acyclic subgraph** is a subgraph of G = (V, E) that contains **no cycles**.
What is a cycle?
**Cycle**: a sequence of edges v₁ → v₂ → ... → vₖ → v₁ where the start and end vertex are the same and no edge repeats.
## Cyclic vs Acyclic

| | Cyclic | Acyclic |
|---|---|---|
| Definition | Contains at least one cycle — a path that starts and ends at the same vertex without repeating edges | Contains no cycles at all |
| Example | Triangle: A → B → C → A | Tree, forest |
| Edges (connected, n vertices) | ≥ n | Exactly n - 1 if connected (a tree) |
| Paths between vertices | Can have multiple paths between two vertices | At most one path between any two vertices |


## Why it matters for MSTs
A spanning tree must be acyclic: if a subgraph has a cycle, you can remove the heaviest edge in that cycle and still keep everything connected — so a minimum-weight connected subgraph never contains a cycle. That's why [[Greedy Technique#Kruskal's Algorithm|Kruskal's algorithm]] rejects any edge that would form a cycle.

- Connected + acyclic = **tree**
- Acyclic but possibly disconnected = **forest**
- Directed graph with no cycles = **DAG** (directed acyclic graph)
