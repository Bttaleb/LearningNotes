---
type: definition
aliases:
  - linked list
  - singly-linked list
  - singly linked list
  - doubly-linked list
  - ListNode
source: "Merge Two Sorted Lists (LeetCode 21)"
description: "A linear chain of nodes, each holding a value and a pointer to the next; reached through its head."
---
# Linked List

**In one line:** a *linear sequence* of nodes where each node holds a **value** and a **pointer to the next node** (`NULL` ends the chain); you only hold the **head**, and reach everything else by following `.next`.

## What it means
- **Node** = `{ value, next }`. **Singly-linked** = one `next`. **Doubly-linked** = `next` *and* `prev`.
- **No random access:** reaching index `k` is **O(k)** (you must walk) — unlike an array's O(1) `a[k]`.
- **But O(1) structural edits:** given a pointer to a node, inserting/deleting/splicing is **O(1)** — just relink `.next`. No shifting (an array insert is O(n)).
- So the trade is: **array** = fast access, slow edits; **linked list** = slow access, fast edits near a known pointer.

**Not a graph.** Each node has **one** `.next` → a *line*. Many neighbors per node → that's a graph (use an [[Adjacency List]], count O(V+E)). "Nodes + pointers" alone doesn't mean graph — count the pointers out of each node.

## Reusable techniques
These recur across almost every linked-list problem:
- **Dummy (sentinel) head:** allocate a throwaway node *before* the real head, build onto it, `return dummy.next`. Kills all the "is the list empty / is this the first node?" special cases. Essential for building a result list.
- **Two pointers:**
  - `prev` / `curr` — in-place reversal, deletion (you need the node *before* the one you change).
  - slow / fast (`+1` / `+2`) — find the middle, detect a cycle.
- **Splice, don't copy:** reuse existing nodes by relinking `.next` instead of allocating new ones → **O(1)** extra space ([[bounded memory]]).

## Example
[[21. Merge Two Sorted Lists]]: walk both lists with two pointers; repeatedly splice the smaller head onto a `tail` built off a **dummy head**. Inputs are sorted, so it's a single monotonic pass — **O(n+m)** time, **O(1)** space (reuses input nodes, no new allocation). The dummy head removes the "which list starts the result?" edge case entirely.

<!-- Notes that use this term show up in the Backlinks pane automatically -->
