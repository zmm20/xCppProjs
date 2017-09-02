#define MAIN
#ifdef MAIN

#include <iostream>
#include <cstdlib>
#include <list>
#include <algorithm>
#include "util/algostuff.hpp" // ¸¨Öúº¯Êý
using namespace std;
using namespace std::placeholders;

int main()
{
    cout << "test 1" << endl;
    {
        vector<int> coll;
        INSERT_ELEMENTS(coll, 1, 9);
        // call print() for each element
        for_each(coll.cbegin(), coll.cend(), // range
            [](int elem) { // operation
            cout << elem << ' ';
        });
        cout << endl;

        // add 10 to each element
        for_each(coll.begin(), coll.end(), // range
            [](int& elem) { // operation
            elem += 10;
        });
        PRINT_ELEMENTS(coll);

        // add 10 to each element
        transform(coll.cbegin(), coll.cend(), // source range
            coll.begin(), // destination range
            [](int elem) { // operation
                return elem + 10;
        });
        PRINT_ELEMENTS(coll);
    }
    cout << endl;

    cout << "test 2" << endl;
    {
        vector<int> coll;
        int num;
        INSERT_ELEMENTS(coll, 1, 9);
        PRINT_ELEMENTS(coll, "coll: ");
        // count elements with value 4
        num = count(coll.cbegin(), coll.cend(), // range
            4); // value
        cout << "number of elements equal to 4: " << num << endl;
        // count elements with even value
        num = count_if(coll.cbegin(), coll.cend(), // range
            [](int elem) { // criterion
            return elem % 2 == 0;
        });
        cout << "number of elements with even value: " << num << endl;
        // count elements that are greater than value 4
        num = count_if(coll.cbegin(), coll.cend(), // range
            [](int elem) { // criterion
            return elem > 4;
        });
        cout << "number of elements greater than 4: " << num << endl;

    }
    cout << endl;

    cout << "test 3" << endl;
    {
        deque<int> coll;
        INSERT_ELEMENTS(coll, 2, 6);
        INSERT_ELEMENTS(coll, -3, 6);
        PRINT_ELEMENTS(coll);
        // process and print minimum and maximum
        cout << "minimum: "
            << *min_element(coll.cbegin(), coll.cend())
            << endl;
        cout << "maximum: "
            << *max_element(coll.cbegin(), coll.cend())
            << endl;
        // print min and max and their distance using minmax_element()
        auto mm = minmax_element(coll.cbegin(), coll.cend());
        cout << "min: " << *(mm.first) << endl; // print minimum
        cout << "max: " << *(mm.second) << endl; // print maximum
        cout << "distance: " << distance(mm.first, mm.second) << endl;

        auto absLess = [](int elem1, int elem2){
            return abs(elem1) < abs(elem2);
        };
        // process and print minimum and maximum of absolute values
        cout << "minimum of absolute values: "
            << *min_element(coll.cbegin(), coll.cend(),
                absLess)
            << endl;
        cout << "maximum of absolute values: "
            << *max_element(coll.cbegin(), coll.cend(),
                absLess)
            << endl;
    }
    cout << endl;

    cout << "test 4" << endl;
    {
        list<int> coll;
        INSERT_ELEMENTS(coll, 1, 9);
        INSERT_ELEMENTS(coll, 1, 9);
        PRINT_ELEMENTS(coll, "coll: ");
        // find first element with value 4
        list<int>::iterator pos1;
        pos1 = find(coll.begin(), coll.end(), // range
            4); // value
        // find second element with value 4
        // - note: continue the search behind the first 4 (if any)
        list<int>::iterator pos2;
        if (pos1 != coll.end()) {
            pos2 = find(++pos1, coll.end(), // range
                4); // value
        }
        // print all elements from first to second 4 (both included)
        // - note: now we need the position of the first 4 again (if any)
        if (pos1 != coll.end() && pos2 != coll.end()) {
            copy(--pos1, ++pos2,
                ostream_iterator<int>(cout, " "));
            cout << endl;
        }
    }
    cout << endl;
    
    cout << "test 5" << endl;
    {
        vector<int> coll;
        vector<int>::iterator pos;
        INSERT_ELEMENTS(coll, 1, 9);
        PRINT_ELEMENTS(coll, "coll: ");
        // find first element greater than 3
        pos = find_if(coll.begin(), coll.end(), // range
            bind(greater<int>(), _1, 3)); // criterion
        // print its position
        cout << "the "
            << distance(coll.begin(), pos) + 1
            << ". element is the first greater than 3" << endl;
        // find first element divisible by 3
        pos = find_if(coll.begin(), coll.end(),
            [](int elem) {
            return elem % 3 == 0;
        });
        // print its position
        cout << "the "
            << distance(coll.begin(), pos) + 1
            << ". element is the first divisible by 3" << endl;
        // find first element not <5
        pos = find_if_not(coll.begin(), coll.end(),
            bind(less<int>(), _1, 5));
        cout << "first value >=5: " << *pos << endl;
    }
    cout << endl;

    cout << "test 6" << endl;
    {

    }
    cout << endl;


    return EXIT_SUCCESS;
}

#endif