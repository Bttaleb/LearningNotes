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

|                                                              |                                 |                                 |                                 |                  |
| ------------------------------------------------------------ | ------------------------------- | ------------------------------- | ------------------------------- | ---------------- |
| **Algorithm**                                                | **Best Case**                   | **Average Case**                | **Worst Case**                  | **Space**        |
| Insertion Sort                                               | Θ(n)                            | Θ(n<sup>2</sup>)                | Θ(n<sup>2</sup>)                | Θ(1)             |
| Binary Search                                                | Θ(1)                            | Θ(logn)                         | Θ(logn)                         | Θ(1)             |
| Topological sort (DFS)                                       | Θ(V + E)                        | Θ(V + E)                        | Θ(V + E)                        | Θ(V)             |
| Mergesort                                                    | Θ(nlogn)                        | Θ(nlogn)                        | Θ(nlogn)                        | Θ(n)             |
| Quicksort                                                    | Θ(nlogn)                        | Θ(nlogn)                        | Θ(n<sup>2</sup>)                | Θ(logn)          |
| Binary Tree Traversal                                        | Θ(n)                            | Θ(n)                            | Θ(n)                            | Θ(n)             |
| Heapsort                                                     | Θ(nlogn)                        | Θ(nlogn)                        | Θ(nlogn)                        | Θ(1)             |
| Heapify (bottom-up)                                          | Θ(n)                            | Θ(n)                            | Θ(n)                            | Θ(1)             |
| AVL Tree                                                     | Θ(logn)                         | Θ(logn)                         | Θ(logn)                         | Θ(n)             |
| Horner's Rule                                                | Θ(n)                            | Θ(n)                            | Θ(n)                            | Θ(1)             |
| Gaussian Elimination                                         | Θ(n<sup>2</sup>)                | Θ(n<sup>2</sup>)                | Θ(n<sup>2</sup>)                | Θ(1)             |
| Comparison / distribution counting sort                      | Θ(n<sup>2</sup>) / Θ(n + range) | Θ(n<sup>2</sup>) / Θ(n + range) | Θ(n<sup>2</sup>) / Θ(n + range) | Θ(n)             |
| Horspool / Boyer Moore                                       | Θ(n/m)                          | Θ(n)                            | Θ(nm)                           | Θ(alphabet)      |
| Hashing                                                      | Θ(1)                            | Θ(1)                            | Θ(n)                            | Θ(n)             |
| Warshall's Transitive Closure                                | Θ(n<sup>3</sup>)                | Θ(n<sup>3</sup>)                | Θ(n<sup>3</sup>)                | Θ(n<sup>2</sup>) |
| Floyd's shortest path                                        | Θ(n<sup>3</sup>)                | Θ(n<sup>3</sup>)                | Θ(n<sup>3</sup>)                | Θ(n<sup>2</sup>) |
| 0/1 Knapsack (DP table)                                      | Θ(nW)                           | Θ(nW)                           | Θ(nW)                           | Θ(nW)            |
| Prim's MST<br>(Minimum Spanning Tree)<br>min-heap + adj list | Θ(E logV)                       | Θ(E logV)                       | Θ(E logE)                       | Θ(V)             |
| Kruskal's MST                                                | Θ(E logE)                       | Θ(E logE)                       | Θ(E logE)                       | Θ(V)             |
| Dijkstra's<br>min-heap                                       | Θ(E logV)                       | Θ(E logV)                       | Θ(E logV)                       | Θ(V)             |
| Huffman Coding                                               | Θ(nlogn)                        | Θ(nlogn)                        | Θ(nlogn)                        | Θ(n)             |
***Θ(nW)*** is a "psuedo-polynomial"
	W is a value, NOT input size

## Unit 5 - Decrease and Conquer