//#define MAIN
#ifdef MAIN

using namespace std;

#include <iostream>
#include <vector>
#include <functional>


// test 1
void func(int x, int y)
{
    cout << "func: (x, y) = (" << x << ", " << y << ")" << endl;
}

// test 2
class C {
public:
    void memfunc(int x, int y) const
    {
        cout << "c::func: (x, y) = (" << x << ", " << y << ")" << endl;
    }
};

int main()
{
    cout << "-------05testFunctionTypeWrapper.cpp-------------" << endl;

    cout << "test 1" << endl;
    {
        // initialize collections of tasks:
        std::vector<std::function<void(int, int)>> tasks;
        tasks.push_back(func);
        tasks.push_back([](int x, int y) {
            cout << "lambdas: (x, y) = (" << x << ", " << y << ")" << endl;
        });

        // call each task:
        for (std::function<void(int, int)> f : tasks)
        {
            f(33, 66);
        }
    }
    cout << endl;
    

    cout << "test 1" << endl;
    {
        std::function<void(const C&, int, int)> mf;
        try
        {
            // mf 只是一个容器, 如果不赋值而直接调用, 则会发生 bad_function_call 异常
            mf = &C::memfunc;
            mf(C(), 42, 77);
        }
        catch (const std::bad_function_call& e)
        {
            cout << e.what() << endl;
        }
    }
    cout << endl;


    return 0;
}
#endif