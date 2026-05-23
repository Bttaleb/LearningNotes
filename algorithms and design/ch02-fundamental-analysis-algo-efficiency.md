	"When you can measure what you are speaking about and express int in numbers than you know something about it; but when you cannot express it in numbers your knowledge is a meagre and unsatisfactory kind: it may be the beginning of knowledge but you have scarcely, in your thoughts, advanced to the stage of science, whatever the matter may be"
	- Lord Kelvin (1842-1907)


Time efficiency (time complexity) -> how fast an algorithm runs
Space efficiency (space complexity) -> amount of memory units required in addition to space needed for its input and output

### How does an algorithm's work grow as it's input grows?
One framework:
1. What do we measure? -> Input size `n`, and a *basic operation*
2. How does work grow with `n`? -> Orders of growth (log<sub>n</sub>, n, n<sup>2</sup>, 2<sup>n</sup>...)
3. Which scenario? -> Worst, Best, Average-Case
4. How do we classify growth **precisely**? -> Big-O, Big-Ω, Big-Θ

## Measuring an inputs size
#list-problems
Obvious observation: **ALL algorithms run longer on larger inputs**
- Takes longer to sort larger arrays, multiply larger matrices
Therefore, investigate algorithms efficiency as a function of some *parameter n*, indicating algorithm's input size
*Most Cases:* selecting such parameter is straightforward -> size of list for problems;
- sorting
- searching
- finding list's smallest element
*Finding*: it doesn't matter which reasonable parameter you pick - analysis comes out same way regardless (for **list problems**)
### Gotcha - Choice of parameter indicating an input size DOES matter

#matrix-multiplication-problems
The input size parameter you choose can change how an algorithm's efficiency appears, **even when two parameters (n) are mathematically equivalent**
*Example*: matrix multiplication
- *n* - the order of the matrix (one side's length)
	A is n·n, B is an n·n matrix == O(N<sup>3</sup>)
- *N* - the total number of elements across both matrices
	N = 2n^2 -> n = √(N/2) == O(N<sup>1.5</sup>)
*Finding*: unlike list problems where the parameter choice is harmless, some problems (**matrix multiplication**) have multiple natural size measures that produce meaningfully different efficiency spaces; **choice requires deliberate attention**

The choice (size metric), can be influenced by operations of the algorithm in question
*Example*: how should we measure an input's size for a spell-checking algorithm?
1. If algorithm examines `individual character as its input` -> **measure size by the number of characters**
2. If algorithm works by `processing words` ->  **count their numbers** in the input
*Example 2*: measuring input size for algorithms checking primality of a positive integer *n*
- Here, input is just 1 number
- it is this numbers magnitude, that determines the input size
*Finding*: measure size by the number *b* of bits in the *n*'s binary representation
	b = [log<sub>2</sub>n] + 1

## Units for Measuring Running Time (Basic Operations)
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
	
```c
// O(n) linear time
// n = 1,000,000
// ~1,000,000 steps to complete
int addUp(int n) {
	int sum = 0;
	for (int i = 0; i <= n; i++) {
		sum += i;
	} 
	return sum;
}
// O(1) constant time
int addUp(int n) {
	int sum = n · (n + 1) / 2;
	return sum;
}
```

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
$100n + 5 ≤ c · n^2$ for all n ≥ n<sub>0</sub> 
For $n ≥ 1$ we know that,
$n ≤ n^2$ and $1 ≤ n^2$ 
So we can replace each term in 100n + 5 with something bigger (in terms of $n^2$)
$100n + 5 ≤ 100n^2 + 5n^2$ (since $n ≤ n^2$ and $1 ≤ n^2$ so $5 ≤ 5n^2$)
$= 105n^2$
So with c = 105 and n<sub>0</sub> = 1, we know the inequality holds