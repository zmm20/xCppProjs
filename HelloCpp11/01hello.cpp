//#define MAIN
#ifdef MAIN

#include <iostream>
#include <cstdlib>
#include <memory>
#include <vector>
#include <string>
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

    return EXIT_SUCCESS;
}

#endif