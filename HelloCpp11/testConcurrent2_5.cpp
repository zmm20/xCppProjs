// 数据竞争模拟
//#define MAIN
#ifdef MAIN

#include <iostream>
#include <string>
#include <thread>

using namespace std;

const size_t loopCount = 1'000'000;
long long g = 0;
void writeData()
{
    for (size_t i = 0; i < loopCount; ++i)
    {
        if (i % 2 == 0)
            g = 0;
        else
            g = -1;
    }
}

int main()
{
    try
    {
        cout << "system thread count: " << std::thread::hardware_concurrency() << endl;
        std::thread t1(writeData);
        //std::thread t2(readData);
        {// main thread: read
            int x = 0;
            for (size_t i = 0; i < loopCount; ++i)
            {
                const auto tmp = g;
                if (tmp == 0 || tmp == -1)
                {
                    continue;
                }
                else
                {
                    ++x;
                    cout << tmp << endl;
                }
            }
            cout << "occur rate: " << x * 1.0 / loopCount * 100 << "%" << endl;
        }
        

        t1.join();
        //t2.join();
    }
    catch (exception e)
    {
        cout << e.what() << endl;
    }

    return EXIT_SUCCESS;
}

#endif