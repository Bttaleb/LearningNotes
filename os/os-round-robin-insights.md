# Round Robin Scheduling — Insights

#os #state #data-flow #performance

## Naming & Variables

- **Name matches the question:** If your purpose is to check "are we done?", `done = true` reads cleaner than `processes_remaining = false`. The variable name should match the question you're asking.

- **Avoid double negatives:** Negation (`!`) is fine, but when your variable name AND your check both involve negation, readers do mental gymnastics. `if (done) break;` beats `if (!processes_remaining) break;`.

- **Pick one system, stick with it:** Don't mix `false` with `1`. If you use `bool`, use `true`/`false`. If you use `int`, use `1`/`0`. Consistency prevents bugs.

## Redundant State

- **Don't duplicate what you already know:** If `remaining_time == 0` already tells you a process is finished, you don't need a separate `is_finished` flag. Every extra variable is something you must keep in sync — redundant state is one of the most common sources of beginner bugs.

- **Struct fields earn their place:** Every field in a struct should be read back by someone later. If you calculate a value, add it to a total, and never access it again — it doesn't need to live on the struct.

## Loop Logic

- **Trust your `while` condition:** If `while (processes_remaining)` already exits when the flag is false, an extra `if (!processes_remaining) break;` inside is redundant. It makes readers wonder "is there a subtle reason for this?"

- **Combine checking and working:** Don't use one loop to check "should I keep going?" and another to do the work. If you're already visiting every process, do the work in the same pass.

## Mutual Exclusion Pattern

- **`if/else` vs mutex — same pattern, different tools:** Both enforce "only one of these should happen." But `if/else` solves a logic problem (guaranteed by the compiler). A mutex solves a concurrency problem (enforced at runtime because the compiler can't guarantee thread ordering).

## Formulas from Meaning

- **Derive, don't memorize:** Turnaround time literally means "how long from arrival to completion" → `completion_time - arrival_time`. Waiting time means "how long doing nothing" → `turnaround_time - burst_time`. If you forget a formula, ask what the word means.

## Efficiency

- **Don't walk the array twice:** If you're already in the `else` block when a process finishes, add to the running total there. A separate loop after does the same work — but costs an extra pass.

- **Don't reach for fancy terms:** "I'm already there, so I'll do it there" is a perfectly valid engineering reason. You don't need "data parallelism" to justify a simple optimization.

## C Gotchas

- **Integer division truncates:** `5 / 126` gives `0` in C. Cast to float: `(float)num_of_processes / current_time`.

- **Order of operations matters for printing:** If you update `current_time` before printing, your "start" calculation uses the new value. Either save start before updating, or be careful what you subtract.

- **`break` vs `continue`:** `break` exits the entire loop. `continue` skips to the next iteration. If Process 2 is done, you want to skip it and check Process 3 — that's `continue`, not `break`.
