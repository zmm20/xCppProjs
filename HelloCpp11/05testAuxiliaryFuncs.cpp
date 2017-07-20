#define MAIN
#ifdef MAIN

#include <iostream>
#include <vector>
#include <algorithm>
#include <ratio>


using namespace std;


// function that compares two pointers by comparing the values to which they point
bool int_ptr_less(int* a, int* b)
{
    return *a < *b;
}

int main()
{
    cout << "----------05testAuxiliaryFuncs.cpp--------" << endl;

    cout << "test 1 " << endl;
    {
        int x = 17;
        int y = 42;
        int z = 33;
        int* px = &x;
        int* py = &y;
        int* pz = &z;
        // call max() with special comparison function
        int* pmax = std::max(px, py, int_ptr_less);
        cout << "max(x, y) = " << *pmax << endl;

        // call minmax() for initializer list with special comparison function
        std::pair<int*, int*> extremes = std::minmax({ px, py, pz }
            , [](int*a, int*b) {
            return *a < *b;
        });


        cout << "minmax(x, y, z) is: " << *extremes.first << ", " << *extremes.second << endl;

        int i = 2;
        long l = 4;
        //std::max(i, l); // ERROR: argument types don¡¯t match
        //std::max({ i,l }); // ERROR: argument types don¡¯t match
        std::max<long>(i, l); // OK
        std::max<long>({ i,l }); // OK

    }
    cout << endl;
    
    cout << "test 2" << endl;
    {
        int x = 17;
        int y = 42;
        int z = 33;

        std::swap(x, y);
        cout << "std::swap(x,y) : x = " << x << ", y = " << y << endl;

        // swap arr
        int arr1[3]{ 0, 1, 2 };
        int arr2[3]{ 3, 4, 5 };
        std::swap(arr1, arr2);

        cout << "arr1: ";
        std::for_each(arr1, arr1 + 3
            , [](int a) {
            cout << a << ", ";
        });
        cout << endl;
    }
    cout << endl;

    cout << "test 3" << endl;
    {
        // ratio, ±àÒëÊ±²Ù×÷
        typedef std::ratio<5, 3> FiveThirds;
        cout << FiveThirds::num << "/" << FiveThirds::den << endl; // 5/3
        typedef std::ratio<25, 15> AlsoFiveThirds; // 5 / 3
        cout << AlsoFiveThirds::num << "/" << AlsoFiveThirds::den << endl; // 1/1
        typedef std::ratio<0> Zero;
        cout << Zero::num << "/" << Zero::den << endl; // 0/1
        typedef std::ratio<7, -3> Neg; // -7/3
        cout << Neg::num << "/" << Neg::den << endl;


        bool eq = ratio_equal<ratio<5, 3>, ratio<25, 15>>::value;
        cout << "ratio_equal<ratio<5, 3>, ratio<25, 15>>::value = " << eq << endl; // 1
        //ratio_multiply<ratio<1, numeric_limits<long long>::max()>, ratio<1, 2>>::type;
        //ratio_divide<FiveThirds, Zero>::type; // error
        cout << "std::nano = " << std::nano::num << "/" << std::nano::den << endl;
    }
    cout << endl;

}

#endif