---
tags:
  - data-flow
  - concurrency
source: OS Class (Feb 2026)
description: "IPC mechanisms: sockets, pipes, and process identification"
date: 2026-02-17
---
# Sockets
- an endpoint for communication
- a concatenation of IP address and port

Socket = [161.25.19.8:1625]
Port = [1625]
Host = [161.25.19.8]

Unlike [[Ordinary Pipes]] (local only), sockets work across machines → foundation of client-server

Three types of sockets
1. Connection-oriented (TCP) -> Reliable
2. Connectionless (UDP) -> Unreliable
3. MulticastSocket class -> Can be sent to multiple recipients

TCP vs UDP = reliability vs performance (same as [[Communications models#Buffering|buffering]] zero-capacity vs unbounded)
Socket I/O can be [[blocking]] or non-blocking ([[Communications models#Synchronization]])
Classic pattern: [[Multithreaded Programming|multithreaded]] servers → one thread per client connection

---

# Pipes
- A conduit allowing for two processes to communicate
Q's
- Unidirectional or Bidirectional?
- If 2-way communication, half or full duplex?
		Half -> one directional data travel @ a.g.t.
		Full -> both directional at same time
- Relation (parent-child) between communication processes?
- Can be used over network?

[[Ordinary Pipes]] (NO access from outside process that created it)
- Parent process creates a pipe -> Uses it to communicate with a child process that created it
- Unidirectional, producer-consumer style

[[Named Pipes]] (access without parent-child relationship)
- Bidirectional
- NO parent-child relationship is necessary between communication
- Exists after communicating processes have finished

| Mechanism          | Scope                   | Requires Relationship? | Survives Process? |
| ------------------ | ----------------------- | ---------------------- | ----------------- |
| [[Ordinary Pipes]] | Same machine            | Yes (parent-child)     | No                |
| [[Named Pipes]]    | Same machine            | No                     | Yes               |
| Sockets            | Same machine OR network | No                     | Connection-based  |
| Shared Memory      | Same machine            | No                     | Depends           |

[[clustered-systems]] nodes communicate via sockets at larger scale

---

# Process Control Block (PCB)
- Data structure used by OS to store information about a specific [[process-management|process]] (unique identifier)
- Contains data such as:
	- Process ID
	- Process state
	- Program counter : Address of next instruction to be executed (each [[Multithreaded Programming|thread]] has its own PC)
	- Registers
	- Memory management information ([[memory]])

PCB = what makes [[execution-models|context switching]] possible (save state TO pcb, load state FROM pcb)

---

[[Communications models]] | [[Ordinary Pipes]] | [[Named Pipes]] | [[blocking]] | [[Multithreaded Programming]] | [[process-management]] | [[execution-models]] | [[memory]] | [[clustered-systems]]
