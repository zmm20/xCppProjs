//#define MAIN
#ifdef MAIN

#include <iostream>
#include <memory>
#include <functional>
#include <future>
using namespace std;

void func(int x, int y)
{
    cout << "func..." << endl;
}
auto l = [](int x, int y) {
    cout << "lambda..." << endl;
};
class C {
public:
    void operator () (int x, int y) const
    {
        cout << "operator()..." << endl;
    }
    void memfunc(int x, int y) const
    {
        cout << "memfunc..." << endl;
    }

};

int main()
{
    cout << "test 1" << endl;
    {
        C c;
        std::shared_ptr<C> sp(new C);
        
        // bind() uses callable objects to bind arguments:
        std::bind(func, 77, 33)(); // calls: func(77,33)
        std::bind(l, 77, 33)(); // calls: l(77,33)
        std::bind(C(), 77, 33)(); // calls: C::operator()(77,33)
        std::bind(&C::memfunc, c, 77, 33)(); // calls: c.memfunc(77,33)
        std::bind(&C::memfunc, sp, 77, 33)(); // calls: sp->memfunc(77,33)
        
        // async() uses callable objects to start (background) tasks:
        std::async(func, 42, 77); // calls: func(42,77)
        std::async(l, 42, 77); // calls: l(42,77)
        std::async(c, 42, 77); // calls: c.operator()(42,77)
        std::async(&C::memfunc, &c, 42, 77); // calls: c.memfunc(42,77)
        std::async(&C::memfunc, sp, 42, 77); // calls: sp->memfunc(42,77)
    }
    cout << endl;
    return EXIT_SUCCESS;
}

#endif