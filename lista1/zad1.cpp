//Created by Wojciech Zurek 17.10.2020

#include <iostream>
#include <string>

// PB: Ta wersja nie jest potrzebna
template <typename T>
T add1(T const &a, T const &b)
{
    T result = a + b;

    return result;
}

template <typename T, typename U>
auto add1(T const &a, U const &b)
{
    return a + T(b);
}

int main(){

    float sum1 = add1(1.0f, 3.5f);
    std::cout << sum1 << std::endl;

    std::string text1 = "I like";
    std::string text2 = " C++";
    std::string SumText = add1(text1, text2);
    std::cout << SumText << std::endl;

    int sum2 = add1(5, 7);
    std::cout << sum2 << std::endl;

    auto sum3 = add1(5, 3.0f);
    std::cout << sum3 << std::endl;

    auto sum4 = add1(3.0f, 5);
    std::cout << sum4 << std::endl;

    return 0;
}