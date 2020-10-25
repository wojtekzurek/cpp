//Created by Wojciech Zurek 24.10.2020

#include <iostream>
#include <math.h>


template <int a, int N>
struct volume
{   
    enum{val = (a<0 || N<0)? -1 : a*volume<a, std::abs(N-1)>::val};
};

template<int a>
struct volume<a, 0>
{
    enum{val=1};
};


int main()
{
    auto i = volume<2, 3>::val;
    auto j = volume<-2, 3>::val;
    auto k = volume<2, -3>::val;
    std::cout << i << "\n" << j << "\n" << k << "\n";

    return 0;
}