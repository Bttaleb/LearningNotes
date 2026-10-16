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
	- 2 pipes are needed total one flowing down, one flowing up. A single pipe can't carry traffic in both directions because 2 separate instructions are needed to avoid corrupting data
2. Input and outputs -> What is the workload? (Count words for this example). What does **one** job contain, what does one **result** message contain?
	- One job contains counting the words in the given array. One result contains how many words were counted
3. Edge cases -> Name 3 things that can go wrong on this channel
	1. read() returns null
	2. read() and write() can happen at the same time
	3. write() can happen before read()
4. Restate -> What must phase 1 do without using "pipe" or "fork"
	- Create a two way stream that allows us to read and write 