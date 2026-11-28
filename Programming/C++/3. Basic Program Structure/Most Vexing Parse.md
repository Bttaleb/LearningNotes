If a line of C++ *can* be read as a function declaration, the compiler *will* read it as one.

### Why is it '*vexing*'?
The code looks like you're creating a variable, but the compiler sees it as a function declaration

### A function declaration looks like:
```cpp
int add(int x, int y); // "add" takes two ints and returns an int
int getNumber();       // "getNumber" takes nothing and returns an int
```
The second line: **type, name, empty parenthesis, semicolon**

## Ex. 1: empty parenthesis
```cpp
std::string foo();   // intent: create an empty string called foo
```

Comparing it with `int getNumber()`:
- it has the same shape: type, name, (), ;

### What makes it hard to spot?
Theres no error on this line, the error shows later when trying to use `foo` as a string:
```cpp
foo.empty();     
// error: foo is a function, not a string, so it has no empty()
```

## Ex. 2: a hidden version
```cpp
int i = 5;
Doubler d(MyInt(i)); // intent: build a MyInt from i, then build a Doubler from that
```
a parameter name may be wrapped in parenthesis
`MyInt(i)` as a parameter name means the same as `MyInt i`, so the compiler reads:
```cpp
Doubler d(MyInt i); // a function 'd' that takes a MyInt named i and returns a Doubler
```

## The fix: braces
Curly braces **can never** be read as a function declaration, so ambiguity dissappears

| Ambiguous              | Unambiguous                                     |
| ---------------------- | ----------------------------------------------- |
| `std::string foo();`   | `std::string foo{}; `or just `std::string foo;` |
| `Doubler d(MyInt(i));` | `Doubler d{MyInt{i}};`                          |
This is why we write `int x{};` instead of `int x();`
- The braces `{}` mean always "make an object", never "declare a function"