#include "../scanner.h"
#include <iostream>
#include <vector>
#include <map>
#include <utility>

int main()
{
  Scanner scanner;

  if (!scanner.scan()) {
    std::cout << "scan fail" << std::endl;
    std::cout << scanner.get_root() << std::endl;
    return 0;
  }
  
  std::map<std::string, std::string> uri_class_table = scanner.get_uri_class_table();
  std::map<std::pair<std::string, std::string>, std::string> uri_method_table = scanner.get_uri_method_table();
  std::map<std::string, std::string>::iterator iter = uri_class_table.begin();
  std::map<std::pair<std::string, std::string>, std::string>::iterator it = uri_method_table.begin();

  for (; iter != uri_class_table.end(); iter++)
    std::cout << "URI:" << iter->first << "\tCLASS:" << iter->second << std::endl;

  for (; it != uri_method_table.end(); it++)
    std::cout << "METHOD:" << it->second << std::endl;
}
