//Created by Wojciech Zurek 30.11.2020

#include <iostream>
#include <thread>
#include <future>
#include <string>
#include <mutex>


std::mutex j_mutex;     //protects

size_t ThreadID() {

    thread_local size_t i = std::hash<std::thread::id>{}(std::this_thread::get_id());
    return i;
}

template <typename T>
void PrintText(T const &text){

    std::lock_guard<std::mutex> lock(j_mutex);
    std::cout << ThreadID() << ": " << text << "\n";
//  it is auto unlock

}

void AsyncFun(std::launch const &method){

    std::future<void> first = std::async(method, PrintText<std::string>, "first");   
    std::future<void> second = std::async(method, PrintText<std::string>, "second");   
    std::future<void> third = std::async(method, PrintText<std::string>, "third");   
    std::future<void> fourth = std::async(method, PrintText<std::string>, "fourth");

    first.get();
    second.get();
    third.get();
    fourth.get();   
}


int main(){

/*
    std::thread t1(argument);
    t1.join();
*/

    std::cout << "ASYNC\n";
    AsyncFun(std::launch::async);

    std::cout << "\nDEFERRED\n";
    AsyncFun(std::launch::deferred);

    return 0;
}