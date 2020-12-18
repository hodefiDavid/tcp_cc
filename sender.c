#include <stdio.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define SERVER_PORT 5060

int main(int argc, char **argv) {
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

//      int msg[] =  malloc()


//    char *buf = malloc(300);
//
//    if (buf == NULL) {
//        /* deal with malloc() failure */
//        printf("error");
//        return -1;
//    }
//    int nread;
///* otherwise do this.  Note 'chunk' instead of 'sizeof buf' */
//    while ((nread = fread(buf, 1, chunk, file)) > 0) {
//        /* as above */
//    }

//    char buf_mes[6];
//    FILE *file;
//    size_t nread;
//
//    file = fopen("t2.txt", "r");
//    if (file) {
//        int i = 0;
////        while ((nread = fread(buf_mes, 1, sizeof(buf_mes), file)) > 0) {
////            fwrite(buf_mes, 1, nread, stdout);
////        }
//        nread = fread(buf_mes, 1, sizeof(buf_mes), file);
//        if (ferror(file)) {
//            printf("error");
//            return -1;
//        }
//        fclose(file);
//    }

    FILE *file_ptr = fopen("1mb.txt", "rb");
    if (file_ptr == NULL) {
        fprintf(stderr, "oh no!");
        return 1;
    }
//    b = atoi(argv[2]);
//    unsigned long byteCount = 0;
//    int ch;
//    while ((ch = fgetc(file_ptr)) != EOF) {
////        if (ch) {//== b
//            byteCount++;
////        }
//    }
//    printf("byteCount = %d\n", byteCount);


    char sendbuffer[100];

    int b;
    int sum = 0;
     do {
        printf("sizeof(sendbuffer) = %d\n", sizeof(sendbuffer));

         b = fread(sendbuffer, 1, sizeof(sendbuffer), file_ptr);
         int bytesSent = send(sock, sendbuffer, b, 0);

        printf("bytesSent = %d\n", bytesSent);

//        file_ptr=+sizeof(sendbuffer);
        sum += bytesSent;
    }while (!feof(file_ptr));
    printf("bytesSent = %d\n", sum);

    printf("The text in the file is:\n%s\n", sendbuffer);


    for (int i = 0; i < 5; i++) {
        char message[] = "Good morning, Vietnam\n";
        int messageLen = strlen(message) + 1;
//        int bytesSent = send(sock, message, messageLen, 0);
//        int bytesSent = send(sock, file, 10, 0);
//        printf("bytesSent = %d", bytesSent);
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