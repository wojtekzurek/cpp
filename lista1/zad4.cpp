//Created by Wojciech Zurek 17.10.2020

#include <iostream>
#include <vector>
#include <typeinfo>

//zad4
template <typename T, typename U>
auto operator*(T &a, U &b)
{
    if(a.size() != b.size())
    {   
        std::cout << "\n\nERROR: sizes of both vectors aren't the same\n";
        return 0;
    }

    if(a.size()==0)
    {
        std::cout << "\n\nERROR: vector size == 0\n";
        return 0;
    }

    auto c = 0;

    for(int i=0; i<a.size(); i++)
        c += a[i]*b[i];
    
    return c;
};
//


template <typename T = int, int U=100>
class Wektor
{

public:
    std::vector<T>* V;

    Wektor()
    {
        V = new std::vector<T>(U);
        std::cout << "constructor a  -- " << U << "\n";
    }

     Wektor(int type)
    {
        V = new std::vector<T>(type);
        std::cout << "constructor b  -- " << type << "  --  "<< U << "\n";
    }   

    T& operator[](int i)
    {
        return V->operator[](i);
    }

    ~Wektor()
    {
        delete V;
    }

    size_t size()
    {
        return V->size();
    }

};




int main()
{
    Wektor<float, 10> wek;
    Wektor<int> wek2(50);
    Wektor<float> wek3(70);
    Wektor ww;
    std::cout << "\n wek2[2] == " << wek2[2];
    wek2[2]=3;
    std::cout << "\n wek2[2] == " << wek2[2];
    std::cout << "\n\n(empty)  ww[2] == "<< ww[2];

    //zad4
    std::cout << "\n\n size of wek2   " << wek2.size();
    std::cout << "\n\n Wektor type of wek3  == " << typeid(wek3[0]).name();
    std::cout << "\n Wektor type of wek2  == " << typeid(wek2[0]).name();

    std::vector<int> s(20);
    s[7]=2;
    int z = s*s;
    std::cout << "\n skalar s == " << z;
    int x = wek2 * wek2;
    std::cout << "\nskalar wek2 == " << x;

    int l = wek2 * s;
    int k = s * wek2;
    std::cout << "\n\nskalar wek2 * s   &   s * wek2 == " << l << " & " << k << "\n";

    return 0;
}