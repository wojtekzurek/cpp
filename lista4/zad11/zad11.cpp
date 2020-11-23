#include <iostream>
#include <omp.h>


int main()
{

//#pragma omp critical
//#pragma omp master
//#pragma omp single
#pragma omp parallel
std::cout << "Witaj z wątku nr " << omp_get_thread_num()
            << " spośród " <<omp_get_num_threads() << "\n";

}

//pyt 1:
// - Po kazdym uruchomieniu programu, otrzymujemy takie same zdania, jednak sa one ulozone w innej kolejnosci
//   i moga byc pomieszane z innymi zdaniami. 
// - Komunikaty wchodza sobie w droge, poniewaz procesy wykonywane sa rownloegle, a wiec w tym samym czasie.
//   Wiele watkow probuje jednoczesnie pisac do tej samej zmiennej (std::cout) co powoduje pomieszanie danych.
//   Takie sytuacje nazywa sie race conditions.

//pyt 2:
// #pragma omp single powoduje wyswietlenie tylko "Witaj z watku nr 0 sposrod 1". Oznacza to ze program zostaje wykonany tylko
//                    przez jeden watek (niekoniecznie glowny) i wyswietlone zostaje tylko jedno zdanie. Zalety: w takim przypadku latwo zachowac kolejnosc
//                    wykonywanych polecen. Wady: wykonywanie polecenia przez jeden watek trwa dluzej niz wykonywanie go przez wszystkie watki. Nie moze byc zagniezdzone
//                    wwewnatrz konstrukcji wspoldzielenia pracy. Moze byc implementowana wolniej niz master, poniewaz jest bardziej skomplikowana i elastyczna.
//                    Zatem mozna powiedziec, ze dyrektywa single powoduje wyszczegolnienie bloku kodu, ktory bedzie przetwarzany tylko przez jeden watek, z bariera na koncu.
//
// #pragma omp master powoduje wyswietlenie takiego samego tekstu jak single. Dzialanie jest podobne do dyrektywy single, tylko kod jest przetwarzany przez watek glowny, bez bariery na koncu.
//                    (bariera - kazdy watek czeka, zanim wszystkie inne watki osiagna ten punkt. Konstrukcje wspoldzielace prace posiadaja ukryta synchronizacje barier na koncu.).
//                    Zalety: moze by zagniezdzona wewnatrz konstrukcji wspoldzielenia pracy. Nie wystepuje zadna niewidoczna bariera zwiazana z synchronizacja z innymi watkami.
//                    Wady: watek glowny wykonuje operacje zwiazane z oblsuga programu i niektore biblioteki chca, aby glowny watek wykonywał określone operacje. 
//                    Na przyklad biblioteka MPI, po zainicjowaniu z poziomem obslugi watkow rownym MPI_THREAD_FUNNELED, zezwala tylko glownym watkom na wykonywanie wywolan MPI.
//
//#pragma omp critical powoduje wyswietlenie takiego samego tekstu jak dwie powyzsze dyrektywy. Jest to dyrektywa, ktora identyfikuje sekcje kodu , ktora musi byc wykonywana
//                    JEDNOCZESNIE przez pojedynczy watek. Jest czesto uzywany do ochrony danych przed blednym stanem (hazard). Oznacza to, ze w przeciwienstwie do master i single
//                    ktore zostana wykonane tylko raz, critical moze zostac wykonana tyle razy, ile jest watkow. Zostala stworzona, zeby unknac race conditions. Sens jej uzycia
//                    mozna zobaczyc, gdy zmienna do redukcji jest tablica i chcemy zastapic klauzule redukcji (maja zastosowanie do zmiennych skalarnych).
//                    Zalety: unikanie race conditions, porzadkowanie wykonywanych rzeczy, serializacja fragmentow kodu. Wady: dyrektywa jest ogolna - moze dotyczyc dowolnego
//                    bloku kodu. Gdy watek wchodzi i wychodzi z sekcji krytycznej (critical section) powoduje znaczny narzut. Nienazwane sekcje krytyczne sa uwazane za jednakowe.