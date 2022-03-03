#include "httpParser.h"
#include "../Data_Structures/Dictionary/dictionary.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "../util/strfunc.h"

char* parseRequestLine(httpRequest* req, char* requestString);
void parseHeaders(httpRequest* req, char* requestString, char* eofHeader);


void parseRequest(httpRequest* req, char* requestString)
{
    int strSize = strlen(requestString);
    char* request = malloc((strSize+1)* sizeof(char));
    char* pointerPos = request;
    memset(request, 0, strSize);
    strcpy(request, requestString);
    
    pointerPos = trimLeft(pointerPos);
    pointerPos = parseRequestLine(req, pointerPos);

    pointerPos = trimLeft(pointerPos);
    
    //seperates header from body
    char* eofHeader = StringFind(pointerPos, "\r\n\r\n");
    *eofHeader = '\0';

    parseHeaders(req, pointerPos, eofHeader);

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
    
    return version+strlen(version)+1;
}

void parseHeaders(httpRequest* req, char* requestString, char* eofHeader)
{
    char* header = trimBoth(strtok(requestString, ":"));
    char* headerValue = trimBoth(strtok(NULL, "\n"));

    while(header != NULL && headerValue != NULL)
    {
        toLowerCase(header);
        toLowerCase(headerValue);
        dictionary_add(req->headers, header, headerValue);
        if((strlen(headerValue)+headerValue) >= eofHeader) break;
        if ((header = trimBoth(strtok(NULL, ":"))) == NULL) break;
        headerValue = trimBoth(strtok(NULL, "\n"));
    }

}

