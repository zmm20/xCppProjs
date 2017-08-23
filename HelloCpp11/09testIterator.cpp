#define MAIN
#ifdef MAIN

#include <iterator>
#include <iostream>
#include <list>
#include <algorithm>
#include <string>
using namespace std;

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
        istream_iterator<string> cinPos(cin);
        ostream_iterator<string> coutPos(cout, " ");
        // while input is not at the end of the file
        // - write every third string
        while (cinPos != istream_iterator<string>()) {
            // ignore the following two strings
            advance(cinPos, 2);
            // read and write the third string
            if (cinPos != istream_iterator<string>()) {
                *coutPos++ = *cinPos++;
            }
        }
        cout << endl;
    }
    cout << endl;


    return EXIT_SUCCESS;
}
#endif