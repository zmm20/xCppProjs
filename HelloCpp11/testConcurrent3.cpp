//#define MAIN
#ifdef MAIN

#include <iostream>
#include <string>
#include <regex>
#include <objbase.h>
#include <fstream>
#include <mutex>
//#include <thread>
#include <future>
#include <chrono>
#include "Base64.h"
#include <condition_variable>
#include <queue>

using namespace std;

std::mutex printMutex; // enable synchronized output with print()
void print(const std::string& s)
{
    // method 1:
    // 注意: 这种方法如果在发生异常, 则mutex 无法被解锁, 所以使用method 2 比较好
    //printMutex.lock();

    // method 2:
    std::lock_guard<std::mutex> l(printMutex);
    for (char c : s) {
        std::cout.put(c);
    }
    std::cout << std::endl;

    // method 1:
    //printMutex.unlock();
}


bool readyFlag;
std::mutex readyMutex;
std::condition_variable readyCondVar;
void thread1()
{
    // do something thread2 needs as preparation
    std::cout << "<return>" << std::endl;
    std::cin.get();
    // signal that thread1 has prepared a condition
    {
        std::lock_guard<std::mutex> lg(readyMutex);
        readyFlag = true;
    } // release lock
    readyCondVar.notify_one();
}
void thread2()
{
    // wait until thread1 is ready (readyFlag is true)
    {
        std::unique_lock<std::mutex> ul(readyMutex);
        readyCondVar.wait(ul, [] { return readyFlag; });
        /*
        //  上一句等效下面
            while (!readyFlag) {
                readyCondVar.wait(ul);
            } 
        */
    } // release lock
    // do whatever shall happen after thread1 has prepared things
    std::cout << "done" << std::endl;
}


std::queue<int> q;
std::mutex queueMutex;
std::condition_variable queueCondVar;
void provider(int val)
{
    // push different values (val til val+5 with timeouts of val milliseconds into the queue
    for (int i = 0; i<6; ++i) {
        {
            std::lock_guard<std::mutex> lg(queueMutex);
            q.push(val + i);
        } // release lock
        queueCondVar.notify_one();
        std::this_thread::sleep_for(std::chrono::milliseconds(val));
    }
}
void consumer(int num)
{
    // pop values if available (num identifies the consumer)
    while (true) {
        int val;
        {
            std::unique_lock<std::mutex> ul(queueMutex);
            queueCondVar.wait(ul, [] { return !q.empty(); });
            val = q.front();
            q.pop();
        } // release lock
        std::cout << "consumer " << num << ": " << val << std::endl;
    }
}
int main()
{
    cout << "theads cout: " << std::thread::hardware_concurrency() << endl;
    cout << "test 1: " << endl;
    {
        auto f1 = std::async(std::launch::async, print, "Hello from a first thread");
        auto f2 = std::async(std::launch::async, print, "Hello from a second thread");
        print("Hello from the main thread");

        this_thread::sleep_for(chrono::seconds(1));
    }
    cout << endl;

    cout << "test 2: " << endl;
    {
        auto f1 = std::async(std::launch::async, thread1);
        auto f2 = std::async(std::launch::async, thread2);

        this_thread::sleep_for(chrono::seconds(2));
    }
    cout << endl;

    cout << "test 3: " << endl;
    {
        // start three providers for values 100+, 300+, and 500+
        auto p1 = std::async(std::launch::async, provider, 100);
        auto p2 = std::async(std::launch::async, provider, 300);
        auto p3 = std::async(std::launch::async, provider, 500);

        // start two consumers printing the values
        auto c1 = std::async(std::launch::async, consumer, 1);
        auto c2 = std::async(std::launch::async, consumer, 2);

        this_thread::sleep_for(chrono::seconds(2));
    }
    cout << endl;

    return EXIT_SUCCESS;
}

#endif