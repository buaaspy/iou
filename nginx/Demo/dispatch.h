#ifndef DEMO_DISPATCH_H
#define DEMO_DISPATCH_H

#include "request.h"

typedef void (http_request_handler*)(http_request_t request, http_response_t response);


#endif
