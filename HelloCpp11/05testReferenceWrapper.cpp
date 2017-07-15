//#define MAIN
#ifdef MAIN

#include <iostream>

using namespace std;




template <typename T>
void foo(T val)
{        
    val += 1;
    cout << "foo"<< endl;
}

int main() 
{
    int x = 0;
    foo(std::ref(x)); // T becomes int&, whereas by calling
    cout << "x = " << x << endl;

    // ͬ��
    foo<std::reference_wrapper<int>>(x);
    cout << "x = " << x << endl;

    // ͬ��
    foo<int&>(x);
    cout << "x = " << x << endl;

    //foo(std::cref(x));//T becomes const int&.
}
#endif