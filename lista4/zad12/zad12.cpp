#include <stdio.h>
#include <time.h>
#include <omp.h>


int main()
{

    const int N = 1000'000'000;
    int i = 0;
    float sum = 0;
    clock_t t0 = clock();

    #pragma omp parrarel for private(i) reduction(+:sum)
    for (i = N-1; i >= 0; --i)
    {
        #pragma omp critical
        sum += 1.0/((float)i+1.0);
    }

    clock_t t1 = clock();

    printf("s = %g\n", sum);
    printf("t = %g\n", ((double)t1 - t0)/CLOCKS_PER_SEC);

}

/*
bez -fopenmp
t = 5.46234
s = 18.8079

z -fopenmp
t = 6.10604
s = 19.4017

-wersja rownolegla daje inny wynik niz szeregowa.

watki       czas        real        user        sys             wyniki      s           t
1                       0m5.339s    0m5.323s    0m0.000s                    18.8079     5.32039
2                       0m2.919s    0m5.831s    0m0.004s                    18.8704     5.83166
4                       0m1.476s    0m5.889s    0m0.005s                    19.0267     5.88134
8                       0m0.772s    0m6.124s    0m0.000s                    19.4017     6.11653
16                      0m0.869s    0m6.064s    0m0.000s                    20.164      6.06202

- Kod jest napisany prawidlowo. Inny wynik wynika z asocjatywnosci operacji (associativity of operations). Aby uzyskac ten sam wynik, nalezy samodzielnie zaimplementowac redukcje,
    przechowujac czesciowa sume kazdego watku we wspolnej tablicy. Nastepnie po takiej operacji watek glowny powinien zsumowac te wszystkie wyniki.

- clock() jest to funkcja zwracajaca czas procesora zuzyty przez program. Zwracana wartosc jest wyrazana w taktach zegara, ktore sa jednostkami o stalej dlugosci
            czasu, ale ta dlugosc jest specyficzna dla kazdego systemu (CLOCKS_PER_SEC).

- Jezeli porownamy czas liczony przez program za pomoca funkcji clock() do czasu mierzonego przez system poleceniem time (user), to mozemy zauwazyc ze obydwa czasy sa
            bardzo podobne (roznica na 3 miejscu po przecinku). Jednak funkcja clock() nie nadaje sie do mierzenia czasu dla wersji rownoleglej programu, gdyz
            zwraca ona skumulowany czas procesora wszystkich watkow, ktore kiedykolwiek istnialy od jego uruchomienia. Do mierzenia czasu w wersji rownoleglej
            nalezy uzyc funkcji wywolania zegara o wysokiej rozdzielczosci (OpenMP omp_get_wtime()).

- w wynikach wyswietlanych przez /usr/bin/time, rzeczywisty czas wykonywania programu jest oznaczony jako 'user', natomiast czas przypadajacy na jeden watek jako 'real'.
            Dzielac wartosc 'user' przez 'real' otrzymamy liczbe watkow wykorzystanych przez program.
*/