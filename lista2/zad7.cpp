//Created by Wojciech Zurek 25.10.2020

#include <iostream>


//template <typename T>
//T add(T a)
//{
//    return a;
//}

auto add()
{
    return 0;
}

template <typename T, typename ... Types>
auto add(T a, Types ... args)
{   
    return a + add(args...);
}

int main()
{
    auto s = add(3, 5, 5);
    auto f = add(3.5f, 7, 5.2, 10);
    std::cout << s << "\n" << f;

    return 0;
}