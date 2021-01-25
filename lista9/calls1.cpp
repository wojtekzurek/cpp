#include "calls1.h"

void calls1(){
    auto& a = singleton::instance();
    a.calls();
}