//#define MAIN
#ifdef MAIN

#include <iostream>
#include <memory>
#include <functional>
#include <string>

using namespace std;


template <typename T>
void bad_print(std::auto_ptr<T> p) // p gets ownership of passed argument
{
    // does p own an object ?
    if (p.get() == NULL) {
        std::cout << "NULL";
    }
    else {
        std::cout << *p;
    }
} // Oops, exiting deletes the object to which p refers


int main()
{
    std::auto_ptr<int> p(new int);
    *p = 42; // change value to which p refers
    bad_print(p); // Oops, deletes the memory to which p refers
    *p = 18; // RUNTIME ERROR
}

#endif