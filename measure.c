/*
    TCP/IP-server
*/
#define MAXDATASIZE 1500
#include<stdio.h>

// Linux and other UNIXes
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>


#define SERVER_PORT 5060  //The port that the server listens

int main()
{    char buf[256];
    socklen_t len;

//    1. open new socket
    int listening_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (listening_sock == -1) {
        perror("failed to open socket");
        return -1;
    }
    printf("new socket opened\n");

//    2. listen to connections
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(SERVER_PORT);

    // Bind the socket to the port with any IP at this port
    int b = bind(listening_sock, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
    if (b == -1) {
        printf("Bind failed with error code : %d", errno);
        return -1;
    }
    printf("Bind() success\n");

    // Make the socket listening; actually mother of all client sockets.
    // 500 is a Maximum size of queue connection requests
    int listener = listen(listening_sock, 500);
    //number of concurrent connections
    if (listener == -1) {
        printf("listen() failed with error code : %d", errno);
        return -1;
    }
    //Accept and incoming connection
    printf("Waiting for incoming TCP-connections...\n");

    struct sockaddr_in clientAddress;  //
    socklen_t clientAddressLen = sizeof(clientAddress);

    while (1)
    {

        memset(&clientAddress, 0, sizeof(clientAddress));
//        clientAddressLen = sizeof(clientAddress);
        int clientSocket = accept(listening_sock, (struct sockaddr *)&clientAddress, &clientAddressLen);
        if (clientSocket == -1)
        {
            printf("listen failed with error code : %d",errno);
            // TODO: close the sockets
            return -1;
        }

        printf("A new client connection accepted\n");

        int numbytes;

        if ((numbytes=recv(clientSocket, buf, MAXDATASIZE, 0)) == -1) {
            perror("recv");
            exit(1);
        }

        buf[numbytes] = '\0';

        printf("Received in pid=%d,"
               "\ntext=: %s \n",getpid(), buf);
        sleep(1);



        //Reply to client
        char message[] = "Welcome to our TCP-server\n";
        int messageLen = strlen(message) + 1;

        int bytesSent = send(clientSocket, message, messageLen, 0);
        if (-1 == bytesSent)
        {
            printf("send() failed with error code : %d",errno);
        }
        else if (0 == bytesSent)
        {
            printf("peer has closed the TCP connection prior to send().\n");
        }
        else if (messageLen > bytesSent)
        {
            printf("sent only %d bytes from the required %d.\n", messageLen, bytesSent);
        }
        else
        {
            printf("message was successfully sent .\n");
        }

    }

    // TODO: All open clientSocket descriptors should be kept
    // in some container and closed as well.

    close(listening_sock);


    return 0;
}