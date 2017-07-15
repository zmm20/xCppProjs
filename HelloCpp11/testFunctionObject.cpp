//#define MAIN

#ifdef MAIN


#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <functional> // the header for the predefined function objects
#include <deque>
#include <set>
#include <iterator>


template <typename T>
inline void PRINT_ELEMENTS(const T& coll,
    const std::string& optstr = "")
{
    std::cout << optstr;
    for (const auto& elem : coll) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}


using namespace std;
using namespace std::placeholders; // 占位符
int main()
{
    cout << "test 1: " << endl;
    {
        deque<int> coll = { 1, 2, 3, 5, 7, 11, 13, 17, 19 };
        PRINT_ELEMENTS(coll, "initialized: ");
        // negate all values in coll

        transform(coll.cbegin(), coll.cend(), // source
            coll.begin(), // destination
            negate<int>()); // operation
        PRINT_ELEMENTS(coll, "negated: ");
        // square all values in coll
        transform(coll.cbegin(), coll.cend(), // first source
            coll.cbegin(), // second source
            coll.begin(), // destination
            multiplies<int>()); // operation
        PRINT_ELEMENTS(coll, "squared: ");
    }
    cout << endl;

    cout << "test 2: " << endl;
    {
        set<int, greater<int>> coll1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        deque<int> coll2;
        // Note: due to the sorting criterion greater<>() elements have reverse order:
        PRINT_ELEMENTS(coll1, "initialized: ");
        // transform all elements into coll2 by multiplying them with 10
        transform(coll1.cbegin(), coll1.cend(), // source
            back_inserter(coll2), // destination
            bind(multiplies<int>(), _1, 10)); // operation, _1用来给transform传递过来的元素占位用的
            //bind1st(multiplies<int>(), 10));  // Before TR1, there were other binders and adapters for functional composition, such as
                                                // bind1st(), bind2nd(), ptr_fun(), mem_fun(), and mem_fun_ref(), but they have been deprecated
                                                // with C++11.
        PRINT_ELEMENTS(coll2, "transformed: ");
        // replace value equal to 70 with 42
        replace_if(coll2.begin(), coll2.end(), // range
            bind(equal_to<int>(), _1, 70), // replace criterion
            42); // new value
        PRINT_ELEMENTS(coll2, "replaced: ");
        // remove all elements with values between 50 and 80
        coll2.erase(remove_if(coll2.begin(), coll2.end(),
                                bind(logical_and<bool>(),
                                bind(greater_equal<int>(), _1, 50), //  x >= 50
                                bind(less_equal<int>(), _1, 80)))   // x <= 80
                    , coll2.end());
        PRINT_ELEMENTS(coll2, "removed: ");
    }
    cout << endl;
}
#endif