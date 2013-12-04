#include <iostream>
#include <string>
#include "../classfactory.h"
 
//@(path="/api/ubuntu")
DECLARE_DYN_CLASS(Test) {
public:
  Test()
  { }

  //@(path="/display", method="UPDATE")
  void display()
  { std::cout << "Test::display()" << std::endl; }
};

//@(path="/api/lxc")
DECLARE_DYN_CLASS(Api) {
 public:
  Api()
  { }

  //@(path="/create", method="POST")
  void do_post()
  { std::cout << "Api::do_post()" << std::endl; }

  //@(path="/create", method="GET")
  void do_get()
  { std::cout << "Api::do_get()" << std::endl; }  
};

int main()
{
  Test* test = (Test*)ClassFactory::create_instance_for_name("Test");
  test->display();

  Api* api = (Api*)ClassFactory::create_instance_for_name("Api");
  api->do_post();
  api->do_get();

  return 0;
}
 
