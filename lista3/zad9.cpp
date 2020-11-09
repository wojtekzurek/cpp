//Created by Wojciech Zurek 6.11.2020

#include "a.h"
#include <iostream>

//copy
A copy(A const &object){       // l-value reference
    std::cout << "l-value reference\n";
    return object;
}

//move
A copy(A &&object){       // r-value reference

    std::cout << "r-value reference\n";
    return std::move(object);
}

int main(){

    std::cout << "first object\n";
    A a{"text"};

    std::cout << "\nsecond object\n";
    A b{ copy(A("text2")) };

    std::cout << "\nthird object\n";
    A c{ copy(a) };

    //get method
    std::cout << "\nGET:\n";

    a.get();
    b.get();
    c.get();

    return 0;
}