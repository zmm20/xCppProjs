//#define MAIN
#ifdef MAIN

#include <iostream>
#include <utility>
#include <tuple>
#include <string>
#include <functional>
#include <complex>
#include "myUtility.hpp"
//#include <algorithm>

using namespace std;

class Foo
{
public:
    Foo(tuple<int, float>) {
        cout << "Foo::Foo(tuple)" << endl;
    }
    template <typename... Args>
    Foo(Args... args) {
        cout << "Foo::Foo(args...)" << endl;
    }
};
int main()
{
    cout << "test 1" << endl;
    {
        // C++11提供一份tuple-like接口: 
        typedef std::pair<int, float> IntFloatPair;
        IntFloatPair p(42, 3.14);
        //std::get<0>(p); // yields p.first
        //std::get<1>(p); // yields p.second
        cout << "first: " << std::get<0>(p) << ", second: " << std::get<1>(p) << endl;
        cout << "pair's size: " << std::tuple_size<IntFloatPair>::value << endl; // yields 2
        std::tuple_element<0, IntFloatPair>::type; // yields int
    }
    cout << endl;

    cout << "test 2" << endl;
    {
        // create tuple t:
        tuple<int, float> t(1, 2.22);
        // pass the tuple as a whole to the constructor of Foo:
        pair<int, Foo> p1(42, t);
        // pass the elements of the tuple to the constructor of Foo:
        pair<int, Foo> p2(piecewise_construct, make_tuple(42), t);

        cout << "p2.first = " << p2.first << endl;
    }
    cout << endl;

    cout << "test 3" << endl;
    {
        auto p1 = make_pair(43, "empty");
        cout << "pair1 = " << p1 << endl;

        pair<int, const char*> p2{44, "hello"};
        cout << "pair2 = " << p2 << endl;

        int a = 45;
        string ss = "world";
        auto p3 = make_pair(move(a), move(ss));
        cout << "pair3 = " << p3 << endl;
    }
    cout << endl;

    cout << "test 4" << endl;
    {
        int i = 0; 
        // 传递引用
        auto p1 = make_pair(ref(i), ref(i));
        ++p1.first;
        ++p1.second;
        cout << "pair1 = " << p1 << endl;

        // 传递常引用
        auto p2 = make_pair(cref(i), cref(i));
        cout << "pair2 = " << p2 << endl;

        auto p3 = make_pair('x', 'y');
        char c;
        tie(std::ignore, c) = p3; // p 被传递给了一个tuple, 第二个参数是个引用
        cout << "c = " << c << endl;
    }
    cout << endl;

    cout << "test 5" << endl;
    {
        // create a four-element tuple
        // - elements are initialized with default value (0 for fundamental types)
        tuple<string, int, int, complex<double>> t;
        // create and initialize a tuple explicitly
        tuple<int, float, string> t1(41, 6.3, "nico");
        // ‘‘iterate’’ over elements:
        cout << get<0>(t1) << " ";
        cout << get<1>(t1) << " ";
        cout << get<2>(t1) << " ";
        cout << endl;
        // create tuple with make_tuple()
        // - auto declares t2 with type of right-hand side
        // - thus, type of t2 is tuple
        auto t2 = make_tuple(22, 44, "nico");
        cout << "tuple 2: " << t2 << endl;
        // assign second value in t2 to t1
        get<1>(t1) = get<1>(t2);

        // comparison and assignment
        // - including type conversion from tuple<int,int,const char*>
        // to tuple<int,float,string>
        if (t1 < t2) { // compares value for value
            t1 = t2; // OK, assigns value for value
        }
    }
    cout << endl;

    cout << "test 6" << endl;
    {
        int n;
        auto tt = tuple_cat(make_tuple(43, 7.7, "hello", tie(n)));
        n = 2;
        cout << "n = " << get<3>(tt) << endl;
    }
    cout << endl;

    return EXIT_SUCCESS;
}


#endif