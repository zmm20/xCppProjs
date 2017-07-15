//#define MAIN
#ifdef MAIN

#include <iostream>
#include <string>
#include <atomic>
#include <thread>
#include <atomic> // for atomics
#include <future> // for async() and futures
#include <chrono> // for durations

using namespace std;

long d;
std::atomic<bool> readyFlag(false);

void provider()
{
    // after reading a character
    std::cout << "<return>" << std::endl;
    std::cin.get();
    // provide some data
    d = 42;
    // and signal readiness
    readyFlag.store(true);
}
void consumer()
{
    // wait for readiness and do something else
    while (!readyFlag.load()) {
        std::cout.put('.').flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    // and process provided data
    std::cout << "\nvalue : " << d << std::endl;
}

int main()
{
    cout << "test 1" << endl;
    {
        // start provider and consumer
        auto p = std::async(std::launch::async, provider);
        auto c = std::async(std::launch::async, consumer);
    }
    cout << endl;
    return EXIT_SUCCESS;
}
#endif