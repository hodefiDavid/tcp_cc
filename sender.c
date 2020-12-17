#include <stdio.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define SERVER_PORT 5060

int main(int argc, char **argv) {//ll
    char buf[256];
    socklen_t len;

//    1. open new socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("failed to open socket");
        return -1;
    }
    printf("new socket opened, num = %d\n", sock);

//    2. create connection to measure
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(SERVER_PORT);

    int connect_flag = connect(sock, (struct sockaddr *) &serverAddress, sizeof(serverAddress));

    printf("connect_flag = %d\n", connect_flag);

//    3. sends large file 5 times

    for (int i = 0; i < 5; i++) {
        char message[] = "Good morning, Vietnam\n";
        int messageLen = strlen(message) + 1;
        int bytesSent = send(sock, message, messageLen, 0);
        printf("bytesSent = %d", bytesSent);
    }

//    len = sizeof(buf);
//
//    if (getsockopt(sock, IPPROTO_TCP, TCP_CONGESTION, buf, &len) != 0) {
//        perror("getsockopt");
//        return -1;
//    }
//
//    printf("Current: %s\n", buf);
//
//
//    strcpy(buf, "reno");
//    len = strlen(buf);
//    if (setsockopt(sock, IPPROTO_TCP, TCP_CONGESTION, buf, len) != 0) {
//        perror("setsockopt");
//        return -1;
//    }
//    len = sizeof(buf);
//    if (getsockopt(sock, IPPROTO_TCP, TCP_CONGESTION, buf, &len) != 0) {
//        perror("getsockopt");
//        return -1;
//    }
//    printf("New: %s\n", buf);

//  6. close socket
    close(sock);
    return 0;
}