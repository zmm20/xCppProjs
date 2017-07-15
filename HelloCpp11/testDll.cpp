//#define MAIN
#ifdef MAIN

#include <test.h> // 我自己写的dll
#include <iostream>

using namespace std;
int main()
{
    int result = MyTest::add(1, 2);
    cout << "result = " << result << endl;

    MyTest::print("hello world");

    MyTest::MyClass obj("中国");
    obj.print();
}

#endif