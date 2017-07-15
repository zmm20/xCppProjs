//#define MAIN
using namespace std;

#include <iostream>
#include <vector>
#include <functional>



#ifdef MAIN


void func(int x, int y)
{
    cout << "func: (x, y) = (" << x << ", " << y << ")" << endl;
}

class C {
public:
    void memfunc(int x, int y) const
    {
        cout << "c::func: (x, y) = (" << x << ", " << y << ")" << endl;
    }
};

int main()
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

    std::function<void(const C&, int, int)> mf;
    mf = &C::memfunc; // 不用管编译器警告
    try
    {
        mf(C(), 42, 77);
    }
    catch (const std::bad_function_call& e)
    {
        cout << e.what() << endl;
    }


    return 0;
}
#endif