Four Levels

| Type   | Grammar Class          | Automaton                | Key Rule / Structural Feature                     | Examples                            |
| ------ | ---------------------- | ------------------------ | ------------------------------------------------- | ----------------------------------- |
| Type 3 | Regular                | Finite State Automaton   | No memory; rules depend on current state          | Valid email formats (`regex`)       |
| Type 2 | Context-Free           | Pushdown Automaton (PDA) | Uses a stack (LIFO) for nested structure          | Balanced Parentheses                |
| Type 1 | Context-Senstive       | Linear Bounded Automaton | Rules depend on surrounding symbols; bounded tape | Matching three counts (a^n b^n c^n) |
| Type 0 | Recursively Enumerable | Turing Machine           | Unrestricted rules; infinite read/write memory    | Any solvable algorithm/halting      |
# Gate 1: Is it even a language/membership problem?
Chomsky framing (`is w ∈ L`) only applies when the problem is a yes/no decision about the structure of ONE string; 2 step check

|        | Language Problem                             | NOT a language problem                             |
| ------ | -------------------------------------------- | -------------------------------------------------- |
| Input  | a *single* string (one symbol stream)        | a *collection* of strings, or strings + other data |
| Output | yes/no - "is it valid / balances / matching" | a string, number, best choice, count               |
Language Problem (membership):
- "is it..."
- "does it..."
NOT a language problem (optimization/search/counting)
- "find the..."
- "longest/shortest/best..."
- "how many..."
- "return the..."

# Gate 2: *If* it's membership - regular or not?
	How much must I remember to check the pattern, as the string grows?
- Bounded state - fixed set of flags or a counter that wraps (mod k) - read left to right once, remember a constant amount -> **Regular (DFA, O(1))**. Signals: "contains substring x", "even number of a's", "starts/ends with..."
- Unbounded matching/nesting - must remember arbitrarily far back to match later -> **Context Free (PDA, Stack)**. Signals: balances/nested everything, `(a^n)(b^n)`, match-to-a-mirror

"Can a fixed number of states handle *any* length?" -> If count is needed without a bound or math something arbitrarily far away, a DFA can't -> not regular

### Insight
"Am I *deciding* yes/no from one string, or *producing* something from strings"
- Deciding yes/no from one string? -> Language world (then ask regular vs CF by memory)
- Producing -> algorithm-family world