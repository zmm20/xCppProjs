//#define MAIN
#ifdef MAIN

#include <test.h> // ���Լ�д��dll
#include <iostream>

using namespace std;
int main()
{
    int result = MyTest::add(1, 2);
    cout << "result = " << result << endl;

    MyTest::print("hello world");

    MyTest::MyClass obj("�й�");
    obj.print();
}

#endif