#include "singleton.h"

singleton::singleton(){
    callsCount = 0;

    std::cout << this << " + \n";
}

singleton::~singleton(){
    std::cout << this << " - \n";
}

void singleton::calls(){
    std::cout << singleton::instancePointer.get() << "   " << ++callsCount << "\n";
}

singleton& singleton::instance(){
    if(singleton::instancePointer == nullptr)
        singleton::instancePointer.reset(new singleton);
    
    return *singleton::instancePointer;
}