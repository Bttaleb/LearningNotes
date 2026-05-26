### 3 pieces of setting up an algorithm analysis
Indicate:
(*i*) a natural [[ch02-fundamental-analysis-algo-efficiency#*Size Metric* -> a specific parameter that scales the work of the algorithm|size metric]] for its inputs
(*ii*) its basic operations
(*iii*) if basic operation count varies for inputs of the same size:
a. Computing the sum of n numbers
	(*i*) n, the number of numbers in the collection
	(*ii*) addition
	(*iii*) No. Control flow is determined by **n**, not the values being summed. The algorithm has a fixed loop that visits each of the **n** elements exactly once and performs one addition per visit.
b. Computing n!
	(*i*) m (magnitude of n)
	(*ii*) multiplication
	(*iii*) 
c. finding the largest element in a list of n numbers
d. Euclid’s algorithm
e. sieve of Eratosthenes
f. pen-and-pencil algorithm for multiplying two n-digit decimal integers

