#ifndef DEMO_STRINGUTILS_H
#define DEMO_STRINGUTILS_H

//@(path="/api/*")
class StringUtils {
 public:
  static int startwith(std::string str, std::string pattern);
  static int endwith(std::string str, std::string pattern);
  static int empty(std::string str);
  static int equal(std::string lstr, std::string rstr);
  static std::string ltrim(std::string str);
  static std::string rtrim(std::string str);
  static std::string trim(std::string str);
  static std::string extractparen(std::string str);
  static std::string extractquote(std::string str);
  static std::vector<std::string> split(std::string str, std::string delimiter);
};

#endif
