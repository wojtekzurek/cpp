#ifndef SINGLETON1
#define SINGLETON1

#include <iostream>
#include <memory>

class singleton{

    int callsCount;
    static std::shared_ptr<singleton> instancePointer;

    singleton();

public:   
    ~singleton();

    static singleton& instance();

    void calls();
};

#endif