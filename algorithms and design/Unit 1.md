Why study algorithms?
1. Practical standpoint -> have to know a standard set of important algorithms from different areas of computing
2. Theoretical standpoint ->Algorithmics (study of algorithms), recognized as the cornerstone of CS. More than a branch of CS; the core of computer science 
What is an algorithm?
- sequence of unambiguous instructions for solving a problem
## 3 methods of solving the same problem: `computing the greatest common divisor of two integers`
### 1. Euclid's Algorithm -> repeated application of equality
- gcd(m,n) = gcd(n, m mod n)
- happens until the 2nd number becomes 0, which makes the problem trivial
- last value of m is also the gcd of the initial m and n
Ex. gcd(60,24) = gcd(24,12) = gcd(12,0) = 12
Step 1:  if n = 0, return value of as the answer and stop; otherwise, proceed to step 2
Step 2: divide `m` by `n` and assign value of `remainder` to `r`
Step 3: Assign the value of `n` to `m` and the value of `r` to `n`. Go to step 1
Pseudocode:
How do we know it comes to a stop?

### 2. Consecutive integer checking algorithm
Step 1: Assign value of min{m,n} to t
Step 2: Divide `m` by `t`. If remainder = 0 -> step 3; otherwise -> step 4
Step 3: Divide `n` by `t`. If remainder = 0 -> return t, stop; otherwise -> step 4
Step 4: Decrease `t` by `1` -> step 2
- Doesn't work correctly if one of inputs = 0

### 3. Middle school procedure
Step 1: Find prime factorization of m
Step 2: Find prime factorization of n
Step 3: Find all common prime factors
Step 4: Compute product of all common prime factors and return as gcd(m,n)
Ex. gcd(60,24)
	60 = 2 * 2 * 3 * 5
	24 = 2 * 2 * 2 * 3
	gcd(60,24) = 2 * 2 * 3 = 12
Why does the procedure in it's current form pass as a legitimate algorithm?
- Prime factorization steps are not defined unambiguously; require list of prime numbers
- Step 3 is not defined clearly enough
- Much more complex and slower than Euclid's

Algorithms are considered to be procedural solutions to problems
These 'solutions' are NOT answers, but specific instructions for getting answers

### Deciding computational means
If central assumption is that instructions are executed one after another;
- Sequential Algorithm -> Instructions executed one after another, one operation at a time
Central assumption of RAM model doesn't hold for some newer computers that can execute concurrently
- Parallel Algorithm -> Operations executed concurrently

### Next Principle Decision
Solve problem exactly(exact algorithm)? 
or 
Solve problem approximately(approximation algorithm)?

**Why opt for an approximation algorithm?**
1. Important problems that cannot be solved exactly for most of their instances
	- Extracting square roots
2. Available algorithms for solving problem exactly can be slow because of problem's intrinsic complexity
	- Very large number of choices
3. Approximation algorithm can be part of more sophisticated algorithm that solved problem exactly

Algorithm design technique (or "strategy" or "paradigm") is a general approach to solving problems algorithmically, applicable to variety of problems
General design techniques:
- Brute force and exhaustive
- Decrease-and-conquer
- Divide-and-conquer
- Transform-and-conquer
- Space and time trade-offs
- Dynamic programming
- Greedy technique
- Iterative improvement
### Prove The Algorithms Correctness
Prove the algo. yields a required result for every legitimate input in a finite amount of time
### Analyzing the Algorithm
Time efficiency -> how fast it can run
Space efficiency -> how much extra memory it uses
**Desirable Characteristics**
`Simplicity`-> easier to understand and program
`Generality` -> designed to solve a whole class of similar problems

Programming an algorithm presents both a `peril` and an `opportunity`
- peril lies in the possibility of making the transition from an algorithm to a program either `incorrectly` or very `inefficiently`

## Problem Types
### `Sorting` -- Rearrange items of a given list
Some special properties
- Stable -> preserves relative order of any 2 equal elements in its input
	- Before sort = 1, 2, 5, 3<sub>a</sub>, 4, 3<sub>b</sub>
	- Stable algorithm MUST preserve order of `a` and `b` after the sort;
	- After sort = 1, 2, 3<sub>a</sub>, 3<sub>b</sub>, 4, 5
- In-Place -> if it DOES NOT require extra memory (or an extra array for the sort)
### `Searching` -- Find given value, called a search key, in a given set
### `String Processing` -- 
### `Graph Problems` -- 
### `Combinatorial Problems` -- 
### `Geometric Problems` -- 
### `Numerical Problems` -- 

## Linear Data Structures
Array
Linked List
Stack
Queue
### Graphs
A collection of points in a plane (**vertices/nodes**)
- Some connected by line segments (**edges**)
Graph *G = <V,E>* -> defined by pair of two sets
1. Finite non empty set 'V' of items (**vertices**)
2. Set 'E' of pairs of these items (**edges**)
Undirected / Directed
A graph is 
	Complete if -> Every pair of its vertices connected by an edge
	Dense if -> Relatively few possible edges missing
	Sparse if -> Few edges relative to number of vertices