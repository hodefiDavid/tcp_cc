/* Server code */
/* TODO : Modify to meet your need */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sendfile.h>
// Linux and other UNIXes
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

#define PORT_NUMBER     5060
#define SERVER_ADDRESS  "192.168.1.7"
#define FILE_TO_SEND    "1mb.txt"

int main(int argc, char **argv) {
    int server_socket;
    int peer_socket;
    socklen_t sock_len;
    ssize_t len;
    struct sockaddr_in server_addr;
    struct sockaddr_in peer_addr;
    int fd;
    int sent_bytes = 0;
    char file_size[256];
    struct stat file_stat;
    int offset;
    int remain_data;

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
    serverAddress.sin_port = htons(PORT_NUMBER);

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

    return 0;
}

