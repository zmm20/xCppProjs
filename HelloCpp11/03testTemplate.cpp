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
    //T::SubType* ptr; // SubType ��T �е�һ����Ա����
    typename T::SubType* ptr; // ע��ֻ�м���typename ����˵��SubType ��T �е�һ������
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