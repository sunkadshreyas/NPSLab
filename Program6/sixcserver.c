#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include <arpa/inet.h>

// Connection Less(UDP) Echo server
// UDP has only itervative server no concurrent server
// Order of function calls : socket() -> bind() -> recvfrom() -> sendto()

void str_echo(int sockfd,struct sockaddr* cli_address, int clilen)
{
      	int n;
      	int bufsize = 1024;
      	char *buffer = malloc(bufsize);
	int addrlen;
	  
	for(;;)
	{
		addrlen = clilen;
		// receive a message from client
  		n=recvfrom(sockfd,buffer,bufsize,0,cli_address,&addrlen);	
		// printf("Message received from client : %s\n",buffer);
		// send the message back to client
		sendto(sockfd,buffer,n,0,cli_address,addrlen);
	}
        //printf("%d n",n);
	
	
}
int main()
{
	int sockfd; 
  	struct sockaddr_in serv_address,cli_address;

	// calling the socket() function
  	if ((sockfd = socket(AF_INET,SOCK_DGRAM,0)) > 0) //sockfd
    		printf("Socket created on Server Side\n");

    	serv_address.sin_family = AF_INET;
	// server address is set to INADDR_ANY so that it can bind 
	// to any available interface
    	// serv_address.sin_addr.s_addr = INADDR_ANY;
	// to bind to local host use following line
	serv_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    	serv_address.sin_port = htons(8080);

    	printf("The address before bind %s  ...\n",inet_ntoa(serv_address.sin_addr));

	// binding to socket
    	if (bind(sockfd,(struct sockaddr *)&serv_address,sizeof(serv_address)) == 0)
    		printf("Bind to Socket Success!!\n");
	else
		printf("Binding Failed!!");

	// calling the helper function	
   	str_echo(sockfd,(struct sockaddr *)&cli_address,sizeof(cli_address));
	  
    	return 0 ;
}
