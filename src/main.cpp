#include <iostream>
#include <utility>
#include <vector>
#include <chrono>
#include "include/simulator_includes.h"

//#include <thread>

void DevWork();

void thread_test();

// test code here, main() measures run time
void DevWork()
{
    using namespace space;
    using namespace space::constants;



    list<sObject*> universe;

    universe.add(new sObject(sPoint(10, 10), 111, 10, "1010"));
    universe.add(new sObject(sPoint(40, 40), 444, 10, "4040"));
    universe.add(new sObject(sPoint(30, 30), 333, 10, "3030"));
    universe.add(new sObject(sPoint(20, 20), 222, 10, "2020"));

    space::sQuadtree quadtree(universe);

    std::cout << quadtree.GetRoot()->GetObject()->GetMass();
}


int main()
{
    // measure program execution time
    auto start = std::chrono::high_resolution_clock::now();

    DevWork();


    auto stop = std::chrono::high_resolution_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

    std::cout << std::endl << "Execution Time: " << ms.count() / 1e6 << " ms";
}

/*
// https://stackoverflow.com/questions/50136540/calling-a-function-every-1-second-precisely
void timer_start(void(&func)(), int interval) 
{
    std::thread([func, interval]() {
        bool keep_going = true;
        while (keep_going) {
            func();
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
            if (interval == 900) {
                keep_going = false;
            }
        }
     }).detach();
}



void thread_test() 
{



    int max = 0;
    int mam = 0;
    std::chrono::milliseconds interval(500);

    std::thread t1([&max, &interval]() {
        while (max < 10) {
            std::cout << max << " ---------\n";
            max++;
            std::this_thread::sleep_for(interval);
        }

    });


    std::thread t2([&mam, &interval]() {
        while (mam < 10) {
            std::cout << mam << " +++++++++++\n";
            mam++;
            std::this_thread::sleep_for(interval);
        }
    });

    t1.join();
    t2.join();



    // https://stackoverflow.com/questions/45442963/how-to-execute-a-while-loop-for-exactly-60-seconds-in-c
    // https://stackoverflow.com/questions/28768144/running-a-function-for-specified-duration-c-with-chrono

}


*/