
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
### Network Protocols
Entities that exchange messages and take actions are hardware or software components of some device
All activity in the Internet that involves two or more communicating remote entities is governed by a **protocol**
eg. making a request to a Web server (typing the URL of a Web page into your Web server)

### Network Edge
End systems sit at the **edge of the network**
*Hosts* and *end systems* are used interchangeably
Hosts are sometimes further divided into: 
1. **clients**: desktops, laptops, smartphones
2. **servers**: powerful machines that store and distribute Web pages, stream video, relay emails
### Access Networks
Network that physically connects an end system to the first router (or edge router) on a path form the end system to any other distant end system 

