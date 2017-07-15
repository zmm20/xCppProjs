//#define MAIN
#ifdef MAIN

#include <iostream>
#include <bitset>
#include <vector>
//#include <stdexcept>
using namespace std;

void print()
{
    cout << "end" << endl;
}

template <typename T, typename... Types>
void print(const T& firstArg, const Types&... args)
{
    cout << firstArg << endl;
    
    print(args...);
}

template <typename T>
using MyVector = std::vector<T>;

template <typename T>
class MyClass
{
    //T::SubType* ptr; // SubType 是T 中的一个成员变量
    typename T::SubType* ptr; // 注意只有加上typename 才能说明SubType 是T 中的一个类型
};
class Q
{
public:
    // method 1:
    //typedef int SubType;

    // method 2:
    class SubType
    {
        int x;
    };
};

int main()
{
    cout << "test 1" << endl;
    {
        print(7.5, "hello", std::bitset<16>(377), 42);
    }
    cout << endl;

    cout << "test 2" << endl;
    {
        MyVector<int> vec{1, 2, 3, 4};
        for (const auto& item : vec)
        {
            cout << item << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "test 3" << endl;
    {
        MyClass<Q> a;
    }
    cout << endl;

    return EXIT_SUCCESS;
}

#endif