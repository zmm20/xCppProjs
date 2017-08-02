//#define MAIN
#ifdef MAIN

#include <iostream>
#include <string>
#include "../testMinGW_createLib/test.h"
#pragma comment(lib, "../testMinGW_createLib/libtest.dll.a")
using namespace std;
using namespace MyPoppler;

int main()
{
    cout << "test 1" << endl;
    {

        int a = 1;
        int b = 2;
        int r = add(a, b);
        cout << "a + b = " << r << endl;

        // 测试容器出错
        // 所以不同库之间, 接口应该是用标准C 接口
        //std::string res = hello("zhou");
        //cout << res << endl;

        
        /*
            C++ 导出类 在此调用会导致连接错误

            http://blog.csdn.net/firstime_tzjz/article/details/8273603
	        文章中称: 
	        C++的dll不具有2进制级别的共享性，也就是说VC和WinGW编译的C++ dll不能混用, 而C的可以. 
        */
        //CMyClass mcls;
        //string name = "zmm";
        //mcls.hello(name.data(), name.size());
    }
    return 0;
}

#endif