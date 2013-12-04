#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <vector>
#include <queue>
#include <map>
#include <iostream>
#include <fstream>

#include "stringutils.h"
#include "scanner.h"

int Scanner::scan()
{
  enum state {JUST_ENTER, CLASS_SCOPE, METHOD_SCOPE, DECLARE_SCOPE};
  DIR *dp;
  struct dirent *dirp;
  struct stat buf;
  std::string tmp;
  std::queue<std::string> que;
  int status;

  // generate filelist
  que.push(root_);
  while (!que.empty()) {
    tmp = que.front();
    que.pop();

    if((dp = opendir(tmp.c_str())) == NULL)
      return 0;

    while((dirp = readdir(dp)) != NULL) {
      tmp.assign(dirp->d_name);

      if (tmp == "." || tmp == ".." || StringUtils::startwith(tmp, "."))
	continue;

      status = stat(tmp.c_str(), &buf);
      if (status >= 0 && S_ISDIR(buf.st_mode)) {
	que.push(tmp);
      } else if (StringUtils::endwith(tmp, ".h") 
		 || StringUtils::endwith(tmp, ".cpp")) {
	filelist_.push_back(tmp.assign(dirp->d_name));
      }
    }

    closedir(dp);      
  }

  // scan annotation
  for (std::vector<std::string>::iterator iter = filelist_.begin();
       iter != filelist_.end();
       iter++) {
    std::string source = *iter;
    std::ifstream stream(source.c_str());
    std::string line;
    std::string class_uri, method_uri;
    std::string class_name, method_name, method;
    state s;

    if (!stream)
      continue;

    s = JUST_ENTER;
    while (getline(stream, line)) {
      std::string tmp;
      if (StringUtils::startwith(StringUtils::ltrim(line), "//@") 
	  && s == JUST_ENTER) {
	class_uri = StringUtils::split(StringUtils::extractparen(line), "=").at(1);
	s = CLASS_SCOPE;
      }

      if (StringUtils::startwith(StringUtils::ltrim(line), "class")
	  && s == CLASS_SCOPE) {
	class_name = StringUtils::split(line, " ").at(1);
	uri_class_table_[class_uri] = class_name;
	s = METHOD_SCOPE;
      }
      
      if (StringUtils::startwith(StringUtils::ltrim(line), "//@")
	  && s == METHOD_SCOPE) {
	method_uri = StringUtils::split(StringUtils::split(line, ",").at(0), "=").at(1);
	if (StringUtils::split(line, ",").size() < 2)
	  method = "";
	else
	  method = StringUtils::split(StringUtils::split(line, ",").at(1), "=").at(1);

	s = DECLARE_SCOPE;
      }

      if (!StringUtils::startwith(StringUtils::ltrim(line), "//@") 
	  && s == DECLARE_SCOPE) {
	method_name = StringUtils::split(StringUtils::trim(line), " ").at(1);
	uri_method_table_.insert(std::make_pair(std::make_pair(method_uri, method), method_name));
	s = METHOD_SCOPE;
      }
       
    }
    
    stream.close();
  }

  return 1;
}
