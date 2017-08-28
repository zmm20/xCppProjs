//#define MAIN
#ifdef MAIN


// basic-http-client.cpp
//#include <cpprest/http_client.h>
#include <cpprest/pplx/pplxtasks.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <array>
//#include <iterator>
using namespace pplx;
using namespace std;

int main()
{
    // http://www.jianshu.com/p/171b8c92bd4e
    cout << "test 1, task 构造" << endl;
    {
        auto tk1 = pplx::task<int>([]() {
            cout << "task construct1 ..." << endl;
            return 10;
        });

        auto tk2 = []()->task<int> {
            cout << "task 2..." << endl;
            return pplx::task_from_result(10); // 从结果直接构造task，用来不再继续执行，返回task<TResult>结果
        };

        auto tk3 = pplx::create_task([]() {
            cout << "task 3..." << endl;
            return 10;
        });

        pplx::task_completion_event<int> tce;
        auto tk4 = pplx::create_task(tce);

        pplx::wait(500);
    }
    cout << endl;

    cout << "test 2, then" << endl;
    {
        auto s = std::make_shared<std::string>("Value 1");

        pplx::create_task([s] {// 异步任务1
            std::cout << "Current Valus:" << *s << std::endl;
            *s = "Value 2";
        }).then([s] {// 异步任务2
            // 在进入then时候, 之前的有所任务已经执行完, 同时lambda 函数的参数为上一个任务的结果
            std::cout << "Current Valus:" << *s << std::endl;
            *s = "Value 3";
            return *s;
        }).then([](string ss){// 异步任务3
            cout << "Current value: " << ss << endl;
            return "";
        });
        pplx::wait(500);

    }
    cout << endl;


    cout << "test 3" << endl;
    {
        std::array<pplx::task<void>, 3> tks = {
            pplx::create_task([] { std::cout << "Hello from taskA." << std::endl; }),
            pplx::create_task([] { std::cout << "Hello from taskB." << std::endl; }),
            pplx::create_task([] { std::cout << "Hello from taskC." << std::endl; })
        };

        auto joinTask = pplx::when_all(std::begin(tks), std::end(tks));

        std::cout << "Hello from the joining thread." << std::endl;
        joinTask.wait();//等待任务完成
    }
    cout << endl;

    cout << "test 4" << endl;
    {
        pplx::cancellation_token_source cts;
        std::cout << "Creating task..." << std::endl;

        auto task = pplx::create_task([cts] {
            bool moreToDo = true;
            while (moreToDo)
            {
                if (cts.get_token().is_canceled())//判定是否被取消了
                {
                    return;
                }
                else
                {
                    moreToDo = []()->bool {
                        std::cout << "Performing work..." << std::endl;
                        pplx::wait(250);
                        return true;
                    }();
                }
            }
        });


        pplx::wait(1000);

        std::cout << "Canceling task..." << std::endl;
        cts.cancel();
        std::cout << "Waiting for task to complete..." << std::endl;
        task.wait();
        std::cout << "Done." << std::endl;
    }
    cout << endl;

    cout << "test 5" << endl;
    {
        pplx::cancellation_token_source cts;
        auto task = pplx::task<void>([cts]() {

            std::cout << "Cancel continue_task" << std::endl;
            cts.cancel();
        }).then([]() {
            std::cout << "this will not run" << std::endl;
        }, cts.get_token());

        try
        {
            if (task.wait() == pplx::task_status::canceled)
            {
                std::cout << "taks has been canceled" << std::endl;
            }
            else
            {
                task.get();
            }
        }
        catch (const std::exception& e)
        {
            std::cout << "exception: " << e.what() << std::endl;
        }
    }
    cout << endl;


    cout << "please enter any character to quit! " << endl;
    getchar();
}


#endif