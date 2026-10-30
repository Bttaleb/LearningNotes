for each link:
divide time into frames of fixed duration,
each frame is divided into a fixed number of time slots

on established network *connection* across a link,
dedicate one time slot in every frame to this *connection*

Before TDM, many connections couldn’t share one link because simultaneous signals interfere. TDM solves this by giving each connection a fixed time slot, at the cost of wasting slots when a connection is idle.

time domain is segmented into frames,
four time slots in each frame

transmission rate of a circuit is equal to the frame rate x number of bits in a slot
eg.
- link transmits: 8,000 fps
- each slot consists of 8 bits
transmission rate = 8,000 * 8 = 64000 bits per second / 64 kbps



