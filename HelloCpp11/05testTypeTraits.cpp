//#define MAIN
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


// test 3
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
           可见, 函数的参数可以只用来区别重载, 而不使用
           这就能理解foo_impl 的第二个参数了: 
            std::is_pointer<T>() 也就是产生了false_type 或 true_type 类型的对象
        */        
        myfunc("zmm1", 1);
        myfunc("zmm2", 2);
    }
    cout << endl;
    
    cout << "test 3" << endl;
    {
        cout << "min(1.1, 2) is " << min_my(1.1, 2) << endl;
    }
    cout << endl;
    

    cout << "test 4" << endl;
    {
        is_const<int>::value; // false
        is_const<const volatile int>::value; // true
        is_const<int* const>::value; // true
        is_const<const int*>::value; // false
        is_const<const int&>::value; // false
        is_const<int[3]>::value; // false
        is_const<const int[3]>::value; // true
        is_const<int[]>::value;// false
        is_const<const int[]>::value; // true

        int i1 = 1;
        int i2 = 2;
        int* const p1 = &i1;
        //p1 = &i2; // error , p1 cannot be modified

        const int* p2 = &i1;
        p2 = &i2;
    }
    cout << endl;


    cout << "test 5" << endl;
    {
        // 数组的维度
        rank<int>::value; // 0
        rank<int[]>::value; // 1
        rank<int[5]>::value; // 1
        rank<int[][7]>::value; // 2
        rank<int[5][7]>::value; // 2

        // 维度的尺度(宽度), 第二模板参数表示第几维
        extent<int>::value; // 0
        extent<int[]>::value; // 0
        extent<int[5]>::value; // 5
        extent<int[][7]>::value; // 0
        extent<int[5][7]>::value; // 5
        extent<int[][7], 1>::value; // 7
        extent<int[5][7], 1>::value; // 7
        extent<int[5][7], 2>::value; // 0

        // 数组元素类型
        remove_extent<int>::type; // int
        remove_extent<int[]>::type; // int
        remove_extent<int[5]>::type; // int
        remove_extent<int[][7]>::type; // int[7]
        remove_extent<int[5][7]>::type; // int[7]

        // 多维数组元素类型
        remove_all_extents<int>::type; // int
        remove_all_extents<int[]>::type; // int
        remove_all_extents<int[5]>::type; // int
        remove_all_extents<int[][7]>::type; // int
        remove_all_extents<int[5][7]>::type; // int
    }
    cout << endl;


}
#endif