#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>


int compare_strings(char a[], char b[])
{
    int c = 0;
    while (a[c] == b[c]) 
    {
        if (a[c] == '\0' || b[c] == '\0')
        break;
        c++;
    }
    if (a[c] == '\0' && b[c] == '\0')
    return 0;
    else
    return -1;
}

int main() {

    int welcomeSocket, Client1, Client2;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;
    char buffer[1024];

    // create server side socket
    welcomeSocket = socket(AF_INET, SOCK_STREAM, 0);
    // fill in the socket address structure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7512);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.01");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
    // bind the server socket
    bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

    // listen for connections
    if (listen(welcomeSocket,5)==0)
        printf("Listening\n");
    else
        printf("Error\n");


    addr_size = sizeof(serverStorage);
    // accept request from client 1
    Client1 = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
    // accept request from client 2
    Client2 = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);

    int cmdEXIT = 0;
 
    while (cmdEXIT == 0)
    {
        // receive message from client 1
        recv(Client1, buffer, 1024, 0);
        // print it on server side
        printf ("Client1 : %s\n", buffer);
        // send to client 2
        send(Client2,buffer,1024,0);
        // if the message is exit then terminate
        if (compare_strings(buffer, "exit")==0)
        {   
            cmdEXIT = 1;
        }
        //sinon
        else 
        {
            // the message is not exit
            memset(&buffer[0], 0, sizeof(buffer));
            // receive message from client 2
            recv(Client2, buffer, 1024, 0);
            // print message on server
            printf ("Client2 : %s\n", buffer);
            // send the message to client 1
            send(Client1,buffer,1024,0);
            // if the message is exit then terminate
            if (compare_strings(buffer, "exit")==0)
            {
                cmdEXIT = 1;
            }
        }
    }

    return 0;
}