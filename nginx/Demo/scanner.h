#ifndef DEMO_SCANNER_H
#define DEMO_SCANNER_H

#include <vector>
#include <string>
#include <map>
#include <utility>

//@(path="/api")
class Scanner {
 public:
  Scanner(std::string root = ".") : root_(root) { }

  //@(path="/iou/lxc/delete", method="POST")  
  int scan();

  std::vector<std::string> get_filelist()
  {
    return filelist_;
  }

  //@(path="/iou/lxc/create", method="GET")
  std::string get_root()
  {
    return root_;
  }
  
  std::map<std::string, std::string> get_uri_class_table()
  {
    return uri_class_table_;
  }

  std::map<std::pair<std::string, std::string>, std::string> get_uri_method_table()
  {
    return uri_method_table_;
  }

 private:
  std::string root_;
  std::vector<std::string> filelist_;
  std::map<std::string, std::string> uri_class_table_;
  std::map<std::pair<std::string, std::string>, std::string> uri_method_table_;
};

#endif
