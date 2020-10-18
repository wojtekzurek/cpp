//Created by Wojciech Zurek 17.10.2020

#include <iostream>
#include <string>


template <typename T, typename U, typename OP>
auto add2(T arg1, U arg2, OP op)
{
    return op(arg1, arg2);
}

int main()
{
    
    int a = 5;
    int b = 2;

    int s = add2(a, b, [=](auto a, auto b){return a+b;});

    float c = 2.1f;
    float d = 4.7f;

    float t = add2(c, d, [=](auto a, auto b){return a-b;});    

    auto u = add2(a, c, [=](auto a, auto b){return a+b;});

    std::cout << s << "\n" << t << "\n" << u << "\n";

    std::string text1 = "I like ";
    std::string text2 = "cpp";

    auto v = add2(text1, text2, [=](auto a, auto b){return a+b;});

    std::cout << v;

    return 0;
}