---
type: exercise
chapter: "06"
tags:
  - chapter/06
  - loops
related:
---

# Chapter NN Exercises

Format: **predict → why → actual → reflect**. Verify by compiling small `.c` programs.

---

## 1) What output does the program fragment produce

### a) 6.1
```c
i = 1;
while (i <= 128) {
	printf("%d ", i);
	i *= 2;
}
```

- **Predict:** 
	output `i` is doubled every time the loop runs until `i` becomes greater than or equal to 128
	1 2 4 8 16 32 64 128
- **Why:**
	`i` is initialized to 1 in the beginning of the loop
	once inside, the value of `i` is printed
	after printing the value, i * 2 is assigned back to i
- **Actual:**
		1 2 4 8 16 32 64 128
- **Match?** ✅ / ❌ —> ✅

### b) 6.2
```c
i = 9384;
do {
	printf("%d ", i);
	i /= 10;
} while (i > 0);
```
- **Predict:** 
	9384 938.4 93.84 9.384 0.9384
- **Why:**
	each time the loop runs, the value of `i` is divided by 10 until the value of `i` is less than 0
- **Actual:**
	9384 938 93 9 
- **Match?** ✅ / ❌ —> ❌
	- `i` isn't a floating point so it doesn't store the numbers after the decimal point
	- because of this, if `i` doesn't contain a whole number (0.9384), any number less than 1 wont print
### c) 6.3
What output does the following *for* statement produce
```c
for (i = 5, j = i - 1; i > 0, j > 0; --i, j = i - 1)
	printf("%d ", i);
```
- **Predict:** 
	4 3 2 1
- **Why:**
	`i` is initialized to 5
	loop runs until 
- **Actual:**
	9384 938 93 9 
- **Match?** ✅ / ❌ —> ❌
	- `i` isn't a floating point so it doesn't store the numbers after the decimal point
	- because of this, if `i` doesn't contain a whole number (0.9384), any number less than 1 wont print
---

## Reflection

**What I want to remember:**
- 

**Mistakes I made:**
- 

**Concepts to revisit:**
- 
