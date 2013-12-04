#include "classfactory.h"

std::map<std::string, create_instance_fun> ClassFactory::class_metainfo_table_;

template<typename ClassType, const char class_name[]>
const RegisterProxy Register<ClassType, class_name>::register_proxy_(class_name, 
    Register<ClassType, class_name>::create_instance);
