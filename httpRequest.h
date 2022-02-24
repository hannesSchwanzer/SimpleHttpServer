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
    const char version[8];
    const char path[1024];
} httpRequest;


#endif