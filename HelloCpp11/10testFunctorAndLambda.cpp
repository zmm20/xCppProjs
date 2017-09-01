//#define MAIN
#ifdef MAIN

#include <iostream>
#include <cstdlib>
#include <list>
#include <algorithm>
#include <iterator>
#include <vector>
#include <functional> // binder
#include <cmath>
#include "util/print.hpp"

using namespace std;
using namespace std::placeholders;

// test 1, 2
class IntSequence {
private:
    int value;
public:
    IntSequence(int initialValue) // constructor
        : value(initialValue) {
    }
    int operator() () { // ¡®¡®function call¡¯¡¯
        return ++value;
    }
};


// test 3
// function object to process the mean value
class MeanValue {
private:
    long num; // number of elements
    long sum; // sum of all element values
public:
    // constructor
    MeanValue() : num(0), sum(0) {
    }
    // ¡®¡®function call¡¯¡¯
    // - process one more element of the sequence
    void operator() (int elem){
        ++num; // increment count
        sum += elem; // add value
    }
    // return mean value
    double value() {
        return static_cast<double>(sum) / static_cast<double>(num);
    }
};

// test 4
char myToupper(char c)
{
    std::locale loc;
    return std::use_facet<std::ctype<char> >(loc).toupper(c);
}
void incr(int& i)
{
    ++i;
}

// test 5
class Person {
private:
    string name;
public:
    Person(const string& n) : name(n) {
    }
    void print() const {
        cout << name << endl;
    }
    void print2(const string& prefix) const {
        cout << prefix << name << endl;
    }
};

// test 6:
template <typename T1, typename T2>
struct fopow
{
    T1 operator() (T1 base, T2 exp) const {
        return std::pow(base, exp);
    }
};

int main()
{
    cout << "test 1" << endl;
    {
        list<int> coll;
        // insert values from 1 to 9
        generate_n(back_inserter(coll), // start
            9, // number of elements
            IntSequence(1)); // generates values, starting with 1
        PRINT_ELEMENTS(coll);
        // replace second to last element but one with values starting at 42
        generate(next(coll.begin()), // start
            prev(coll.end()), // end
            IntSequence(42)); // generates values, starting with 42
        PRINT_ELEMENTS(coll);
    }
    cout << endl;

    cout << "test 2" << endl;
    {
        list<int> coll;
        IntSequence seq(1); // integral sequence starting with 1
        // insert values from 1 to 4
        // - pass function object by reference
        // so that it will continue with 5
        generate_n<back_insert_iterator<list<int>>, int, IntSequence&>(back_inserter(coll), // start
                4, // number of elements
                seq); // generates values
        PRINT_ELEMENTS(coll);
        // insert values from 42 to 45
        generate_n(back_inserter(coll), // start
            4, // number of elements
            IntSequence(42)); // generates values
        PRINT_ELEMENTS(coll);
        // continue with first sequence
        // - pass function object by value
        // so that it will continue with 5 again
        generate_n(back_inserter(coll), // start
            4, // number of elements
            seq); // generates values
        PRINT_ELEMENTS(coll);
        // continue with first sequence again
        generate_n(back_inserter(coll), // start
            4, // number of elements
            seq); // generates values
        PRINT_ELEMENTS(coll);
    }
    cout << endl;

    cout << "test 3" << endl;
    {
        vector<int> coll = { 1, 2, 3, 4, 5, 6, 7, 8 };
        // process and print mean value
        MeanValue mv = for_each(coll.begin(), coll.end(), // range
            MeanValue()); // operation
        cout << "mean value: " << mv.value() << endl;
    }
    cout << endl;

    cout << "test 4" << endl;
    {
        auto plus10 = std::bind(std::plus<int>(),
            std::placeholders::_1,
            10);
        std::cout << "+10: " << plus10(7) << std::endl;
        auto plus10times2 = std::bind(std::multiplies<int>(),
                std::bind(std::plus<int>(), std::placeholders::_1, 10),
                2);
        std::cout << "+10 *2: " << plus10times2(7) << std::endl;
        auto pow3 = std::bind(std::multiplies<int>(),
            std::bind(std::multiplies<int>(), std::placeholders::_1, std::placeholders::_1),
            std::placeholders::_1);
        std::cout << "x*x*x: " << pow3(7) << std::endl;
        auto inversDivide = std::bind(std::divides<double>(),
            std::placeholders::_2,
            std::placeholders::_1);
        std::cout << "invdiv: " << inversDivide(49, 7) << std::endl;

        string s("Internationalization");
        string sub("Nation");
        // search substring case insensitive
        string::iterator pos;
        pos = search(s.begin(), s.end(), // string to search in
            sub.begin(), sub.end(), // substring to search
            bind(equal_to<char>(), // compar. criterion
                bind(myToupper, _1),
                bind(myToupper, _2)));
        if (pos != s.end()) {
            cout << "\"" << sub << "\" is part of \"" << s << "\""
                << endl;
        }

        int i = 0;
        bind(incr, i)(); // increments a copy of i, no effect for i
        cout << "i = " << i << endl;
        bind(incr, ref(i))(); // increments i
        cout << "i = " << i << endl;
    }
    cout << endl;

    cout << "test 5" << endl;
    {
        vector<Person> coll = { Person("Tick"), Person("Trick"), Person("Track") };
        // call member function print() for each person
        for_each(coll.begin(), coll.end(), bind(&Person::print, _1));
        cout << endl;
        // call member function print2() with additional argument for each person
        for_each(coll.begin(), coll.end(), bind(&Person::print2, _1, "Person: "));
        cout << endl;
        // call print2() for temporary Person
        bind(&Person::print2, _1, "This is: ")(Person("nico"));
    }
    cout << endl;

    cout << "test 6" << endl;
    {
        vector<int> coll = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        // print 3 raised to the power of all elements
        transform(coll.begin(), coll.end(), // source
            ostream_iterator<float>(cout, " "), // destination
            bind(fopow<float, int>(), 3, _1)); // operation
        cout << endl;
        // print all elements raised to the power of 3
        transform(coll.begin(), coll.end(), // source
            ostream_iterator<float>(cout, " "), // destination
            bind(fopow<float, int>(), _1, 3)); // operation
        cout << endl;
    }
    cout << endl;

    cout << "test 7" << endl;
    {// ²Î¿¼test 4
        list<int> coll = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        PRINT_ELEMENTS(coll, "coll: ");
        // remove third element
        int count = 0; // call counter
        auto pos = remove_if(coll.begin(), coll.end(), // range
            [count](int) mutable { // remove criterion
            return ++count == 3;
        });
        coll.erase(pos, coll.end());
        PRINT_ELEMENTS(coll, "3rd removed: ");
    }
    cout << endl;


    return EXIT_SUCCESS;
}

#endif