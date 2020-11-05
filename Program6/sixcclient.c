#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

// Connection Less(UDP) Echo client
// Order of function calls : socket() -> sendto() -> recvfrom()

void str_cli(FILE *fp, int sockfd,struct sockaddr* serv_address, int servlen)
{
	int bufsize = 1024, count;
   	char *buffer = malloc(bufsize);
	int addrlen = sizeof(struct sockaddr_in);
	struct sockaddr_in *server_addr;
	int len_addr = sizeof(struct sockaddr_in);

	// receive message from standard input
	while(1)
	{
		printf("Enter a message : ");
		if(fgets(buffer,bufsize,fp)==NULL)
		{
			break;
		}
		// send the message to server
		// sendto combination of connect and send
		sendto(sockfd, buffer, sizeof(buffer),0,serv_address,servlen);  

		// receive message from server
		// recvfrom combination of recv and accept
  		if((count=recvfrom(sockfd, buffer, bufsize, 0, (struct sockaddr*)server_addr, &len_addr)>0)) 
		{
			// print the message
			printf("Message echoed by server : ");
    			fputs(buffer,stdout);
			break;
  		}
	}
	
  	// printf("\nEOF\n");
}
int main(int argc,char *argv[])
{
	int sockfd;
  	struct sockaddr_in serv_address;

	// calling the socket() function
  	if ((sockfd = socket(AF_INET,SOCK_DGRAM,0)) > 0)
  		printf("The Socket was create on Client side.\n");
  	serv_address.sin_family = AF_INET;
	// 8080 is a port we can use others as well like 16001
  	serv_address.sin_port = htons(8080);

  	inet_pton(AF_INET,argv[1],&serv_address.sin_addr);

	// calling the helper function
  	str_cli(stdin,sockfd,(struct sockaddr *)&serv_address,sizeof(serv_address));


  	exit(0);
}
