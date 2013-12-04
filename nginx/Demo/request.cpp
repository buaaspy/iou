#include "request.h"

struct http_request {
  string request_method;
  string request_uri;
  string query_string;
};

