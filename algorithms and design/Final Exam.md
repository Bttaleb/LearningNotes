### Big Picture: Design-Technique Map

**Relate a problem to a smaller/different version of itself**
- How does the reduction happen?

|                            |                                                                                                                              |                                        |
| -------------------------- | ---------------------------------------------------------------------------------------------------------------------------- | -------------------------------------- |
| **Technique**              | **Relationship**                                                                                                             | **Signature**                          |
| Decrease and Conquer (U5)  | Solve **ONE** smaller instance, then extend to full solution                                                                 | Insertion sort, binary search          |
| Divide and Conquer (U6)    | Split into **SEVERAL** subproblems, solve each then combine                                                                  | Mergesort, quicksort                   |
| Transform and Conquer (U7) | **TRANSFORM** into<br>- simpler instance, OR<br>- different representation, OR<br>- different problem<br>**THEN** solve that | Presorting, heap, Gaussian elimination |
| Space-Time trade offs (U8) | **PRECOMPUTE/STORE** extra data for fast queries                                                                             | Counting sort, Horspool, hashing       |
| Dynamic Programming (U9)   | **OVERLAPPING** subproblems solved once and stored in a table (bottom-up)                                                    | Knapsack, Floyd, Warshall              |
| Greedy (U10)               | Build solution by sequence of locally-best, unalterable choices                                                              | Prim, Kruskal, Dijkstra, Huffman       |

### Classic Traps
`DP (Dynamic Programming) vs. D&C (Divide-and-Conquer)`
- Splitting both problems, ***BUT***
- D&C **subproblems** are independent
- DP exists **because** subproblems overlap (makes recursion exponential)
`Greedy vs DP`
- Greedy commits to one choice <- faster but only correct when the choice or optimal substructure holds
- DP considers all choices and picks best (via table)

### Complexity Reference Table

|                        |               |                  |                  |           |
| ---------------------- | ------------- | ---------------- | ---------------- | --------- |
| **Algorithm**          | **Best Case** | **Average Case** | **Worst Case**   | **Space** |
| Insertion Sort         | Θ(n)          | Θ(n<sup>2</sup>) | Θ(n<sup>2</sup>) | Θ(1)      |
| Binary Search          | Θ(1)          | Θ(logn)          | Θ(logn)          | Θ(1)      |
| Topological sort (DFS) | Θ(V + E)      | Θ(V + E)         | Θ(V + E)         | Θ(V)      |
| Mergesort              | Θ(nlogn)      | Θ(nlogn)         | Θ(nlogn)         | Θ(n)      |
| Quicksort              | Θ(nlogn)      | Θ(nlogn)         | Θ(n<sup>2</sup>) | Θ(logn)   |
| Binary Tree Traversal  | 1             |                  |                  |           |
|                        |               |                  |                  |           |
