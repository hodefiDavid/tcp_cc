/*
    TCP/IP-server
*/

#include<stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/time.h>

#define SERVER_PORT 5060  //The port that the server listens

int main() {
    char buf[100];//was 256
//    socklen_t len;

//  1. open new socket
//  in order to get information from the client
    int listening_sock = socket(AF_INET, SOCK_STREAM, 0);
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

//            struct timespec spec;
//            clock_gettime(CLOCK_REALTIME, &spec);
//            time_t start_time = spec.tv_nsec;

            struct timeval stop, start;
            gettimeofday(&start, NULL);

            printf("A new client connection accepted\n");

            int numbytes;
            char reply[10] = "OK";
            write(clientSocket, reply, sizeof(reply));
/*
        char buffer[8192]; // or whatever you like, but best to keep it large
        int count = 0;
        int total = 0;

        while ((count = recv(clientSocket, &buffer[total], sizeof(buffer), 0)) > 0) {
            total += count;
            // At this point the buffer is valid from 0..total-1, if that's enough then process it and break, otherwise continue
        }
        if (count == -1) {
            perror("recv");
        } else if (count == 0) {
            // EOS on the socket: close it, exit the thread, etc.
        }
        printf("total = %d", total);
*/

//          4. received the file
            do {
                numbytes = recv(clientSocket, buf, 100, 0);
//                printf("%d ", numbytes);
                sumOfBytes += numbytes;
            } while (numbytes != 0);

            if (sumOfBytes == 1048576) {
//                if (sumOfBytes == 8388608) {
                printf("Received %d byetes\n", sumOfBytes);
                printf("Received 1mb completely, file number %d \n", file_num++);
            } else {
                printf("Received %d byetes\n", sumOfBytes);
            }

//            clock_gettime(CLOCK_REALTIME, &spec);
//            time_t end_time = spec.tv_nsec;
//            double dt = ((double) end_time - start_time) / 1000000000;
            gettimeofday(&stop, NULL);

            double dt = (double) ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec) / 1000000;
            sum_time += dt;
            printf("Time to receive the file from the client was %f second\n", dt);

            sumOfBytes = 0;
            printf("Listing...\n");
            buf[numbytes] = '\0';
//            sleep(1);


//        printf("Received in pid=%d,"
//               "\ntext=: %s \n", getpid(), buf);
            sleep(1);

//            Reply to client
/*
            char message[] = "Server get the file\n";
            int messageLen = strlen(message) + 1;

            int bytesSent = send(clientSocket, message, messageLen, 0);
            if (-1 == bytesSent) {
                printf("send() failed with error code : %d", errno);
            } else if (0 == bytesSent) {
                printf("peer has closed the TCP connection prior to send().\n");
            } else if (messageLen > bytesSent) {
                printf("sent only %d bytes from the required %d.\n", messageLen, bytesSent);
            } else {
                printf("message was successfully sent .\n");
            }
*/

        }

//      5. calculate the average
        double avg_time = sum_time / 5;
        char CC[100];
        if (i == 0)
            strcpy(CC, "cubic");
        else
            strcpy(CC, "reno");

        printf("\nAverage time to get 5 files in TPC CC %s is: %f\n\n", CC, avg_time);
        // TODO: All open clientSocket descriptors should be kept
        // in some container and closed as well.
    }
//  10. close socket
    close(listening_sock);
    return 0;
}