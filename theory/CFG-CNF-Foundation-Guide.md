# CFG & CNF Foundation Guide — HW5 Reference

## 1. Core Concepts You Need

### What is a Context-Free Grammar (CFG)?

A CFG is a set of rewriting rules that define a language. It has four parts:

- **V** — a finite set of *variables* (non-terminals). These are placeholders that get rewritten.
- **Σ** (sigma) — a finite set of *terminals*. These are the actual symbols in the strings of the language (like `a`, `b`, `0`, `1`).
- **S** — the *start symbol* (one of the variables).
- **P** — *production rules* of the form `A → α`, meaning variable A can be replaced by string α.

A grammar **generates** a language: the set of all terminal strings you can derive starting from S by repeatedly applying production rules.

### Derivations

A derivation is the step-by-step process of replacing variables using productions until only terminals (or λ) remain.

```
Example:  S → aSb | λ
S ⇒ aSb ⇒ aaSbb ⇒ aaλbb = aabb
```

This grammar generates {aⁿbⁿ : n ≥ 0}.

### Parse Trees

A parse tree visually represents a derivation:
- Root = start symbol
- Internal nodes = variables
- Leaves (read left to right) = the derived string
- Each parent-to-children connection = one production rule applied

Parse trees matter because **if a single string has two different parse trees, the grammar is ambiguous.**

---

## 2. Q1 — Identifying the Language of a Grammar (20 pts)

**Grammar:**
```
V = {S},  Σ = {a, b},  Start = S
S → aSb | bSa | SS | λ
```

### How to Approach "What language does this generate?"

**Strategy:** Generate small strings, look for a pattern, then prove it.

**Step 1 — Understand each production's role:**
| Rule | What it does |
|------|-------------|
| S → aSb | Wraps an `a` on the left and a `b` on the right |
| S → bSa | Wraps a `b` on the left and an `a` on the right |
| S → SS | Concatenates two strings from the language |
| S → λ | Base case — produces the empty string |

**Step 2 — Generate examples:**
- λ (empty string): #a = 0, #b = 0
- ab: S ⇒ aSb ⇒ ab. #a = 1, #b = 1
- ba: S ⇒ bSa ⇒ ba. #a = 1, #b = 1
- aabb: S ⇒ aSb ⇒ aaSbb ⇒ aabb. #a = 2, #b = 2
- abba: S ⇒ SS ⇒ aSbS ⇒ abS ⇒ abbSa ⇒ abba. #a = 2, #b = 2
- abab: S ⇒ SS ⇒ aSbS ⇒ abS ⇒ abaSb ⇒ abab. #a = 2, #b = 2

**Step 3 — Spot the pattern:**
Every generated string has an **equal number of a's and b's**.

**The language is: L = { w ∈ {a,b}* : #a(w) = #b(w) }**
All strings over {a,b} where the count of a's equals the count of b's.

**Why this works:**
- `S → aSb` and `S → bSa` each add exactly one `a` and one `b`
- `S → SS` concatenates two balanced strings (still balanced)
- `S → λ` is the base (0 = 0)

No production can ever make the counts unequal.

### General Skill: Identifying a Grammar's Language

1. List what each production "does" in plain English
2. Derive 5–8 small strings and count/categorize them
3. State a conjecture (the pattern)
4. Argue briefly why the grammar can generate *all* strings matching the pattern and *only* those strings

---

## 3. Q2 — Designing a CFG for a Given Language (20 pts)

**Language:** L = { aⁿbᵐ : m ≥ n, m − n is even }

### How to Approach "Give a CFG for L"

**Strategy:** Break the language into structural layers that map to production rules.

**Step 1 — Understand the constraints:**
- Starts with some a's, then some b's (all a's before all b's)
- At least as many b's as a's (m ≥ n)
- The *excess* b's (m − n) must be even

**Step 2 — Decompose the structure:**
Think of a valid string aⁿbᵐ as built from two parts:
1. **Matched pairs** — for every `a`, there's a corresponding `b`. This accounts for n a's and n b's.
2. **Extra b's** — the remaining (m − n) b's, which must be an even number.

**Step 3 — Build productions for each part:**

For the matched pairs (like aⁿbⁿ):
```
S → aSb    (adds one a-b pair)
S → B      (done with pairs, switch to extra b's)
```

For the even number of extra b's:
```
B → bbB    (adds b's two at a time — guarantees even)
B → λ      (stop — zero extra b's is even too)
```

**Complete grammar:**
```
S → aSb | B
B → bbB | λ
```

**Verification:**
- a²b⁶ (n=2, m=6, m−n=4 ✓): S ⇒ aSb ⇒ aaSbb ⇒ aaBbb ⇒ aabbBbb ⇒ aabbbbBbb ⇒ aabbbbbb ✓
- ab (n=1, m=1, m−n=0 ✓): S ⇒ aSb ⇒ aBb ⇒ ab ✓
- abb (n=1, m=2, m−n=1): odd excess — **cannot** be generated ✓ (correct rejection)

### General Skill: Designing CFGs

1. **Parse the constraints** — what are the structural requirements?
2. **Decompose into layers** — matched parts, free parts, constrained parts
3. **One variable per "job"** — S handles the paired structure, B handles the extra
4. **Verify with examples** — test strings that should AND shouldn't be in the language

---

## 4. Q3 — Converting to Chomsky Normal Form (30 pts)

**Grammar to convert:**
```
S → A | AB0 | A1A
A → A0 | λ
B → B1 | BC
C → CB | CA | 1B
```

### The 5 Steps of CNF Conversion (applied to this grammar)

**The goal:** Every production must be in one of two forms:
- `X → YZ` (exactly two variables)
- `X → a` (exactly one terminal)

---

### STEP 1: Eliminate λ-productions

**Find nullable variables:** A variable is nullable if it can derive λ.
- A → λ directly, so **A is nullable**
- Check if anything else becomes nullable through A: S → A, and A is nullable, so **S is nullable**. But S is the start symbol — we handle that specially.
- B → BC, B → B1 — B needs at least a `1` or a C, and C always produces something. **B is not nullable.**
- C → CB | CA | 1B — always produces something. **C is not nullable.**

**Nullable set: {A, S}**

**Add new productions** by removing nullable variables in all combinations:

| Original | New productions (removing A in all combos) |
|----------|-------------------------------------------|
| S → A | S → λ (but we'll remove all λ's) |
| S → AB0 | S → B0 (remove A) |
| S → A1A | S → 1A, A1, 1 (remove first A, second A, both) |
| A → A0 | A → 0 (remove A) |
| C → CA | C → C (unit prod — handle in step 2) |

**Delete all λ-productions.** If S needs to generate λ, add a new start S₀ → S | λ. (Check if the original language includes λ — here S → A → λ, so yes.)

**Grammar after Step 1:**
```
S₀ → S | λ
S → A | AB0 | B0 | A1A | 1A | A1 | 1
A → A0 | 0
B → B1 | BC
C → CB | CA | C | 1B
```

---

### STEP 2: Eliminate unit productions

**Unit productions are:** S₀ → S, S → A, C → C

Note: S → 1 is NOT a unit production — it has a terminal on the right side, not a variable. Single-terminal productions like A → a are already valid in CNF.

C → C is trivially useless — just delete it.

**For S → A:** Whatever A produces non-unitarily, give directly to S.
- A → A0 | 0, so add: S → A0 | 0

**For S₀ → S:** Whatever S produces non-unitarily, give directly to S₀.
- After expanding S, add all of S's non-unit productions to S₀.

**Grammar after Step 2:**
```
S₀ → AB0 | B0 | A1A | 1A | A1 | 1 | A0 | 0 | λ
S → AB0 | B0 | A1A | 1A | A1 | 1 | A0 | 0
A → A0 | 0
B → B1 | BC
C → CB | CA | 1B
```

---

### STEP 3: Eliminate useless symbols

**Sub-step 3a — Find generating symbols** (can derive a terminal string):
- A → 0 ✓ (generates "0")
- S → 1 ✓, S → 0 ✓
- B → B1... but B needs to eventually produce terminals. B → B1 → B11 → ... B never has a non-B production without another variable. B → BC, and C → 1B. So B → BC → B(1B) → ... this loops. **Check carefully:** Is there any way B produces only terminals? B → B1 keeps the B. B → BC keeps B and adds C. There's no base case for B.

  **B is non-generating.** It can never derive a string of pure terminals.

- C → 1B — since B is non-generating, and C → CB and C → CA both require C itself... C → 1B requires B which is non-generating. C → CB requires B. C → CA requires C to already generate. **C is non-generating.**

**Remove B, C, and all productions containing them:**

```
S₀ → A1A | 1A | A1 | 1 | A0 | 0 | λ
S → A1A | 1A | A1 | 1 | A0 | 0
A → A0 | 0
```

**Sub-step 3b — Find reachable symbols** (reachable from S₀):
- From S₀: we see S₀ uses A, and references terminal 0, 1. S appears... wait, we already eliminated S₀ → S. Do we still reference S? Looking at the grammar, S₀'s productions don't reference S anymore. But S₀ could have originally gone to S. Let me recheck — after step 2, S₀ got all of S's productions directly. So S₀ doesn't reference S.

  **S is unreachable** from S₀ (no production of S₀ contains S on the right side).

**Remove S:**
```
S₀ → A1A | 1A | A1 | 1 | A0 | 0 | λ
A → A0 | 0
```

---

### STEP 4: Replace terminals in mixed productions

Any production with length ≥ 2 that contains terminals needs new variables for those terminals.

Introduce: **T₀ → 0** and **T₁ → 1**

| Before | After |
|--------|-------|
| S₀ → A1A | S₀ → AT₁A |
| S₀ → 1A | S₀ → T₁A |
| S₀ → A1 | S₀ → AT₁ |
| S₀ → A0 | S₀ → AT₀ |
| A → A0 | A → AT₀ |

Productions already in valid form (single terminal): S₀ → 1, S₀ → 0, A → 0 — leave as-is.

```
S₀ → AT₁A | T₁A | AT₁ | 1 | AT₀ | 0 | λ
A → AT₀ | 0
T₀ → 0
T₁ → 1
```

---

### STEP 5: Break down long productions

Only one production has more than 2 symbols on the right: **S₀ → AT₁A**

Introduce new variable: **X₁ → T₁A**

Replace: S₀ → AT₁A becomes **S₀ → AX₁**

**Final CNF Grammar:**
```
S₀ → AX₁ | T₁A | AT₁ | 1 | AT₀ | 0 | λ
A → AT₀ | 0
T₀ → 0
T₁ → 1
X₁ → T₁A
```

Every production is now X → YZ, X → a, or S₀ → λ (allowed for start symbol). ✓

---

## 5. Q4 — Proving Ambiguity (30 pts)

**Grammar:**
```
S → Sa | Sb | S₁
S₁ → aS₁a | bS₁b | T
T → Tb | Ta | $
```

**Task:** Show ambiguity by drawing two distinct parse trees for `a$aa`.

### What is Ambiguity?

A grammar is **ambiguous** if there exists at least one string that has **two or more different parse trees** (equivalently, two different leftmost derivations).

### Strategy for Finding Ambiguity

1. Pick the target string: `a$aa`
2. Try to derive it in two structurally different ways
3. Draw the parse tree for each derivation

### Finding Two Derivations of `a$aa`

**Derivation 1 — the rightmost `a` comes from S → Sa:**
```
S ⇒ Sa ⇒ S₁a ⇒ aS₁aa ⇒ aTaa ⇒ a$aa
```
Breakdown:
- S → Sa (adds the last `a`)
- S → S₁ (switch to S₁)
- S₁ → aS₁a (wraps with `a...a`, giving `a S₁ a` + the outer `a` = `a S₁ aa`)
- S₁ → T (switch to T)
- T → $ (base case)

**Derivation 2 — the rightmost `a` comes from T → Ta:**
```
S ⇒ S₁ ⇒ aS₁a ⇒ aTa ⇒ aTaa ⇒ a$aa
```
Breakdown:
- S → S₁ (go directly to S₁, no S → Sa used)
- S₁ → aS₁a (wraps with `a...a`)
- S₁ → T (switch to T)
- T → Ta (T adds an `a` on the right, so `aTa` becomes `a(Ta)a` = `aTaa`)
- T → $ (base case)

**Key difference:**
- **Tree 1:** The rightmost `a` is produced by **S → Sa** at the top level.
- **Tree 2:** The rightmost `a` is produced by **T → Ta** deep inside the tree, and S goes directly to S₁ (never uses S → Sa).

These two trees have different structures at the root — that's your proof of ambiguity.

### How to Draw Parse Trees

```
Tree 1 (S → Sa at root):       Tree 2 (S → S₁ at root):

      S                              S
     / \                             |
    S   a  ← from S→Sa              S₁
    |                              / | \
    S₁                            a  S₁  a  ← from S₁→aS₁a
   /|\                               |
  a  S₁  a  ← from S₁→aS₁a         T
     |                              / \
     T                             T   a  ← from T→Ta
     |                             |
     $   ← from T→$               $  ← from T→$

Leaves: a $ a a                  Leaves: a $ a a
```

**Tree 1:** The rightmost `a` is a direct child of the root S (via S → Sa).
**Tree 2:** The rightmost `a` is a child of T (via T → Ta), and S goes straight to S₁.
Same string, different tree structures → **grammar is ambiguous**.

### General Skill: Proving Ambiguity

1. Look for "overlap" — places where two different rules could account for the same part of the string
2. Specifically look for right-recursion in multiple variables (here S → Sa AND T → Ta both "add an `a` on the right")
3. The string you pick should exploit this overlap
4. Draw both trees clearly, and explain *where* they differ

---

## 6. Quick Reference: CNF Checklist

| Step | What to do | What to look for |
|------|-----------|-----------------|
| 1. λ-productions | Find nullable vars → add combos → delete λ rules | Any `A → λ` |
| 2. Unit productions | Find chains A → B → C... → expand | Any `A → B` (single variable) |
| 3. Useless symbols | Remove non-generating, then non-reachable | Vars that loop forever or are orphaned |
| 4. Terminal replacement | New var for each terminal in mixed rules | `A → aB` type productions |
| 5. Break long rules | Chain into pairs with new vars | Right side with 3+ symbols |

**Final valid forms:** `A → BC` or `A → a` (plus optionally `S₀ → λ` for start symbol)
