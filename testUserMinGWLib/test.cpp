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

        // ������������
        //std::string res = hello("zhou");
        //cout << res << endl;

        // ���Բ�ͬ��֮��, �ӿ�Ӧ�����ñ�׼C �ӿ�
    }
    return 0;
}