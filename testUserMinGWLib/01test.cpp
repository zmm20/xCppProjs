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

        // ������������
        // ���Բ�ͬ��֮��, �ӿ�Ӧ�����ñ�׼C �ӿ�
        //std::string res = hello("zhou");
        //cout << res << endl;

        
        /*
            C++ ������ �ڴ˵��ûᵼ�����Ӵ���

            http://blog.csdn.net/firstime_tzjz/article/details/8273603
	        �����г�: 
	        C++��dll������2���Ƽ���Ĺ����ԣ�Ҳ����˵VC��WinGW�����C++ dll���ܻ���, ��C�Ŀ���. 
        */
        //CMyClass mcls;
        //string name = "zmm";
        //mcls.hello(name.data(), name.size());
    }
    return 0;
}

#endif