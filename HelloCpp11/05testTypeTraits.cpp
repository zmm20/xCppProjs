#define MAIN
#ifdef MAIN

#include <iostream>
#include <string>
using namespace std;


// test 1:
template <typename T>
void func(const T& val)
{
    if (std::is_pointer<T>::value) {
        std::cout << "foo() called for a pointer" << std::endl;
    }
    else {
        std::cout << "foo() called for a value"  << std::endl;
    }
}
// compiler error
//template <typename T>
//void foo(const T& val)
//{
//    if (is_pointer<T>::value)
//        cout << *val << endl;
//    else
//        cout << val << endl;
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

// test 2
void myfunc(std::string ss, int)
{
    cout << "hello : " << ss << endl;
}
void myfunc(std::string ss, float)
{
    cout << "hello : " << ss << endl;
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
    cout << "-----------------05testTypeTraits.cpp--------------" << endl;
    // test
    cout << "test 1" <<  endl;
    {
        int i = 5;
        func(i);
        func(&i);

        foo(i);
        foo(&i);
    }
    cout << endl;

    cout << "test 2" << endl;
    {
        /*
           �ɼ�, �����Ĳ�������ֻ������������, ����ʹ��
           ��������foo_impl �ĵڶ���������: 
            std::is_pointer<T>() Ҳ���ǲ�����false_type �� true_type ���͵Ķ���
        */        
        myfunc("zmm1", 1);
        myfunc("zmm2", 2);
    }
    cout << endl;
    

    cout << "min(1.1, 2) is " << min_my(1.1, 2) << endl;

    // ����ά��
    cout << "rank<int>::value = " << rank<int>::value << endl;
    cout << "rank<int[]>::value = " << rank<int[]>::value << endl;
    cout << "rank<int[5]>::value = " << rank<int[5]>::value << endl;
    cout << "rank<int[][7]>::value = " << rank<int[][7]>::value << endl;
    cout << "rank<int[5][7]>::value = " << rank<int[5][7]>::value << endl;
}
#endif