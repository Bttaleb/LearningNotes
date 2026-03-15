**Time: Count the loops**
"How many times does the innermost operation run?"
___O(1)___ = NO loop
- arr[0]
___O(n)___ = 1 loop
- for x in arr:
___O(n^2)___ = Nested loops over THE SAME data
- for i: for j
___O(log n)___ = Loops that HALVE each step
- while n > 1: n //= 2
___O(2^n)___ = Recursion that branches twice 
- f(n-1) + f(n-2)
___O(n log n)___ = sorting, split + merge OR partition + recurse
- sorted(arr)

**Space: Count the NEW data structures**
"Did I create anything new that grows with the input?"
___O(1) Space___  = few variables, doesn't grow
- total = 0; i = 0
___O(n) Space___ = new set/list/dict. that grows with input size
- seen = set( ); result = [ ]
___O(n^2) Space___ = 2D grid/matrix that scales with input squared
- grid = [[0]*n for _ in range(n)]

