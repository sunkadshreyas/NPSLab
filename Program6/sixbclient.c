#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

// program to demonstrate connection oriented(TCP) echo client
// this is for iterative client
// socket() -> connect() -> send() -> recv()

void str_cli(FILE *fp, int sockfd)
{
	int bufsize = 1024, count;
	char *buffer = malloc(bufsize);

	// receive data from keyboard
	while(fgets(buffer,bufsize,fp)!=NULL)
	{
		// send data to server
		send(sockfd,buffer,sizeof(buffer),0);
		// receive data from server
		if((count=recv(sockfd,buffer,sizeof(buffer),0)) > 0)
		{
			fputs(buffer,stdout);
		}
	}
}

int main(int argc,char *argv[])
{
	int create_socket;
  	struct sockaddr_in address;
  	if ((create_socket = socket(AF_INET,SOCK_STREAM,0)) > 0)
  		printf("The Socket was created\n");
  	address.sin_family = AF_INET;
  	address.sin_port = htons(15001);
  	inet_pton(AF_INET,argv[1],&address.sin_addr);
  	if (connect(create_socket,(struct sockaddr *) &address, sizeof(address)) == 0)
  		printf("The connection was accepted with the server %s...\n",argv[1]);
   	else
		printf("error in connect \n");
	// call the function to handle send and receieve
  	str_cli(stdin,create_socket);
}
