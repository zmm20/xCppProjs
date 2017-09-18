//#define MAIN
#ifdef MAIN

#include <iostream>
#include <cstdlib>
#include <list>
#include <algorithm>
#include <random>
#include "util/algostuff.hpp" // 辅助函数
using namespace std;
using namespace std::placeholders;

// test 8
// checks whether an element is even or odd
bool checkEven(int elem, bool even)
{
    if (even) {
        return elem % 2 == 0;
    }
    else {
        return elem % 2 == 1;
    }
}

// test 40:
class MyRandom {
public:
    ptrdiff_t operator() (ptrdiff_t max) {
        double tmp;
        tmp = static_cast<double>(rand())
            / static_cast<double>(RAND_MAX);
        return static_cast<ptrdiff_t>(tmp * max);
    }
};


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
        deque<int> coll;
        coll = { 1, 2, 7, 7, 6, 3, 9, 5, 7, 7, 7, 3, 6 };
        PRINT_ELEMENTS(coll);
        // find three consecutive elements with value 7
        deque<int>::iterator pos;
        pos = search_n(coll.begin(), coll.end(), // range
            3, // count
            7); // value
                // print result
        if (pos != coll.end()) {
            cout << "three consecutive elements with value 7 "
                << "start with " << distance(coll.begin(), pos) + 1
                << ". element" << endl;
        }
        else {
            cout << "no four consecutive elements with value 7 found"
                << endl;
        }
        // find four consecutive odd elements
        pos = search_n(coll.begin(), coll.end(), // range
            4, // count
            0, // value
            [](int elem, int value) { // criterion
            return elem % 2 == 1;
        });
        // print result
        if (pos != coll.end()) {
            cout << "first four consecutive odd elements are: ";
            for (int i = 0; i<4; ++i, ++pos) {
                cout << *pos << ' ';
            }
        }
        else {
            cout << "no four consecutive elements with value > 3 found";
        }
        cout << endl;
    }
    cout << endl;

    cout << "test 7" << endl;
    {
        deque<int> coll;
        list<int> subcoll;
        INSERT_ELEMENTS(coll, 1, 7);
        INSERT_ELEMENTS(coll, 1, 7);
        INSERT_ELEMENTS(subcoll, 3, 6);
        PRINT_ELEMENTS(coll, "coll: ");
        PRINT_ELEMENTS(subcoll, "subcoll: ");
        // search first occurrence of subcoll in coll
        deque<int>::iterator pos;
        pos = search(coll.begin(), coll.end(), // range
            subcoll.begin(), subcoll.end()); // subrange
                                             // loop while subcoll found as subrange of coll
        while (pos != coll.end()) {
            // print position of first element
            cout << "subcoll found starting with element "
                << distance(coll.begin(), pos) + 1
                << endl;
            // search next occurrence of subcoll
            ++pos;
            pos = search(pos, coll.end(), // range
                subcoll.begin(), subcoll.end()); // subrange
        }
    }
    cout << endl;

    cout << "test 8" << endl;
    {
        vector<int> coll;
        INSERT_ELEMENTS(coll, 1, 9);
        PRINT_ELEMENTS(coll, "coll: ");
        // arguments for checkEven()
        // - check for: ‘‘even odd even’’
        bool checkEvenArgs[3] = { true, false, true };
        // search first subrange in coll
        vector<int>::iterator pos;
        pos = search(coll.begin(), coll.end(), // range
            checkEvenArgs, checkEvenArgs + 3, // subrange values
            checkEven); // subrange criterion
                        // loop while subrange found
        while (pos != coll.end()) {
            // print position of first element
            cout << "subrange found starting with element "
                << distance(coll.begin(), pos) + 1
                << endl;
            // search next subrange in coll
            pos = search(++pos, coll.end(), // range
                checkEvenArgs, checkEvenArgs + 3, // subr. values
                checkEven); // subr. criterion
        }
    }
    cout << endl;

    cout << "test 9" << endl;
    {
        deque<int> coll;
        list<int> subcoll;
        INSERT_ELEMENTS(coll, 1, 7);
        INSERT_ELEMENTS(coll, 1, 7);
        INSERT_ELEMENTS(subcoll, 3, 6);
        PRINT_ELEMENTS(coll, "coll: ");
        PRINT_ELEMENTS(subcoll, "subcoll: ");
        // search last occurrence of subcoll in coll
        deque<int>::iterator pos;
        pos = find_end(coll.begin(), coll.end(), // range
            subcoll.begin(), subcoll.end()); // subrange
        
        // loop while subcoll found as subrange of coll
        deque<int>::iterator end(coll.end());
        while (pos != end) {
            // print position of first element
            cout << "subcoll found starting with element "
                << distance(coll.begin(), pos) + 1
                << endl;
            // search next occurrence of subcoll
            end = pos;
            pos = find_end(coll.begin(), end, // range
                subcoll.begin(), subcoll.end()); // subrange
        }
    }
    cout << endl;

    cout << "test 10" << endl;
    {
        vector<int> coll;
        list<int> searchcoll;
        INSERT_ELEMENTS(coll, 1, 11);
        INSERT_ELEMENTS(searchcoll, 3, 5);
        PRINT_ELEMENTS(coll, "coll: ");
        PRINT_ELEMENTS(searchcoll, "searchcoll: ");
        // search first occurrence of an element of searchcoll in coll
        vector<int>::iterator pos;
        pos = find_first_of(coll.begin(), coll.end(), // range
            searchcoll.begin(), // beginning of search set
            searchcoll.end()); // end of search set
        cout << "first element of searchcoll in coll is element "
            << distance(coll.begin(), pos) + 1
            << endl;
        // search last occurrence of an element of searchcoll in coll
        vector<int>::reverse_iterator rpos;
        rpos = find_first_of(coll.rbegin(), coll.rend(), // range
            searchcoll.begin(), // beginning of search set
            searchcoll.end()); // end of search set
        cout << "last element of searchcoll in coll is element "
            << distance(coll.begin(), rpos.base())
            << endl;
    }
    cout << endl;

    cout << "test 11" << endl;
    {
        vector<int> coll;
        coll.push_back(1);
        coll.push_back(3);
        coll.push_back(2);
        coll.push_back(4);
        coll.push_back(5);
        coll.push_back(5);
        coll.push_back(0);
        PRINT_ELEMENTS(coll, "coll: ");
        // search first two elements with equal value
        vector<int>::iterator pos;
        pos = adjacent_find(coll.begin(), coll.end());
        if (pos != coll.end()) {
            cout << "first two elements with equal value have position "
                << distance(coll.begin(), pos) + 1
                << endl;
        }
        // search first two elements for which the second has double the value of the first
        pos = adjacent_find(coll.begin(), coll.end(), // range
            [](int elem1, int elem2) {
            return elem1 * 2 == elem2;
        }); // criterion
        if (pos != coll.end()) {
            cout << "first two elements with second value twice the "
                << "first have pos. "
                << distance(coll.begin(), pos) + 1
                << endl;
        }
    }
    cout << endl;

    cout << "test 12" << endl;
    {
        vector<int> coll1;
        list<int> coll2;
        INSERT_ELEMENTS(coll1, 1, 7);
        INSERT_ELEMENTS(coll2, 3, 9);
        PRINT_ELEMENTS(coll1, "coll1: ");
        PRINT_ELEMENTS(coll2, "coll2: ");
        // check whether both collections are equal
        if (equal(coll1.begin(), coll1.end(), // first range
            coll2.begin())) { // second range
            cout << "coll1 == coll2" << endl;
        }
        else {
            cout << "coll1 != coll2" << endl;
        }
        // check for corresponding even and odd elements
        if (equal(coll1.begin(), coll1.end(), // first range
            coll2.begin(), // second range
            [](int elem1, int elem2)
        {
            return elem1 % 2 == elem2 % 2;
        })) 
        { // comparison criterion
            cout << "even and odd elements correspond" << endl;
        }
        else {
            cout << "even and odd elements do not correspond" << endl;
        }
    }
    cout << endl;

    cout << "test 13" << endl;
    {
        vector<int> coll1;
        list<int> coll2;
        deque<int> coll3;
        coll1 = { 1, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        coll2 = { 1, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
        coll3 = { 11, 12, 13, 19, 18, 17, 16, 15, 14, 11 };
        PRINT_ELEMENTS(coll1, "coll1: ");
        PRINT_ELEMENTS(coll2, "coll2: ");
        PRINT_ELEMENTS(coll3, "coll3: ");
        // check whether both collections have equal elements in any order
        if (is_permutation(coll1.cbegin(), coll1.cend(), // first range
            coll2.cbegin())) { // second range
            cout << "coll1 and coll2 have equal elements" << endl;
        }
        else {
            cout << "coll1 and coll2 don’t have equal elements" << endl;
        }
        // check for corresponding number of even and odd elements
        if (is_permutation(coll1.cbegin(), coll1.cend(), // first range
            coll3.cbegin(), // second range
            [](int elem1, int elem2)
        {
            return elem1 % 2 == elem2 % 2;
        })) 
        { // comparison criterion
            cout << "numbers of even and odd elements match" << endl;
        }
        else {
            cout << "numbers of even and odd elements don’t match" << endl;
        }
    }
    cout << endl;

    cout << "test 14" << endl;
    {
        vector<int> coll1 = { 1, 2, 3, 4, 5, 6 };
        list<int> coll2 = { 1, 2, 4, 8, 16, 3 };
        PRINT_ELEMENTS(coll1, "coll1: ");
        PRINT_ELEMENTS(coll2, "coll2: ");
        // find first mismatch
        auto values = mismatch(coll1.cbegin(), coll1.cend(), // first range
            coll2.cbegin()); // second range
        if (values.first == coll1.end()) {
            cout << "no mismatch" << endl;
        }
        else {
            cout << "first mismatch: "
                << *values.first << " and "
                << *values.second << endl;
        }
        // find first position where the element of coll1 is not
        // less than the corresponding element of coll2
        values = mismatch(coll1.cbegin(), coll1.cend(), // first range
            coll2.cbegin(), // second range
            less_equal<int>()); // criterion
        if (values.first == coll1.end()) {
            cout << "always less-or-equal" << endl;
        }
        else {
            cout << "not less-or-equal: "
                << *values.first << " and "
                << *values.second << endl;
        }

    }
    cout << endl;

    cout << "test 15" << endl;
    {
        list<int> c1, c2, c3, c4;
        // fill all collections with the same starting values
        INSERT_ELEMENTS(c1, 1, 5);
        c4 = c3 = c2 = c1;
        // and now some differences
        c1.push_back(7);
        c3.push_back(2);
        c3.push_back(0);
        c4.push_back(2);
        // create collection of collections
        vector<list<int>> cc;
        cc.insert(cc.begin(), { c1, c2, c3, c4, c3, c1, c4, c2 });
        // print all collections
        for_each(cc.cbegin(), cc.cend(),
            [](const list<int>& l)
        {
            PRINT_ELEMENTS(l);
        });
        cout << endl;
        // sort collection lexicographically
        sort(cc.begin(), cc.end(), // range
            [](const list<int>& l1, const list<int>& l2)
        {
            return lexicographical_compare
            (l1.cbegin(), l1.cend(), // first range
                l2.cbegin(), l2.cend()); // second range
        }); // sorting criterion

        // print all collections again
        for_each(cc.cbegin(), cc.cend(),
            [](const list<int>& l)
        {
            PRINT_ELEMENTS(l);
        });
    }
    cout << endl;

    cout << "test 16" << endl;
    {
        vector<int> coll1 = { 1, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        PRINT_ELEMENTS(coll1, "coll1: ");
        // check whether coll1 is sorted
        if (is_sorted(coll1.begin(), coll1.end())) {
            cout << "coll1 is sorted" << endl;
        }
        else {
            cout << "coll1 is not sorted" << endl;
        }
        map<int, string> coll2;
        coll2 = { { 1,"Bill" },{ 2,"Jim" },{ 3,"Nico" },{ 4,"Liu" },{ 5,"Ai" } };
        PRINT_MAPPED_ELEMENTS(coll2, "coll2: ");
        // define predicate to compare names
        auto compareName = [](const pair<int, string>& e1,
            const pair<int, string>& e2) {
            return e1.second<e2.second;
        };
        // check whether the names in coll2 are sorted
        if (is_sorted(coll2.cbegin(), coll2.cend(),
            compareName)) {
            cout << "names in coll2 are sorted" << endl;
        }
        else {
            cout << "names in coll2 are not sorted" << endl;
        }
        // print first unsorted name
        auto pos = is_sorted_until(coll2.cbegin(), coll2.cend(),
            compareName);
        if (pos != coll2.end()) {
            cout << "first unsorted name: " << pos->second << endl;
        }
    }
    cout << endl;

    cout << "test 17" << endl;
    {
        vector<int> coll = { 5, 3, 9, 1, 3, 4, 8, 2, 6 };
        PRINT_ELEMENTS(coll, "coll: ");
        // define predicate: check whether element is odd:
        auto isOdd = [](int elem) {
            return elem % 2 == 1;
        };
        // check whether coll is partitioned in odd and even elements
        if (is_partitioned(coll.cbegin(), coll.cend(), // range
            isOdd)) { // predicate
            cout << "coll is partitioned" << endl;
            // find first even element:
            auto pos = partition_point(coll.cbegin(), coll.cend(),
                isOdd);
            cout << "first even element: " << *pos << endl;
        }
        else {
            cout << "coll is not partitioned" << endl;
        }
    }
    cout << endl;

    cout << "test 18" << endl;
    {
        vector<int> coll1 = { 9, 8, 7, 7, 7, 5, 4, 2, 1 };
        vector<int> coll2 = { 5, 3, 2, 1, 4, 7, 9, 8, 6 };
        PRINT_ELEMENTS(coll1, "coll1: ");
        PRINT_ELEMENTS(coll2, "coll2: ");
        // check whether the collections are heaps
        cout << boolalpha << "coll1 is heap: "
            << is_heap(coll1.cbegin(), coll1.cend()) << endl;
        cout << "coll2 is heap: "
            << is_heap(coll2.cbegin(), coll2.cend()) << endl;
        // print the first element that is not a heap in coll2
        auto pos = is_heap_until(coll2.cbegin(), coll2.cend());
        if (pos != coll2.end()) {
            cout << "first non-heap element: " << *pos << endl;
        }
    }
    cout << endl;

    cout << "test 19" << endl;
    {
        vector<int> coll;
        vector<int>::iterator pos;
        INSERT_ELEMENTS(coll, 1, 9);
        PRINT_ELEMENTS(coll, "coll: ");
        // define an object for the predicate (using a lambda)
        auto isEven = [](int elem) {
            return elem % 2 == 0;
        };
        // print whether all, any, or none of the elements are/is even
        cout << boolalpha << "all even?: "
            << all_of(coll.cbegin(), coll.cend(), isEven) << endl;
        cout << "any even?: "
            << any_of(coll.cbegin(), coll.cend(), isEven) << endl;
        cout << "none even?: "
            << none_of(coll.cbegin(), coll.cend(), isEven) << endl;
    }
    cout << endl;

    // 11.6 更易型算法
    cout << "test 20" << endl;
    {
        vector<string> coll1 = { "Hello", "this", "is", "an", "example" };
        list<string> coll2;
        // copy elements of coll1 into coll2
        // - use back inserter to insert instead of overwrite
        copy(coll1.cbegin(), coll1.cend(), // source range
            back_inserter(coll2)); // destination range
                                   // print elements of coll2
                                   // - copy elements to cout using an ostream iterator
        copy(coll2.cbegin(), coll2.cend(), // source range
            ostream_iterator<string>(cout, " ")); // destination range
        cout << endl;
        // copy elements of coll1 into coll2 in reverse order
        // - now overwriting
        copy(coll1.crbegin(), coll1.crend(), // source range
            coll2.begin()); // destination range
                            // print elements of coll2 again
        copy(coll2.cbegin(), coll2.cend(), // source range
            ostream_iterator<string>(cout, " ")); // destination range
        cout << endl;
    }
    cout << endl;

    cout << "test 21" << endl;
    {
        // 注意, copy 相关算法的第三个参数不能位于第一个与第二个实参形成的区间内
        // initialize source collection with ‘‘. ........abcdef..........’’
        vector<char> source(10, '.');
        for (int c = 'a'; c <= 'f'; c++) {
            source.push_back(c);
        } 
        source.insert(source.end(), 10, '.');
        PRINT_ELEMENTS(source, "source: ");

        // copy all letters three elements in front of the ’a’
        vector<char> c1(source.cbegin(), source.cend());
        copy(c1.cbegin() + 10, c1.cbegin() + 16, // source range
            c1.begin() + 7); // destination range
        PRINT_ELEMENTS(c1, "    c1: ");
        // copy all letters three elements behind the ’f’
        vector<char> c2(source.cbegin(), source.cend());
        copy_backward(c2.cbegin() + 10, c2.cbegin() + 16, // source range
            c2.begin() + 19); // destination range
        PRINT_ELEMENTS(c2, "    c2: ");
    }
    cout << endl;

    cout << "test 22" << endl;
    {
        vector<string> coll1 = { "Hello", "this", "is", "an", "example" };
        list<string> coll2;
        // copy elements of coll1 into coll2
        // - use back inserter to insert instead of overwrite
        // - use copy() because the elements in coll1 are used again
        copy(coll1.cbegin(), coll1.cend(), // source range
            back_inserter(coll2)); // destination range
                                   // print elements of coll2
                                   // - copy elements to cout using an ostream iterator
                                   // - use move() because these elements in coll2 are not used again
        move(coll2.cbegin(), coll2.cend(), // source range
            ostream_iterator<string>(cout, " ")); // destination range
        cout << endl;
        // copy elements of coll1 into coll2 in reverse order
        // - now overwriting (coll2.size() still fits)
        // - use move() because the elements in coll1 are not used again
        move(coll1.crbegin(), coll1.crend(), // source range
            coll2.begin()); // destination range
                            // print elements of coll2 again
                            // - use move() because the elements in coll2 are not used again
        move(coll2.cbegin(), coll2.cend(), // source range
            ostream_iterator<string>(cout, " ")); // destination range
        cout << endl;
    }
    cout << endl;

    cout << "test 23" << endl;
    {
        vector<int> coll1;
        list<int> coll2;

        INSERT_ELEMENTS(coll1, 1, 9);
        PRINT_ELEMENTS(coll1, "coll1: ");
        // negate all elements in coll1
        transform(coll1.cbegin(), coll1.cend(), // source range
            coll1.begin(), // destination range
            negate<int>()); // operation
        PRINT_ELEMENTS(coll1, "negated: ");
        // transform elements of coll1 into coll2 with ten times their value
        transform(coll1.cbegin(), coll1.cend(), // source range
            back_inserter(coll2), // destination range
            bind(multiplies<int>(), _1, 10)); // operation
        PRINT_ELEMENTS(coll2, "coll2: ");
        // print coll2 negatively and in reverse order
        transform(coll2.crbegin(), coll2.crend(), // source range
            ostream_iterator<int>(cout, " "), // destination range
            [](int elem) { // operation
            return -elem;
        });
        cout << endl;
    }
    cout << endl;

    cout << "test 24" << endl;
    {
        vector<int> coll1;
        list<int> coll2;
        INSERT_ELEMENTS(coll1, 1, 9);
        PRINT_ELEMENTS(coll1, "coll1: ");
        // square each element
        transform(coll1.cbegin(), coll1.cend(), // first source range
            coll1.cbegin(), // second source range
            coll1.begin(), // destination range
            multiplies<int>()); // operation
        PRINT_ELEMENTS(coll1, "squared: ");
        // add each element traversed forward with each element traversed backward
        // and insert result into coll2
        transform(coll1.cbegin(), coll1.cend(), // first source range
            coll1.crbegin(), // second source range
            back_inserter(coll2), // destination range
            plus<int>()); // operation
        PRINT_ELEMENTS(coll2, "coll2: ");
        // print differences of two corresponding elements
        cout << "diff: ";
        transform(coll1.cbegin(), coll1.cend(), // first source range
            coll2.cbegin(), // second source range
            ostream_iterator<int>(cout, " "), // destination range
            minus<int>()); // operation
        cout << endl;
    }
    cout << endl;

    cout << "test 25" << endl;
    {
        vector<int> coll1;
        deque<int> coll2;
        INSERT_ELEMENTS(coll1, 1, 9);
        INSERT_ELEMENTS(coll2, 11, 23);
        PRINT_ELEMENTS(coll1, "coll1: ");
        PRINT_ELEMENTS(coll2, "coll2: ");
        // swap elements of coll1 with corresponding elements of coll2
        deque<int>::iterator pos;
        pos = swap_ranges(coll1.begin(), coll1.end(), // first range
            coll2.begin()); // second range
        PRINT_ELEMENTS(coll1, "\ncoll1: ");
        PRINT_ELEMENTS(coll2, "coll2: ");
        if (pos != coll2.end()) {
            cout << "first element not modified: "
                << *pos << endl;
        }
        // mirror first three with last three elements in coll2
        swap_ranges(coll2.begin(), coll2.begin() + 3, // first range
            coll2.rbegin()); // second range
        PRINT_ELEMENTS(coll2, "\ncoll2: ");
    }
    cout << endl;

    cout << "test 26" << endl;
    {
        // print ten times 7.7
        fill_n(ostream_iterator<float>(cout, " "), // beginning of destination
            10, // count
            7.7); // new value
        cout << endl;
        list<string> coll;
        // insert "hello" nine times
        fill_n(back_inserter(coll), // beginning of destination
            9, // count
            "hello"); // new value
        PRINT_ELEMENTS(coll, "coll: ");
        // overwrite all elements with "again"
        fill(coll.begin(), coll.end(), // destination
            "again"); // new value
        PRINT_ELEMENTS(coll, "coll: ");
        // replace all but two elements with "hi"
        fill_n(coll.begin(), // beginning of destination
            coll.size() - 2, // count
            "hi"); // new value
        PRINT_ELEMENTS(coll, "coll: ");
        // replace the second and up to the last element but one with "hmmm"
        list<string>::iterator pos1, pos2;
        pos1 = coll.begin();
        pos2 = coll.end();
        fill(++pos1, --pos2, // destination
            "hmmm"); // new value
        PRINT_ELEMENTS(coll, "coll: ");
    }
    cout << endl;

    cout << "test 27" << endl;
    {
        list<int> coll;
        // insert five random numbers
        generate_n(back_inserter(coll), // beginning of destination range
            5, // count
            rand); // new value generator
        PRINT_ELEMENTS(coll);
        // overwrite with five new random numbers
        generate(coll.begin(), coll.end(), // destination range
            rand); // new value generator
        PRINT_ELEMENTS(coll);
    }
    cout << endl;

    cout << "test 28" << endl;
    {
        array<int, 10> coll;
        iota(coll.begin(), coll.end(), // destination range
            42); // start value
        PRINT_ELEMENTS(coll, "coll: ");
    }
    cout << endl;

    cout << "test 29" << endl;
    {
        list<int> coll;
        INSERT_ELEMENTS(coll, 2, 7);
        INSERT_ELEMENTS(coll, 4, 9);
        PRINT_ELEMENTS(coll, "coll: ");
        // replace all elements with value 6 with 42
        replace(coll.begin(), coll.end(), // range
            6, // old value
            42); // new value
        PRINT_ELEMENTS(coll, "coll: ");
        // replace all elements with value less than 5 with 0
        replace_if(coll.begin(), coll.end(), // range
            [](int elem) { // criterion for replacement
            return elem<5;
        },
            0); // new value
        PRINT_ELEMENTS(coll, "coll: ");
    }
    cout << endl;

    cout << "test 30" << endl;
    {
        list<int> coll;
        INSERT_ELEMENTS(coll, 2, 6);
        INSERT_ELEMENTS(coll, 4, 9);
        PRINT_ELEMENTS(coll);
        // print all elements with value 5 replaced with 55
        replace_copy(coll.cbegin(), coll.cend(), // source
            ostream_iterator<int>(cout, " "), // destination
            5, // old value
            55); // new value
        cout << endl;
        // print all elements with a value less than 5 replaced with 42
        replace_copy_if(coll.cbegin(), coll.cend(), // source
            ostream_iterator<int>(cout, " "), // destination
            bind(less<int>(), _1, 5), // replacement criterion
            42); // new value
        cout << endl;
        // print each element while each odd element is replaced with 0
        replace_copy_if(coll.cbegin(), coll.cend(), // source
            ostream_iterator<int>(cout, " "), // destination
            [](int elem) { // replacement criterion
            return elem % 2 == 1;
        },
            0); // new value
        cout << endl;
    }
    cout << endl;

    cout << "test 31" << endl;
    {
        vector<int> coll;
        INSERT_ELEMENTS(coll, 2, 6);
        INSERT_ELEMENTS(coll, 4, 9);
        INSERT_ELEMENTS(coll, 1, 7);
        PRINT_ELEMENTS(coll, "coll: ");
        // remove all elements with value 5
        vector<int>::iterator pos;
        pos = remove(coll.begin(), coll.end(), // range
            5); // value to remove
        PRINT_ELEMENTS(coll, "size not changed: ");
        // erase the ‘‘removed’’ elements in the container
        coll.erase(pos, coll.end());
        PRINT_ELEMENTS(coll, "size changed: ");
        // remove all elements less than 4
        coll.erase(remove_if(coll.begin(), coll.end(), // range
            [](int elem) { // remove criterion
            return elem<4;
        }),
            coll.end());
        PRINT_ELEMENTS(coll, "<4 removed: ");
    }
    cout << endl;

    cout << "test 32" << endl;
    {
        list<int> coll1;
        INSERT_ELEMENTS(coll1, 1, 6);
        INSERT_ELEMENTS(coll1, 1, 9);
        PRINT_ELEMENTS(coll1);
        // print elements without those having the value 3
        remove_copy(coll1.cbegin(), coll1.cend(), // source
            ostream_iterator<int>(cout, " "), // destination
            3); // removed value
        cout << endl;
        // print elements without those having a value greater than 4
        remove_copy_if(coll1.cbegin(), coll1.cend(), // source
            ostream_iterator<int>(cout, " "), // destination
            [](int elem) { // criterion for elements NOT copied
            return elem>4;
        });
        cout << endl;
        // copy all elements not less than 4 into a multiset
        multiset<int> coll2;
        remove_copy_if(coll1.cbegin(), coll1.cend(), // source
            inserter(coll2, coll2.end()), // destination
            bind(less<int>(), _1, 4)); // elements NOT copied
        PRINT_ELEMENTS(coll2);
    }
    cout << endl;

    cout << "test 33" << endl;
    {
        // source data
        int source[] = { 1, 4, 4, 6, 1, 2, 2, 3, 1, 6, 6, 6, 5, 7,
            5, 4, 4 };
        list<int> coll;
        // initialize coll with elements from source
        copy(begin(source), end(source), // source
            back_inserter(coll)); // destination
        PRINT_ELEMENTS(coll);
        // remove consecutive duplicates
        auto pos = unique(coll.begin(), coll.end());
        // print elements not removed
        // - use new logical end
        copy(coll.begin(), pos, // source
            ostream_iterator<int>(cout, " ")); // destination
        cout << "\n\n";
        // reinitialize coll with elements from source
        copy(begin(source), end(source), // source
            coll.begin()); // destination
        PRINT_ELEMENTS(coll);
        // remove elements if there was a previous greater element
        coll.erase(unique(coll.begin(), coll.end(),
            greater<int>()),
            coll.end());
        PRINT_ELEMENTS(coll);
    }
    cout << endl;

    cout << "test 34" << endl;
    {
        // source data
        int source[] = { 1, 4, 4, 6, 1, 2, 2, 3, 1, 6, 6, 6, 5, 7,
            5, 4, 4 };
        // initialize coll with elements from source
        list<int> coll;
        copy(begin(source), end(source), // source
            back_inserter(coll)); // destination
        PRINT_ELEMENTS(coll);
        // print elements with consecutive duplicates removed
        unique_copy(coll.cbegin(), coll.cend(), // source
            ostream_iterator<int>(cout, " ")); // destination
        cout << endl;
        // print elements without consecutive entries that differ by one
        unique_copy(coll.cbegin(), coll.cend(), // source
            ostream_iterator<int>(cout, " "), // destination
            [](int elem1, int elem2)
        {
            return elem1 + 1 == elem2 || elem1 - 1 == elem2;
        }); // duplicates criterion
        cout << endl;
    }
    cout << endl;

    cout << "test 35" << endl;
    {
        vector<int> coll;
        INSERT_ELEMENTS(coll, 1, 9);
        PRINT_ELEMENTS(coll, "coll: ");
        // reverse order of elements
        reverse(coll.begin(), coll.end());
        PRINT_ELEMENTS(coll, "coll: ");
        // reverse order from second to last element but one
        reverse(coll.begin() + 1, coll.end() - 1);
        PRINT_ELEMENTS(coll, "coll: ");
        // print all of them in reverse order
        reverse_copy(coll.cbegin(), coll.cend(), // source
            ostream_iterator<int>(cout, " ")); // destination
        cout << endl;
    }
    cout << endl;

    cout << "test 36" << endl;
    {
        vector<int> coll;
        INSERT_ELEMENTS(coll, 1, 9);
        PRINT_ELEMENTS(coll, "coll: ");
        // rotate one element to the left
        rotate(coll.begin(), // beginning of range
            coll.begin() + 1, // new first element
            coll.end()); // end of range
        PRINT_ELEMENTS(coll, "one left: ");
        // rotate two elements to the right
        rotate(coll.begin(), // beginning of range
            coll.end() - 2, // new first element
            coll.end()); // end of range
        PRINT_ELEMENTS(coll, "two right: ");
        // rotate so that element with value 4 is the beginning
        rotate(coll.begin(), // beginning of range
            find(coll.begin(), coll.end(), 4), // new first element
            coll.end()); // end of range
        PRINT_ELEMENTS(coll, "4 first: ");
    }
    cout << endl;

    cout << "test 37" << endl;
    {
        set<int> coll;
        INSERT_ELEMENTS(coll, 1, 9);
        PRINT_ELEMENTS(coll);
        // print elements rotated one element to the left
        set<int>::const_iterator pos = next(coll.cbegin());
        rotate_copy(coll.cbegin(), // beginning of source
            pos, // new first element
            coll.cend(), // end of source
            ostream_iterator<int>(cout, " ")); // destination
        cout << endl;
        // print elements rotated two elements to the right
        pos = coll.cend();
        advance(pos, -2);
        rotate_copy(coll.cbegin(), // beginning of source
            pos, // new first element
            coll.cend(), // end of source
            ostream_iterator<int>(cout, " ")); // destination
        cout << endl;
        // print elements rotated so that element with value 4 is the beginning
        rotate_copy(coll.cbegin(), // beginning of source
            coll.find(4), // new first element
            coll.cend(), // end of source
            ostream_iterator<int>(cout, " ")); // destination
        cout << endl;
    }
    cout << endl;

    cout << "test 38" << endl;
    {
        vector<int> coll;
        INSERT_ELEMENTS(coll, 1, 3);
        PRINT_ELEMENTS(coll, "on entry: ");
        // permute elements until they are sorted
        // - runs through all permutations because the elements are sorted now
        // 下一个排列, 使用前, 首先确保序列已排序
        while (next_permutation(coll.begin(), coll.end())) {
            PRINT_ELEMENTS(coll, " ");
        }
        PRINT_ELEMENTS(coll, "afterward: ");
        // permute until descending sorted
        // - this is the next permutation after ascending sorting
        // - so the loop ends immediately
        while (prev_permutation(coll.begin(), coll.end())) {
            PRINT_ELEMENTS(coll, " ");
        }
        PRINT_ELEMENTS(coll, "now: ");
        // permute elements until they are sorted in descending order
        // - runs through all permutations because the elements are sorted in descending order now
        while (prev_permutation(coll.begin(), coll.end())) {
            PRINT_ELEMENTS(coll, " ");
        }
        PRINT_ELEMENTS(coll, "afterward: ");
    }
    cout << endl;

    cout << "test 39" << endl;
    {
        vector<int> coll;
        INSERT_ELEMENTS(coll, 1, 9);
        PRINT_ELEMENTS(coll, "coll: ");
        // shuffle all elements randomly
        random_shuffle(coll.begin(), coll.end());
        PRINT_ELEMENTS(coll, "shuffled: ");
        // sort them again
        sort(coll.begin(), coll.end());
        PRINT_ELEMENTS(coll, "sorted: ");
        // shuffle elements with default engine
        default_random_engine dre;
        shuffle(coll.begin(), coll.end(), // range
            dre); // random-number generator
        PRINT_ELEMENTS(coll, "shuffled: ");
    }
    cout << endl;

    cout << "test 40" << endl;
    {
        vector<int> coll;
        INSERT_ELEMENTS(coll, 1, 9);
        PRINT_ELEMENTS(coll, "coll: ");
        // shuffle elements with self-written random-number generator
        MyRandom rd;
        random_shuffle(coll.begin(), coll.end(), // range
            rd); // random-number generator
        PRINT_ELEMENTS(coll, "shuffled: ");
    }
    cout << endl;

    cout << "test 41" << endl;
    {
        vector<int> coll1;
        vector<int> coll2;
        INSERT_ELEMENTS(coll1, 1, 9);
        INSERT_ELEMENTS(coll2, 1, 9);
        PRINT_ELEMENTS(coll1, "coll1: ");
        PRINT_ELEMENTS(coll2, "coll2: ");
        cout << endl;
        // move all even elements to the front
        vector<int>::iterator pos1, pos2;
        pos1 = partition(coll1.begin(), coll1.end(), // range
            [](int elem) { // criterion
            return elem % 2 == 0;
        });
        pos2 = stable_partition(coll2.begin(), coll2.end(), // range
            [](int elem) { // criterion
            return elem % 2 == 0;
        });
        // print collections and first odd element
        PRINT_ELEMENTS(coll1, "coll1: ");
        cout << "first odd element: " << *pos1 << endl;
        PRINT_ELEMENTS(coll2, "coll2: ");
        cout << "first odd element: " << *pos2 << endl;
    }
    cout << endl;

    cout << "test 42" << endl;
    {
        vector<int> coll = { 1, 6, 33, 7, 22, 4, 11, 33, 2, 7, 0, 42, 5 };
        PRINT_ELEMENTS(coll, "coll: ");
        // destination collections:
        vector<int> evenColl;
        vector<int> oddColl;
        // copy all elements partitioned accordingly into even and odd elements
        partition_copy(coll.cbegin(), coll.cend(), // source range
            back_inserter(evenColl), // destination for even elements
            back_inserter(oddColl), // destination for odd elements
            [](int elem) { // predicate: check for even elements
            return elem % 2 == 0;
        });
        PRINT_ELEMENTS(evenColl, "evenColl: ");
        PRINT_ELEMENTS(oddColl, "oddColl: ");
    }
    cout << endl;

    cout << "test 43" << endl;
    {
        deque<int> coll;
        INSERT_ELEMENTS(coll, 1, 9);
        INSERT_ELEMENTS(coll, 1, 9);
        PRINT_ELEMENTS(coll, "on entry: ");
        // sort elements
        sort(coll.begin(), coll.end());
        PRINT_ELEMENTS(coll, "sorted: ");
        // sorted reverse
        sort(coll.begin(), coll.end(), // range
            greater<int>()); // sorting criterion
        PRINT_ELEMENTS(coll, "sorted >: ");
    }
    cout << endl;

    cout << "test 44" << endl;
    {
        // fill two collections with the same elements
        vector<string> coll1 = { "1xxx", "2x", "3x", "4x", "5xx", "6xxxx",
            "7xx", "8xxx", "9xx", "10xxx", "11", "12",
            "13", "14xx", "15", "16", "17" };
        vector<string> coll2(coll1);
        PRINT_ELEMENTS(coll1, "on entry:\n ");
        auto lessLength = [](const string& s1, const string& s2)
        {
            return s1.length() < s2.length();
        };
        // sort (according to the length of the strings)
        sort(coll1.begin(), coll1.end(), // range
            lessLength); // criterion
        stable_sort(coll2.begin(), coll2.end(), // range
            lessLength); // criterion
        PRINT_ELEMENTS(coll1, "\nwith sort():\n ");
        PRINT_ELEMENTS(coll2, "\nwith stable_sort():\n ");
    }
    cout << endl;

    cout << "test 45" << endl;
    {
        deque<int> coll;
        INSERT_ELEMENTS(coll, 3, 7);
        INSERT_ELEMENTS(coll, 2, 6);
        INSERT_ELEMENTS(coll, 1, 5);
        PRINT_ELEMENTS(coll);
        // sort until the first five elements are sorted
        partial_sort(coll.begin(), // beginning of the range
            coll.begin() + 5, // end of sorted range
            coll.end()); // end of full range
        PRINT_ELEMENTS(coll);
        // sort inversely until the first five elements are sorted
        partial_sort(coll.begin(), // beginning of the range
            coll.begin() + 5, // end of sorted range
            coll.end(), // end of full range
            greater<int>()); // sorting criterion
        PRINT_ELEMENTS(coll);
        // sort all elements
        partial_sort(coll.begin(), // beginning of the range
            coll.end(), // end of sorted range
            coll.end()); // end of full range
        PRINT_ELEMENTS(coll);
    }
    cout << endl;

    cout << "test 46" << endl;
    {
        deque<int> coll1;
        vector<int> coll6(6); // initialize with 6 elements
        vector<int> coll30(30); // initialize with 30 elements
        INSERT_ELEMENTS(coll1, 3, 7);
        INSERT_ELEMENTS(coll1, 2, 6);
        INSERT_ELEMENTS(coll1, 1, 5);
        PRINT_ELEMENTS(coll1);
        // copy elements of coll1 sorted into coll6
        vector<int>::const_iterator pos6;
        pos6 = partial_sort_copy(coll1.cbegin(), coll1.cend(),
            coll6.begin(), coll6.end());
        // print all copied elements
        copy(coll6.cbegin(), pos6,
            ostream_iterator<int>(cout, " "));
        cout << endl;
        // copy elements of coll1 sorted into coll30
        vector<int>::const_iterator pos30;
        pos30 = partial_sort_copy(coll1.cbegin(), coll1.cend(),
            coll30.begin(), coll30.end(),
            greater<int>());
        // print all copied elements
        copy(coll30.cbegin(), pos30,
            ostream_iterator<int>(cout, " "));
        cout << endl;
    }
    cout << endl;

    cout << "test 47" << endl;
    {
        deque<int> coll;
        INSERT_ELEMENTS(coll, 3, 7);
        INSERT_ELEMENTS(coll, 2, 6);
        INSERT_ELEMENTS(coll, 1, 5);
        PRINT_ELEMENTS(coll);
        // extract the four lowest elements
        nth_element(coll.begin(), // beginning of range
            coll.begin() + 3, // element that should be sorted correctly
            coll.end()); // end of range
                         // print them
        cout << "the four lowest elements are: ";
        copy(coll.cbegin(), coll.cbegin() + 4,
            ostream_iterator<int>(cout, " "));
        cout << endl;
        // extract the four highest elements
        nth_element(coll.begin(), // beginning of range
            coll.end() - 4, // element that should be sorted correctly
            coll.end()); // end of range
                         // print them
        cout << "the four highest elements are: ";
        copy(coll.cend() - 4, coll.cend(),
            ostream_iterator<int>(cout, " "));
        cout << endl;
        // extract the four highest elements (second version)
        nth_element(coll.begin(), // beginning of range
            coll.begin() + 3, // element that should be sorted correctly
            coll.end(), // end of range
            greater<int>()); // sorting criterion
                             // print them
        cout << "the four highest elements are: ";
        copy(coll.cbegin(), coll.cbegin() + 4,
            ostream_iterator<int>(cout, " "));
        cout << endl;
    }
    cout << endl;
	
	cout << "test 48" << endl;
	{
		vector<int> coll;
		INSERT_ELEMENTS(coll,3,7);
		INSERT_ELEMENTS(coll,5,9);
		INSERT_ELEMENTS(coll,1,4);
		PRINT_ELEMENTS (coll, "on entry: ");
		// convert collection into a heap
		make_heap (coll.begin(), coll.end());
		PRINT_ELEMENTS (coll, "after make_heap(): ");
		// pop next element out of the heap
		pop_heap (coll.begin(), coll.end());
		coll.pop_back();
		PRINT_ELEMENTS (coll, "after pop_heap(): ");
		// push new element into the heap
		coll.push_back (17);
		push_heap (coll.begin(), coll.end());
		PRINT_ELEMENTS (coll, "after push_heap(): ");
		// convert heap into a sorted collection
		// - NOTE: after the call it is no longer a heap
		sort_heap (coll.begin(), coll.end());
		PRINT_ELEMENTS (coll, "after sort_heap(): ");
	}
	cout << endl;

    cout << "test 49" << endl;
    {
        list<int> coll;
        INSERT_ELEMENTS(coll, 1, 9);
        PRINT_ELEMENTS(coll);
        // check existence of element with value 5
        if (binary_search(coll.cbegin(), coll.cend(), 5)) {
            cout << "5 is present" << endl;
        }
        else {
            cout << "5 is not present" << endl;
        }
        // check existence of element with value 42
        if (binary_search(coll.cbegin(), coll.cend(), 42)) {
            cout << "42 is present" << endl;
        }
        else {
            cout << "42 is not present" << endl;
        }
    }
    cout << endl;

    cout << "test 50" << endl;
    {

        list<int> coll;
        vector<int> search;
        INSERT_ELEMENTS(coll, 1, 9);
        PRINT_ELEMENTS(coll, "coll: ");
        search.push_back(3);
        search.push_back(4);
        search.push_back(7);
        PRINT_ELEMENTS(search, "search: ");
        // check whether all elements in search are also in coll
        if (includes(coll.cbegin(), coll.cend(),
            search.cbegin(), search.cend())) {
            cout << "all elements of search are also in coll"
                << endl;
        }
        else {
            cout << "not all elements of search are also in coll"
                << endl;
        }
    }
    cout << endl;

    cout << "test 51" << endl;
    {
        list<int> coll;
        INSERT_ELEMENTS(coll, 1, 9);
        INSERT_ELEMENTS(coll, 1, 9);
        coll.sort();
        PRINT_ELEMENTS(coll);
        // print first and last position 5 could get inserted
        auto pos1 = lower_bound(coll.cbegin(), coll.cend(),
            5);
        auto pos2 = upper_bound(coll.cbegin(), coll.cend(),
            5);
        cout << "5 could get position "
            << distance(coll.cbegin(), pos1) + 1
            << " up to "
            << distance(coll.cbegin(), pos2) + 1
            << " without breaking the sorting" << endl;
        // insert 3 at the first possible position without breaking the sorting
        coll.insert(lower_bound(coll.begin(), coll.end(),
            3),
            3);
        // insert 7 at the last possible position without breaking the sorting
        coll.insert(upper_bound(coll.begin(), coll.end(),
            7),
            7);
        PRINT_ELEMENTS(coll);
    }
    cout << endl;

    cout << "test 52" << endl;
    {
        list<int> coll;
        INSERT_ELEMENTS(coll, 1, 9);
        INSERT_ELEMENTS(coll, 1, 9);
        coll.sort();
        PRINT_ELEMENTS(coll);
        // print first and last position 5 could get inserted
        pair<list<int>::const_iterator, list<int>::const_iterator> range;
        range = equal_range(coll.cbegin(), coll.cend(),
            5);
        cout << "5 could get position "
            << distance(coll.cbegin(), range.first) + 1
            << " up to "
            << distance(coll.cbegin(), range.second) + 1
            << " without breaking the sorting" << endl;
    }
    cout << endl;

    cout << "test 53" << endl;
    {
        list<int> coll1;
        set<int> coll2;
        // fill both collections with some sorted elements
        INSERT_ELEMENTS(coll1, 1, 6);
        INSERT_ELEMENTS(coll2, 3, 8);
        PRINT_ELEMENTS(coll1, "coll1: ");
        PRINT_ELEMENTS(coll2, "coll2: ");
        // print merged sequence
        cout << "merged: ";
        merge(coll1.cbegin(), coll1.cend(),
            coll2.cbegin(), coll2.cend(),
            ostream_iterator<int>(cout, " "));
        cout << endl;
    }
    cout << endl;

    cout << "test 55" << endl;
    {
        vector<int> c1 = { 1, 2, 2, 4, 6, 7, 7, 9 };
        deque<int> c2 = { 2, 2, 2, 3, 6, 6, 8, 9 };
        // print source ranges
        cout << "c1: ";
        copy(c1.cbegin(), c1.cend(),
            ostream_iterator<int>(cout, " "));
        cout << endl;
        cout << "c2: ";
        copy(c2.cbegin(), c2.cend(),
            ostream_iterator<int>(cout, " "));
        cout << '\n' << endl;
        // sum the ranges by using merge()
        cout << "merge(): ";
        merge(c1.cbegin(), c1.cend(),
            c2.cbegin(), c2.cend(),
            ostream_iterator<int>(cout, " "));
        cout << endl;
        // unite the ranges by using set_union()
        cout << "set_union(): ";
        set_union(c1.cbegin(), c1.cend(),
            c2.cbegin(), c2.cend(),
            ostream_iterator<int>(cout, " "));
        cout << endl;
        // intersect the ranges by using set_intersection()
        cout << "set_intersection(): ";
        set_intersection(c1.cbegin(), c1.cend(),
            c2.cbegin(), c2.cend(),
            ostream_iterator<int>(cout, " "));
        cout << endl;
        // determine elements of first range without elements of second range
        // by using set_difference()
        cout << "set_difference(): ";
        set_difference(c1.cbegin(), c1.cend(),
            c2.cbegin(), c2.cend(),
            ostream_iterator<int>(cout, " "));
        cout << endl;
        // determine difference the ranges with set_symmetric_difference()
        cout << "set_symmetric_difference(): ";
        set_symmetric_difference(c1.cbegin(), c1.cend(),
            c2.cbegin(), c2.cend(),
            ostream_iterator<int>(cout, " "));
        cout << endl;
    }
    cout << endl;

    cout << "test 56" << endl;
    {
        list<int> coll;
        // insert two sorted sequences
        INSERT_ELEMENTS(coll, 1, 7);
        INSERT_ELEMENTS(coll, 1, 8);
        PRINT_ELEMENTS(coll);
        // find beginning of second part (element after 7)
        list<int>::iterator pos;
        pos = find(coll.begin(), coll.end(), // range
            7); // value
        ++pos;
        // merge into one sorted range
        inplace_merge(coll.begin(), pos, coll.end());
        PRINT_ELEMENTS(coll);
    }
    cout << endl;

    cout << "test 57" << endl;
    {
        vector<int> coll;
        INSERT_ELEMENTS(coll, 1, 9);
        PRINT_ELEMENTS(coll);
        // process sum of elements
        cout << "sum: "
            << accumulate(coll.cbegin(), coll.cend(), // range
                0) // initial value
            << endl;
        // process sum of elements less 100
        cout << "sum: "
            << accumulate(coll.cbegin(), coll.cend(), // range
                -100) // initial value
            << endl;
        // process product of elements
        cout << "product: "
            << accumulate(coll.cbegin(), coll.cend(), // range
                1, // initial value
                multiplies<int>()) // operation
            << endl;
        // process product of elements (use 0 as initial value)
        cout << "product: "
            << accumulate(coll.cbegin(), coll.cend(), // range
                0, // initial value
                multiplies<int>()) // operation
            << endl;
    }
    cout << endl;

    cout << "test 58" << endl;
    {
        list<int> coll;
        INSERT_ELEMENTS(coll, 1, 6);
        PRINT_ELEMENTS(coll);
        // process sum of all products
        // (0 + 1*1 + 2*2 + 3*3 + 4*4 + 5*5 + 6*6)
        cout << "inner product: "
            << inner_product(coll.cbegin(), coll.cend(), // first range
                coll.cbegin(), // second range
                0) // initial value
            << endl;
        // process sum of 1*6 ... 6*1
        // (0 + 1*6 + 2*5 + 3*4 + 4*3 + 5*2 + 6*1)
        cout << "inner reverse product: "
            << inner_product(coll.cbegin(), coll.cend(), // first range
                coll.crbegin(), // second range
                0) // initial value
            << endl;
        // process product of all sums
        // (1 * 1+1 * 2+2 * 3+3 * 4+4 * 5+5 * 6+6)
        cout << "product of sums: "
            << inner_product(coll.cbegin(), coll.cend(), // first range
                coll.cbegin(), // second range
                1, // initial value
                multiplies<int>(), // outer operation
                plus<int>()) // inner operation
            << endl;
    }
    cout << endl;

    cout << "test 59" << endl;
    {
        vector<int> coll;
        INSERT_ELEMENTS(coll, 1, 6);
        PRINT_ELEMENTS(coll);
        // print all partial sums
        partial_sum(coll.cbegin(), coll.cend(), // source range
            ostream_iterator<int>(cout, " ")); // destination
        cout << endl;
        // print all partial products
        partial_sum(coll.cbegin(), coll.cend(), // source range
            ostream_iterator<int>(cout, " "), // destination
            multiplies<int>()); // operation
        cout << endl;
    }
    cout << endl;

    cout << "test 60" << endl;
    {
        deque<int> coll;
        INSERT_ELEMENTS(coll, 1, 6);
        PRINT_ELEMENTS(coll);
        // print all differences between elements
        adjacent_difference(coll.cbegin(), coll.cend(), // source
            ostream_iterator<int>(cout, " ")); // destination
        cout << endl;
        // print all sums with the predecessors
        adjacent_difference(coll.cbegin(), coll.cend(), // source
            ostream_iterator<int>(cout, " "), // destination
            plus<int>()); // operation
        cout << endl;
        // print all products between elements
        adjacent_difference(coll.cbegin(), coll.cend(), // source
            ostream_iterator<int>(cout, " "), // destination
            multiplies<int>()); // operation
        cout << endl;
    }
    cout << endl;

    cout << "test 61" << endl;
    {
        //vector<int> coll = { 17, -3, 22, 13, 13, -9 };
        vector<int> coll = { 1, 2, 3, 4, 5, 6 };
        PRINT_ELEMENTS(coll, "coll: ");
        // convert into relative values
        adjacent_difference(coll.cbegin(), coll.cend(), // source
            coll.begin()); // destination
        PRINT_ELEMENTS(coll, "relative: ");
        // convert into absolute values
        partial_sum(coll.cbegin(), coll.cend(), // source
            coll.begin()); // destination
        PRINT_ELEMENTS(coll, "absolute: ");
    }
    cout << endl;

    return EXIT_SUCCESS;
}

#endif