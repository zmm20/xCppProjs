#define MAIN
#ifdef MAIN


#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iterator>
#include <set>
#include <deque>
#include <array>

using namespace std;
template <typename T>
void PRINT_ELEMENTS(const T& coll, const std::string& optstr = "");
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

        // l move之后 最好不要再被使用
        for (auto& node : l)
        {
            node = "1";
        }
        cout << "after overwirte,  list elements: ";
        copy(l.begin(), l.end(), ostream_iterator<string>(cout, " "));
        cout << endl;
    }
    cout << endl;

    cout << "test 2" << endl;
    {
        int intArr[]{1, 2, 3, 4, 5, 6};
        set<int> s(begin(intArr), end(intArr));
        cout << "set elements: ";
        copy(s.begin(), s.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
    }
    cout << endl;


    /*
    cout << "test 3" << endl;
    {
        std::deque<int> d{ std::istream_iterator<int>(std::cin),
            std::istream_iterator<int>() };
        //std::deque<int> d((std::istream_iterator<int>(std::cin)),
        //    (std::istream_iterator<int>()));
        // 下面定义是错误的, 因为这种情况会被编译器当做返回deque<int> 的函数声明
        //std::deque<int> c(std::istream_iterator<int>(std::cin),
        //    std::istream_iterator<int>());
        copy(d.begin(), d.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
    }
    cout << endl;
    */

    cout << "test 4" << endl;
    {
        array<int, 5> a1 = {0};
        // array<int> a2({ 1, 2, 3, 4, 5 }); //error
        //array<int, 5> a3 = ({ 0, 1, 2, 3, 4}); // erro 

        cout << "array size: " << a1.size()<< endl;

        a1.fill(2);
        copy(a1.begin(), a1.end(), ostream_iterator<int>(cout, " "));
        cout << endl;

        array<char, 40> buf;
        strcpy(&buf[0], "hello, world");
        //strcpy(buf.data(), "hello, world");
        cout << buf.data() << endl;


        // tuple 接口
        typedef array<string, 5> FiveStrs;
        FiveStrs a4= { "hello", "zmm", "how", "are", "you" };
        cout << "a4 size = " << tuple_size<FiveStrs>::value << endl;
        tuple_element<1, FiveStrs>::type firstTypeInstance = get<1>(a4);
        cout << "second element: " << firstTypeInstance << endl;

        // 完整示例:
        // create array with 10 ints
        array<int, 10> a = { 11, 22, 33, 44 };
        PRINT_ELEMENTS(a);
        // modify last two elements
        a.back() = 9999999;
        a[a.size() - 2] = 42;
        PRINT_ELEMENTS(a);
        // process sum of all elements
        cout << "sum: "
            << accumulate(a.begin(), a.end(), 0)
            << endl;
        // negate all elements
        transform(a.begin(), a.end(), // source
            a.begin(), // destination
            negate<int>()); // operation
        PRINT_ELEMENTS(a);
    }
    cout << endl;


    cout << "test 5" << endl;
    {

    }
    cout << endl;

    cout << "test 6" << endl;
    {

    }
    cout << endl;

    cout << "test 7" << endl;
    {

    }
    cout << endl;
    return 0;
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