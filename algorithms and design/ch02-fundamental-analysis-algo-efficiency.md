
Time efficiency (time complexity) -> how fast an algorithm runs
Space efficiency (space complexity) -> amount of memory units required in addition to space needed for its input and output

## Measure input size
- find units for measuring and algorithm's runtime -> identify the *basic operation* (operation contributing the most to total running time)
- compute number of times basic operation is executed
Efficiency analysis framework **ignores** multiplicative constants, *focuses* on the count's order of growth to within a constant multiple for large size input

An algorithm with an efficiency of exponential would be considered impractical because of long runtime

## Worse/Best/Average-Case Efficiencies
Assumptions:
- a list is implemented as an array
- `A[i] != K` will not be checked if the first one fails

```c
//searches for given value in given array by sequential search
//Input: an array A[0, n-1]
//Output: index of the first element in array A that matches K
// OR
// -1 if there are no matching elements
i <- 0
while i < n and A[i] != K do
	i <- i + 1
if i < n return i
else return -1
```
Worst case -> efficiency for worst case input of size n (runs the longest of all inputs)
- analyze to see what kind of inputs yield largest value of basic operation's count C(n)
Best Case -> efficiency for best case input of size n (runs the fastest of all inputs)