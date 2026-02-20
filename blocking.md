### Synchronization
	[[Blocking]] <—> Non-blocking
Blocking]]: Synchronous
	- Blocking send — sender is blocked until message is received
	- Blocking receive — receiver is blocked until message is available (NOT SENT!)

Different combinations are made possible with <mark style="background:#fff88f">synchronization</mark>, if both send AND receive are blocking, we have a #rendezvous