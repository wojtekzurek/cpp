//Created by Wojciech Zurek 12.12.2020 100%

#include <iostream>
#include <list>
#include <functional>
#include <thread>
#include <mutex>
#include <future>


class TaskList{

    std::list< std::function<double()> > Tasks;
    std::list< std::thread > Threads;
    std::list<double> Results;
    std::mutex task_mutex;
    std::mutex average_mutex;
    bool bStop = false;

    std::condition_variable th_stat;
    std::condition_variable th_wait_for_all;
    int WorkingThreadCount = 0;

public:
    TaskList(int a){
        for(int i=0; i<a; i++){
            Threads.push_back(std::thread(&TaskList::doTask, this)); 
            WorkingThreadCount++;
        }
    }

    ~TaskList(){
//        stop();
    }

    void add_task(std::function<double()> task){
        std::unique_lock<std::mutex> lock1(task_mutex);

        Tasks.push_back(task);
        th_stat.notify_one();

    }

    double average(){

        std::unique_lock<std::mutex> lock2(average_mutex);
  
        double result = 0.0;

        for(auto& rs : Results){
            result += rs;
            std::cout << result << "\n";
        }

        if(!Results.empty())
            result = result / Results.size();
        else
            result = 0.0;        


        return result;
    }

    void stop(){
        std::unique_lock<std::mutex> lock1(task_mutex);
        bStop = true;
        th_stat.notify_all();
        lock1.unlock();

        for(auto &thread : Threads)
            thread.join();

    }

private:
    void doTask(){
        std::unique_lock<std::mutex> lock1(task_mutex);
        while(!bStop){
             
            while(Tasks.empty() && !bStop)
                th_stat.wait(lock1);

            std::function<double()> task;
            while(!Tasks.empty()){
                task = Tasks.front();
                Tasks.pop_front();
                lock1.unlock();
                double r = task();
                std::unique_lock<std::mutex> lock2(average_mutex);

                Results.push_back(r); 
                lock1.lock();
            }   

        }
        th_wait_for_all.notify_one();
        WorkingThreadCount--;
    }

};

double ExFun1(){
    return 2.5;
}

double ExFun2(){
    return 9.1;
}


int main(){

    TaskList list1 = {5};

    list1.add_task(ExFun1);
    list1.add_task(ExFun2);
    list1.add_task(ExFun1);
    list1.add_task(ExFun1);
    list1.add_task(ExFun1);
    list1.add_task(ExFun1);
    list1.add_task(ExFun1);
    list1.add_task(ExFun1);
    list1.stop();

    double x = list1.average();
    std::cout << x;

    return 0;
}