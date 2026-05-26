### 3 pieces of setting up an algorithm analysis
Indicate:
(*i*) a natural [[ch02-fundamental-analysis-algo-efficiency#*Size Metric* -> a specific parameter that scales the work of the algorithm|size metric]] for its inputs
(*ii*) its basic operations
(*iii*) if basic operation count varies for inputs of the same size:
a. Computing the sum of n numbers
	(*i*) n, the number of numbers in the collection
	(*ii*) addition
	(*iii*) No. Control flow is determined by **n**, not the values being summed. The algorithm has a fixed loop that visits each of the **n** elements exactly once and performs one addition per visit.
b. Computing  n!
	(*i*) [[ch02-fundamental-analysis-algo-efficiency#Gotcha - Choice of parameter indicating an input size DOES matter|n itself]] (integer being factorialized)
	(*ii*) multiplication
	(*iii*) No, the loop iterates exactly n-1 times, determined solely by **n**. There are no input values that could affect control flow
c. finding the largest element in a list of n numbers
	(*i*) n, the number of elements in the list
	(*ii*) comparison (each element is compared against the current largest-so-far)
	(*iii*) No, the algorithm must compares every element to the running maximum to be able to confirm the maximum. So it performs exactly n-1 comparisons for any inputs of size n. Control flow is determined by n alone. 
d. Euclid’s algorithm
	(*i*)
	(*ii*)
	(*iii*)
e. sieve of Eratosthenes
	(*i*)
	(*ii*)
	(*iii*)
f. pen-and-pencil algorithm for multiplying two n-digit decimal integers
	(*i*)
	(*ii*)
	(*iii*)

