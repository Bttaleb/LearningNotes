## Problem:
You have a plain struct:
```cpp
struct Date {
	int year;
	int month;
	int day;
};

Date d{2050, 4, 10}; // positional: values are matched to members by ORDER
```
Is the date April 10 or October 4?
	To answer this, you need to check the struct definition
The fix: label each value
```cpp
Date d{ .year = 2050, .month = 4, .day = 10 };
// .year is a designator: it names the member that the value goes into
// the value no longer depends on remembering the order
```

### What does Aggregate mean?
A plain bundle of *public data*
There are two ways to build an object
1. A **constructor** runs. The type defines a special function
```cpp
class Account {
public: 
	Account(int startingBalance) { /* validate, set up... */ }
private:
	int balance;
};

Account a{100};   // calls the constructor -> decides whats 100 means
```

2. *Members* are filled directly. The type is a plain bundle of public data with no constructor (**aggregate initialization**)
```cpp
struct Date {
	int year;
	int month;
	int day;
};

Date d{2050, 4, 10}; // year = 2050, month = 4, day = 10; no function runs
```
`Date` is an **aggregate** (a collection of parts)
### How to recognize a constructor
```cpp
class Account {
public:
    Account(int startingBalance) { ... }   // ← constructor
//  ↑       ↑
//  │       └ parameters: what you must provide to build one
//  └ SAME NAME as the class, and NO return type (not even void)

    int getBalance() { ... }               // ← ordinary function: has a return type
};
```

### What counts as an aggregate?
Arrays: `int a[3] {1, 2, 3};`
Structs or Classes that have:
- no constructors you wrote
- no private or protected data members
- no virtual functions
In short: everything is public and there's no code that runs on construction

### Where do designated initializers fit?
When aggregate initialization has labels:
```cpp
Date d{ 2050, 4, 10 };     // aggregate init, matched by position
Date d{ .year = 2050, .month = 4, .day = 10 } // aggregate init, labeled
```

With an **aggregate**, braces guarantee that every member gets a value
```cpp
Date a{2050, 4, 10}; // all three set
Date b{2050};        // year = 2050, month and day are set to 0
Date c{};            // all three set to 0
Date d;              // no braces: all three are GARBAGE, same as int x;
```

### Members must be initialized in the same order in which they are declared in the struct