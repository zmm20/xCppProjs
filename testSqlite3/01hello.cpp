#define MAIN
#ifdef MAIN

#include <iostream>
#include <sqlite3.h>
using namespace std;

int main()
{
    cout << "test 1" << endl;
    {
        cout << "current sqlite version: " << sqlite3_libversion() << endl;
    }
    cout << endl;

    getchar();

    return EXIT_SUCCESS;
}

#endif