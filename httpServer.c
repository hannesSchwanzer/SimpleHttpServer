#include "common.h"
#include <stdio.h>
#include <string.h>

#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int listenfd, connfd, n;
    struct sockaddr_in servaddr;
    uint8_t buff[MAXLINE+1];
    uint8_t recvline[MAXLINE+1];
    uint16_t SERVER_PORT;


    if (argc<2) {
        printf("USAGE: %s (Portnumber)\n", *argv);
        exit(EXIT_FAILURE);
    }
    SERVER_PORT = atoi(argv[1]);

    printf("Starting Server on port %u\n", SERVER_PORT);

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )  err_n_die("socket error.");
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERVER_PORT);

    if ((bind(listenfd, (struct sockaddr*) &servaddr, sizeof(servaddr))) < 0) err_n_die("bind error.");

    if ((listen(listenfd, 10)) < 0) err_n_die("listen error.");

    while(true) {
        struct sockaddr_in addr;
        socklen_t addr_len;
        (void) addr;
        (void) addr_len;

        printf("waiting for a connection on port %d\n", SERVER_PORT);
        fflush(stdout);
        connfd = accept(listenfd, (struct sockaddr*) NULL, NULL);

        memset(recvline, 0, MAXLINE);

        while ( (n = read(connfd, recvline, MAXLINE-1) ) > 0) 
        {
            fprintf(stdout, "\n%s", recvline);

            if (recvline[n-1] == '\n') break;
            memset(recvline, 0, MAXLINE);
        }
        if (n<0) err_n_die("read error");

        int file = open("index.html", S_IRUSR);
        if (file == -1) err_n_die("file open error.");
        
        int fsize = lseek(file, 0, SEEK_END);
        lseek(file, 0, SEEK_SET);



        snprintf((char *) buff, sizeof(buff), "HTTP/1.0 200 OK \r\n\r\n");

        write(connfd, (char*) buff, strlen((char*) buff));

        sendfile(connfd, file, 0, fsize);

        close(connfd);

    }

    return EXIT_SUCCESS;
}