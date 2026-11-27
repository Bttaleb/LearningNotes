Code is written to source files (text) and then passed to the compiler. The compiler then compiles the text into some sort of binary (executable binary)

## Pre-processor Statements
The first thing a compiler executes when a source file is received (whatever starts with `#`)
ex. `#include <iostream>`
- `include` finds the file called `iostream`, takes all the contents, and pastes it into our current file
- files that are "included" are known as *header files*
Our `main` function is known as our *entry point*
	control flow statements, or calls to other functions can change the order of the code executed

```cpp
#include <iostream>
int main() {
	std::cout << "Hello Word" << std::endl;
	/* is the same as */
	std::count.print("Hello World").print(std::endl);
	/* `Hello World` is pushed to `cout` (which prints to console), then        pushes an `endline`, which tells our console to advance to the next line
	*/
	std::cin.get();
	/* `get()` reads the next character typed by the user */
}
```

### Overloaded Operator
`<<` is an OO, think of them as a function (although it looks like an operator, operators are just functions)

How do we get text from a source file to an executable binary file?
1. Load the pre-processor`