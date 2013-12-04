#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <utility>
#include "stringutils.h"

int StringUtils::startwith(std::string str, std::string pattern)
{
  if (StringUtils::empty(str) || StringUtils::empty(pattern))
    return 0;
  return str.compare(0, pattern.size(), pattern) == 0;
}

int StringUtils::endwith(std::string str, std::string pattern)
{
  if (StringUtils::empty(str) || StringUtils::empty(pattern)) \
    return 0;
  return str.compare(str.size() - pattern.size(), pattern.size(), pattern) == 0;
}

int StringUtils::empty(std::string str)
{
  return str.empty();
}

std::string StringUtils::ltrim(std::string str)
{
  std::string::iterator iter=find_if(str.begin(),str.end(),not1(std::ptr_fun<int>(::isspace)));
  str.erase(str.begin(),iter);
  return str;
}

std::string StringUtils::rtrim(std::string str) 
{     
  std::string::reverse_iterator rev_iter=find_if(str.rbegin(),str.rend(),not1(std::ptr_fun<int>(::isspace)));
  str.erase(rev_iter.base(),str.end());
  return str;
}

std::string StringUtils::trim(std::string str)
{
  return ltrim(rtrim(str));
}  

std::string StringUtils::extractparen(std::string str)
{
  std::string::size_type lpos, rpos;
  
  lpos = str.find_first_of('(');
  rpos = str.find_last_of(')');
  if (lpos == std::string::npos
      || rpos == std::string::npos
      || lpos >= rpos + 1)
    return "";

  return str.substr(lpos + 1, rpos - lpos - 1);
}

std::vector<std::string> StringUtils::split(std::string str, std::string delimiter)
{
  int pos;
  std::vector<std::string> result;

  str.append(delimiter);

  int size = str.size();
  for (int i = 0; i < size; i++) {
    pos = str.find(delimiter, i);
    if (pos < size) {
      std::string s = str.substr(i, pos - i);
      result.push_back(StringUtils::trim(s));
      i = pos + delimiter.size() - 1;
    }
  }

  return result;  
}
