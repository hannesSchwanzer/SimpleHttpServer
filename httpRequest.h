#ifndef _HTTP_REQUEST_
#define _HTTP_REQUEST_

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

typedef struct {
    enum requestMethod method;
    char* version;
    char* path;
} httpRequest;

httpRequest* create_httpRequest();
void free_httpRequest(httpRequest* req);

#endif