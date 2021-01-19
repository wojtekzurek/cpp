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
    std::mutex tank_mutex;

public:
    ZbiornikPaliwa(unsigned int iloscDostepnegoPaliwa){
        fuelCapacity = iloscDostepnegoPaliwa;
    }

    unsigned int pobierz(unsigned int fuel){

        std::unique_lock<std::mutex> lock2(tank_mutex);

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
    std::list<std::shared_ptr<ZbiornikPaliwa>> ConnectedTanksList;
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

    void connect(std::shared_ptr<ZbiornikPaliwa> &tank){
        std::unique_lock<std::mutex> lock1(fuel_mutex);
        ConnectedTanksList.push_back(tank);       
    }

private:
    void work(){

        std::unique_lock<std::mutex> lock1(fuel_mutex);
        while(!ConnectedTanksList.empty()){

            unsigned int fuel = ConnectedTanksList.front()->pobierz(fuel_consumption);

            if(fuel == 0)
                ConnectedTanksList.pop_front();      
            
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

    std::list<std::shared_ptr<ZbiornikPaliwa>> Tanks;
    for(int i=0; i<10; i++){
        Tanks.push_back(std::make_shared<ZbiornikPaliwa>(10));
    }

    for(auto &ptr : Tanks){
        engine1.connect(ptr);
        engine2.connect(ptr);
        engine3.connect(ptr);
    }

    return 0;
}