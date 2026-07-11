1. Apply dynamic programming algorithm to solve the instance 5,1,2,10,6
2. Apply dynamic programming algorithm to find all the solutions to the change-making problem for the denominations 1, 3, 5, and the amount n = 9
3. Apply the bottom up dynamic programming algorithm to the following instance of the knapsack problem

| item | weight | value |
| ---- | ------ | ----- |
| 1    | 3      | $25   |
| 2    | 2      | $20   |
| 3    | 1      | $15   |
| 4    | 4      | $40   |
| 5    | 5      | $50   |
capacity W = 6

How do we find recurrence?
Step 1 - Almost every DP focuses on final choice or final element: What do i do about the last coin in the row?

Step 2 - Enumerate choices for that decision
List every distinct option, for the last coin -> Take it or skip it

Step 3 - For each choice, "what smaller subproblem am I left with"
- If I TAKE last coin (coin n), I collect C<sub>n</sub>
	- Adjacency rule forbids the (n-1) coin, so we must look at the (n-2) coin -> This leaves us with F(n-2). Total: C<sub>n</sub> + F(n-2)
- If I SKIP it, I collect nothing: I can use the n-1 coin: F(n-1)

Step 4 - Combine choices with max or min
Coin row wants the maximum
 - F(n) = max( C<sub>n</sub> + F(n-2) ,  F(n-1) )

Step 5 - Find base case: smallest input where there's no decision to make
F(0) = 0 => (no coins, nothing to collect)
F(1) = C<sub>1</sub> => (one coin, no adjacency conflict)

Looking at the F(n-2) coin is the consequence of the rule "no two adjacent coins". When we take coin n, coin n-1 becomes off limits. Jumping to F(n-2) guarantees we skip over the forbidden neighbor