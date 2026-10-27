
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
### **Access Networks**
 are networks that physically connects an end system to the first router (or edge router) on a path from the end system to any other distant end system 
### **How a Home Connects to the Internet**
is by using the two most prevalent types of broadband residential access;
	1. **digital subscriber line (DSL)**
	2. **cable**
**DSL** Internet access is obtained from the same *local telephone company (telco)* that provides its wired local phone access. Thus when **DSL** is used, a customer's *telco* is also its ISP.
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
	requires special modems called *cable modems* (an external device), connects to home PC through Ethernet

