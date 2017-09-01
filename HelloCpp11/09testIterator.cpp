//#define MAIN
#ifdef MAIN

#include <iterator>
#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <vector>
#include <deque>
#include <unordered_set>
using namespace std;

template <typename T>
inline void PRINT_ELEMENTS(const T& coll, const std::string& optstr = "")
{
    std::cout << optstr;
    for (const auto& elem : coll) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}
void print(int elem);


// test 9
// general distance()
template <typename Iterator>
typename std::iterator_traits<Iterator>::difference_type distance_my(Iterator pos1, Iterator pos2)
{
    return distance(pos1, pos2, std::iterator_traits<Iterator>::iterator_category());
}
// distance() for random-access iterators
template <typename RaIterator>
typename std::iterator_traits<RaIterator>::difference_type
distance(RaIterator pos1, RaIterator pos2, std::random_access_iterator_tag)
{
    return pos2 - pos1;
}
// distance() for input, forward, and bidirectional iterators
template <typename InIterator>
typename std::iterator_traits<InIterator>::difference_type
distance(InIterator pos1, InIterator pos2, std::input_iterator_tag)
{
    typename std::iterator_traits<InIterator>::difference_type d;
    for (d = 0; pos1 != pos2; ++pos1, ++d) {
        ;
    }
    return d;
}


// test 10
// class template for insert iterator for associative and unordered containers
template <typename Container>
class asso_insert_iterator
    : public std::iterator <std::output_iterator_tag,
    typename Container::value_type>
{
protected:
    Container& container; // container in which elements are inserted
public:
    // constructor
    explicit asso_insert_iterator(Container& c) : container(c) {
    }
    // assignment operator
    // - inserts a value into the container
    asso_insert_iterator<Container>&
        operator= (const typename Container::value_type& value) {
        container.insert(value);
        return *this;
    }
    // dereferencing is a no-op that returns the iterator itself
    asso_insert_iterator<Container>& operator* () {
        return *this;
    }
    // increment operation is a no-op that returns the iterator itself
    asso_insert_iterator<Container>& operator++ () {
        return *this;
    }
    asso_insert_iterator<Container>& operator++ (int) {
        return *this;
    }
};
// convenience function to create the inserter
template <typename Container>
inline asso_insert_iterator<Container> asso_inserter(Container& c)
{
    return asso_insert_iterator<Container>(c);
}


int main()
{
    cout << "test 1" << endl;
    {
        list<int> coll;
        // insert elements from 1 to 9
        for (int i = 1; i <= 9; ++i) {
            coll.push_back(i);
        }
        list<int>::iterator pos = coll.begin();
        // print actual element
        cout << *pos << endl;
        // step three elements forward
        advance(pos, 3);
        // print actual element
        cout << *pos << endl;
        // step one element backward
        advance(pos, -1);
        // print actual element
        cout << *pos << endl;
    }
    cout << endl;
    
    cout << "test 2" << endl;
    {
        //istream_iterator<string> cinPos(cin);
        //ostream_iterator<string> coutPos(cout, " ");
        //// while input is not at the end of the file
        //// - write every third string
        //while (cinPos != istream_iterator<string>()) {
        //    // ignore the following two strings
        //    advance(cinPos, 2);
        //    // read and write the third string
        //    if (cinPos != istream_iterator<string>()) {
        //        *coutPos++ = *cinPos++;
        //    }
        //}
        //cout << endl;
    }
    cout << endl;

    cout << "test 2" << endl;
    {
        list<int> coll;
        // insert elements from 1 to 9
        for (int i = 1; i <= 9; ++i) {
            coll.push_back(i);
        }
        PRINT_ELEMENTS(coll);
        // swap first and second value
        iter_swap(coll.begin(), next(coll.begin()));
        PRINT_ELEMENTS(coll);
        // swap first and last value
        iter_swap(coll.begin(), prev(coll.end()));
        PRINT_ELEMENTS(coll);
    }
    cout << endl;

    cout << "test 3" << endl;
    {
        // create list with elements from 1 to 9
        vector<int> coll = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        // find position of element with value 5
        vector<int>::const_iterator pos;
        pos = find(coll.cbegin(), coll.cend(), 5);
        // print value to which iterator pos refers
        cout << "pos: " << *pos << endl;
        // convert iterator to reverse iterator rpos
        vector<int>::const_reverse_iterator rpos(pos);
        // print value to which reverse iterator rpos refers
        cout << "rpos: " << *rpos << endl;
    }
    cout << endl;

    cout << "test 4" << endl;
    {
        // create deque with elements from 1 to 9
        deque<int> coll = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        // find position of element with value 2
        deque<int>::const_iterator pos1;
        pos1 = find(coll.cbegin(), coll.cend(), // range
            2); // value
                // find position of element with value 7
        deque<int>::const_iterator pos2;
        pos2 = find(coll.cbegin(), coll.cend(), // range
            7); // value
                // print all elements in range [pos1,pos2)
        for_each(pos1, pos2, // range
            print); // operation
        cout << endl;
        // convert iterators to reverse iterators
        deque<int>::const_reverse_iterator rpos1(pos1);
        deque<int>::const_reverse_iterator rpos2(pos2);
        // print all elements in range [pos1,pos2) in reverse order
        for_each(rpos2, rpos1, // range
            print); // operation
        cout << endl;
    }
    cout << endl;

    cout << "test 5" << endl;
    {
        // create list with elements from 1 to 9
        list<int> coll = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        // find position of element with value 5
        list<int>::const_iterator pos;
        pos = find(coll.cbegin(), coll.cend(), // range
            5); // value
        // print value of the element
        cout << "pos: " << *pos << endl;
        // convert iterator to reverse iterator
        list<int>::const_reverse_iterator rpos(pos);
        // print value of the element to which the reverse iterator refers
        cout << "rpos: " << *rpos << endl;
        // convert reverse iterator back to normal iterator
        list<int>::const_iterator rrpos;
        rrpos = rpos.base();
        // print value of the element to which the normal iterator refers
        cout << "rrpos: " << *rrpos << endl;
    }
    cout << endl;

    cout << "test 6" << endl;
    {
        vector<int> coll;
        // create back inserter for coll
        // - inconvenient way
        back_insert_iterator<vector<int> > iter(coll);
        // insert elements with the usual iterator interface
        *iter = 1;
        iter++;
        *iter = 2;
        iter++;
        *iter = 3;
        PRINT_ELEMENTS(coll);
        // create back inserter and insert elements
        // - convenient way
        back_inserter(coll) = 44;
        back_inserter(coll) = 55;
        PRINT_ELEMENTS(coll);
        // use back inserter to append all elements again
        // - reserve enough memory to avoid reallocation
        coll.reserve(2 * coll.size());
        copy(coll.begin(), coll.end(), // source
            back_inserter(coll)); // destination
        PRINT_ELEMENTS(coll);
    }
    cout << endl;

    cout << "test 7" << endl;
    {
        // create ostream iterator for stream cout
        // - values are separated by a newline character
        ostream_iterator<int> intWriter(cout, "\n");
        // write elements with the usual iterator interface
        *intWriter = 42;
        intWriter++;
        *intWriter = 77;
        intWriter++;
        *intWriter = -5;
        // create collection with elements from 1 to 9
        vector<int> coll = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        // write all elements without any delimiter
        copy(coll.cbegin(), coll.cend(),
            ostream_iterator<int>(cout));
        cout << endl;
        // write all elements with " < " as delimiter
        copy(coll.cbegin(), coll.cend(),
            ostream_iterator<int>(cout, " < "));
        cout << endl;
    }
    cout << endl;

    cout << "test 8" << endl;
    {
        //// create istream iterator that reads integers from cin
        //istream_iterator<int> intReader(cin);
        //// create end-of-stream iterator
        //istream_iterator<int> intReaderEOF;
        //// while able to read tokens with istream iterator
        //// - write them twice
        //while (intReader != intReaderEOF) {
        //    cout << "once: " << *intReader << endl;
        //    cout << "once again: " << *intReader << endl;
        //    ++intReader;
        //}
    }
    cout << endl;

    cout << "test 9" << endl;
    {
        vector<int> coll{ 1, 2, 3, 4, 5, 6 };
        auto pos = std::find(coll.cbegin(), coll.cend(), 3);
        if (pos != coll.cend())
        {
            cout << "element 3's distance to begin is " << distance_my(coll.cbegin(), pos) << endl;
        }
    }
    cout << endl;


    cout << "test 10" << endl;
    {
        std::unordered_set<int> coll;
        // create inserter for coll
        // - inconvenient way
        asso_insert_iterator<decltype(coll)> iter(coll);
        // insert elements with the usual iterator interface
        *iter = 1;
        iter++;
        *iter = 2;
        iter++;
        *iter = 3;
        PRINT_ELEMENTS(coll);
        // create inserter for coll and insert elements
        // - convenient way
        asso_inserter(coll) = 44;
        asso_inserter(coll) = 55;
        PRINT_ELEMENTS(coll);
        // use inserter with an algorithm
        std::vector<int> vals = { 33, 67, -4, 13, 5, 2 };
        std::copy(vals.begin(), vals.end(), // source
            asso_inserter(coll)); // destination
        PRINT_ELEMENTS(coll);
    }
    cout << endl;


    return EXIT_SUCCESS;
}

void print(int elem)
{
    cout << elem << ' ';
}

#endif