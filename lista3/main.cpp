//Created by Wojciech Zurek 5.11.2020

#include <iostream>
#include <vector>
#include "a.h"

int main(){

    std::vector<A> vec;

    std::string s = "I like cpp";
    std::string z = "cpp is funny";

    std::cout << "first push back\n";
    vec.push_back( A{ s } );

    std::cout << "\nsecond push back\n";
    vec.push_back( A{ z } );

    return 0;
}