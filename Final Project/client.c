#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, const char *argv[]) {
    int socketfd;
    struct sockaddr_in server_addr;
    /*setup the server address*/
    bzero((char *)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(1234);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    /* First call to socket() function */
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }
    /*connect to the server*/
    if (connect(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }
    char buffer[256], option[256];
    while (1) {
        /*What's your requirement?*/
        bzero(buffer, 256);
        read(socketfd, buffer, 255);
        printf("%s", buffer);

        /*send option to the server*/
        scanf("%s", option);
        write(socketfd, option, strlen(option));

        if (option[0] == '1') {
            bzero(buffer, 256);
            read(socketfd, buffer, 255);
            printf("%s", buffer);
            bzero(buffer, 256);
            scanf("%s", buffer);
            write(socketfd, buffer, strlen(buffer));
            /*get the address*/
            bzero(buffer, 256);
            read(socketfd, buffer, 255);
            printf("address get from domain name : %s\n\n", buffer);
        } else if (option[0] == '2') {
            bzero(buffer, 256);
            read(socketfd, buffer, 255);
            printf("%s", buffer);
            bzero(buffer, 256);
            scanf("%s", buffer);
            write(socketfd, buffer, strlen(buffer));
            /*get the email*/
            bzero(buffer, 256);
            read(socketfd, buffer, 255);
            printf("Email get from server : %s\n\n", buffer);
        } else if (option[0] == '3' && strlen(option) == 1) {
            break;
        } else {
            printf("Invalid input\n\n");
        }
    }
    close(socketfd);
    return 0;
}
