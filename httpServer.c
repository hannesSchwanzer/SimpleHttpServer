#include "util/common.h"
#include "httpFunctions/httpRequest.h"
#include "httpFunctions/httpParser.h"
#include "settings.h"
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
#include <fcntl.h>
#include <stdbool.h>

#define BUFF_SIZE 4096
char buffRequest[BUFF_SIZE];
char buffResponse[BUFF_SIZE];

int readLine(int fd, char *buff, int buff_size);


bool strempty(char* str)
{
    return *str=='\0';
}

void readRequest(httpRequest* req, int connfd)
{
    memset(buffRequest, 0, BUFF_SIZE);
    if (read(connfd, buffRequest, BUFF_SIZE-1) == -1)
        err_n_die("reading request error.");

    parseRequest(req, buffRequest);
    printf("\n-----------------------------------\nRequest Header:\n\tMethod: %d\n\tPath: %s\n\tVersion: %s\n", req->method, req->path, req->version);
    dictionary_print(req->headers);
}

void handleRequest(httpRequest* req, int connfd)
{
    char filepath[1024];
    switch (req->method)
    {
    case GET:
        memset(filepath, 0, 1024);
        memset(buffResponse, 0, BUFF_SIZE);
        if (req->path==NULL)
        {
            snprintf((char *) buffResponse, sizeof(buffResponse), "HTTP/1.0 400 Bad Request \r\n\r\n");
            write(connfd, (char*) buffResponse, strlen((char*) buffResponse));
            return;
        } 
        else if (strempty(req->path))
        {
            sprintf(filepath, "%s/%s", FOLDER, DEFAULT_FILE);
        } 
        else
        {
            sprintf(filepath, "%s/%s", FOLDER, req->path);
        }

        int file = open(filepath, O_RDONLY);
        if (file == -1) {
            snprintf((char *) buffResponse, sizeof(buffResponse), "HTTP/1.0 404 Not Found \r\n\r\n");
            write(connfd, (char*) buffResponse, strlen((char*) buffResponse));
        } else {
            snprintf((char *) buffResponse, sizeof(buffResponse), "HTTP/1.0 200 OK \r\n\r\n");
            write(connfd, (char*) buffResponse, strlen((char*) buffResponse));
            int fsize = lseek(file, 0, SEEK_END);
            lseek(file, 0, SEEK_SET);
            sendfile(connfd, file, 0, fsize);
            close(file);
        }

        break;
    
    default:
        snprintf((char *) buffResponse, sizeof(buffResponse), "HTTP/1.0 501 Not Implemented \r\n\r\n");
        write(connfd, (char*) buffResponse, strlen((char*) buffResponse));
        break;
    }
}

int main(int argc, char **argv)
{
    int listenfd, connfd, n;
    struct sockaddr_in servaddr;
    uint16_t SERVER_PORT;
    (void) n;

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

        printf("\nWaiting for a connection on port %d\n", SERVER_PORT);
        fflush(stdout);
        connfd = accept(listenfd, (struct sockaddr*) NULL, NULL);

        httpRequest* request = create_httpRequest();

        readRequest(request, connfd);
        
        handleRequest(request, connfd);
        

        free_httpRequest(request);

        
        close(connfd);

    }

    return EXIT_SUCCESS;
}