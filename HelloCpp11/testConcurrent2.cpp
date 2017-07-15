//#define MAIN
#ifdef MAIN

#include <future>
#include <string>
#include <thread>
#include <chrono>
#include <random>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <ctime>
#include <vector>
#include <list>
#include <queue>

using namespace std;

void doSomething(int num, char c);
void doSomething2(std::promise<std::string>& p);
int main()
{
    cout << "test 1:" << endl;
    {
        //std::cout << "ID of \"no thread\": " << std::thread::id() << std::endl;

        //try 
        //{
        //    // 线程对象必须要声明是否"想要等待线程结束", 要么调用join(), 要么调用detach().
        //    thread t1(doSomething, 5, '.'); // print five dots in separate thread
        //    cout << "- started fg thread " << t1.get_id() << endl;
        //    // print other characters in other background threads
        //    for (int i = 0; i<5; ++i) {
        //        thread t(doSomething, 10, 'a' + i); // print 10 chars in separate thread
        //        cout << "- detach started bg thread " << t.get_id() << endl;
        //        t.detach(); // detach thread into the background
        //    }
        //    cin.get(); // wait for any input (return)
        //    cout << "- join fg thread " << t1.get_id() << endl;
        //    t1.join(); // wait for t1 to finish
        //}
        //catch (const exception& e) {
        //    cerr << "EXCEPTION: " << e.what() << endl;
        //}

        //std::cout << "ID of \"no thread\": " << std::thread::id() << std::endl;
    }
    cout << endl;

    cout << "test 2" << endl;
    {
        try 
        {
            // start thread using a promise to store the outcome
            std::promise<std::string> p;
            std::thread t(doSomething2, std::ref(p));//
            t.detach();
            // create a future to process the outcome
            std::future<std::string> f(p.get_future());
            // process the outcome
            std::cout << "result: " << f.get() << std::endl;
        }
        catch (const std::exception& e) 
        {
            std::cerr << "EXCEPTION: " << e.what() << std::endl;
        }
        catch (...)
        {
            std::cerr << "EXCEPTION " << std::endl;
        }
    }
    cout << endl;
}

void doSomething(int num, char c)
{// 线程任务中, 任何异常若未被捕捉都会造成程序终止
    //static int i = 0;
    //++i;
    //if (i == 4)
    //    throw "test ";

    try {
        // random-number generator (use c as seed to get different sequences)
        default_random_engine dre(42 * c);
        uniform_int_distribution<int> id(10, 1000);
        for (int i = 0; i<num; ++i) {
            this_thread::sleep_for(chrono::milliseconds(id(dre)));
            cout.put(c).flush();
        }
    }
    // make sure no exception leaves the thread and terminates the program
    catch (const exception& e) {
        cerr << "THREAD-EXCEPTION (thread "
            << this_thread::get_id() << "): " << e.what() << endl;
    }
    catch (...) {
        cerr << "THREAD-EXCEPTION (thread "
            << this_thread::get_id() << ")" << endl;
    }
}

void doSomething2(std::promise<std::string>& p)
{
    try 
    {
        // read character and throw exceptiopn if ’x’
        std::cout << "read char (’x’ for exception): ";
        char c = std::cin.get();
        if (c == 'x') 
        {
            throw std::runtime_error(std::string("char ") + c + " read");
        }
        
        std::string s = std::string("char ") + c + " processed";
        p.set_value(std::move(s)); // store result
    }
    catch (...) 
    {
        // current_exception()  将当前异常以类型 std::exception_ptr 生成出来
        p.set_exception(std::current_exception()); // store exception
        // p.set_exception_at_thread_exit(std::current_exception());
    }
}
#endif