/*
    TCP/IP-server
*/

#include<stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>

#define SERVER_PORT 5060  //The port that the server listens

int main() {
    char buf[100];//was 256
//    socklen_t len;

//  1. open new socket
//  in order to get information from the client
    int listening_sock = socket(AF_INET, SOCK_STREAM, 0);
//    close(listening_sock);
    if (listening_sock == -1) {
        perror("failed to open socket");
        return -1;
    }
    printf("new socket opened\n");

//  2. listen to connections
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(SERVER_PORT);

//  Bind the socket to the port with any IP at this port
    int b = bind(listening_sock, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
    if (b == -1) {
        printf("Bind failed with error code : %d", errno);
        return -1;
    }
    printf("Bind() success\n");

    // Make the socket listening; actually mother of all client sockets.
    // 500 is a Maximum size of queue connection requests
    int listener_flag = listen(listening_sock, 500);
    //number of concurrent connections
    if (listener_flag == -1) {
        printf("listen() failed with error code : %d", errno);
        return -1;
    }
    //Accept and incoming connection
    printf("Waiting for incoming TCP-connections...\n");

    struct sockaddr_in clientAddress;  //
    socklen_t clientAddressLen = sizeof(clientAddress);
    for (int i = 0; i < 2; i++) {
        int sumOfBytes = 0;
        int file_num = 1;
        double sum_time = 0;
        while (file_num <= 5) {
//          3. accept connection from "sender"
            memset(&clientAddress, 0, sizeof(clientAddress));
            int clientSocket = accept(listening_sock, (struct sockaddr *) &clientAddress, &clientAddressLen);
            if (clientSocket == -1) {
                printf("listen failed with error code : %d", errno);
                close(listening_sock);
                return -1;
            }

            printf("A new client connection accepted\n");

            int numbytes;
            char reply[10] = "OK";
            write(clientSocket, reply, sizeof(reply));

            struct timeval stop, start;
            gettimeofday(&start, NULL);

//          4. received the file
            do {
                numbytes = recv(clientSocket, buf, 100, 0);
                sumOfBytes += numbytes;
            } while (numbytes != 0);

            if (sumOfBytes == 1048576) {
                printf("Received %d byetes\n", sumOfBytes);
                printf("Received 1mb completely, file number %d \n", file_num++);
            } else {
                printf("Received %d byetes\n", sumOfBytes);
            }

            gettimeofday(&stop, NULL);

            double dt = (double) ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec) / 1000000;
            sum_time += dt;
            printf("Time to receive the file from the client was %f second\n", dt);

            sumOfBytes = 0;
            printf("Listing...\n");
            buf[numbytes] = '\0';

            sleep(1);

        }

//      5. calculate the average
        double avg_time = sum_time / 5;
        char CC[100];
        if (i == 0)
            strcpy(CC, "cubic");
        else
            strcpy(CC, "reno");

        printf("\nAverage time to get 5 files in TPC CC %s is: %f\n\n", CC, avg_time);

    }
//  10. close socket
    close(listening_sock);
    return 0;
}