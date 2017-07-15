//#define MAIN
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

    std::swap(x, y);
    cout << "std::swap(x,y) : x = " << x << ", y = " << y << endl;

    // swap arr
    int arr1[3]{0, 1, 2};
    int arr2[3]{3, 4, 5};
    std::swap(arr1, arr2);

    cout << "arr1: ";
    std::for_each(arr1, arr1 + 3
            , [](int a) {
        cout << a << ", ";
            });
    cout << endl << endl;

     // ratio, ±àÒëÊ±²Ù×÷
    typedef std::ratio<5, 3> FiveThirds;
    cout << FiveThirds::num << "/" << FiveThirds::den << endl;
    typedef std::ratio<25, 15> AlsoFiveThirds;
    cout << AlsoFiveThirds::num << "/" << AlsoFiveThirds::den << endl;
    typedef std::ratio<0> Zero;
    cout << Zero::num << "/" << Zero::den << endl;
    typedef std::ratio<7, -3> Neg;
    cout << Neg::num << "/" << Neg::den << endl;
    bool eq = ratio_equal<ratio<5, 3>, ratio<25, 15>>::value;
    cout << "ratio_equal<ratio<5, 3>, ratio<25, 15>>::value = " << eq << endl;
    //ratio_multiply<ratio<1, numeric_limits<long long>::max()>, ratio<1, 2>>::type;
    //ratio_divide<FiveThirds, Zero>::type; // error
    cout << "std::nano = " << std::nano::num << "/" << std::nano::den << endl;
}

#endif