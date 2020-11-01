//Created by Wojciech Zurek 17.10.2020

#include <iostream>
#include <vector>


template <typename T = int, int U=100>
class Wektor
{

public:
    std::vector<T>* V;

    Wektor()
    {
        V = new std::vector<T>(U);
    }

     Wektor(int type)
    {
        V = new std::vector<T>(type);
    }   

    // PB: Brak drugiego operatora indeksowania - do pobierania składowych z niemodyfikowalnych obiektów
    T& operator[](int i)
    {
        return V->operator[](i);
    }

    ~Wektor()
    {
        delete V;
    }

};


int main()
{
    Wektor<float, 10> wek;
    Wektor<int> wek2(50);
    Wektor<float> wek3(70);
    Wektor ww;
    std::cout << wek2[2];
    wek2[2]=3;
    std::cout << std::endl << wek2[2];
    std::cout << std::endl << ww[2];

    return 0;
}