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
- Sequential Algorithm -> Instructions executed one after another, one operation at a time
- Parallel Algorithm ->