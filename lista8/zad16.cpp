//zad16.cpp created by Wojciech Zurek 17.01.2021

#include <iostream>
#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include <chrono>
#include <list>

class ZbiornikPaliwa
{
    unsigned int fuelCapacity;

public:
    ZbiornikPaliwa(unsigned int iloscDostepnegoPaliwa){
        fuelCapacity = iloscDostepnegoPaliwa;
    }

    unsigned int pobierz(unsigned int fuel){

        if(fuelCapacity - fuel >= 0){
            fuelCapacity = fuelCapacity - fuel;
            return fuel;
        }else
            return 0;
    }
};

class Silnik
{
    std::thread engine_thread;
    std::vector<std::shared_ptr<ZbiornikPaliwa>> ConnectedTanksList;
    unsigned int engine_interval;
    unsigned int fuel_consumption;
    std::mutex fuel_mutex;

public:
    Silnik(unsigned int interval, unsigned int fuel){
        
        engine_interval = interval;
        fuel_consumption = fuel;

        engine_thread = std::thread(&Silnik::work, this);
    }

    ~Silnik(){
        engine_thread.join();
    }

    void connect(ZbiornikPaliwa const &tank){
        ConnectedTanksList.push_back(std::make_shared<ZbiornikPaliwa>(tank));       
    }

private:
    void work(){

        std::unique_lock<std::mutex> lock1(fuel_mutex);
        while(!ConnectedTanksList.empty()){

            for(size_t i=0; i<ConnectedTanksList.size(); i++){
                unsigned int fuel = ConnectedTanksList[i]->pobierz(fuel_consumption);

                if(fuel == 0)
                    ConnectedTanksList.erase(ConnectedTanksList.begin() + i);       
            }
            lock1.unlock();

            std::this_thread::sleep_for(std::chrono::seconds(engine_interval));

            lock1.lock();    
        }
    }
};


int main(){

    Silnik engine1(2, 5);
    Silnik engine2(1, 1);
    Silnik engine3(3, 2);

    std::list<ZbiornikPaliwa> Tanks;
    for(int i=0; i<10; i++){
        Tanks.push_back(ZbiornikPaliwa(10));
    }

    for(auto &tank : Tanks){
        engine1.connect(tank);
        engine2.connect(tank);
        engine3.connect(tank);
    }

    return 0;
}