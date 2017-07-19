//#define MAIN
#ifdef MAIN

#include <iostream>

using namespace std;



// test 1
template <typename T>
void foo(T val)
{        
    val += 1;
    cout << "foo"<< endl;
}

int main() 
{
    cout << "-----------05testReferenceWrapper.cpp----------------" << endl;

    cout << "test 1" << endl;
    {
        int x = 0;
        foo(std::ref(x)); // T becomes int&, whereas by calling
        cout << "x = " << x << endl;
        //foo(std::cref(x));//T becomes const int&.

        // ͬ��
        foo<std::reference_wrapper<int>>(x);
        cout << "x = " << x << endl;

        // ͬ��
        foo<int&>(x);
        cout << "x = " << x << endl;
    }
    cout << endl;
    
}
#endif