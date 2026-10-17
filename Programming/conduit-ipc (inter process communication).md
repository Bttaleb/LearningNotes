What is a pipe?
- a one-way byte stream that lives in the kernel
- `pipe(fds)` gives 2 file descriptors: fds[0] (read) & fds[1] (write)
A pipe only connects a *process* to itself
What makes it **IPC**?
- When `fork()` executes, the child inherits copies of each ends
- Each side closes the end it doesn't use

```
    coordinator             worker
   write(fds[1]) ──► [kernel buffer ~64KB] ──► read(fds[0])
```
A [[protocol]] is needed as 
- two `write()`s of 100 bytes each can come out as one `read()` of 200 bytes,
- or as reads of 37 and 163
Messages are imposed **on top** of the steam

## Polya Step 1: Understand the problem
1. Topology -> You have 1 coordinator and N workers. Jobs flow **down** to workers and results flow **back up**. How many pipes needed total? Why can't a single pipe carry traffic in both directions?
	- 1 coordinator, N workers -> **2N pipes** (one job pipe + one result pipe)
2. Input and outputs -> What is the workload? (Count words for this example). What does **one** job contain, what does one **result** message contain?
	- A message = data only
	- Frame: `[len: u32][type: u8][payload: len bytes]`
	- JOB: (type=1): `[job_id: u32][text_len: u32][text: text_len bytes]`
	- RESULT (type=2): `[job_id: u32][word_count: u64][compute_ns: u64]`
3. Edge cases -> What can go wrong on this channel

| Case              | What happens                                                              | Handling                                                    |
| ----------------- | ------------------------------------------------------------------------- | ----------------------------------------------------------- |
| Short read        | read() returns fewer bytes than asked                                     | Loop until the full N bytes recieved                        |
| EOF (End of File) | read() returns 0 when all write ends are closed                           | Treat as "peer is done"                                     |
| Forgotten close() | fd table is copied on fork -> write end has 2 references; EOF never fires | Each side closes the end it doesn't use, right after fork() |
| Signal Interrupt  | read() returns -1                                                         | Retry                                                       |
| Reader gone       | write() to a pipe with no reader -> SIGPIP (kills process by default)     | Ignore SIGPIPE, handle EPIPE                                |
| Full buffer       | 64KB pipe buffer fills -> write() blocks                                  | Deadlock                                                    |
| Deadlock          | coordinator blocked writing to A's full job pipe                          | Circular wait                                               |
| Worker crash      | job lost mid flight                                                       | Detect via EOF                                              |
| Chunk Boundary    | A word split across two chunks gets counted twice                         | Split chunks on whitespace, not fixed byte offset           |
| Zombies           | Exited workers keep a process table entry until reaped                    | waitpid() every worker                                      |

4. Restate -> What must phase 1 do without using "pipe" or "fork"
	- Split a large text file into chunks,
	- hand each chunk to one of N independent worker processes that count words in parallel, 
	- collect each count back tagged with it's job ID,
	- sum them into a total, and record per job latency and overall throughput as the **baseline** that later transports must beat 

### Function Design Recipe
1. Purpose -> what is this function trying to accomplish
	- Fill `buf` with exactly `n` bytes from `fd`, even though `read()` might hand them over in pieces
2. Inputs -> what does it receive
	- `fd`: where our bytes come from
	- `buf`: where we put them
	- `n`: how many bytes the caller needs
3. Output -> What does it return, for each possible outcome
	

| Outcome                                   | `read_exact` return |
| ----------------------------------------- | ------------------- |
| Got all `n` bytes                         | n                   |
| Other side closed before any byte arrived | 0                   |
| Other side closed partway                 | -1                  |
| A real error                              | -1                  |

1. Examples -> Trace concrete inputs -> expected outputs by hand

| Call # | `got` before | write into pos.      | Ask for how many | read() returns | `got` after |
| ------ | ------------ | -------------------- | ---------------- | -------------- | ----------- |
| 1      | 0            | buf + 0              | 10               | 4              | 4           |
| 2      | 4            | buf + 4              | 6                | 3              | 7           |
| 3      | 7            | buf + 7              | 3                | 3              | 10          |
| 4      | 10           | loop ends (finished) |                  |                |             |

1. Pattern -> Look at examples, what repeats? what changes?
	- **Write into** is always `buf + got`
	- **Ask for** is always `n - got`
	- **Got after** is always `got before + read() return`
	- Loop ends when `got` reached 10, which is the value for how many asked for, so the loop keeps going while `got < n`
2. Template -> Turn pattern into code skeleton

```c
read_exact(fd, buf, n):
	got = 0
	while (got < n):
		r = read(fd, (char *)buf + got, n - got)
		if r < 0:
			if errno == EINTR: continue
			return -1
		if r == 0:
			if got == 0: return 0
			return -1
		got = got + r
	return n

```

1. Fill In -> Complete the skeleton

| Case                        | Path                             | Returns |
| --------------------------- | -------------------------------- | ------- |
| All bytes arrived in pieces | Loop -> got += r; until got == n | n       |
| Signal Interrupt            | r < 0, EINTR -> continue         | retries |
| Real error                  | r < 0, not EINTR                 | -1      |
| Clean EOF                   | r == 0, got == 0                 | 0       |
| Truncated                   | r == 0, got > 0                  | -1      |


2. Test -> Run examples

In C, `p + k` (buf + got) doesn't add `k` elements, so it moves forward by `k * sizeof(*p)` bytes 

