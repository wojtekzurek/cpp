//Created by Wojciech Zurek 24.10.2020

#include <iostream>
#include <string>
#include <cstring>


template <typename T>
T add1(T const &a, T const &b)
{
    T result = a + b;

    return result;
}

template <typename T, typename U>
auto add1(T const &a, U const &b)
{
    return a + b;
}

// PB: Ta wersja ne jest potrzebna
template <typename T>
auto add1(T* a, T* b)
{
    return *a + *b;
}

// PB: Ta funkcja nie modyfukuje argumentów, więc powinna przyjmować wskaźniki do stałych,
//     ale po zmianie na:
//     auto add1(T const *a, U const *b)
//     nie zadziała. I ten problem trzeba było rozwiązać.
template <typename T, typename U>
auto add1(T* a, U* b)
{
    return *a + *b;
}

auto add1(const char* a, const char* b)
{
    return std::string(a) + std::string(b);
}

int main(){

    float sum1 = add1(1.0f, 3.5f);
    std::cout << sum1 << std::endl;

    std::string text1 = "I like";
    std::string text2 = " C++";
    std::string SumText = add1(text1, text2);
    std::cout << SumText << std::endl;

    auto sum2 = add1(5.2f, 7);
    std::cout << sum2 << std::endl;

    auto sum3 = add1(5, 3.7f);
    std::cout << sum3 << std::endl;

    auto sum4 = add1(3.0f, 5);
    std::cout << sum4 << std::endl;

    //ZAD5
    int a = 5, b = 7;
    int* x = &a;
    int* y = &b;
    int sum5 = add1(x, y);
    std::cout << sum5 << std::endl;

    float c = 9.3f;
    float* z = &c;
    auto sum6 = add1(x, z);
    std::cout << sum6 << std::endl;

    const char* f = "text1";
    const char* s = "text2";
    auto sum7 = add1(f, s);
    std::cout << sum7 << std::endl;

    return 0;
}