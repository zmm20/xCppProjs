//#define MAIN
#ifdef MAIN

#include <future>
#include <thread>
#include <chrono>
#include <random>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <ctime>
#include <vector>
#include <list>

using namespace std;

int doSomething(char c);
int func1();
int func2();
void task1();

struct Test5 {
    void doSomething(char c, shared_future<int> f);
    int queryNumber();
};
int main()
{
    cout << "18.2 the high-level interface: async() and futures" << endl;
    cout << "test 1: " << endl;
    {
        std::default_random_engine random(time(NULL));
        std::uniform_int_distribution<int> dis1(0, 100);
        std::uniform_real_distribution<double> dis2(0.0, 1.0);

        for (int i = 0; i < 10; ++i)
            cout << dis1(random) << ' ';
        cout << endl;

        for (int i = 0; i < 10; ++i)
            cout << dis2(random) << ' ';
        cout << endl;
    }
    cout << endl;
    
    cout << "test 2: " << endl;
    {
        //std::cout << "starting func1() in background and func2() in foreground:" << std::endl;

        //// start func1() asynchronously (now or later or never):
        //std::future<int> result1(std::async(func1));

        //// call func2() synchronously (here and now)
        //// print result (wait for func1() to finish and add its result to result2
        //int result2 = func2();
        //int result = result1.get() + result2; // 注意, 不要写成: result1.get() + func2()
        //std::cout << "\nresult of func1()+func2(): " << result
        //    << std::endl;
    }
    cout << endl;

    cout << "test 3: " << endl;
    {
        //cout << "starting 2 tasks" << endl;
        //cout << "- task1: process endless loop of memory consumption" << endl;
        //cout << "- task2: wait for <return> and then for task1" << endl;
        //auto f1 = async(task1); // start task1() asynchronously (now or later or never)
        //cin.get(); // read a character (like getchar())
        //cout << "\nwait for the end of task1: " << endl;
        //try {
        //    f1.get(); // wait for task1() to finish (raises exception if any)
        //}
        //catch (const exception& e) {
        //    cerr << "EXCEPTION: " << e.what() << endl;
        //}
    }
    cout << endl;

    cout << "test 4: " << endl;
    {
        //cout << "starting 2 operations asynchronously" << endl;
        //// start two loops in the background printing characters . or +
        //auto f1 = async([] { doSomething('.'); });
        //auto f2 = async([] { doSomething('+'); });
        //// if at least one of the background tasks is running
        //if (f1.wait_for(chrono::seconds(0)) != future_status::deferred ||
        //    f2.wait_for(chrono::seconds(0)) != future_status::deferred) 
        //{
        //    int count = 0;
        //    // poll until at least one of the loops finished
        //    while (f1.wait_for(chrono::seconds(0)) != future_status::ready &&
        //        f2.wait_for(chrono::seconds(0)) != future_status::ready) 
        //    {                
        //        //Another reason for an endless loop here might be that the thread executing the loop has the processor
        //        //and the other threads are not getting any time to make the future ready. This can reduce the speed of
        //        //programs dramatically. The quickest fix is to call yield() (see Section 18.3.7, page 981) inside the
        //        //loop:
        //        this_thread::yield(); // hint to reschedule to the next thread

        //        ++count;
        //    }
        //    cout << "wait count = " << count;
        //}
        //cout.put('\n').flush();
        //try 
        //{// wait for all loops to be finished and process any exception
        //    f1.get();
        //    f2.get();
        //}
        //catch (const exception& e) 
        //{
        //    cout << "\nEXCEPTION: " << e.what() << endl;
        //}
        //cout << "\ndone" << endl;
    }
    cout << endl;

    cout << "test 5: " << endl;
    {
        Test5 t;
        try {
            // start one thread to query a number
            // To be able to use auto for this declaration, you can, alternatively, use the share() member function :
            // auto f = async(queryNumber).share();
            shared_future<int> f = async(&Test5::queryNumber, &t); // 第二个参数可以是 引用 或 指针
            // start three threads each processing this number in a loop
            auto f1 = async(launch::async, &Test5::doSomething, t, '.', f);
            auto f2 = async(launch::async, &Test5::doSomething, t, '+', f);
            auto f3 = async(launch::async, &Test5::doSomething, t, '*', f);
            // wait for all loops to be finished
            f1.get();
            f2.get();
            f3.get();
        }
        catch (const exception& e) {
            cout << "\nEXCEPTION: " << e.what() << endl;
        }
        cout << "\ndone" << endl;
    }
    cout << endl;
    
    return EXIT_SUCCESS;
}

int doSomething(char c)
{
    // random-number generator (use c as seed to get different sequences)
    std::default_random_engine dre(c);
    std::uniform_int_distribution<int> id(10, 1000);
    // loop to print character after a random period of time
    for (int i = 0; i<10; ++i) {
        this_thread::sleep_for(chrono::milliseconds(id(dre)));
        cout.put(c).flush();
    }
    return c;
}
int func1()
{
    return doSomething('.');
}
int func2()
{
    return doSomething('+');
}
void task1()
{
    // endless insertion and memory allocation
    // - will sooner or later raise an exception
    // - BEWARE: this is bad practice
    list<int> v;
    while (true) {
        for (int i = 0; i<1000000; ++i) {
            v.push_back(i);
        }
        cout.put('.').flush();
    }
}

int Test5::queryNumber()
{
    // read number
    cout << "read number: ";
    int num;
    cin >> num;
    // throw exception if none
    if (!cin) {
        throw runtime_error("no number read");
    }
    return num;
}
void Test5::doSomething(char c, shared_future<int> f)
{
    try {
        // wait for number of characters to print
        int num = f.get(); // get result of queryNumber()
        for (int i = 0; i<num; ++i) {
            this_thread::sleep_for(chrono::milliseconds(100));
            cout.put(c).flush();
        }
    }
    catch (const exception& e) {
        cerr << "EXCEPTION in thread " << this_thread::get_id()
            << ": " << e.what() << endl;
    }
}
#endif