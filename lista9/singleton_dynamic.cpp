#include "singleton_dynamic.h"

void calls2(){
    auto& ptr = singleton::instance();
    ptr.calls();
}

singleton& instance(){
    return singleton::instance();
}