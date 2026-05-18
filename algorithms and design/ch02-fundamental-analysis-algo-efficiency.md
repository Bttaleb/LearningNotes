
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
`T(n) = c_op · C(n)`

*Key Insight*: If asking "how much **slower** does this algorithm get if **input doubles**", you compute the ratio:
T(2n) / T(n) = ((c_op · C(2n)) / ((c_op · C(n))
*c_op* divides out completely. Only *C(n)*'s shape matters;
## Asymptotic Notations
Two runners on a track; who's faster in the long run?
Big-O -> `Upper-Bound` -> "at most"
	This algorithm will never do *more* work than this
	O(n<sup>2</sup>) means: in the worst scenario, growth is capped at n<sup>2</sup>, never more
	"This job will take at most 2 weeks", could finish in 3 days, but never more than 2 weeks
Big-Ω -> `Lower-Bound` -> "at least"
	This algorithm will never do *less* work than this
	Ω(n) means: no matter what, this thing does at least linear work, you can't make it faster than the growth rate
	"This job will take at least 3 days", could take longer, but never less than 3 days
Big-Θ -> `Tight-Bound`; *A* and **B** are in the same league -- same order of growth
	Growth is locked in, not slower or faster
	"This job will take 3-5 days, guaranteed"

| Notation | t(n) growth                                        | g(n) growth                                |
| -------- | -------------------------------------------------- | ------------------------------------------ |
| O        | `<=`g(n) is the upper bound<br>no faster than g(n) | upper ceiling <br>(higher order of growth) |
| Ω        | `>=`g(n) is the lower bound<br>no slower than g(n) | lower floor<br>(lower)                     |
| Θ        | **=** g(n)<br>exactly as fast as g(n)              | exact match                                |

t(n) ∈ O(g(n)) means: There exists constants c > 0 and n<sub>0</sub> > 0 such that
	`t(n) ≤ c · g(n)   for all n ≥ n₀`
	"Does my algorithm's actual cost function `t(n)` fit in inside this growth class `g(n)`?"
where; 
	`t(n)` -> whatever functions describes your algorithm's runtime
	`g(n)` -> whatever comparison function you're testing against (n, n<sup>2</sup>, n·log<sub>n</sub>)
PROOF:
$100n + 5 ∈ O(n²)$
"The function $100n + 5$ grows no faster than $n²$"
We need to find constants c > 0 and n<sub>0</sub> > 0 such that:
$100n + 5 <= c · n^2$ for all n >= n<sub>0</sub> 
