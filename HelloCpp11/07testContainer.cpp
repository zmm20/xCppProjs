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
#include <forward_list>
#include <set>
#include <map>
#include <complex>
#include <iomanip>
using namespace std;
template <typename T>
void PRINT_ELEMENTS(const T& coll, const std::string& optstr = "");
void printLists(const string& s, const forward_list<int>& l1, const forward_list<int>& l2);

// type for runtime sorting criterion
class RuntimeCmp {
public:
    enum cmp_mode { normal, reverse };

private:
    cmp_mode mode;
public:
    // constructor for sorting criterion
    // - default criterion uses value normal
    RuntimeCmp(cmp_mode m = normal) : mode(m) {
    }
    // comparison of elements
    // - member function for any element type
    template <typename T>
    bool operator() (const T& t1, const T& t2) const {
        return mode == normal ? t1<t2 : t2<t1;
    }
    // comparison of sorting criteria
    bool operator== (const RuntimeCmp& rc) const {
        return mode == rc.mode;
    }
};


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
        // 预留5 个内存空间测试
        // 从以下2 个方法的输出可以判断出 method 2 效率更高, 因为没有元素初始化动作
        // method 1:
        vector<int> v0(5);
        cout << "vector0 elements: ";
        for (const auto& e : v0)
            cout << e << " ";
        cout << endl;

        // method 2:
        vector<int> v1;
        // 一旦实际元素个数超过 v1.capacity(), 则就会重新分配内存
        cout << "refore reserve, v1 capacity() = " << v1.capacity() << endl;
        v1.reserve(5);
        cout << "after, v1 capacity() = " << v1.capacity() << endl;

        cout << "vector1 elements: ";
        for (const auto& e : v1)
            cout << e << " ";
        cout << endl;
    }
    cout << endl;

    cout << "test 6" << endl;
    {
        forward_list<int> list = { 1, 2, 3, 4, 5, 97, 98, 99 };

        // method1:
        //auto posBefore = list.before_begin();
        //for (auto pos = list.begin(); pos != list.end(); ++pos, ++posBefore) {
        //    if (*pos % 2 == 0) {
        //        break; // element found
        //    }
        //}

        // method 2:
        auto posBefore = list.before_begin();
        // 自 c++11 提供了next
        for (; next(posBefore) != list.end(); ++posBefore) {
            if (*next(posBefore) % 2 == 0) {
                break; // element found
            }
        }


        // and insert a new element in front of the first even element
        list.insert_after(posBefore, 42);
        PRINT_ELEMENTS(list);


        // create two forward lists
        forward_list<int> list1 = { 1, 2, 3, 4 };
        forward_list<int> list2 = { 77, 88, 99 };
        printLists("initial:", list1, list2);
        // insert six new element at the beginning of list2
        list2.insert_after(list2.before_begin(), 99);
        list2.push_front(10);
        list2.insert_after(list2.before_begin(), { 10,11,12,13 });
        printLists("6 new elems:", list1, list2);
        // insert all elements of list2 at the beginning of list1
        list1.insert_after(list1.before_begin(),
            list2.begin(), list2.end());
        printLists("list2 into list1:", list1, list2);
        // delete second element and elements after element with value 99
        list2.erase_after(list2.begin());
        list2.erase_after(find(list2.begin(), list2.end(),
            99),
            list2.end());
        printLists("delete 2nd and after 99:", list1, list2);
        // sort list1, assign it to list2, and remove duplicates
        list1.sort();
        list2 = list1;
        list2.unique();
        printLists("sorted and unique:", list1, list2);
        // merge both sorted lists into list1
        list1.merge(list2);
        printLists("merged:", list1, list2);

    }
    cout << endl;

    cout << "test 7" << endl;
    {
        set<int> c({1, 2, 4, 5, 6});
        cout << "lower_bound(3): " << *c.lower_bound(3) << endl;
        cout << "upper_bound(3): " << *c.upper_bound(3) << endl;
        cout << "equal_range(3): " << *c.equal_range(3).first << " "
            << *c.equal_range(3).second << endl;
        cout << endl;
        cout << "lower_bound(5): " << *c.lower_bound(5) << endl;
        cout << "upper_bound(5): " << *c.upper_bound(5) << endl;
        cout << "equal_range(5): " << *c.equal_range(5).first << " "
            << *c.equal_range(5).second << endl;
    }
    cout << endl;

    cout << "test 8" << endl;
    {
        std::set<double> c({1.1, 2.2, 4.4, 3.3});
        // insert value and process return value
        double value = 3.3;
        auto status = c.insert(value);
        if (status.second) {
            std::cout << value << " inserted as element " << endl;
        }
        else {
            std::cout << value << " already exists as element " << endl;
        }
        std::cout << "distence = " << std::distance(c.begin(), status.first) + 1 << std::endl;

        // 可见 set 与 multiset 的 insert 返回值类型是不同的
        std::multiset<int> d;
        auto it = d.insert(4);
        cout << "multiset new element: " << *it << endl;

    }
    cout << endl;

    cout << "test 9" << endl;
    {
        // type of a set that uses this sorting criterion
        typedef set<int, RuntimeCmp> IntSet;

        // create, fill, and print set with normal element order
        // - uses default sorting criterion
        IntSet coll1 = { 4, 7, 5, 1, 6, 2, 5 };
        PRINT_ELEMENTS(coll1, "coll1: ");
        // create sorting criterion with reverse element order
        RuntimeCmp reverse_order(RuntimeCmp::reverse);
        // create, fill, and print set with reverse element order
        IntSet coll2(reverse_order);
        coll2 = { 4, 7, 5, 1, 6, 2, 5 };
        PRINT_ELEMENTS(coll2, "coll2: ");

        if (coll1.value_comp() == coll2.value_comp()) {
            cout << "coll1 and coll2 have the same sorting criterion"
                << endl;
        }
        else {
            cout << "coll1 and coll2 have a different sorting criterion"
                << endl;
        }
        // assign elements AND sorting criterion
        // 注意赋值操作要求2 容器排序类型相同(比较准则可能不同)
        coll1 = coll2;
        coll1.insert(3);
        PRINT_ELEMENTS(coll1, "coll1: ");
        // just to make sure...
        if (coll1.value_comp() == coll2.value_comp()) {
            cout << "coll1 and coll2 have the same sorting criterion"
                << endl;
        }
        else {
            cout << "coll1 and coll2 have a different sorting criterion"
                << endl;
        }
    }
    cout << endl;
    cout << "test 10" << endl;
    {
        typedef std::map<std::string, float> MyMap_T;
        MyMap_T coll{ {"zmm", 11}, {"xh", 12} };

        // method 1:
        // add 10 to the value of each element:
        std::for_each(coll.begin(), coll.end(),
            [](std::pair<const std::string, float>& elem) {
            elem.second += 10;
        });

        // method 2:
        std::for_each(coll.begin(), coll.end(),
            [](MyMap_T::value_type& elem) {
            elem.second += 10;
        });

        // method 3:
        std::for_each(coll.begin(), coll.end(),
            [](decltype(coll)::value_type& elem) {
            elem.second += 10;
        });

        for (const auto& item : coll)
            std::cout << "key: " << item.first << ", value: " << item.second << std::endl;

    }
    cout << endl;

    cout << "test 11" << endl;
    {
        map<string, std::complex<float>> m;
        m.emplace(std::piecewise_construct, make_tuple("hello"), make_tuple(3.4, 7.8));
        m.emplace(std::piecewise_construct, make_tuple("world"), make_tuple(4.4, 7.7));
        cout << "map size: " << m.size() << endl;
        for (const auto& item : m)
            cout << item.first << " : " << item.second << endl;
    }
    cout << endl;

    cout << "test 12, erase 用法" << endl;
    {
        float value = 1.1;
        {
            // c++11
            std::map<std::string, float> coll{ { "hello", 1.1 },{ "world", 2.2 } };
            for (auto pos = coll.begin(); pos != coll.end(); ) {
                if (pos->second == value) {
                    pos = coll.erase(pos); // possible only since C++11
                }
                else {
                    ++pos;
                }
            }
        }
        {
            // c++11 之前
            typedef std::map<std::string, float> StringFloatMap;
            StringFloatMap coll{ { "hello", 1.1 },{ "world", 2.2 } };
            StringFloatMap::iterator pos;
            // remove all elements having a certain value
            for (pos = coll.begin(); pos != coll.end(); ) {
                if (pos->second == value) {
                    // Note that pos++ increments pos so that it refers to the next element but yields a copy of its original value.
                    coll.erase(pos++); // 
                }
                else {
                    ++pos;
                }
            }
        }        
    }
    cout << endl;

    cout << "test 13" << endl;
    {
        // create map / associative array
        // - keys are strings
        // - values are floats
        typedef map<string, float> StringFloatMap;
        StringFloatMap stocks; // create empty container
                               // insert some elements
        stocks["BASF"] = 369.50;
        stocks["VW"] = 413.50;
        stocks["Daimler"] = 819.00;
        stocks["BMW"] = 834.00;
        stocks["Siemens"] = 842.20;
        stocks["123456789012"] = 0;
        // print all elements
        StringFloatMap::iterator pos;
        cout << ios::left; // left-adjust values
        for (pos = stocks.begin(); pos != stocks.end(); ++pos) {
            cout << "stock: " << setw(12) << pos->first
                << "price: " << pos->second << endl;
        }
        cout << endl;
        // boom (all prices doubled)
        for (pos = stocks.begin(); pos != stocks.end(); ++pos) {
            pos->second *= 2;
        }
        // print all elements
        for (pos = stocks.begin(); pos != stocks.end(); ++pos) {
            cout << "stock: " << setw(12) << pos->first
                << "price: " << pos->second << endl;
        }
        cout << endl;
        // rename key from "VW" to "Volkswagen"
        // - provided only by exchanging element
        stocks["Volkswagen"] = stocks["VW"];
        stocks.erase("VW");
        // print all elements
        for (pos = stocks.begin(); pos != stocks.end(); ++pos) {
            cout << "stock: " << setw(12) << pos->first
                << "price: " << pos->second << endl;
        }
    }
    cout << endl;

    cout << "test 14" << endl;
    {
    }
    cout << endl;

    cout << "test 15" << endl;
    {
    }
    cout << endl;
    cout << "test 16" << endl;
    {
    }
    cout << endl;
    cout << "test 17" << endl;
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

void printLists(const string& s, const forward_list<int>& l1,
    const forward_list<int>& l2)
{
    cout << s << endl;
    cout << " list1: ";
    copy(l1.cbegin(), l1.cend(), ostream_iterator<int>(cout, " "));
    cout << endl << " list2: ";
    copy(l2.cbegin(), l2.cend(), ostream_iterator<int>(cout, " "));
    cout << endl;
}
#endif