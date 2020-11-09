//Created by Wojciech Zurek 9.11.2020

#include <iostream>
#include "a.h"

template<typename T>
const A copy(T&& object){

    if(std::is_rvalue_reference<decltype(object)>::value){

        std::cout << "r-value reference\n";
        return std::move(object);
    }else{

        std::cout << "l-value reference\n";
        return object;  //czy moze return A{ object } ???
    }
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