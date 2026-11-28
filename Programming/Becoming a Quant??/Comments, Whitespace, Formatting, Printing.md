How to write clear, readable code using comments to explain logic, proper whitespace and formatting conventions, how to display output to users with printing statements

## Input/Output Library (io library)

### std::cout
Allows us to send data to the console to be printed as text
	*cout* stands for "character output"
```cpp
#include <iostream> // for std:cout
```

### std::endl
Output a newline
```cpp
std::cout << "Hi!" << std::endl // causes cursor to move to next line
```

### std::cout is buffered
- Statements in our program request that outputs be sent to the console
- Output is typically NOT send to console immediately. Instead, the requested output "gets in line", and is stored in a region of memory set aside to collect to request (*buffer*)
- Periodically, the *buffer* is flushed (all data collected in buffer is **transferred** to its destination (the console))

### std::endl vs \n
- std::endl is *inefficient* as it does two jobs: outputs a new line, flushes the buffer (which is slow)

### std::cin
- Whereas `std::cout` prints data to console (using insertion operator `<<` to provide data), `std::cin` (stands for character input) reads input from keyboard (using extraction operator `>>`)

### std::cin is buffered
- Individual characters you enter as input are added to end of input buffer, inside `std::cin`
- Enter key is also stored as a `\n` character
- Extraction operator `>>` removes characters from the front of the input buffer & converts them into a value assigned to the associated variable

### The Basic Extraction Process
1. if `std::cin` is not in good state, which happens when prior extraction failed & `std::cin` has not been cleared, then no extraction is attempted, and process aborts
2. Leading whitespace characters are discarded from input bugger
3. If input buffer is not empty, operator `>>` waits for user to enter more data
4. Operator `>>` extracts as many consecutive characters as it can, until encountering a newline character or character that is not valid for the variable being extracted to
The result of the extraction process is:
- if extraction aborted in step 1, no extraction attempt occured
- If any characters were extracted in step 4, success. Extracted chars. are converted into a value and is copy-assigned to the variable
- If no chars. could be extracted in step 4, extraction failed. Object being extracted to is copy-assigned value `0`

### `operator<<` vs `operator>>`
- `std::cin` and `std::cout` always go on left-hand side of operator
- `std::cout` is used to output a value (cout = character output)
- `std::cin` is used to get an input value (cin = character input)]
- `<<` is used with `std::cout`, and shows the direction that data is moving
	`std::cout << 4` moves value 4 to console
	`>>` is used with `std::cin`, and shows the direction that data is moving
	`std::cin >> x` moves the value the user entered from the keyboard to variable `x`

## Quiz

```cpp
#include <iostream>

int main() {
	std::cout << "Enter a number: ";
	int x{};
	std::cin >> x;
	std::cout << "You entered " << x << `\n`;
	
	return 0;
}
```

**a)** A letter, such as `h`
Result: 0, integers can't hold letters so *extraction* fails. `x` is assigned value 0
b) A number with a fractional part 3.2, or numbers less than 0.5 and greater than 0.5
Result: The whole number, the fraction/decimal is dropped (NOT rounded)
c) A small negative integer, -3
Result: -3
d) A word, such as `hello`
Result: 0, integers can't hold strings
e) A really big number (at least 3 billion)
Result: likely the number 2147483647, entering a value larger than the largest number `x` can hold will be set to the largest number `x` can hold
f) A few letters followed by a small number `abc123`
Result: 0, integers can't hold letters, *extraction* fails
