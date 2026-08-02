### Big Picture: Design-Technique Map

**Relate a problem to a smaller/different version of itself**
- How does the reduction happen?

|                                 |                                                                                                                              |                                                                        |
| ------------------------------- | ---------------------------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------- |
| **Technique**                   | **Relationship**                                                                                                             | **Signature**                                                          |
| Decrease and Conquer (U5)       | Solve **ONE** smaller instance, then extend to full solution                                                                 | - Topological Sort<br>- Insertion sort<br>- Binary search              |
| Divide and Conquer (U6)         | Split into **SEVERAL** subproblems, solve each then combine                                                                  | - Quicksort / Hoare's Partition<br>- Mergesort                         |
| Transform and Conquer (U7)      | **TRANSFORM** into<br>- simpler instance, OR<br>- different representation, OR<br>- different problem<br>**THEN** solve that | - Heap Construction (heapify)<br>- Presorting                          |
| Space-Time trade offs (U8)      | **PRECOMPUTE/STORE** extra data for fast queries                                                                             | Counting sort, Horspool, hashing                                       |
| Dynamic Programming (U9)        | **OVERLAPPING** subproblems solved once and stored in a table (bottom-up)                                                    | - Coin-row<br>- Coin-Change<br>- 0/1 knapsack<br>- Floyd<br>- Warshall |
| Greedy (U10)                    | Build solution by sequence of locally-best, unalterable choices                                                              | Prim, Kruskal, Dijkstra, Huffman                                       |
| Backtracking / Branch and Bound | Build state-space tree, with bounds                                                                                          | Assignment Problems                                                    |

### Classic Traps
`DP (Dynamic Programming) vs. D&C (Divide-and-Conquer)`
- Splitting both problems, ***BUT***
- D&C **subproblems** are independent
- DP exists **because** subproblems overlap (makes recursion exponential)
`Greedy vs DP`
- Greedy optimizes the next step, DP optimizes the whole path
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

## 1. Topological Sorting -> Source-Removal Algorithm
**Main Idea** -> Given `directed acyclic graph (DAG)`
- Linear ordering of vertices such that every edge points "forward"
	-  If there's an edge 'u' -> 'v', then u comes before v in the list
**Analogy** -> Getting dressed
- Socks before shoes, shirt before jacket
- Some items have no orders between them (sock vs. shirt)
**The Removal Algorithm**
1. Find a source (vertex with nothing pointing to it)
2. Add it to output list and remove it from graph (delete it and all outgoing edges)
3. Removing it drops its neighbors
4. Repeat until graph is empty
![[Excalidraw-topological_ordering]]

## 2. Array Partition -> Hoare's Algo
**Main Idea** -> Partitioning is the `engine` inside quicksort (Divide & Conquer)
- Pick a pivot, rearrange everything so that:
	- Everything **less than or equal to** pivot sits to its left
	- Everything **greater than or equal to** pivot sits to its right
**Analogy** -> Sorting a room of people by height around one "reference" person
- Send shorter people left, taller people right
- After shuffle, reference person is standing where they'll finish;
	- the two groups are still jumbled, to be sorted later
**Hoare's Partition** -> 
`r` and `l` = index bounds of the subarray: `A[l..r]`, where:
	`l` is the leftmost index; $l = 0$
	`r` is the rightmost index; $r=n-1$ 
Pivot `p` = `A[l]`, (first element) 
`i = l` , `j = r + 1` 
Scan `i` **rightward**, stopping @ first element **greater than or equal to** `p`
Scan `j` **leftward**, stopping @ first element **less than or equal to** `p`
If `i < j`, swap A[i] and A[j], continue
When `i` is **greater than or equal to** `j`, stop and swap pivot into place: swap A[l] and A[j]
Now `j` is the split point
![[Excalidraw-Hoare]]

## 3. Heap Construction -> Bottom-up Heapify
**Main Idea** -> **Max-heap** is a complete binary tree (stored as array) where;
- every parent is **greater than or equal to** its children
- turns array into heap in Θ(n) time (transform and conquer)
**Analogy** -> Corporate reorganization from bottom up
- start a lowest managers who have reports (last non-lead node)
- for each, if subordinate outranks the boss, promote strongest subordinate
- sifting weaking manager down until they sit above ONLY weaker people
- working upward
**Algorithm** -> for `i` from **last parent** (index [n/2] - 1) **down to 0**
- sift A[i] down; repeatedly compare with its larger child
- if child is bigger, swap and continue from child's position
- stop when node is **greater than or equal to** both children or becomes a leaf
![[Excalidraw-Heapify]]

## 4. MST -> Kruskal's
**Main Idea**: an MST of *weighted connected graph* is **acyclic**
- Exactly |V| - 1 edges
**Analogy** -> Laying the cheapest possible road network to connect every town
- Lay cheapest first
- Skip roads whose two towns are **already connected** by roads you've built
**Algorithm**
1. Sort all edges by increasing weight
2. Go through them in order, add edge if it **does not** create a cycle
3. Stop when you have |V| - 1 edges
*If adding an edge closes a cycle, heaviest edge in that cycle is never needed*
![[Excalidraw-MST(Kruskal)]]

## 5. MST -> Prims
**Main Idea** -> Greedy by vertex: grow one tree outward from smart vertex
- each step adding the cheapest edge that connects a new vertex
**Analogy** -> A spreading vine from one seed, at any moment the vine reaches out along its single cheapest available tendril to gran one new, not-yet reached point.
- Always one connected plant, never separate pieces (key difference from Kruskal's which can grow several forest fragments)
**Algorithm** -> 
1. Start from any vertex; put it in the tree V<sub>T</sub>
2. Look at all edges crossing from V<sub>T</sub> to outside vertices. Pick the minimum-weight such edges.
3. Add that edge and its new vertex to the tree
4. Repeat until all vertices are in the tree (|V| - 1 edges added)
![[Excalidraw-Prims]]

### Prim vs Kruskal
**Prim**'s keeps *one growing connected tree* & picks cheapest edge
**Kruskal**'s picks *globally cheapest edge* and may build several fragments that merge later

## 6. Comparison Counting Sort
**Main Idea** -> Space-Time tradeoff
- Instead of moving elements around by comparison, count for each element how many other smaller than it
**Analogy** -> Assigning race finishers to podium positions by tallying wins
- For each runner, ask "how many runners did you beat?"
- If you beat 3 others, you finish in position 3 (idx 0), every runners beat-count is their finishing slot
**Algorithm** -> For each pair (i, j) with i < j;
	if A[i] < A[j], increment Count[j],
	else, increment Count[i]
- After all pairs, Count[i] = number of elements smaller than A[i]
- Place each A[i] into output position Count[i]
![[Excalidraw-Comparison_counting]]

## 7. Coin-Row Problem (Dynamic Programming)
**Main Idea** -> A row of n coins with values c<sub>1</sub>...c<sub>n</sub>. Pick coins for **MAX TOTAL VALUE**, but not two adjacent coins
- Define a named quantity for a sub-instance, find recurrence, fill table bottom-up
**Analogy** -> Walking down a buffet where you may take dishes, but never two dishes sitting next to each other. At each dish, **take it** (previous dish is restricted), or **skip it** (keep whatever you'd accumulate up to the previous dish)
**The Recurrence** -> F(i) = max amount obtainable from first `i` coins
- **Take coin `i`** -> get c<sub>i</sub> plus best from coins 1..i-2 (coin i-1 is forbidden)
	- c<sub>i</sub> + F(i-2)
- **Skip coin `i`** -> keep F(i-1), F(i) = max((F(i-1), c<sub>i</sub> + F(i-2)), with F(0) = 0, F(1) = c<sub>1</sub>
![[Excalidraw-CoinRow]]

## 8. Money Change (Minimum Coins DP)
**Main Idea** -> Given coin denominations and target amount;
- use fewest coins to make exactly that amount (bottom-up DP), **indexed by amount** rather than position
**Analogy** -> Filling a jug to an exact line using cups of fixed sizes, minimizing pours
- To reach the 10-mark, ask for each cup size `c`, "what's the fewest pours to reach 10-c?" 
- `10-c` is an **amount**, -> where the jug was sitting at *before* your final pour
- The number of pours to reach that level is `F(10-c)`
**The Recurrence** -> F(m) = fewest coins to make amount `m`; "what was the last coin I added to make amount m?"
- Suppose last coin is c<sub>j</sub>.
- Before placing, we already made m - c<sub>j</sub> 
- F(m) = min over each coin c<sub>j</sub> <= m of (F(m-c<sub>j</sub> + 1)), with F(0) = 0
	`+1` = the one coin you're placing right now
	F(m-c<sub>j</sub>) = "solve the same problem on what's left"
	![[Excalidraw-MoneyChange]]