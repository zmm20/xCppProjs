#define MAIN
#ifdef MAIN


#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
#include <set>

using namespace std;
int main()
{
    cout << "test 1" << endl;
    {
        list<string> l = {"11", "22", "33"};

        vector<string> v(make_move_iterator(l.begin()), make_move_iterator(l.end()));

        cout << "vector size = " << v.size() << ", elements: ";
        copy(v.begin(), v.end(), ostream_iterator<string>(cout, " "));
        cout << endl;

        cout << "list size = " << l.size() << ", elements: ";
        copy(l.begin(), l.end(), ostream_iterator<string>(cout, " "));
        cout << endl;

        for (auto& node : l)
        {
            node = "1";
        }
        cout << "after overwirte,  list elements: ";
        copy(l.begin(), l.end(), ostream_iterator<string>(cout, " "));
        cout << endl;
    }
    cout << endl;

    cout << "test 1" << endl;
    {
        int intArr[]{1, 2, 3, 4, 5, 6};
        set<int> s(begin(intArr), end(intArr));
        cout << "set elements: ";
        copy(s.begin(), s.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
    }
    cout << endl;

    return 0;
}
#endif