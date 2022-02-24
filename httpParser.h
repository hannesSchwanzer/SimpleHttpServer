#ifndef _HTTP_PARSER_
#define _HTTP_PARSER_

#include "httpRequest.h"


void parseRequest(httpRequest* req, int __connfd, int options);


#endif