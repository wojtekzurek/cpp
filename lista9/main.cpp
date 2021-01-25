#include "calls1.h"
#include "singleton_dynamic.h"

int main(){
    auto &ptr = singleton::instance();
    ptr.calls();
    instance().calls();
    calls1();
    calls2();
}