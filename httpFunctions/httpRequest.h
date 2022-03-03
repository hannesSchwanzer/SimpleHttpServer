#ifndef _HTTP_REQUEST_
#define _HTTP_REQUEST_

#include "../Data_Structures/Dictionary/dictionary.h"

enum requestMethod{
    GET,
    POST,
    HEAD,
    PUT,
    DELETE,
    CONNECT,
    OPTIONS,
    TRACE,
    PATCH
};

typedef struct httpRequest{
    enum requestMethod method;
    char* version;
    char* path;
    Dictionary* headers;
} httpRequest;

httpRequest* create_httpRequest();
void free_httpRequest(httpRequest* req);

#endif