#ifndef DEMO_CLASSFACTORY_H
#define DEMO_CLASSFACTORY_H

#include <string>
#include <map>
#include <utility>

typedef void* (*create_instance_fun)(void);

class ClassFactory
{
 public:
  static create_instance_fun get_class_create_fun_by_name(std::string class_name)
  {
    std::map<std::string, create_instance_fun>::const_iterator iter;
    iter = class_metainfo_table_.find(class_name);

    return iter == class_metainfo_table_.end() ? NULL : iter->second;
  }

  static void* create_instance_for_name(std::string class_name)
  {
    create_instance_fun create_fun = get_class_create_fun_by_name(class_name);

    if (create_fun == NULL)
      return NULL;
    return (*create_fun)();
  }
  
  static void register_class(std::string class_name, create_instance_fun create_fun)
  {
    class_metainfo_table_.insert(std::make_pair(class_name, create_fun));
  }
  
 private:
  static std::map<std::string, create_instance_fun> class_metainfo_table_;
};

class RegisterProxy
{
 public:
  RegisterProxy(std::string class_name, create_instance_fun create_fun)
  {
    ClassFactory::register_class(class_name, create_fun);
  }
};

template<typename ClassType, const char class_name[]>
class Register
{
 public:
  Register()
  {
    const RegisterProxy tmp = register_proxy_;
  }

  static void* create_instance()
  {
    return new ClassType;
  }

 private:
  static const RegisterProxy register_proxy_;
};

#define DECLARE_DYN_CLASS(ClassType)					        \
  char no_use_anywhere_else##ClassType[] = #ClassType;			        \
  class ClassType : public Register<ClassType, no_use_anywhere_else##ClassType>

#endif
