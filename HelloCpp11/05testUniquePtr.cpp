//#define MAIN
#ifdef MAIN

#include <iostream>
#include <memory>
#include <functional>
#include <string>

using namespace std;

class ClassADeleter
{
public:
    void operator () (int* p) {
        std::cout << "call delete for int object" << std::endl;
        delete[] p;
    }
};


template <typename T>
using uniquePtr = std::unique_ptr<T, void(*)(T*)>; // alias template

int main()
{
    cout << "---------------05testUniquePtr.cpp-------------------" << endl;

    cout << "test 1" << endl;
    {
        std::unique_ptr<std::string> up(new std::string("nico"));
        (*up)[0] = 'N'; // replace first character
        up->append("lai"); // append some characters
        std::cout << *up << std::endl; // print whole string
    }
    cout << endl;


    cout << "test 2" << endl;
    {
        // test 1
        std::string* sp = new std::string("hello");
        std::unique_ptr<std::string> up1(sp);
        //    std::unique_ptr<std::string> up2(sp); // ERROR: up1 and up2 own same data

        // test 2
        // copy the unique_ptr
        //std::unique_ptr<std::string> up2(up1); // ERROR: not possible
        // transfer ownership of the unique_ptr
        std::unique_ptr<std::string> up3(std::move(up1)); // OK
    }
    cout << endl;

    cout << "test 3" << endl;
    {
        //string* pstr = new string[10];
        //delete pstr;

        //int* pInt = new int[10];
        //delete pInt;

        // 可见, 删除基本类型数组, delete虽然没有运行时错误, 而非基本类型会发生错误
        // 而就算不报错, 也会存在资源泄漏. 同理下面一句也报错
        //std::unique_ptr<std::string> up(new std::string[10]); // runtime ERROR

        std::unique_ptr<std::string[]> up4(new std::string[10]); // OK

        //std::cout << *up << std::endl; // ERROR: * not defined for arrays
        up4[0] = "hello world";
        std::cout << up4[0] << std::endl; // OK
        /*
            Note also that this class does not allow getting initialized by an array of a derived type.
            This reflects that fact that polymorphism does not work for plain arrays.
        */

    }
    cout << endl;
    

    cout << "test 4" << endl;
    {// 自定义删除deleter 用法
        // test4
        std::unique_ptr<int, ClassADeleter> a(new int(5));
        std::unique_ptr<int, void(*)(int*)> b(new int[10],
            [](int* p) {
            cout << "delete for b" << endl;
            delete[] p;
        });
        std::unique_ptr<int, std::function<void(int*)>> c(new int[10],
            [](int* p) {
            cout << "delete for c" << endl;
            delete[] p;
        });

        auto l = [](int* p) {
            cout << "delete for d" << endl;
            delete[] p;
        };
        std::unique_ptr<int, decltype(l)> d(new int[10], l);

      
        // 匿名模板
        uniquePtr<int> e(new int[10], [](int* p) { // used here
            cout << "delete for e" << endl;
            delete[] p;
        });
    }
    cout << endl;
   
}
#endif