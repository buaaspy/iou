#include "pipe.h"

#include <string.h>

std::string fork_exe_read(const std::string& cmd)
{
  const int kmax_buf = 1024;
  int status;
  std::string result;
  char result_buf[kmax_buf];
  FILE *fp;

  fp = popen(cmd.c_str(), "r");
  if(NULL == fp) {
      perror("faliled to create pipe !");
      exit(1);
  }

  while(fgets(result_buf, sizeof(result_buf), fp) != NULL) {
    result += result_buf;
    result += "<br/>";
  }

  status = pclose(fp);
  if(-1 == status) {
      perror("failed to close pipe fd !");
      exit(1);
  }

  return result;
}
