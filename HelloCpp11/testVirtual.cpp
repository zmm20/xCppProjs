//#define MAIN
#ifdef MAIN

#include <iostream>
#include <tuple>
#include <string>
#include "printTuple.hpp"

using namespace std;

class A
{
public:
    A() {};
    virtual ~A() // = 0 不能声明为纯虚
    {
        cout << "~A" << endl;
    };
};

class B : public A
{
public:
    B() : A(){};
    ~B() override
    {
        cout << "~B" << endl;
    }
};

class C : public B
{
public:
    C() : B(){}
    ~C() override
    {
        cout << "~C" << endl;
    }
};

int main()
{
	/*tuple<int, float, string> t(77, 1.1, "more light");
	cout << "io: " << t << endl;*/

    A* base = new C();
    delete base;

	return 0;
}
#endif