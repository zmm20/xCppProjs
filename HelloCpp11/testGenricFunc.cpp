//#define MAIN

#ifdef MAIN

#include <iostream>
#include <string>
#include <vector>



using namespace std;

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

int main()
{
    cout << "test 1: " << endl;
    {
        vector<string> coll{"hello", "world"};
        PRINT_ELEMENTS(coll, "all elements: ");
    }
    cout << endl;

    cout << "test 2: " << endl;
    {
    }
    cout << endl;

    cout << "test 3: " << endl;
    {
    }
    cout << endl;

    cout << "test 4: " << endl;
    {
    }
    cout << endl;
}
#endif