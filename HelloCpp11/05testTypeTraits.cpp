//#define MAIN
#ifdef MAIN

#include <iostream>
using namespace std;


constexpr int func()
{
    return 5;
}

template <typename T>
void func(const T& val)
{
    if (std::is_pointer<T>::value) {
        std::cout << "foo() called for a pointer" << std::endl;
    }
    else {
        std::cout << "foo() called for a value" << std::endl;
    }
}

// compiler error
//template <typename T>
//void foo(const T& val)
//{
//    std::cout << (std::is_pointer<T>::value ? *val : val)
//        << std::endl;
//}

// foo() implementation for pointer types:
template <typename T>
void foo_impl(const T& val, std::true_type)
{
    std::cout << "foo() called for pointer to " << *val
        << std::endl;
}
// foo() implementation for non-pointer types:
template <typename T>
void foo_impl(const T& val, std::false_type)
{
    std::cout << "foo() called for value to " << val
        << std::endl;
}
template <typename T>
void foo(const T& val)
{
    foo_impl(val, std::is_pointer<T>());
}

template <typename T1, typename T2>
typename std::common_type<T1, T2>::type min_my(const T1& x, const T2& y)
{
    if (x > y)
        return y;
    else
        return x;
}

int main()
{
    // test
    int i = 5;
    func(i);
    func(&i);

    foo(i);
    foo(&i);

    cout << "min(1.1, 2) is " << min_my(1.1, 2) << endl;

    // Êý×éÎ¬Êý
    cout << "rank<int>::value = " << rank<int>::value << endl;
    cout << "rank<int[]>::value = " << rank<int[]>::value << endl;
    cout << "rank<int[5]>::value = " << rank<int[5]>::value << endl;
    cout << "rank<int[][7]>::value = " << rank<int[][7]>::value << endl;
    cout << "rank<int[5][7]>::value = " << rank<int[5][7]>::value << endl;
}
#endif