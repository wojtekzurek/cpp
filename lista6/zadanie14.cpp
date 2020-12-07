//Created by Wojciech Zurek 07.12.2020

#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <vector>

void cross(std::vector<double> const &a, std::vector<double> const &b, std::promise<double> prom){

    if(a.size() != b.size()){
        prom.set_exception(std::make_exception_ptr(
            std::invalid_argument("x")
        ));
    }else{
        double sum = 0;

        for(size_t i=0; i < a.size(); i++)
        sum += a[i] * b[i];

        prom.set_value(sum);
    }
}

int main(){

    std::vector<double> vectorA {1.0, 5.4, 7.3, 9.2, 3.8};
    std::vector<double> vectorB {5.3, 8.0, 3.2, 0.5, 6.6};
    std::vector<double> vectorC {4.9, 6.4, 3.3, 5.2};

    std::thread thread[10];
    std::promise<double> sum_promise[10];
    std::future<double> sum_future[10];

    for(int i=0; i < 10; i++){

        try{
            sum_future[i] = sum_promise[i].get_future();
            thread[i] = std::thread(cross, vectorA, vectorB, std::move(sum_promise[i]));
            std::cout << sum_future[i].get() << "\n";
            thread[i].join();
        }catch(...){
            std::cout << "\nwrong vectors size\n";
        }

    }

    return 0;
}