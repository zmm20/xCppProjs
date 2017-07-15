#define MAIN
#ifdef MAIN
#include <iostream>
#include <vector>
#include <string>
#include <numeric>

using namespace std;

auto getValue()
{
    return 1.4;
}

// class [[deprecated]] flaky
class flaky
{
public:
    auto getX() {
        return x;
    }
private:
    [[deprecated]] int x = 1; // [[deprecated("被废弃原因")]]
};

int main()
{
    cout << "test 1: " << endl;
    {
        auto x = getValue();
        cout << "x = " << x << endl;
    }
    cout << endl;

    cout << "test 2: " << endl;
    {
        std::vector<int> ivec = { 1, 2, 3, 4 };
        std::vector<std::string> svec = { "red", "green", "blue" };

        auto adder = [](auto op1, auto op2) { return op1 + op2; }; // 泛型Lambdas
        std::cout << "int result : " << std::accumulate(ivec.begin(), ivec.end(), 0, adder) << "\n";
        std::cout << "string result : " << std::accumulate(svec.begin(), svec.end(), std::string(""), adder) <<"\n";
    }
    cout << endl;

    cout << "test 3: " << endl;
    {
        flaky f;
        cout << "f.getX() = " << f.getX() << endl;
    }
    cout << endl;
    

    cout << "test 4: " << endl;
    {
        int val = 0b11110000;
        cout << "val = " << val << endl;
        cout << "Output mask: " << 0b1000'0001'1000'0000 << endl;
        cout << "Proposed salary: $" << 300'000.00 << endl;

    }
    cout << endl;

    return EXIT_SUCCESS;
}

#endif