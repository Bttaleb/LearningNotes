- an endpoint for communication
- a concatenation of IP address and port

Socket = [161.25.19.8:1625]
Port = [1625]
Host = [161.25.19.8]

Three types of sockets
1. Connection-oriented (TCP) -> Reliable
2. Connectionless (UDP) -> Unreliable
3. MulticastSocket class -> Can be sent to multiple recipients

Pipes
- A conduit allowing for two processes to communicate
Q's
- Unidirectional or Bidirectional?
- If 2-way communication, half or full duplex?
		Half -> one directional data travel @ a.g.t.
		Full -> both directional at same time
- Relation (parent-child) between communication processes?
- Can be used over network?

[[ordinary-pipes|Ordinary Pipes]] (NO access from outside process that created it)
- Parent process creates a pipe -> Uses it to communicate with a child process that created it

[[Named Pipes]] (access without parent-child relationship)
- Bidirectional
- NO parent-child relationship is necessary between communication
- Exists after communicating processes have finished

Process Control Block (PCB)
- Data structure used by OS to store information about a specific process (unique identifier)
- Contains data such as:
	- Process ID
	- Process state
	- Program counter : Address of next instruction to be executed
	- Registers : 
	- Memory management information