What is a pipe?
- a one-way byte stream that lives in the kernal
- `pipe(fds)` gives 2 file descriptors: fds[0] (read) & fds[1] (write)
A pipe only connects a *process* to itself
What makes it **IPC**?
- When `fork()` executes, the child inherits copies of each ends
- Each side closes the end it doesn't use

```
    coordinator             worker
   write(fds[1]) ──► [kernel buffer ~64KB] ──► read(fds[0])
```
