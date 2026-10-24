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

### Function Design Recipe (read_exact function)
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
4.  Examples -> Trace concrete inputs -> expected outputs by hand

| Call # | `got` before | write into pos.      | Ask for how many | read() returns | `got` after |
| ------ | ------------ | -------------------- | ---------------- | -------------- | ----------- |
| 1      | 0            | buf + 0              | 10               | 4              | 4           |
| 2      | 4            | buf + 4              | 6                | 3              | 7           |
| 3      | 7            | buf + 7              | 3                | 3              | 10          |
| 4      | 10           | loop ends (finished) |                  |                |             |

5.  Pattern -> Look at examples, what repeats? what changes?
	- **Write into** is always `buf + got`
	- **Ask for** is always `n - got`
	- **Got after** is always `got before + read() return`
	- Loop ends when `got` reached 10, which is the value for how many asked for, so the loop keeps going while `got < n`
6. Template -> Turn pattern into code skeleton

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

7. Fill In -> Complete the skeleton

| Case                        | Path                             | Returns |
| --------------------------- | -------------------------------- | ------- |
| All bytes arrived in pieces | Loop -> got += r; until got == n | n       |
| Signal Interrupt            | r < 0, EINTR -> continue         | retries |
| Real error                  | r < 0, not EINTR                 | -1      |
| Clean EOF                   | r == 0, got == 0                 | 0       |
| Truncated                   | r == 0, got > 0                  | -1      |


8. Test -> Run examples

In C, `p + k` (buf + got) doesn't add `k` elements, so it moves forward by `k * sizeof(*p)`bytes 

## write_all function
1. Purpose
	- Send exactly `n` bytes from `buf` to `fd`, even though `write()` might accept them in pieces
2. Inputs:
	- fd, where we write to
	- buf, where we read from
	- n, data being transferred
3. Output:

| Outcome                    | Returns                                              |
| -------------------------- | ---------------------------------------------------- |
| Sent all `n` bytes         | n                                                    |
| The reader is gone (EPIPE) | -1, errno = EPIPE (precondition: SIGPIPE is ignored) |
| A real error               | -1                                                   |
| Interrupted                | Not visible to caller, retries internally            |
4. Pseudocode


**Job Pipe**: coordinator *writes* -> worker *reads*
**Result Pipe**: worker writes -> coordinator *reads*
Each process (job/result) holds one end of each pipe
- If you find yourself thinking "the coordinator reads from the job (process) pipe", its a sign it forgot to close an end

## Test functions

| Test               | Scenario                                                          | Expects                           | Proves                                                                            |
| ------------------ | ----------------------------------------------------------------- | --------------------------------- | --------------------------------------------------------------------------------- |
| test_chunked_read  | Child writes "ABCD", "EFG", "HIJ" with sleeps; parent asks for 10 | ret == 10 AND buf == "ABCDEFGHIJ" | The loop survives short reads, and 'buf + got' puts each chunk in the right place |
| test_clean_eof     | Child writes nothing, closes                                      | ret == 0                          | EOF between messages = normal goodbyte (worker sees "no more jobs")               |
| test_truncated_eof | Child writes "ABCDE" (5), closes; parent asks for 10              | ret == -1                         | EOF mid message = error; got > 0 flips the same event from 0 to -1                |
| test_bad_fd        | read_exact(-1, buf, 10), no pipe or fork                          | ret = -1 AND errno = EBADF        | Real read() errors pass through with the correct errno                            |
|                    |                                                                   |                                   |                                                                                   |
### **test_chunked_read**

	returns n on success
	
```c
// CHILD  process (scripted writer)
if (pid == 0) {
	close(fds[0]);
	write(fds[1], "ABCD", 4);
	usleep(1000);
	write(fds[1], "EFG", 3);
	usleep(1000);
	write(fds[1], "HIJ", 3);
	usleep(1000);
	close(fds[1]);
	_exit(0);
}
// PARENT process (scripted reader)
if (pid > 0) {
	close(fds[`]); // close wrie end
	char buf[10]; // allocate a 10 byte buffer
	ssize_t ret = read_exact(fds[0], buf, 10); // caller for a return value
	
	// if our returned value is 10 and it's equal to "ABCDEFGHIJ" in our buffer,         then we can move on
	if (ret == 10 && memcmp(buf, "ABCDEFGHIJ", 10) == 0) {
		printf("PASS: chunked read");
	} else {
		printf("FAIL: chunked read (ret=%zd, buf='%.*s')\n", ret, 10, buf)'
	}
	
	close(fds[0]); // close our read pipe
	waitpid(pid, NULL, 0); // terminate the process (avoid zombie)
}
```

## test_clean_eof

	return 0 on clean EOF
	
```c
// CHILD process
if (pid == 0) {
	close(fds[0]); // close the read end
	close(fds[1]); // close the write end
	_exit(0); // exit the process
}
// PARENT process
if (pid > 0) {
	close(fds[1]); // close writer
	char buf[10]; // create 10 byte buffer
	ssize_t ret = read_exact(fds[0], buf, 10); // read our bytes from the buffer
	
	if (ret == 0) { // if no bytes read, clean pass
		printf("PASS: clean eof");
	} else { // fail anything else, return its value
		printf("FAIL: clean eof (expected ret=0, got ret=%zd)", ret);
		close(fds[0]); // close reader
	}
	close(fds[0]); // outside close reader
	waitpid(pid, NULL, 0); // terminate process
}
```


## test_truncated_eof
	return -1 on truncated eof (missing bytes)
```c
// CHILD process
if (pid == 0) {
	close(fds[0]); // close reader
	write(fds[1], "ABCDE", 5); // write 5 bytes
	close(fds[1]); // close writer
	_exit(0);
}
// PARENT process
if (pid > 0) {
	close(fds[1]);
	char buf[10];
	ssize_t ret = read_exact(fds[0], buf, 10); // we're asking for 10 bytes          (rememeber the child only sent 5 bytes)
	if (ret == -1) {
		printf("PASS: truncated EOF check");
	} else {
		printf("FAIL: truncated EOF (expected ret=-1, got ret=%zd)", ret);
	}
	
	close(fds[0]);
	waitpid(pid, NULL, 0);
}
```

## test_bad_fd
	returns -1 on real error
	
```c
char buf[10];
ssize_t ret = read_exact(-1, buf, 10); // -1 guarantees we never get a valid ticket number
// kernel: look up slot -1 in this process's fd table (no such slot)
if (ret < 0 && errno == EBADF) {
	printf("PASS: real error");
} else {
	printf("FAIL: real error (expected ret=-1, got ret=%zd"), ret);
}
```

## Helper Functions
How can we find the *helper function's* parameters?
- Put them side by side (diff)
- Label the lines that are the same/different
- The same lines go into the helper body
- Name the ROLE of each different line

1. **Chunks**: what's the C type of "an array of strings", and what extra parameters does the helper need?
	
```c
const char *chunks[]
```

2. **Expected** `buf`: how does `NULL` let one parameter mean either "check against this string" or "don't check"?
	Since `NULL` is a signal *from the caller to the helper*, the helper has no expectation for `buf` in it's test

| Caller Passes | Helper Does                    |
| ------------- | ------------------------------ |
| "ABCDEFGHIJ"  | memcmp(buf, expected_buf, ...) |
| NULL          | Skips the check                |

3. **Bytes asked for vs. expected** `ret`: same type, or different?
	Different types since we need to be able to hand positive and negative numbers
	
| Parameter       | Type      | Why                                                                                                |
| --------------- | --------- | -------------------------------------------------------------------------------------------------- |
| Bytes asked for | size_t    | It's a size, never negative. Passed straight to `read_exact`'s `n`, so it should match that type   |
| Expected `ret`  | `ssize_t` | Has to hold `-1`. It's compared with `read_exact`'s **return value**, so it should match that type |


|                           | chunked read         | clean EOF | truncated EOF       |
| ------------------------- | -------------------- | --------- | ------------------- |
| What the child writes     | "ABCD", "EFG", "HIJ" | nothing   | "ABCDE" (one chunk) |
| Bytes the parent asks for | 10                   | 10        | 10                  |
| Expected `ret`            | 10                   | 0         | -1                  |
| Check `buf`?              | yes, "ABCDEFGHIJ"    | no        | no                  |
| Test name                 | chunked read         | clean eof | truncated eof       |

## write_all tests

| Outcome                  | How to trigger it                                                                  | Expected `ret` | Expected `errno` | Testable? |
| ------------------------ | ---------------------------------------------------------------------------------- | -------------- | ---------------- | --------- |
| All bytes written        | write_all(fd, "ABCDEFHIJ", 10)                                                     | 10 (n)         |                  | Yes       |
| Reader is gone           | child closes its read end and exits before parent writes, and `SIGPIPE` is ignored | -1             | EPIPE            | yes       |
| Bad fd                   | fd = -1                                                                            | -1             | EBADF            | yes       |
| write() returns 0 -> EIO | unreachable with real pipes                                                        | -1             | EIO              | No        |
| EINTR retry              | signal mid-write                                                                   |                |                  | no        |
1. The child reads and checks the bytes. How does it report the result to the parent? What does waitpid(pid, NULL, 0) throw away?
	 `NULL` throws away the child's exit status. `waitpid` reaps the child, whatever is passes as the second argument. To receive it, pass an `int` to fill instead of `NULL`
	 
```c
int status;
waitpid(pid, &status, 0);
WIFEXITED(status) // true if the child exited normall (not killed by a signal)
WEXITSTATUS(status) // the number it passed to _(exit)
```
2. Is it okay for the child to use `read_exact` to read them, even though we should "test one thing at a time"? What's different now compared to when test 1 was written
	 `read_exact` is verified, earlier it was untested. Now that is has its own passing test covering every outcome, including mutation checks that showed those tests can detect bugs, we can trust its infrastructure
Parent (writer, function under test)
close()