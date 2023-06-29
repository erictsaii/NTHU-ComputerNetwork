#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void doprocessing(int sock);
typedef struct Data {
    char id[200];
    char email[200];
} Data;

Data data[200];
int data_size = 0;

int main(int argc, char *argv[]) {
    int sockfd, newsockfd, portno, clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n, pid;

    /*read the file*/
    FILE *fp = fopen("query.txt", "r");

    while (fscanf(fp, "%s%s", data[data_size].id, data[data_size].email) != EOF) {
        data_size++;
    }

    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    /* Initialize socket structure */
    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno = 1234;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }
    listen(sockfd, 10);
    clilen = sizeof(cli_addr);

    while (1) {
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);

        if (newsockfd < 0) {
            perror("ERROR on accept");
            exit(1);
        }

        pid = fork();

        if (pid == 0) {
            close(sockfd);
            doprocessing(newsockfd);
            exit(0);
        } else {
            close(newsockfd);
        }
    }
}

void doprocessing(int sock) {
    int n;
    char in[256], out[256];

    while (1) {
        bzero(out, 256);
        strcpy(out, "What's your requirement? 1.DNS 2.QUERY 3.QUIT : ");
        write(sock, out, strlen(out));

        bzero(in, 256);
        bzero(out, 256);
        read(sock, in, 255);
        printf("recieved : %s\n", in);

        if (in[0] == '1') {
            strcpy(out, "Input URL address : ");
            write(sock, out, strlen(out));
            bzero(out, 256);
            bzero(in, 256);
            read(sock, in, 255);
            printf("recieved : %s\n", in);
            struct hostent *host = gethostbyname(in);
            if (host == 0) {
                strcpy(out, "No such URL address");
            } else {
                strcpy(out, inet_ntoa(*((struct in_addr *)host->h_addr)));
            }
            write(sock, out, strlen(out));
            bzero(out, 256);
            usleep(1000);
        } else if (in[0] == '2') {
            int found = 0;
            strcpy(out, "Input student ID : ");
            write(sock, out, strlen(out));
            bzero(out, 256);
            bzero(in, 256);
            read(sock, in, 255);
            printf("recieved : %s\n", in);
            for (int i = 0; i < data_size; i++) {
                if (strcmp(in, data[i].id) == 0) {
                    strcpy(out, data[i].email);
                    found = 1;
                }
            }
            if (!found) {
                strcpy(out, "No such student ID");
            }
            write(sock, out, strlen(out));
            bzero(out, 256);
            usleep(1000);
        } else if (in[0] == '3' && strlen(in) == 1) {
            usleep(1000);
            break;
        }
    }
}