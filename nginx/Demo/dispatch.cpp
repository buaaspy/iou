#include <stdio.h>
#include "dispatch.h"


typedef void (http_request_handler*)(http_request_t request, http_response_t response);

typedef uri_dispatcher* uri_dispatcher_t;
struct uri_dispatcher {
  const char* uripattern;
  http_request_handler handler;
};

struct uri_engine {
  int uri_dispatcher_count;
  uri_dispatcher_t dispatchers;
};

struct uri_engine engine;

int loadconf(const char* confpath)
{
  FILE* fstream = fopen(confpath, "r");
  if (fstream == NULL) {
    fprintf(stderr, "cannot find config file !");
    return 0;
  }


  fclose(fstream);

  return 1;
}

static int demo_register_uri_dispatcher()
{
  
}

