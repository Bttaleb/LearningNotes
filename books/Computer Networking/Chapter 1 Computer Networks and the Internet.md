
Devices that connect to the internet are called **hosts** or **end systems**. **End systems** are connected together by a network of **communication links** and **[[packet switches]]**.
	Different links can transmit data at different rates, with **transmission rate** of a link measures in bits/second.
End systems send data to other end systems
	The sending end system **segments the data and adds header bytes to each segment**. The result, known as **packets** are sent through the network to the destination end system, where they are reassembled. 
Sequence of communication links and packet switches traversed by a packet from the sending end system to the receiving end system is known as a **route** or **path**. 
End systems access the Internet through **[[Internet Service Providers (ISPs)]]

End systems, packet switches, and other pieces of the Internet run a [[protocol]] that control the sending and receiving of information within the Internet

Applications include mobile/smartphone apps, Internet messaging, mapping road-traffic are said to be **distributed applications** (involve multiple end systems that exchange data with each other)
Internet applications run on end systems **NOT** in the packet switches in the network core

How does one program running on one end system instruct the Internet to deliver data to another program running on another end system?
	End systems attached to the Internet provide a **[[socket interface]]**
### **Network Protocols**
are the hardware or software components of some device that exchange messages and take actions. All activity in the Internet that involves two or more communicating remote entities is governed by a **[[protocol]]**
eg. making a request to a Web server (typing the URL of a Web page into your Web server)
### **The Network Edge**
 describes the end systems that sit at the **edge of the network**
*Hosts* and *end systems* are used interchangeably
Hosts are sometimes further divided into: 
1. **clients**: desktops, laptops, smartphones
2. **servers**: powerful machines that store and distribute Web pages, stream video, relay emails
## **Access Networks**
 are networks that physically connects an end system to the first router (or edge router) on a path from the end system to any other distant end system 
is by using the two most prevalent types of broadband residential access;
	1. **digital subscriber line (DSL)**
	2. **cable**
### **DSL** Internet access
is obtained from the same *local telephone company (telco)* that provides its wired local phone access. Thus when **DSL** is used, a customer's *telco* is also its ISP.
	The home's DSL modem takes digital data and translates it to high frequency tones for transmission over telephone wires to the CO; the analog signals from many such houses are translated back into digital format at the DSLAM
Each customer's DSL modem uses the existing telephone line exchange data with a digital subscriber line access multiplexer located in the *telco's* central office (CO). The DSL modem then takes digital data and translates it to high-frequency tones for transmission over telephone wires to the CO.
Residential telephone line carries both data & traditional telephone signals, encoded at different frequencies
	- High-speed downstream channel, 50 kHz to 1 MHz band
	- Medium-speed upstream channel, 4 kHz to 50 kHz band
	- Ordinary two-way telephone channel, 0 to 4kHz band
This approach makes it appear as three separate links
Customer side:
	- splitter separates data and telephone signals arriving and forwards the signal to the DSL modem
*Telco* side:
	- In the CO, DSLAM separates data and phone signals and sends the data to the Internet
**DSL** standards define multiple transmission rates;
- downstream rates (of 24 Mbs and 52 Mbs), and
	which is said to be asymmetric with
- upstream rates (of 3.5 Mbps and 16 Mbps)
the newest standard provides up and down of 1 Gbps
### **Cable Internet access**
makes use of the cable television company's existing cable television infrastructure.
	requires special modems called *cable modems* (an external device), which connects to a home PC (through Ethernet)
- a shared broadcast medium
	every packet sent by the head end travels downstream on every link to every home., every packet sent by a home travels on the upstream channel to the head end.
If several users are simultaneously **downloading a video file** on the *downstream channel*;
	actual rate at which each user receives its video file will be lower than the aggregate downstream rate
If there are a few active users and they are all Web surfing;
	each user may receive Web pages at the full cable downstream rate
*Upstream channel* is also shared thus, a distributed multiple access protocol is needed to coordinate transmission & avoid collisions
### **Fiber to the home (FTTH)**
provides an optical fiber path from the CO directly to the home in gigabits per second range.
	The simplest optical distribution network is called direct fiber, one fiber leaving the CO for each home. Each fiber leaving the CO is shared by many homes until the fiber gets close to the homes
Internet access looks like;
	- Each home as an optical network terminator (ONT)
	- ONT is connected by dedicated optical fiber to a neighborhood splitter
	- Splitter combines a # of homes onto a single shared optical fiber.
	- Optical fiber connects to an optical line terminator (OLT)
	- OLT connects to the Internet via telco router
### **Access in the Enterprise: Ethernet & WiFi**
are accessible through the **local area network (LAN)** which is used to connect an end system to the edge router.
	Ethernet is more prevalent, providing 100 Mbps to tens of Gbps vs. the server's 1 Gbps to 10 Gbps access.
	In a wireless LAN setting, users transmit/receive packets to/from an access point that is connected into the enterprise's network. 
### **Wide-Area Wireless Access: 3G, LTE 4G, & 5G**
	How do mobile devices message, share photos in social networks, make mobile payments, watch movies, stream music, and more?
By employing the same wireless infrastructure used for cell telephony to send/receive packets. Users need to be within a few tens of kilometers vs. WiFi's few tens of meters
## Physical Media
What is meant by a physical medium?
	HFC uses a combination of fiber and coaxial cable, DSL & Ethernet use copper wire, mobile access networks use radio spectrum
Consider a bit traveling from one end system:
- travels through a series of links & routers to another end system
- with many routers transmitting and receiving the same bit
- the bit is being sent across a **physical medium**
Physical media fall into two categories:
- **guided media** -> waves are guided along a solid medium (fiber optic, twisted pair copper wire, coaxial cable)
- **unguided media** -> waves propagate in the atmosphere and in outer space (wireless LAN, digital satellite channel)
## The Network Core
the mesh of packet switches and links that interconnects the Internet's end systems
To send a message from a source end system to a destination end system, the message must be broken into smaller chunks or **packets**
	Between source & destination, packets travel through communication links & *packet switches*
Packets are transmitted over comm. link at a rate equal to the *full* transmission rate of the link
### Store-and-Forward Transmission (packet switching)
for routers focuses on transmission at the inputs to the links
	the packet switch must receive the entire packet before it can begin to transmit the first bit of the packet onto the outbound link.
Calculating the amount of time from when the source begins to send the packet, until the destination has received the entire packet:
- The source (end system) begins to transmit at time 0;
- at time *L/R* seconds, the source has transmitted the entire packet, and the entire packet has been received and stored at the router
- at time *2L/R*, the router transmitted the entire packet, and the entire packet has been received by the destination
Routers need to receive, store, and process the entire packet before forwarding

Calculating the amount of time from when the source begins to send the first packet until the destination has received all three packets:
- at time *L/R*, router beings to forward the first packet
- also at time *L/R*, source will begin to send the second packet
- thus, at time *2L/R*, destination has received the first packet and the router has received the second packet
- similarly, at time *3L/R*, destination has received the first two packets, router has received the third packet
- at time *4L/R*, destination received all three packets

**Key Contrast**:
- *One packet* -> store-and-forward penalty is fully exposed. Half the time, one of the two links sits idle
- Several packets -> pipelining. Only the first packet pays the extra hop delay to "full the pipe". After that, a packet arrives at the destination every *L/R*, as if the router weren't there

General case of sending one packet from source to destination over a path consisting of N links each of rate R (thus, N-1 routers between source and destination). End-to-end delay is:
	d<sub>end-to-end</sub> = N · L/R

What would the delay be for P packets sent over a series of N links?
	delay = (N + P - 1) · L/R
- The first packet needs N · L/R to cross all N links
- Each of the remaining P - 1 packets arrive L/R after the one before it

### Queuing Delays and Packet Loss
Each packet switch has multiple links attached. For each link, the switch has an **output buffer/queue**, which stores packets that the router is about to send to that link.
What if the packet finds the link busy with the transmission of another packet?
	The arriving packet must wait in the output buffer. Thus, packets suffer output buffer **queuing delays**. 
	**Packet loss** occurs when an arriving packet finds the buffer completely full with other waiting packets. Either arriving packets or already-queued packets will be dropped.
### Forwarding Tables and Routing Protocols
How does the router determine which link it should forward the packet onto?
When a source end system wants to send a packet to a destination end system:
- the source includes the destination's IP address in the packet header
- on packet arrival (router), examines a portion of the packet's destination address and forwards the packet to an adjacent router
	More specifically, each router has a forwarding table that maps destination addresses to that router's outbound links. When a packet arrives, the router examines the address and searches the table, using this destination address to direct the packet to its appropriate outbound link
End-to-end routing process is analogous to a car driver who does not use maps but instead prefers to ask for directions
	The Internet has a number of special **routing protocols**, used to automatically set forwarding tables. A routing protocol may determine the shortest path from each router to each destination and use the shortest path results to configure the forwarding tables in the routers
### Circuit Switching
another fundamental approach to moving data through a network of links and switches.
Resources are *reserved* for the duration of a communication session between end systems
- buffers and link transmission rates provide the path for resources during the session
In packet-switched networks, resources are *not reserved*;
Analogy:
Consider two restaurants:
1. requires reservations -> must call before leaving home, but may immediately be seated and order a meal
2. neither requires reservations nor accepts them -> don't need to reserve a table, but must wait for a table before being seated
Before the sender of a message can send the information, the network must establish a connection between the *sender* and *receiver*.
	Also known as a **circuit**, in which the *network* reserves a constant transmission rate in the network's links for the duration of the connection

When two hosts want to communicate, the network establishes a dedicated **end-to-end connection**

A circuit switched network may look like; four circuit switches interconnected by four links. Each link has four circuits, so that each link can support four connections. The hosts are directly connected to one of the switches.
	In order for Host A to communicate to Host B, the network reserves one circuit on each of the two links.
In contrast, in packet-switched networks, such as the Internet, the packet is sent into the network without reserving any link resources whatsoever. So if congestion were to happen, the packet will have to wait in a buffer and suffer a delay

### Multiplexing Implementation
is done with either: 
- **[[frequency-division multiplexing (FDM)]]** or
- **[[time-division multiplexing (TDM)]]**