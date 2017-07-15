//#define MAIN

#ifdef MAIN


#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <iterator>
#include <string>

// PRINT_ELEMENTS()
// - prints optional string optstr followed by
// - all elements of the collection coll
// - in one line, separated by spaces
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
int main()
{
    cout << "test 1: " << endl;
    {
        // create vector with elements from 1 to 6 in arbitrary order
        vector<int> coll = { 2, 5, 4, 1, 6, 3 };
        cout << "origin vector: ";
        std::for_each(coll.cbegin(), coll.cend(), [](const int& e) {cout << e << " "; });
        cout << endl;
        // find and print minimum and maximum elements
        auto minpos = min_element(coll.cbegin(), coll.cend());
        cout << "min: " << *minpos << endl;
        auto maxpos = max_element(coll.cbegin(), coll.cend());
        cout << "max: " << *maxpos << endl;
        // sort all elements
        sort(coll.begin(), coll.end());
        cout << "after sort: ";
        //for (const auto i : coll)
        //    cout << i << " ";
        std::for_each(coll.cbegin(), coll.cend(), [](const int& e) { cout << e << " "; });
        cout << endl;

        // find the first element with value 3
        // - no cbegin()/cend() because later we modify the elements pos3 refers to
        auto pos3 = find(coll.begin(), coll.end()// range
            , 3); // value
// reverse the order of the found element with value 3 and all following elements
        reverse(pos3, coll.end());
        // print all elements
        cout << "after reverse: ";
        for (auto elem : coll)
            cout << elem << " ";
        cout << endl;
    }
    cout << endl;

    cout << "test 2: " << endl;
    {
        vector<int> coll1{ 1, 2, 3, 4, 5 };
        vector<int> coll2{ 1, 2, 3, 4, 5, 6 };
        // coll2 范围必须大于等于coll1
        // 每个元素都对应相等才行, 如果值相同, 但顺序不同则结果不相等
        if (equal(coll1.begin(), coll1.end(), // first range
            coll2.begin())) // second range
            cout << "equal" << endl;
        else
            cout << "not equal" << endl;
    }
    cout << endl;

    cout << "test 3: " << endl;
    {
        list<int> coll1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        cout << "coll1: ";
        for (const auto e : coll1)
            cout << e << " ";
        cout << endl;

        vector<int> coll2;
        // RUNTIME ERROR:
        // - overwrites nonexisting elements in the destination
        //copy(coll1.cbegin(), coll1.cend(), // source
        //    coll2.begin()); // destination
        coll2.resize(coll1.size());
        copy(coll1.cbegin(), coll1.cend(), // source
            coll2.begin()); // destination
        cout << "coll2: ";
        for (const auto e : coll2)
            cout << e << " ";
        cout << endl;
    }
    cout << endl;

    cout << "test 4: " << endl;
    {
        list<int> coll1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        cout << "coll1: ";
        for (const auto e : coll1)
            cout << e << " ";
        cout << endl;

        // copy the elements of coll1 into coll2 by appending them
        vector<int> coll2;
        copy(coll1.cbegin(), coll1.cend(), // source
            back_inserter(coll2)); // destination
        cout << "coll2: ";
        for (const auto e : coll2)
            cout << e << " ";
        cout << endl;

        // copy the elements of coll1 into coll3 by inserting them at the front
        // - reverses the order of the elements
        deque<int> coll3;
        copy(coll1.cbegin(), coll1.cend(), // source
            front_inserter(coll3)); // destination
        cout << "coll3: ";
        for (const auto e : coll3)
            cout << e << " ";
        cout << endl;

        // copy elements of coll1 into coll4
        // - only inserter that works for associative collections
        set<int> coll4;
        copy(coll1.cbegin(), coll1.cend(), // source
            inserter(coll4, coll4.begin())); // destination
        cout << "coll4: ";
        for (const auto e : coll4)
            cout << e << " ";
        cout << endl;
    }
    cout << endl;

    cout << "test 5: " << endl;
    {
        //cout << "please input words, end until encounter end-of-file" << endl;
        //vector<string> coll;
        //// read all words from the standard input
        //// - source: all strings until end-of-file (or error)
        //// - destination: coll (inserting)
        //// ctrl + z
        //copy(istream_iterator<string>(cin), // start of source
        //    istream_iterator<string>(), // end of source
        //    back_inserter(coll)); // destination

        //// sort elements
        //sort(coll.begin(), coll.end());
        //// print all elements without duplicates
        //// - source: coll
        //// - destination: standard output (with newline between elements)
        //unique_copy(coll.cbegin(), coll.cend(), // source
        //    ostream_iterator<string>(cout, ", ")); // destination
    }
    cout << endl;

    cout << "test 6: " << endl;
    {
        vector<int> coll;
        // insert elements from 1 to 9
        for (int i = 1; i <= 9; ++i) {
            coll.push_back(i);
        }
        // print all element in reverse order
        copy(coll.crbegin(), coll.crend(), // source
            ostream_iterator<int>(cout, " ")); // destination
        cout << endl;

        // 随机访问迭代器可以通过－号计算距离
        int d = coll.end() - coll.begin();
        cout << "coll.end() - coll.begin() = " << d << endl;
        // 其它迭代器使用distence函数
        d = distance(coll.begin(), coll.end());
        cout << "distence(coll.begin(), coll.end()) = " << d << endl;
    }
    cout << endl;

    cout << "test 7: " << endl;
    {
        list<int> coll;
        // insert elements from 6 to 1 and 1 to 6
        for (int i = 1; i <= 6; ++i) {
            coll.push_front(i);
            coll.push_back(i);
        }
        // print all elements of the collection
        cout << "pre: ";
        copy(coll.cbegin(), coll.cend(), // source
            ostream_iterator<int>(cout, " ")); // destination
        cout << endl;
        // remove all elements with value 3
        remove(coll.begin(), coll.end(), // range
            3); // value
        // print all elements of the collection
        cout << "post: ";
        copy(coll.cbegin(), coll.cend(), // source
            ostream_iterator<int>(cout, " ")); // destination
        cout << endl;
    }
    cout << endl;

    cout << "test 8: " << endl;
    {
        list<int> coll;
        // insert elements from 6 to 1 and 1 to 6
        for (int i = 1; i <= 6; ++i) {
            coll.push_front(i);
            coll.push_back(i);
        }
        // print all elements of the collection
        cout << "pre: ";
        copy(coll.cbegin(), coll.cend(), // source
            ostream_iterator<int>(cout, " ")); // destination
        cout << endl;
        // remove all elements with value 3
        list<int>::iterator end = remove(coll.begin(), coll.end(),
            3);
        // print resulting elements of the collection
        copy(coll.begin(), end,
            ostream_iterator<int>(cout, " "));
        cout << endl;
        // print number of removed elements
        cout << "number of removed elements: "
            << distance(end, coll.end()) << endl;
        // remove ‘‘removed’’ elements
        coll.erase(end, coll.end());
        // print all elements of the modified collection
        copy(coll.cbegin(), coll.cend(),
            ostream_iterator<int>(cout, " "));
        cout << endl;
    }
    cout << endl;

    cout << "test 9: " << endl;
    {
        // unordered set with elements from 1 to 9
        set<int> coll = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        // print all elements of the collection
        copy(coll.cbegin(), coll.cend(),
            ostream_iterator<int>(cout, " "));
        cout << endl;
        // Remove all elements with value 3
        // - algorithm remove() does not work
        // - instead member function erase() works
        int num = coll.erase(3);
        // print number of removed elements
        cout << "number of removed elements: " << num << endl;
        // print all elements of the modified collection
        copy(coll.cbegin(), coll.cend(),
            ostream_iterator<int>(cout, " "));
        cout << endl;
        
    }
    cout << endl;

    cout << "test 10: " << endl;
    {
        std::set<int> coll1;
        std::vector<int> coll2;
        // insert elements from 1 to 9 into coll1
        for (int i = 1; i <= 9; ++i) {
            coll1.insert(i);
        }
        PRINT_ELEMENTS(coll1, "initialized: ");
        // transform each element from coll1 to coll2
        // - square transformed values
        std::transform(coll1.cbegin(), coll1.cend(), // source
            std::back_inserter(coll2), // destination
            [](const int& v){return v * v; }); // operation
        PRINT_ELEMENTS(coll2, "squared: ");
    }
    cout << endl;

    cout << "test 11: " << endl;
    {

    }
    cout << endl;

    cout << "test 12: " << endl;
    {

    }
    cout << endl;

    cout << "test 13: " << endl;
    {

    }
    cout << endl;

    cout << "test 14: " << endl;
    {

    }
    cout << endl;
    return EXIT_SUCCESS;
}
#endif