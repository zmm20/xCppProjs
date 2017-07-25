#define MAIN

#ifdef MAIN

#include <iostream>
#include <cstdlib>
#include <vector>
#include <deque>
#include <array>
#include <string>
#include <list>
#include <forward_list>
#include <numeric>

using namespace std;

void printLists(const list<int>& l1, const list<int>& l2);
template <typename T>
void PRINT_ELEMENTS(const T& coll, const std::string& optstr = "");
int main()
{
    cout << "test 1: " << endl;
    {
        vector<int> coll; // vector container for integer elements
        // append elements with values 1 to 6
        cout << "before appending data: coll capacity: " << coll.capacity() 
             << ", size : " << coll.size()
            << ", max_size : " << coll.max_size() << endl;
        for (int i = 1; i <= 6; ++i) {
            coll.push_back(i);
        }
        cout << "after appending data: coll capacity: " << coll.capacity() << endl;
        coll.erase(coll.end() - 1); // 元素的移除并不会导致vector 该项内存释放, 这就造成了内存的浪费
        cout << "after errase: coll capacity: " << coll.capacity() << endl;
        coll.shrink_to_fit();
        cout << "after shrink_to_fit: coll capacity: " << coll.capacity() << endl;
        // print all elements followed by a space
        /*for (int i = 0; i<coll.size(); ++i) {
            cout << coll[i] << ' ';
        }*/
        std::copy(coll.cbegin(), coll.cend(), ostream_iterator<int>(cout, " "));
        cout << endl;

        vector<string> strColl;
        strColl.reserve(2);// 预定2 个元素的内存空间
        cout << "before appending data: strColl capacity: " << strColl.capacity() 
            << ", size : " << strColl.size()
            << ", max_size : " << strColl.max_size() << endl;
        //strColl[0] = "hello"; // runtime error
        //strColl[1] = "world";
        strColl.push_back("hello");
        strColl.push_back("world");
        cout << "after appending data: strColl capacity: " << strColl.capacity() << endl;
        strColl.push_back("zhou");
        cout << "when exceed capacity after appendingd data: strColl capacity: " << strColl.capacity() << endl;

        std::vector<char> v; // create vector as dynamic array of chars
        v.resize(41); // make room for 41 characters (including ’\0’)
        strcpy(&v[0], "hello, world"); // copy a C-string into the vector
        printf("%s\n", &v[0]); // print contents of the vector as C-string
        printf("%s\n", v.data()); // since c++11
    }
    cout << endl;
    
    cout << "test 2: " << endl;
    {
        // create empty deque of strings
        deque<string> coll;
        // insert several elements
        coll.assign(3, string("string"));
        coll.push_back("last string");
        coll.push_front("first string");
        // print elements separated by newlines
        copy(coll.cbegin(), coll.cend(),
            ostream_iterator<string>(cout, ","));
        cout << endl;
        // remove first and last element
        coll.pop_front();
        coll.pop_back();
        // insert ‘‘another’’ into every element but the first
        for (unsigned i = 1; i < coll.size(); ++i) {
            coll[i] = "another " + coll[i];
        }
        // change size to four elements
        coll.resize(4, "resized string");
        // print elements separated by newlines
        copy(coll.cbegin(), coll.cend(),
            ostream_iterator<string>(cout, ", "));
        cout << endl;
    }
    cout << endl;


    cout << "test 3: " << endl;
    {
        // array container of 5 string elements:
        array<string, 5> coll = { "hello", "world" };
        coll.back() = "last";
        // print each element with its index on a line
        for (int i = 0; i<coll.size(); ++i) {
            cout << i << ": " << coll[i] << endl;
        }
        cout << "array.front() = " << coll.front() << endl;
        cout << "array.back() = " << coll.back() << endl;

        try {
            string str = coll.at(10); // array 只有at() 会抛出异常
        }
        catch (std::out_of_range& e) // out_of_range
        {
            cout << e.what() << endl;
        }

        std::array<char, 41> a; // create static array of 41 chars
        strcpy(a.data(), "hello, world"); // copy a C-string into the array
        cout << a.data() << endl;

        // Arrays provide the tuple interface
        typedef std::array<std::string, 5> FiveStrings;
        FiveStrings b = { "hello", "nico", "how", "are", "you" };
        cout << "tuple_size = " << std::tuple_size<FiveStrings>::value << endl; // yields 5
        std::tuple_element<1, FiveStrings>::type; // yields std::string
        cout << std::get<1>(b) << endl; // yields std::string("nico")

        array<int, 10> iArr = { 1, 2, 3, 4 };
        cout << "int array: ";
        for (auto i : iArr)
            cout << i << " ";
        cout << "sum: "
            << std::accumulate(iArr.begin(), iArr.end(), 0)
            << endl;
    }
    cout << endl;

    cout << "test 4: " << endl;
    {
        list<char> coll; // list container for character elements
        
        if (!coll.empty())
            cout << coll.front(); // runtime error => undefined behavior


        // append elements from ’a’ to ’z’
        for (char c = 'a'; c <= 'z'; ++c) {
            coll.push_back(c);
        }
        // print all elements:
        // - use range-based for loop
        for (auto elem : coll) {
            cout << elem << ' ';
        }
        cout << endl;

        coll.remove_if([](const char& i) {return i == 'z'; });

        // print all elements
        // - while there are elements
        // - print and remove the first element
        while (!coll.empty()) {
            cout << coll.front() << ' ';
            coll.pop_front();
        }
        cout << endl;


        // create two empty lists
        list<int> list1, list2;
        for (int i = 0; i<6; ++i) {
            list1.push_back(i);
            list2.push_front(i);
        }
        printLists(list1, list2);

        cout << "insert all elements of list1 before the first element with value 3 of list2"
            " find() returns an iterator to the first element with value 3: " << endl;
        list2.splice(find(list2.begin(), list2.end(), // destination position
            3),
            list1); // source list
        printLists(list1, list2);

        cout << "move first element of list2 to the end: " << endl;
        list2.splice(list2.end(), // destination position
            list2, // source list
            list2.begin()); // source position
        printLists(list1, list2);

        cout << "sort second list, assign to list1 and remove duplicates:" << endl;
        list2.sort();
        list1 = list2;
        list2.unique(); // 去除连续重复元素, 如果不连续但是重复则不去除
        printLists(list1, list2);
        
        cout << "merge both sorted lists into the first list" << endl;
        list1.merge(list2);
        printLists(list1, list2);
    }
    cout << endl;

    cout << "test 5: " << endl;
    {
        // create forward-list container for some prime numbers
        forward_list<long> coll = { 2, 3, 5, 7, 11, 13, 17 };
        // resize two times
        // - note: poor performance
        coll.resize(9);
        coll.resize(10, 99);
        // print all elements:
        for (auto elem : coll) {
            cout << elem << ' ';
        }
        cout << endl;

        // the only valid operations for return values of before_begin() are ++, == , and != .
        auto it = coll.before_begin();
        ++it;
        cout << "++it = " << *it << endl;
        coll.insert_after(coll.before_begin()// position
                        , { 77, 88, 99 }); // values
        cout << "insert_after: ";
        for (auto elem : coll) {
            cout << elem << ' ';
        }
        cout << endl;

        cout << "splice_after: " << endl;
        forward_list<int> l1 = { 1, 2, 3, 4, 5 };
        forward_list<int> l2 = { 97, 98, 99 };
        // find 3 in l1
        auto posOf3 = l1.before_begin();
        for (auto pb1 = l1.begin(); pb1 != l1.end(); ++pb1, ++posOf3) {
            if (*pb1 == 3) {
                break; // found
            }
        }
        // find 99 in l2
        auto posOf99 = l2.before_begin();
        for (auto pb2 = l2.begin(); pb2 != l2.end(); ++pb2, ++posOf99) {
            if (*pb2 == 99) {
                break; // found
            }
        }
        // splice 3 from l1 to l2 before 99
        l2.splice_after(posOf99, l1, // destination
            posOf3); // source
        PRINT_ELEMENTS(l1, "l1: ");
        PRINT_ELEMENTS(l2, "l2: ");
    }
    cout << endl;

    cout << "test 6: " << endl;
    {

    }
    cout << endl;

    cout << "test 7: " << endl;
    {

    }
    cout << endl;
    return EXIT_SUCCESS;
}

void printLists(const list<int>& l1, const list<int>& l2)
{
    cout << "list1: ";
    copy(l1.cbegin(), l1.cend(), ostream_iterator<int>(cout, " "));
    cout << endl << "list2: ";
    copy(l2.cbegin(), l2.cend(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

template <typename T>
inline void PRINT_ELEMENTS(const T& coll, const std::string& optstr)
{
    std::cout << optstr;
    for (const auto& elem : coll) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

#endif