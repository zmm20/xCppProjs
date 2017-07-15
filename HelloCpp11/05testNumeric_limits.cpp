#define MAIN
#ifdef MAIN


#include <iostream>
#include <limits>

using namespace std;

constexpr int func()
{
    return 5;
}

int main()
{
    cout << "----------------05testNumeric_limits.cpp-----------------" << endl;

    //const int aa = 5;
    int array[func()]; // array[aa]
    cout << "array[0] = " << array[0] << endl;

    cout << "float digits: " << numeric_limits<float>::digits << endl
        << "double digits: " << numeric_limits<double>::digits << endl
        << "int digits: " << numeric_limits<int>::digits << endl
        << "char digits: " << numeric_limits<char>::digits << endl;


    // use textual representation for bool
    cout << boolalpha;

    // print maximum of integral types
    cout << "max(short): " << numeric_limits<short>::max() << endl;
    cout << "max(int): " << numeric_limits<int>::max() << endl;
    cout << "max(long): " << numeric_limits<long>::max() << endl;
    cout << endl;
    
    // print maximum of floating-point types
    cout << "max(float): "
        << numeric_limits<float>::max() << endl;
    cout << "max(double): "
        << numeric_limits<double>::max() << endl;
    cout << "max(long double): "
        << numeric_limits<long double>::max() << endl;
    cout << endl;
    
    // print whether char is signed
    cout << "is_signed(char): "
        << numeric_limits<char>::is_signed << endl;
    cout << endl;
    // print whether numeric limits for type string exist
    cout << "is_specialized(string): "
        << numeric_limits<string>::is_specialized << endl;
    
    return 0;
}
#endif