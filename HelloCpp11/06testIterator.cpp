//#define MAIN

#ifdef MAIN

#include <iostream>
#include <array>
#include <string>
#include <vector>


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


using namespace std;
int main()
{
    cout << "test 1" << endl;
    {
        int index = 0;
        array<string, 5> strArr{"hello", "world"};
        // cbegin(), cend() 是从c++11之后才有的
        for (auto pos = strArr.cbegin(); pos != strArr.cend(); ++pos)
        {
            cout << "index = " << index << ", value = " << *pos << endl;
            ++index;
        }
    }
    cout << endl;

    cout << "test 2" << endl;
    {
        vector<int> coll1; // empty collection
        vector<int> coll2; // empty collection

        // RUNTIME ERROR:
        // - beginning is behind the end of the range
        vector<int>::iterator pos = coll1.begin();
        //reverse(++pos, coll1.end()); // 第一个参数范围错误
        // insert elements from 1 to 9 into coll1
        for (int i = 1; i <= 9; ++i) {
            coll1.push_back(i);
        }
        PRINT_ELEMENTS(coll1, "coll1 elements: ");
        
        // RUNTIME ERROR:
        // - overwriting nonexisting elements, 应该在加一句: coll2.resize(coll1.size()); 或使用插入迭代器
        //copy(coll1.cbegin(), coll1.cend(), // source
        //    coll2.begin()); // destination

        // RUNTIME ERROR:
        // - collections mistaken
        // - cbegin() and cend() refer to different collections
        //copy(coll1.cbegin(), coll2.cend(), // source
        //    coll1.end()); // destination
    }
    cout << endl;

}

#endif