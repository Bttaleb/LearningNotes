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

## How do we find recurrence given the problem set?
We can start with the definition of $F(n)$, a named answer to a smaller version of the whole problem
$F(n)$ = the maximum you can collect from the first n coins
We're defining a function whose value we don't know yet, BUT whose *meaning* is pinned down exactly
What $F$ **IS NOT** describing: a procedure
What $F$ IS describing: a quantity, "the best possible score using only n coins"

## How do we find the formula?
### Move 1: Assume the answer to smaller cases exist already
Pretend we know $F(1)$ through $F(n-1)$, they're handed to us, correct and free
Our job: Given these, how do we compute $F(n)$
- We reduced an impossible "solve everything" into a tiny "solve one more step"
### Move 2: Look at the last element and ask "what are my options for it?"
If we reason about the whole arrangement of $n$ coins, that's exponential and hopeless (what happens to one final element?)

### Move 3: In each universe, what's the leftover, and how do I score it?
Universe "coin $n$ is IN" - Then we collect coin C<sub>n</sub>, what's left to decide is coins 1...n-2 (because n-1 is forbidden)

## What does $F(n-2)$ mean?
Looking at the F(n-2) coin is the consequence of the rule "no two adjacent coins". When we take coin n, coin n-1 becomes off limits. Jumping to F(n-2) guarantees we skip over the forbidden neighbor, hence C<sub>n</sub> or **Coin n** + F(n-2) or **the next coin that isn't adjacent**
