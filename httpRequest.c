#include "httpRequest.h"
#include <stdio.h>
#include <stdlib.h>

httpRequest* create_httpRequest() 
{
    httpRequest* request = malloc(sizeof(httpRequest));

    *request = (httpRequest) {
        0, NULL, NULL
    };

    return request;
}

void free_httpRequest(httpRequest* req)
{
    //free(req->host);
    free(req->path);
    free(req->version);
    
    free(req);
}