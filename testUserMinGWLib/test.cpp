#include <iostream>
#include <string>
#include "../testMinGW_createLib/test.h"
#pragma comment(lib, "../testMinGW_createLib/libtest.lib")
using namespace std;
int main()
{
    cout << "test 1" << endl;
    {

        int a = 1;
        int b = 2;
        int r = add(a, b);
        cout << "a + b = " << r << endl;

        // 测试容器出错
        //std::string res = hello("zhou");
        //cout << res << endl;

        // 所以不同库之间, 接口应该是用标准C 接口
    }
    return 0;
}