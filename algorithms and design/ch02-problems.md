### 3 pieces of setting up an algorithm analysis
Indicate:
(*i*) a natural [[ch02-fundamental-analysis-algo-efficiency#*Size Metric* -> a specific parameter that scales the work of the algorithm|size metric]] for its inputs
(*ii*) its basic operations
(*iii*) basic operation count varies for inputs of the same size? (does algorithm's control flow depend on the input values, or only on n?):

a. Computing the sum of n numbers
	(*i*) n, the number of numbers in the collection
	(*ii*) addition
	(*iii*) No. Control flow is determined by **n**, not the values being summed. The algorithm has a fixed loop that visits each of the **n** elements exactly once and performs one addition per visit.
b. Computing n!
	(*i*) [[ch02-fundamental-analysis-algo-efficiency#Gotcha - Choice of parameter indicating an input size DOES matter|n itself]] (integer being factorialized)
	(*ii*) multiplication
	(*iii*) No, the loop iterates exactly n-1 times, determined solely by **n**. There are no input values that could affect control flow
c. Finding the largest element in a list of n numbers
	(*i*) n, the number of elements in the list
	(*ii*) comparison (each element is compared against the current largest-so-far)
	(*iii*) No, the algorithm must compare every element to the running maximum to confirm the maximum. So it performs exactly n-1 comparisons for any inputs of size n. Control flow is determined by n alone. 
d. Euclid’s algorithm
	(*i*) n, the smaller of the two input integers
	(*ii*) modulo division
	(*iii*) Yes, the number of mod operations depends on the specific values of m and n, not just their magnitudes. For inputs of comparable size, the count can range from 1 iteration up to many. Control flow depends on when remainders reach 0 (value-dependent)
e. sieve of Eratosthenes
	(*i*) n, a single number (upper bound)
	(*ii*) assignment (cross out numbers)
	(*iii*) No. Control flow (outer loop runs to √n; inner crossing-out loops run to n in steps of i) is determined entirely by **n**. The input *is* the size metric, so there are no other input values that could affect execution — same n produces an identical execution every time.
f. pen-and-pencil algorithm for multiplying two n-digit decimal integers
	(*i*) n, the number of digits in each integer
	(*ii*) single digit multiplication (each digit multiplied with each digit of the other)
	(*iii*) No. The algorithm always performs exactly n<sup>2</sup> single-digit multiplications regardless of digit values. The structure (n partial-product rows, each with n digit-mults) is determined entirely by **n**. Carries and the final row-sum are *auxiliary work* and don't change the basic-operation count.

| Part | Algorithm            | Basic Operation           | (*iii*)<br>Varies?                             |
| ---- | -------------------- | ------------------------- | ---------------------------------------------- |
| a    | sum of n numbers     | addition                  | No                                             |
| b    | n!                   | multiplication            | No                                             |
| c    | find largest         | comparison                | No                                             |
| d    | Euclid's gcd         | modulo                    | Yes, # of mod ops. depends on value of n and m |
| e    | sieve                | assignment (crossing out) | No                                             |
| f    | pen-and-pencil mult. | single digit mult.        | No                                             |


	

---

## Lessons Learned — Mistakes & Insights

Transferable lessons from wrong/imprecise answers across problems (a)–(f). Each one is a *pattern* of mistake worth catching in future problems.

### 1. Don't confuse "input" with "input content"
- **Wrong move (in (a)):** Read "sum of n numbers" as one really long number whose length is n.
- **Why it's wrong:** "Sum of n numbers" means n *separate* numbers — the input is a **collection of n items**, not a single number with n digits.
- **Right answer:** Input is a collection; size metric is **n = the count of items**.
- **Transferable rule:** When a size-metric pattern (collection-count vs. magnitude-of-a-single-number) doesn't fit cleanly, that's a signal you may have *misread the input*, not that the analysis is hard. Reread the problem and ask "what *is* the input — a collection, a single number, a string?" before reaching for machinery.

### 2. The reason for (iii) must point to algorithm structure, not just feel
- **Wrong move (in (a)):** Justified "no, count doesn't vary" with "because the input is the same size for an easy basic operation."
- **Why it's wrong:** That's circular — "same size → same operations" is what we're *trying to explain*, not the explanation. "Easy basic operation" doesn't do any work either.
- **Right answer:** The algorithm has a **fixed loop** that visits each of n elements exactly once. Control flow depends only on **n**, never on the values. So the count is structurally locked to n.
- **Transferable rule:** A well-formed (iii) answer names the algorithm's **control flow** and explains whether it's determined purely by n (no variation) or also by the values (variation). Hand-wavy language is a tell that the structural fact isn't in your head yet.

### 3. Don't tangle input size with output
- **Wrong move (in (c)):** Wrote "(i) n, the largest nth element."
- **Why it's wrong:** The problem mentions n (the count of elements), "the nth element" (a specific position), and "the largest" (the output) — three different things crossed wires in one phrase.
- **Right answer:** n = the **number of elements in the list**. The fact that the algorithm finds "the largest" is what it *produces*, not what describes its input.
- **Transferable rule:** Size metric describes the **input**. Output, position indices, and intermediate values are irrelevant to (i). Keep these mentally tagged: input vs. output vs. internal state.

### 4. Commit to a single size metric — don't just list the inputs
- **Wrong move (in (d)):** Wrote "(i) n and m (integers being used in modulo arithmetic)."
- **Why it's wrong:** That just names the inputs; it doesn't pick a parameter to measure work *against*. A size metric is a *single* quantity (or a clearly defined function of inputs).
- **Right answer:** **n, the smaller of the two integers** (or `min(m, n)`, or the bit-length of the smaller one — pick one and be specific).
- **Transferable rule:** When the input has multiple parts, the size metric is usually one specific function of them (the smaller, the longer, the count, the magnitude). Pick one and justify it; never just list the inputs.

### 5. Choice of size metric matters — see [[ch02-fundamental-analysis-algo-efficiency#Gotcha - Choice of parameter indicating an input size DOES matter|Ch02 Gotcha]]
- **Wrong move (in (b)):** Wrote "(i) m (magnitude of n)" — overgeneralizing from the primality example where magnitude was the metric.
- **Why it's wrong:** For factorial, the conventional metric is just **n itself**. Using "number of bits of n" instead would make the same algorithm look **exponential** (~2^b multiplications) instead of linear (n−1 multiplications) — purely from the metric choice.
- **Right answer:** **n itself** (the integer being factorialized). The algorithm performs n−1 multiplications, linear in n.
- **Transferable rule:** Don't reflexively transfer "magnitude" framing across problems. Match the metric to **how the algorithm naturally scales** — if the algorithm loops n times, n is the natural metric. If the algorithm uses log-style tricks, bit-length might be.

### 6. Precision in (ii) — modulo ≠ division
- **Wrong move (in (d)):** Wrote "(ii) division."
- **Why it's imprecise:** Euclid's algorithm uses **m mod n** — it discards the quotient and keeps the remainder. "Division" alone loses that nuance.
- **Right answer:** **Modulo (remainder) operation**, or "modulo division" if pairing the two.
- **Transferable rule:** Name the operation the algorithm *actually depends on*, not the broader category. If only the remainder is used, call it modulo.

### 7. "Reusing results" ≠ "value-dependent control flow"
- **Wrong move (in (d)(iii)):** Justified "yes, varies" with "the value of the result is reused as input."
- **Why it's wrong:** Algorithm (a) also reuses results (the running sum updates each loop) — yet (a)'s count is fixed. So "reuses results" can't be the discriminator.
- **Right answer:** The number of iterations depends on **how quickly the remainders shrink to zero**, which depends on the *specific values* of m and n. Same-size inputs can take 1 iteration (when n divides m) or many (Fibonacci-pair worst case).
- **Transferable rule:** The discriminator for (iii) is always: **does the algorithm's control flow depend on the input values, or only on n?** Phrase it that way.

### 8. Always trace a concrete example to verify (iii)
- **What I should have done in (d):** Actually run gcd(60, 1), gcd(60, 24), and gcd(60, 13) before answering. Got 1, 2, and 6 iterations respectively for inputs of "the same size" — that's the proof that the count varies.
- **Transferable rule:** When (iii) is non-obvious, **pick two or three same-size inputs and trace by hand**. If they all take the same number of operations → (iii) is no. If they diverge → (iii) is yes. Empirical check beats hand-wavy reasoning every time.

### 9. Don't confuse input with what the algorithm *constructs* internally
- **Wrong move (in (e)):** Wrote "(i) the input is n numbers starting from 2."
- **Why it's wrong:** That list (2, 3, ..., n) isn't supplied by the user — the algorithm *generates* it internally from the single input n. The user hands the algorithm one number; the algorithm builds the list as it runs.
- **Right answer:** Input is one integer **n** (the upper bound). The list of integers from 2 to n is the algorithm's *internal state*, not its input.
- **Transferable rule:** Distinguish three things in every problem: **input** (what the user supplies), **internal state** (what the algorithm builds during execution), and **output** (what it returns). Size metric describes the *input* only. This is the same family as Lesson 3, applied to internal state instead of output.

### 10. Basic operation isn't always arithmetic
- **Wrong move (in (e)):** Wrote "(ii) counting?" — the question mark itself was telling.
- **Why it's wrong:** The sieve isn't counting anything. Picture the algorithm on paper: your pencil is crossing out numbers. That's the engine. In code, it's a memory write (`sieve[i] = false`) — an **assignment**, not an arithmetic op.
- **Right answer:** **Assignment** (marking a number as composite / setting a sentinel value).
- **Transferable rule:** The basic operation can be any kind of repeated work — addition, multiplication, comparison, **assignment**, swap, increment. Match the operation to what the algorithm is *physically doing*, not to arithmetic ops you've seen before. When in doubt, picture the pen-and-paper version and watch your hand.

### 11. Basic operation lives in the innermost loop / dominant work
- **Wrong move (in (f)):** Wrote "(ii) addition" — the pen-and-pencil mult algorithm does both multiplications and additions, and addition got picked.
- **Why it's wrong:** The **single-digit multiplications** sit in the innermost loop (n × n = n² of them, one for every digit-pair). The additions (carries within a row, summing the rows at the end) are downstream / auxiliary work.
- **Right answer:** **Single-digit multiplication** — the dominant operation in the innermost loop.
- **Transferable rule:** When an algorithm performs multiple kinds of operations, pick the basic operation that lives in the **innermost loop** and **dominates the work**. Don't pick a slower-running auxiliary op just because it happens to appear in the algorithm.

### 12. Auxiliary work ≠ variation in basic-operation count
- **Wrong move (in (f)(iii)):** Justified "yes, varies" with "if the result of one of the multiplications is greater than 9 then we need to do carry over and addition work."
- **Why it's wrong:** Carries are **auxiliary work** that may or may not happen depending on values — but they don't change the count of **single-digit multiplications** (the basic operation). You still do exactly n² digit-mults whether 4×3=12 (carry) or 4×2=8 (no carry).
- **Right answer:** **No, count doesn't vary.** Always n² single-digit multiplications. Carries and final row-summing are auxiliary work, irrelevant to the basic-operation count.
- **Transferable rule:** Once you pick the basic operation in (ii), **answer (iii) only about that operation**. Auxiliary work (carries, bookkeeping, finalization) can vary with values without changing the basic-operation count. This is the same family as Lesson 7 — "side effects of the algorithm" don't automatically mean (iii) is yes.

---

## The (iii) discriminator, distilled

A single mental test for (iii) in any future problem:

> **Does the algorithm's control flow (loops, branches, termination conditions) depend on the input *values*, or only on its *size n*?**
>
> - Only on n → (iii) is **no**. Structure-driven, value-independent.
> - On the values → (iii) is **yes**. Best/worst/average cases are now meaningful.

Trace one or two same-size inputs to confirm if uncertain.
