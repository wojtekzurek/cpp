//Created by Wojciech Zurek
#ifndef ACLASS
#define ACLASS

#include <string>
#include <iostream>


class A
{
    char* field;
    size_t length;

public:
    //reference constructor
    A(std::string const &text){
        length = text.size();  
        field = new char[length];
        text.copy(field, length);

        std::cout << "REFERENCE CONSTRUCTOR for " << field << "\n";
    };

    //copy constructor
    A(A const &object)          //lvalue ref
        : A{ object.field }{

        std::cout << "COPY CONSTRUCTOR for " << field << "\n";
    }

    //move constructor
    A(A &&object)               //rvalue ref
        : field{object.field}, length{object.length} {

        object.field = nullptr;    
        std::cout << "MOVE CONSTRUCTOR for " << field << "\n";
    }  

    const char* get() const {
        std::cout << "get: " << field << "\n";
        return field;
    }

    //destructor
    ~A(){
        if(field){
            std::cout << "DESTRUCTOR for " << field << "\n";
            
            delete [] field;
        }
    }

};



#endif