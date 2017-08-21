//#define MAIN
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
#include <unordered_set>
#include <unordered_map>
#include <memory>
using namespace std;
template <typename T>
void PRINT_ELEMENTS(const T& coll, const std::string& optstr = "");
void printLists(const string& s, const forward_list<int>& l1, const forward_list<int>& l2);

// test 9:
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


// test 14
class CMyClass
{
    std::string m_str;
public:
    CMyClass() // 使用容器的 resize 成员, 必须要声明默认构造函数
    {
        m_str = "default";
        cout << "contructor..." << m_str << endl;
    }
    CMyClass(std::string ss)
    {
        m_str = ss;
        cout << "contructor..." << m_str << endl;
    }
    ~CMyClass()
    {
        cout << "destructor..." << m_str << endl;
    }
};


// test 16
// function object to compare strings
// - allows you to set the comparison criterion at runtime
// - allows you to compare case insensitive
class RuntimeStringCmp {
public:
    // constants for the comparison criterion
    enum cmp_mode { normal, nocase };
private:
    // actual comparison mode
    const cmp_mode mode;
    // auxiliary function to compare case insensitive
    static bool nocase_compare(char c1, char c2) {
        return toupper(c1) < toupper(c2);
    }
public:
    // constructor: initializes the comparison criterion
    RuntimeStringCmp(cmp_mode m = normal) : mode(m) {
    }
    // the comparison
    bool operator() (const string& s1, const string& s2) const {
        if (mode == normal) {
            return s1<s2;
        }
        else {
            return lexicographical_compare(s1.begin(), s1.end(),
                s2.begin(), s2.end(),
                nocase_compare);
        }
    }
};
// container type:
// - map with
// - string keys
// - string values
// - the special comparison object type
typedef map<string, string, RuntimeStringCmp> StringStringMap;
// function that fills and prints such containers
void fillAndPrint(StringStringMap& coll);


// test 17
// from boost (functional/hash):
// see http://www.boost.org/doc/libs/1_35_0/doc/html/hash/combine.html
template <typename T>
inline void hash_combine(std::size_t& seed, const T& val)
{
    seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}
// auxiliary generic functions to create a hash value using a seed
template <typename T>
inline void hash_val(std::size_t& seed, const T& val)
{
    hash_combine(seed, val);
}
template <typename T, typename... Types>
inline void hash_val(std::size_t& seed,
    const T& val, const Types&... args)
{
    hash_combine(seed, val);
    hash_val(seed, args...);
}
// auxiliary generic function to create a hash value out of a heterogeneous list of arguments
template <typename... Types>
inline std::size_t hash_val(const Types&... args)
{
    std::size_t seed = 0;
    hash_val(seed, args...);
    return seed;
}
class Customer {
private:
    string fname;
    string lname;
    long no;
public:
    Customer(const string& fn, const string& ln, long n)
        : fname(fn), lname(ln), no(n) {}
    friend ostream& operator << (ostream& strm, const Customer& c) {
        return strm << "[" << c.fname << "," << c.lname << ","
            << c.no << "]";
    }
    friend class CustomerHash;
    friend class CustomerEqual;
};
class CustomerHash
{
public:
    std::size_t operator() (const Customer& c) const {
        return hash_val(c.fname, c.lname, c.no);
    }
};
class CustomerEqual
{
public:
    bool operator() (const Customer& c1, const Customer& c2) const {
        return c1.no == c2.no;
    }
};

// test 18
// generic output for pairs (map elements)
template <typename T1, typename T2>
std::ostream& operator << (std::ostream& strm, const std::pair<T1, T2>& p)
{
    return strm << "[" << p.first << "," << p.second << "]";
}
template <typename T>
void printHashTableState(const T& cont)
{
    // basic layout data:
    std::cout << "size: " << cont.size() << "\n";
    std::cout << "buckets: " << cont.bucket_count() << "\n";
    std::cout << "load factor: " << cont.load_factor() << "\n";
    std::cout << "max load factor: " << cont.max_load_factor() << "\n";
    // iterator category:
    if (typeid(typename std::iterator_traits<typename T::iterator>::iterator_category)
        == typeid(std::bidirectional_iterator_tag)) {
        std::cout << "chaining style: doubly-linked" << "\n";
    }
    else {
        std::cout << "chaining style: singly-linked" << "\n";
    }
    // elements per bucket:
    std::cout << "data: " << "\n";
    for (auto idx = 0; idx != cont.bucket_count(); ++idx) {
        std::cout << " b[" << std::setw(2) << idx << "]: ";
        for (auto pos = cont.begin(idx); pos != cont.end(idx); ++pos) {
            std::cout << *pos << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}


// test 20
class Item {
private:
    std::string name;
    float price;
public:
    Item(const std::string& n, float p = 0) : name(n), price(p) {
    }
    std::string getName() const {
        return name;
    }
    void setName(const std::string& n) {
        name = n;
    }
    float getPrice() const {
        return price;
    }
    float setPrice(float p) {
        price = p;
        return price;
    }
};
template <typename Coll>
void printItems(const std::string& msg, const Coll& coll)
{
    std::cout << msg << std::endl;
    for (const auto& elem : coll) {
        std::cout << ' ' << elem->getName() << ": "
            << elem->getPrice() << std::endl;
    }
}

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
        vector<CMyClass> coll;
        cout << "reserve 5 element..." << endl;
        coll.reserve(5);

        cout << "push_back 2 elment..." << endl;
        //coll.push_back(CMyClass("hello"));
        CMyClass obj1("hello");
        CMyClass obj2("world");
        coll.push_back(std::move(obj1));
        coll.push_back(std::move(obj2));

        cout << "resize 1 before" << endl;
        coll.resize(1);
        cout << "resize 1 completed" << endl;

        // 可见 clear 并没有释放内存
        cout << "clear before" << endl;
        coll.clear();
        cout << "clear completed" << endl;
        cout << "collection capacitiy: " << coll.capacity() << endl;
    }
    cout << endl;

    cout << "test 15" << endl;
    {
        // create multimap as string/string dictionary
        multimap<string, string> dict;
        // insert some elements in random order
        dict.insert({ { "day","Tag" },{ "strange","fremd" },
        { "car","Auto" },{ "smart","elegant" },
        { "trait","Merkmal" },{ "strange","seltsam" },
        { "smart","raffiniert" },{ "smart","klug" },
        { "clever","raffiniert" } });
        // print all elements
        cout.setf(ios::left, ios::adjustfield);
        cout << ' ' << setw(10) << "english "
            << "german " << endl;
        cout << setfill('-') << setw(20) << ""
            << setfill(' ') << endl;
        for (const auto& elem : dict) {
            cout << ' ' << setw(10) << elem.first
                << elem.second << endl;
        }
        cout << endl;
        // print all values for key "smart"
        string word("smart");
        cout << word << ": " << endl;
        for (auto pos = dict.lower_bound(word);
            pos != dict.upper_bound(word);
            ++pos) {
            cout << " " << pos->second << endl;
        }
        // print all keys for value "raffiniert"
        word = ("raffiniert");
        cout << word << ": " << endl;
        for (const auto& elem : dict) {
            if (elem.second == word) {
                cout << " " << elem.first << endl;
            }
        }
    }
    cout << endl;
    cout << "test 16" << endl;
    {
        // create a container with the default comparison criterion
        StringStringMap coll1;
        fillAndPrint(coll1);
        // create an object for case-insensitive comparisons
        RuntimeStringCmp ignorecase(RuntimeStringCmp::nocase);
        // create a container with the case-insensitive comparisons criterion
        StringStringMap coll2(ignorecase);
        fillAndPrint(coll2);
    }
    cout << endl;
    cout << "test 17" << endl;
    {
        // unordered set with own hash function and equivalence criterion
        unordered_set<Customer, CustomerHash, CustomerEqual> custset;
        custset.insert(Customer("nico", "josuttis", 42));
        PRINT_ELEMENTS(custset);
    }
    cout << endl;

    cout << "test 18" << endl;
    {
        // create and initialize an unordered set
        std::unordered_set<int> intset = { 1,2,3,5,7,11,13,17,19 };
        printHashTableState(intset);
        // insert some additional values (might cause rehashing)
        intset.insert({ -7,17,33,4 });
        printHashTableState(intset);
    }
    cout << endl;

    cout << "test 19" << endl;
    {
        // create and initialize an unordered multimap as dictionary
        std::unordered_multimap<string, string> dict = {
            { "day","Tag" },
            { "strange","fremd" },
            { "car","Auto" },
            { "smart","elegant" },
            { "trait","Merkmal" },
            { "strange","seltsam" }
        };
        printHashTableState(dict);
        // insert some additional values (might cause rehashing)
        dict.insert({ { "smart","raffiniert" },
        { "smart","klug" },
        { "clever","raffiniert" }
        });
        printHashTableState(dict);
        // modify maximum load factor (might cause rehashing)
        dict.max_load_factor(0.7);
        printHashTableState(dict);
    }
    cout << endl;

    cout << "test 20" << endl;
    {
        // two different collections sharing Items
        typedef shared_ptr<Item> ItemPtr;
        set<ItemPtr> allItems;
        deque<ItemPtr> bestsellers;
        // insert objects into the collections
        // - bestsellers are in both collections
        bestsellers = { ItemPtr(new Item("Kong Yize",20.10)),
            ItemPtr(new Item("A Midsummer Night’s Dream",14.99)),
            ItemPtr(new Item("The Maltese Falcon",9.88)) };
        allItems = { ItemPtr(new Item("Water",0.44)),
            ItemPtr(new Item("Pizza",2.22)) };
        allItems.insert(bestsellers.begin(), bestsellers.end());
        // print contents of both collections
        printItems("bestsellers:", bestsellers);
        printItems("all:", allItems);
        cout << endl;
        // double price of bestsellers
        for_each(bestsellers.begin(), bestsellers.end(),
            [](shared_ptr<Item>& elem) {
            elem->setPrice(elem->getPrice() * 2);
        });
        // replace second bestseller by first item with name "Pizza"
        bestsellers[1] = *(find_if(allItems.begin(), allItems.end(),
            [](shared_ptr<Item> elem) {
            return elem->getName() == "Pizza";
        }));
        // set price of first bestseller
        bestsellers[0]->setPrice(44.77);
        // print contents of both collections
        printItems("bestsellers:", bestsellers);
        printItems("all:", allItems);



        // 注意, vector<Item&> books; 这样申明不可行
        std::vector<std::reference_wrapper<Item>> books; // elements are references
        Item f("Faust", 12.99);
        books.push_back(f); // insert book by reference
        // print books:
        for (const auto& book : books) {
            std::cout << book.get().getName() << ": "
                << book.get().getPrice() << std::endl;
        }
        f.setPrice(9.99); // modify book outside the containers
        std::cout << books[0].get().getPrice() << std::endl; // print price of first book
                                                             // print books using type of the elements (no get() necessary):
        for (const Item& book : books) {
            std::cout << book.getName() << ": " << book.getPrice() << std::endl;
        }
    }
    cout << endl;

    cout << "test 21" << endl;
    {
        cout << "please enter some string" << endl;
        // create a string vector
        // - initialized by all words from standard input
        vector<string> coll((istream_iterator<string>(cin)),
            istream_iterator<string>());
        // sort elements
        sort(coll.begin(), coll.end());
        cout << "after sort: " << endl;
        // print all elements ignoring subsequent duplicates
        unique_copy(coll.cbegin(), coll.cend(),
            ostream_iterator<string>(cout, " "));
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

void fillAndPrint(StringStringMap& coll)
{
    // insert elements in random order
    coll["Deutschland"] = "Germany";
    coll["deutsch"] = "German";
    coll["Haken"] = "snag";
    coll["arbeiten"] = "work";
    coll["Hund"] = "dog";
    coll["gehen"] = "go";
    coll["Unternehmen"] = "enterprise";
    coll["unternehmen"] = "undertake";
    coll["gehen"] = "walk";
    coll["Bestatter"] = "undertaker";
    // print elements
    cout.setf(ios::left, ios::adjustfield);
    for (const auto& elem : coll) {
        cout << setw(15) << elem.first << " "
            << elem.second << endl;
    }
    cout << endl;
}
#endif