#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
// client side

int main(int argc,char *argv[])
{
	int create_socket;
	int bufsize = 1024, cont;
	char *buffer = malloc(bufsize);
	char command_name[50];

	struct sockaddr_in address;
 	if ((create_socket = socket(AF_INET,SOCK_STREAM,0)) > 0)
  		printf("Client Socket created\n");

  	address.sin_family = AF_INET;
  	address.sin_port = htons(15001);
  	inet_pton(AF_INET,argv[1],&address.sin_addr);

	// connect() system call with server	
  	if (connect(create_socket,(struct sockaddr *) &address, sizeof(address)) == 0)
  		printf("The connection was accepted with the server %s...\n",argv[1]);

	while(1)
	{
  		printf("Enter The command to execute or END to quit : ");
       		gets(command_name);
		int res = strcmp(command_name, "END");
  		send(create_socket, command_name, sizeof(command_name), 0);
		if(res == 0)
			break;
	}
  	return close(create_socket);
}
