#ifndef DEMO_URLPARSE_H
#define DEMO_URLPARSE_H

#include <vector>
#include <string>
#include <utility>
using std::vector;
using std::string;
using std::pair;
using std::make_pair;

typedef pair<string, string> kv;
vector<string> split_request_url(string uri);
string get_param(string uri);
vector<kv> split_param(string param);
string decodeURIComponent(string uri);

#endif
