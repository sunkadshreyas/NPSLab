#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include <arpa/inet.h>
#include<string.h>

// server side

int main()
{
	int count,create_socket,new_socket,addrlen,fd;
	int bufsize = 1024;
	char *buffer = malloc(bufsize);
	char command_name[50];
	struct sockaddr_in address;
  	if ((create_socket = socket(AF_INET,SOCK_STREAM,0)) > 0)
    		printf("server socket created\n");

    	address.sin_family = AF_INET;
    	address.sin_addr.s_addr = INADDR_ANY;
    	address.sin_port = htons(15001);

    	if (bind(create_socket,(struct sockaddr *)&address,sizeof(address)) == 0)
    		printf("Binding Socket\n");

	// listen for connections
    	listen(create_socket,3);

    	addrlen = sizeof(struct sockaddr_in);
    	new_socket = accept(create_socket,(struct sockaddr *)&address,&addrlen);
    	if (new_socket > 0)
    	{
        	printf("The Client %s is Connected...\n",inet_ntoa(address.sin_addr));
    	}
	while(1)
	{
    		count = recv(new_socket,command_name, 50,0);
		command_name[count] = '\0';
    		printf("A request for command_name %s Received..\n\n", command_name);
		int result = strcmp(command_name, "END");
		if(result == 0)
			break;
		printf("The execution of command is  : \n");
		system(command_name);
		printf("\n");
	}
    	close(new_socket);
    	return close(create_socket);
}
