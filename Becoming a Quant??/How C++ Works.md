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

## Turning Source Code Into an Executable Binary
Four-stage compilation pipeline
1. **Preprocessing** (cleaning up and preparing raw source text)
	- Strips Comments
	- Expands macros
	- Inserts headers
	- Result -> A pure, expanded text file
2. **Compilation** (expands text, checks for errors, then translates high-level logic into low-level *assembly code* tailored to the CPU architecture)
	- Lexing & Parsing -> Breaks text into tokens
	- Optimization -> Rearranges or simplifies instructions to make code run faster
	- Result -> Text file containing human-readable assembly
3. **Assembly** (translates assembly instructions directly into raw binary machine code)
	- Translation -> Converts mnemonic instructions `MOV`, `ADD`
	- Result -> A binary object file
4. **Linking** (combines all separate object files & external libraries into runnable program)
	- Symbol Resolution -> Matches function calls in code to actual definitions
	- Memory Layout -> Organizes binary into structure segments
	- Result -> Final executable binary

### How do we build a C++ program across multiple files?
1. Separate **declarations** (what exists) from **definitions** (how it works)
2. Compile each source file independently
3. Link them together into a single executable