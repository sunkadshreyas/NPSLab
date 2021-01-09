
## Multicast Routing

Implement a simple multicast routing mechanism.
Algorithm server side:
Create an AF_INET, SOCK_DGRAM type socket.
Initialize a sockaddr_in structure with the destination group IP address and port number.
Set the IP_MULTICAST_LOOP socket option according to whether the sending system should receive a copy of the multicast datagrams that are transmitted.
Set the IP_MULTICAST_IF socket option to define the local interface over which you want to send the multicast datagrams.
Send the datagram.
Algorithm Client side:
Create an AF_INET, SOCK_DGRAM type socket.
Set the SO_REUSEADDR option to allow multiple applications to receive datagrams that are destined to the same local port number.
Use the bind() verb to specify the local port number.  Specify the IP address as INADDR_ANY in order to receive datagrams that are addressed to a multicast group.
Use the IP_ADD_MEMBERSHIP socket option to join the multicast group that receives the datagrams.  When joining a group, specify the class D group address along with the IP address of a local interface.  The system must call the IP_ADD_MEMBERSHIP socket option for each local interface receiving the multicast datagrams.
Receive the datagram.
