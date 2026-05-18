
Time efficiency (time complexity) -> how fast an algorithm runs
Space efficiency (space complexity) -> amount of memory units required in addition to space needed for its input and output

### How does an algorithm's work grow as it's input grows?
One framework:
1. What do we measure? -> Input size `n`, and a *basic operation*
2. How does work grow with `n`? -> Orders of growth (log<sub>n</sub>, n, n<sup>2</sup>, 2<sup>n</sup>...)
3. Which scenario? -> Worst, Best, Average-Case
4. How do we classify growth **precisely**? -> Big-O, Big-Ω, Big-Θ

## Basic Operations
Count the most time consuming operation in it's innermost loop
	Sorting -> key comparison (are these elements in order?)
	Matrix Multiplication -> multiplication (slowest arithmetic operation)
If the basic operation runs `C(n)` times, and each takes time `c_op`, then:
`T(n) = c_op * C(n)`
- `T(n)` -> whatever function describes your algorithms runtime

*Key Insight*: If asking "how much **slower** does this algorithm get if **input doubles**", *c_op* cancels out. Only *C(n)*'s shape matters

## Asymptotic Notations
Two runners on a track; who's faster in the long run?
Big-O -> `Upper-Bound`; Runner *A* is never faster than Runner **B** by more than a constant factor;  *A* is at most THIS fast
Big-Ω -> `Lower-Bound`; *A* is at least THIS fast (or slow)
Big-Θ -> `Tight-Bound`; *A* and **B** are in the same league -- same order of growth

t(n) ∈ O(g(n)