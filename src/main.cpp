#include <iostream>
#include <utility>
#include <vector>
#include <chrono>
#include "simulator_includes.h"
//#include <thread>

void DevWork();
void thread_test();
space::Object CreateObject(int x, int y, int mass, int velocity, std::string name);

// test code here, main() measures run time
void DevWork()
{
    //std::vector<space::Object> objects;
    //CreateObjects(objects);
    const double AU = 1.496e11;

    space::universe<space::Object> universe;


    universe.add(CreateObject(10, 10, 10, 10, "a"));
    universe.add(CreateObject(20, 20, 20, 10, "b"));
    universe.add(CreateObject(-30, 30, 30, 10, "c"));
    //universe.add(CreateObject(10, 10, 10, 10, "d"));
    //universe.add(CreateObject(10, 10, 10, 10, "e"));
    //universe.add(CreateObject(10, 10, 10, 10, "f"));

    space::QuadTree tree(universe);

    /*
    this->PrintChildren(this->root);
    this->PrintChildren(this->root->top_left);
    this->PrintChildren(this->root->top_left->top_right);
    this->PrintChildren(this->root->top_right);*/
    //tree.PrintChildren(tree.root);
    //tree.PrintChildren(tree.root->top_right);
    //tree.PrintChildren(tree.root->top_left->top_right);

}

// copy elision, copy constructor not ran, use optimization when compiling
space::Object CreateObject(int x, int y, int mass, int velocity, std::string name) {
    return space::Object(x, y, mass, velocity, std::move(name));
}
















int main() 
{
    // measure program execution time
    auto start = std::chrono::high_resolution_clock::now();



    DevWork();

    
    auto stop = std::chrono::high_resolution_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

    std::cout << std::endl << "Execution Time: " << ms.count() / 1e6 << " ms";
    //std::cin.get();
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