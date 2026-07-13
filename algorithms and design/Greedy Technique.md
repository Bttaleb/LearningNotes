Suggests constructing a solution through a sequence of steps, each expanding a partially constructed solution until complete
Given an optimization problem, it is easy to figure out how to proceed in a greedy manner
Difficult to prove that a greedy algorithm yields an optimal solution

Where can we apply the greedy strategy?
- change making for "normal" coin denominations
- minimum spanning tree (MST)
- single-source shortest paths
- simple scheduling problems
- Huffman codes

Change Making Problem
Given unlimited amounts of coins of denominations d1 > ... > dm, give change for amount n with least number of coins
Example: d<sub>1</sub> = 25c, d<sub>2</sub> = 10c, d<sub>3</sub> = 5c, d<sub>4</sub> = 1c and n = 48
- "Greedy" thinking leads to one quarter, reduces the remaining amount the most, to 23 cents
- Second step, you cannot give a quarter because it violates the problem's constraints
- Best selection in this step = 1 dime, reducing amount to 13c
- Giving one more dime leaves us with 3c, given by 3 pennies

Prim's Algorithm => results in a minimum spanning tree (MST)
Given n points, connect them in the cheapest possible way so there will be a path between every pair of points
The points given can be represented by:
- vertices of a graph
- possible connections by the graph's edges
- connection costs by the edge weights
Then, the question can be posed as the minimum spanning tree problem
Does Prim's always yield a minimum spanning tree?
Yes, it can be proven by induction
How efficient is Prim's?
Depends on:
- Data structure chosen for the graph
- Priority queue of the set V - V<sub>T</sub> whose vertex priorities are the distances to the nearest tree vertices
IF graph is represented by its weight matrix and priority queue is implemented as unordered array, runtime will be in 𝚯(|V|<sup>2</sup>)

Kruskal's Algorithm
Looks at minimum spanning tree of weighted connected graph G = V, E as an acyclic subgraph with |V| - 1 edges for which the sum of the edge weights is the smallest
Step 1: Remove all looks and Parallel Edges
Step 2: Arrange all edges in their increasing order of weight 
Step 3: Start adding edges to the graph beginning from the one which has the least weight without violating the spanning tree properties
- We can consider not including the edge in the graph if, by adding one edge, the spanning tree property does not hold
