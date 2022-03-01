#include "httpParser.h"
#include <string.h>
#include <stdlib.h>

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


char* parseRequestLine(httpRequest* req, char* requestString);
void parseHeaders(httpRequest* req, char* requestString);

void parseRequest(httpRequest* req, char* requestString)
{
    int strSize = strlen(requestString);
    char* request = malloc((strSize+1)* sizeof(char));
    memset(request, 0, strSize);
    strcpy(request, requestString);
    int pos = 0;
    
    while (!(pos<strSize) && (*request == '\n' || *request == '\r' || *request == ' '))
    {
        pos++;
        request++;
    }
    if (pos>=strSize) {
        return;
    }
    request = parseRequestLine(req, request);

    //parseHeaders(req, request);

    free(request);
}

char* parseRequestLine(httpRequest* req, char* requestString)
{
    char* method = strtok(requestString, " ");
    char* uri = strtok(NULL, " ");
    char* version = strtok(NULL, "\r\n");
    
    req->path = malloc(sizeof(char)*(strlen(uri)+1));
    strcpy(req->path, uri+1);
    req->path[strlen(uri)-1] = '\0';
    req->version = malloc(sizeof(char)*(strlen(version)+1));
    strncpy(req->version, version, strlen(version));

    if (strncmp(method, "GET", 3) == 0)
    {
    req->method = GET;
    }
    else if (strncmp(method, "POST", 4) == 0)
        req->method = POST;
    else
        req->method = 0;
    
    //requestString = version;
    //while (*requestString != '\0')
    //{
    //    requestString++;
    //}
    //requestString++;
    return requestString;
}

void parseHeaders(httpRequest* req, char* requestString)
{
    (void) req;
    (void) requestString;
}

