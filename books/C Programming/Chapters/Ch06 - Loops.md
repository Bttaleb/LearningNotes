---
type: chapter
chapter: "6"
title: Loops
book: K.N. King — C Programming, A Modern Approach
tags:
  - status/learning
  - topic/loops
  - chapter/6
related: []
---
## Iteration Statements
- `while` -> loops whose controlling expression is tested **before** loop body is executed
- `do` -> if the expression is tested **after** the loop body is executed
- `for` -> loops that increment or decrement a counting variable

### *while* Statement

```c
while (expression) statement

while (i < n)     // controlling expression
	i = i * 2;    // loop body
	
//countdown
i = 10;
while (i > 0) {
	printf("T minus %d seconds and counting\n", i);
	i--;
}
```

Observations about the *while* statement:
- The controlling expression is **FALSE** when a while loop **terminates**
- Since controlling expression is tested **before** the loop is executed, body may not be executed at all
Cross-link related ideas inline: `[[Ch04 - Expressions#Operator precedence]]`.

## *do* Statement

Essentially same as the *while* statement, except controlling expression is tested **after** each execution of the loop body.
- handy for loops that must execute at least once

```c
do statement while (expression)

//countdown
i = 10;
do {
	printf("T minus %d seconds and counting", i) // loop body
	i--;
} while (i > 0); // controlling expression
```

- Loop body is executed first, then the controlling expression is evaluated
- If value of expression is nonzero -> loop body is executed again, expression evaluated once more
Do statement turns out to be more attractive, because every integer (even 0) has at least one integer

```c
//replacing the do loop by a similar while loop
while (n > 0) {  // if n is initally 0, loop doesn't execute at all
	n /= 10;
	digits++;
}
Output: The number has 0 digit(s)
```

## *for* Statement
Ideal for loops that have a **"counting" variable**

```c
for (expr1 ; expr2; expr3 ) statement
for (i = 10; i > 0; i--)
	printf("T minus %d and counting\n", i);
```
Variable *i* -> initialized to 10, then *i* is tested to see if it's greater than 0
Since it is -> "T minus 10 and counting" is printed
Then -> *i* is decremented

*for* is closely related to the *while*

```c
expr1; // initialization step performed before loop begins
while (expr2) { // controls loop termination (continues executing as long 
	statement    // as value of expr2 == nonzero)
	expr3; // operation to be performed at the end of each loop iteration
}

i = 10; //initialization
while (i > 0) { // loop termination
	printf("T minus %d and counting\n", i);
	i--; // operation to be performed at the end
}
```

### *for* statement idioms
- usually best choice for loops that "count up" (increment a variable) or "count down" (decrement a variable)
```c
// Counting UP from 0 TO n-1
for (i = 0; i < n; i++)
// Counting UP from 1 TO n
for (i = 1; i <= n; i++) 
// Counting DOWN from n-1 to 0
for (i = n - 1; i >= 0; i++)
// Counting DOWN from n to 1
for (i = n; i > 0; i--)
```
Some beginner errors:
 - Using `<` or `>` in the controlling expression
	 - Counting up -> `<` or `<=`
	 - Counting down -> `>` or `>=`
- Using == in controlling expression instead of `<`, `<=`, `>`, `>=`
	- Controlling expression BEGIN `true` -> LATER `false` so loop can terminate
- "Off-by-one" errors; `i <= n` instead of `i < n`
## Omitting Expressions in *for* statements

*for* statements are flexible
- If the first expression is omitted (*expr1*), no initialization is performed before execution

```c
i = 10; // omit the first expr1 (expr1)
for (; i > 0; i--)
	printf("T minus %d and counting. \n", i);
	
for (i = 10; i > 0;)
	printf("T minus %d and counting. \n", i--); // omit third (expr3) post decrement,
```

## Exiting a Loop
`break`: transfers control just *past* the end of a loop
- can only escape one level of nesting
Ex. 
```c
while (...) {
	switch (...) {
		...
		break; //transfers control OUT of switch, but not out of while
		...
	}
}
```

`continue`: transfers control to a point just *before* the end of the loop body
Ex. Reads a series of numbers and computes their sum
```c
n = 0;
sum = 0;
while (n < 10) {
	scanf("%d", &i);
	if (i == 0)
		continue
	sum += i;
	n++;
	/* continue jumps to here */
}
```

`goto`: capable of jumping to *any* statement in a function, provided the statement has a **label**
```c
/* labeled statement */
identifier : statement
/* goto statement */
goto identifier ;

for (d = 2; d < n; d++) {
	if (n % d == 0)
		goto done; 
	done:
	if (d < n)
		printf("%d is divisible by %d\n" n, d);
	else
		printf("%d is a prime\n", n);
}
```

`break` doesn't have the desired effect (exiting from a `switch` but not from the loop)
- `goto` solves this problem (useful for exiting nested)
```c
while (...) {
	switch (...) {
		...
		goto loop_done;
		...
	}
}
loop_done: ...
```

## *Null* statements
- Good for writing loops whose bodies are empty (ex. prime-finding loop)
```c
for (d = 2; d < n; d++)
	if (n % d == 0)
		break;
// moving n % d == 0 condition into the loop's controlling expression makes the body of the loop empty
for (d = 2; d < n && n % d != 0; d++)
/* empty loop body */
```

---

## Exercises

[[ChNN Exercises]]

