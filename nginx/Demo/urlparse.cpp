#include "urlparse.h"

static vector<string> split_string(string url, string delimiter)
{
  int pos;
  vector<string> result;

  url += delimiter;

  int size = url.size();
  for (int i = 0; i < size; i++) {
    pos = url.find(delimiter, i);
    if (pos < size) {
      string s = url.substr(i, pos - i);
      result.push_back(s);
      i = pos + delimiter.size() - 1;
    }
  }

  return result;
}

vector<string> split_request_url(string url)
{
  return split_string(url, "/");
}

string get_param(string url)
{
  int pos;
  string param;

  pos = url.find_first_of("?");
  if (pos == string::npos)
    return "";

  param = url.substr(pos + 1, url.length() - pos - 1);

  return param;
}

vector<kv> split_param(string param)
{
  int pos;
  string key, value;
  vector<kv> result;

  vector<string> kvs = split_string(param, "&");
  for (vector<string>::iterator iter = kvs.begin();
       iter != kvs.end();
       iter++) {
    pos = (*iter).find("=");
    key = (*iter).substr(0, pos);
    value = (*iter).substr(pos + 1, (*iter).length() - pos - 1);
    result.push_back(make_pair(key, value));
  }

  return result;
}

string decodeURIComponent(string uri)
{
  string searchstr = "%2520";
  string replacestr = " ";
  string::size_type pos = 0;
  while ((pos = uri.find(searchstr, pos)) != string::npos ) {
    uri.replace(pos, searchstr.size(), replacestr);
    pos++;
  }

  return uri;
}
