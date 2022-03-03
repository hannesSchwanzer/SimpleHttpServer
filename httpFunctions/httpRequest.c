#include "httpRequest.h"
#include <stdio.h>
#include <stdlib.h>

httpRequest* create_httpRequest() 
{
    httpRequest* request = malloc(sizeof(httpRequest));

    Dictionary* dict = malloc(sizeof(Dictionary));
    dictionary_init(dict, 101);

    *request = (httpRequest) {
        0, NULL, NULL, dict
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