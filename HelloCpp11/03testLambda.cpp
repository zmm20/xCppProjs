//#define MAIN
#ifdef MAIN

#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>
#include <functional>
#include <string>
#include <map>
using namespace std;

auto doSomething = [](int i)
{
    cout << i << ".";
};
void mySleep(decltype(doSomething))
{
    for (int i = 0; i < 3; ++i)
    {
        this_thread::sleep_for(chrono::milliseconds(500));
        doSomething(i);
    }
}

std::function<int(int, int)> returnLambda()
{
    return [](int x, int y) {
        return x * y;
    };
}

template <typename T1, typename T2>
auto add(T1 x, T2 y) -> decltype(x + y)
{
    return x + y;
}

int main()
{
    cout << "test 1" << endl;
    {
        // c++14 ����:
        auto l = [](const auto& x, const auto& y) {
            return x + y;
        };
        cout << l(1, 2) << endl;
        cout << l(1, 2.5) << endl;
        string str1 = "hello";
        string str2 = "world";
        //cout << l(str1, str2) << endl;

        // c++14 ����
        // c++11 �β��б��ǲ�����auto ��
        vector<int> vec{ 1, 2, 3, 4 };
        transform(vec.cbegin(), vec.cend(), vec.begin(), [](const auto& item) { 
            return item * 2;
        });
        for (const auto& item : vec)
            cout << item << " ";
        cout << endl;
    }
    cout << endl;

    cout << "test 2" << endl;
    {
        [] {
            cout << "hello world" << endl;
        } (); // ����ִ��
        
        // decltype() �����ñ������ҳ����ʽ����.
        map<string, float> coll{ {"a", 11}, {"b", 12} };
        for (decltype(coll)::value_type elem : coll)
        {
            cout << elem.first << " : " << elem.second << endl;
        }

        // ���ﲻ�����Զ���lambda ��
        // ��Ϊÿ��lambda �Ǹ��������ĺ�������, ÿ�������Ƕ�һ�޶���
        // mySleep����ʱ���Ѿ�ָ����lambda����������
        mySleep(doSomething);
        cout << endl;
    }
    cout << endl;


    cout << "test 3" << endl;
    {
        int x = 0;
        int y = 33;
        // ָ��y Ϊ���÷�ʽ����
        // ��: [=, &y]
        auto aaa = [x, &y] { 
            cout << "x: " << x << endl;
            cout << "y: " << y << endl;
            ++y;
        };
        x = y = 10;
        aaa();
        aaa();
        cout << "finaly y= " << y << endl;
    }
    cout << endl;


    cout << "test 4" << endl;
    {
        int id = 0;
        // passing by value �� passing by reference
        auto f = [id]() mutable {
            cout << "id: " << id << endl;
            ++id;
        };
        id = 42;
        f();
        f();
        f();
        cout << "finaly id= " << id << endl;
        /*
        �����lambda �൱������ĺ�������
        class {
        private:
            int id; // copy of outside id
        public:
            void operator() () {
                std::cout << "id: " << id << std::endl;
                ++id; // OK
            }
        };
        */
    }
    cout << endl;

    cout << "test 5" << endl;
    {
        auto lf = returnLambda();
        std::cout << lf(6, 7) << endl;
    }
    cout << endl;

    cout << "test 6" << endl;
    {
        std::cout << add(6, 7.5) << endl;
    }
    cout << endl;

    return EXIT_SUCCESS;
}
#endif