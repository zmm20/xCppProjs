//#define MAIN

#ifdef MAIN


#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>


using namespace std;

int main()
{
    cout << "test 1: " << endl;
    {
        multiset<string> cities{
            "Braunschweig", "Hanover", "Frankfurt", "New York",
            "Chicago", "Toronto", "Paris", "Frankfurt"
        };
        // print each element:
        for (const auto& elem : cities) {
            cout << elem << " ";
        }
        cout << endl;
        // insert additional values:
        cities.insert({ "London", "Munich", "Hanover", "Braunschweig" });
        // print each element:
        for (const auto& elem : cities) {
            cout << elem << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "test 2: " << endl;
    {
        multimap<int, string> coll; // container for int/string values
                                    // insert some elements in arbitrary order
                                    // - a value with key 1 gets inserted twice
        coll = { { 5,"tagged" },
        { 2,"a" },
        { 1,"this" },  // 相同的key保持插入顺序
        { 4,"of" },
        { 6,"strings" },
        { 1,"is" },
        { 3,"multimap" } };
        // print all element values
        // - element member second is the value
        for (auto elem : coll) {
            cout << elem.second << ' '; // 注意 key的类型是 const int 或 const int&
        }
        cout << endl;
    }
    cout << endl;

    cout << "test 3: " << endl;
    {
        unordered_multiset<string> cities{
            "Braunschweig", "Hanover", "Frankfurt", "New York",
            "Chicago", "Toronto", "Paris", "Frankfurt"
        };
        // print each element:
        for (const auto& elem : cities) {
            cout << elem << " ";
        }
        cout << endl;
        // insert additional values:
        cities.insert({ "London", "Munich", "Hanover", "Braunschweig" });
        // print each element:
        for (const auto& elem : cities) {
            cout << elem << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "test 4: " << endl;
    {
        unordered_map<string, double> coll{ { "tim", 9.9 },
        { "struppi", 11.77 }
        };
        // square the value of each element:
        for (pair<const string, double>& elem : coll) {
            elem.second *= elem.second; // 注意 key的类型
        }
        // print each element (key and value):
        for (const auto& elem : coll) {
            cout << elem.first << ": " << elem.second << endl;
        }
    }
    cout << endl;

    cout << "test 5: " << endl;
    {
        // type of the container:
        // - unordered_map: elements are key/value pairs
        // - string: keys have type string
        // - float: values have type float
        unordered_map<string, float> coll;
        // insert some elements into the collection
        // - using the syntax of an associative array
        coll["VAT1"] = 0.16;
        coll["VAT2"] = 0.07;
        coll["Pi"] = 3.1415;
        coll["an arbitrary number"] = 4983.223;
        coll["Null"] = 0;
        // change value
        coll["VAT1"] += 0.03;
        // print difference of VAT values
        cout << "VAT difference: " << coll["VAT1"] - coll["VAT2"] << endl;

        cout << "coll count: " << coll.size() << endl;
        cout << "undefine1 = " << coll["undefine1"] << endl; // 如果直接使用coll["undefine"], 会产生一个新的元素到map中
        cout << "affter count: " << coll.size() << endl;
        //coll.at("undefine2") = 33; // runtime error
        coll.at("VAT1") = 1;
        cout << "VAT1 = " << coll.at("VAT1") << endl;
    }
    cout << endl;
    return EXIT_SUCCESS;
}
#endif