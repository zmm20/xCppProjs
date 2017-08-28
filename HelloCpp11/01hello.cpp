//#define MAIN
#ifdef MAIN

#include <iostream>
#include <cstdlib>
#include <memory>
#include <vector>
#include <string>
#include <cstdlib>
#include <locale>
#include <functional>
#include <cassert>
using namespace std;

class MyClass {
    friend ostream& operator << (ostream& os, const MyClass& m);
public:
    MyClass(const std::string& s) : m_ss(s) // explicit
    {

    }    
private:
    string m_ss;
};

ostream& operator << (ostream& os, const MyClass& m)
{
    os << m.m_ss;

    return os;
}

enum class Salutation : char
{
    mr, ms, co, none
};

// test 4
void hello(string name);


// test 5:
// 普通函数
int TestFunc(int a)
{
    return a;
}
// Lambda表达式
auto lambda = [](int a)->int { return a; };
// 仿函数(functor)
class Functor
{
public:
    int operator()(int a)
    {
        return a;
    }
};
// 1.类成员函数
// 2.类静态函数
class TestClass
{
public:
    int ClassMember(int a) { return a; }
    static int StaticMember(int a) { return a; }
};

// test 5, http://www.csdn.net/article/2015-12-03/2826381%EF%BC%9Freload=1
template<typename T, typename... Args>
struct has_member_foo
{
private:
    template<typename U> 
    static auto check(int) -> decltype(std::declval<U>().foo(std::declval<Args>()...), std::true_type());

    template<typename U> 
    static std::false_type check(...);
public:
    enum { value = std::is_same<decltype(check<T>(0)), std::true_type>::value };
};
struct MyStruct
{
    string foo() { return ""; }
    int foo(int i) { return i; }
};

int main()
{
    
    cout << "test 1: " << endl;
    {
        std::vector<std::string> vs{"aaa", "bbb", "ccc"};
        for (const MyClass& elem : vs)
        {
            cout << elem << endl;
        }
    }
    cout << endl;

    cout << "test 2" << endl;
    {
        // 测试枚举的底层类型
        std::underlying_type<Salutation>::type aa;
        //cout <<  << endl;
    }
    cout << endl;

    cout << "test 3" << endl;
    {
        vector<string> coll{"中国", "china", "hello", "你好", "满满"};
        string ss;
        std::locale loc;
        for (const auto& e : coll)
        {
            if (std::isalpha(e[0], loc))
                ss += e + " ";
            else
                ss += e;
        }
        cout << ss << endl;
    }
    cout << endl;

    cout << "test 4" << endl;
    {
        // 函数类型声明 method 1
        typedef void FNC_hello1(string);
        FNC_hello1* f1 = hello;
        f1("method 1");

        // 函数类型声明 method 2
        typedef void (FNC_hello2)(string);
        FNC_hello2& f2 = hello;
        f2("method 2");

        // 函数指针类型声明
        typedef void(*FNC_hello_ptr)(string);
        FNC_hello_ptr f3 = hello;
        f3("method 3");

        // stl 函数包装对象
        std::function<void(string)> f4 = hello;
        f4("method 4");

    }
    cout << endl;


    cout << "test 5" << endl;
    {
        std::function< int(int)> Functional;
        // 普通函数
        Functional = TestFunc;
        int result = Functional(10);
        cout << "普通函数：" << result << endl;

        // Lambda表达式
        Functional = lambda;
        result = Functional(20);
        cout << "Lambda表达式：" << result << endl;

        // 仿函数
        Functor testFunctor;
        Functional = testFunctor;
        result = Functional(30);
        cout << "仿函数：" << result << endl;

        // 类成员函数
        TestClass testObj;
        Functional = std::bind(&TestClass::ClassMember, testObj, std::placeholders::_1);
        result = Functional(40);
        cout << "类成员函数：" << result << endl;

        // 类静态函数
        Functional = TestClass::StaticMember;
        result = Functional(50);
        cout << "类静态函数：" << result << endl;
    }
    cout << endl;


    cout << "test 5" << endl;
    {
        static_assert(has_member_foo<MyStruct>::value, "true");
        static_assert(has_member_foo<MyStruct, int>::value, "true");
    }
    cout << endl;

    cout << "test 6" << endl;
    {
        auto bodyStream = response.body();
        streams::stringstreambuf sbuffer;
        auto& target = sbuffer.collection();

    }
    cout << endl;

    return EXIT_SUCCESS;
}

void hello(string name)
{
    cout << "hello " << name << endl;
}

#endif