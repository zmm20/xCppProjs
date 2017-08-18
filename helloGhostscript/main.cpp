#include <Windows.h>
#include <iostream>
#include "GsHelper.h"
using namespace std;

int main()
{
    cout << "hello world" << endl;

    CGsHelper&  helper = CGsHelper::getInstance();
    // ע����Ϊ���ص���release �汾��dll, ����exe Ҳ������release ��ʽ����
    if (!helper.loadDll(R"(C:\Program Files (x86)\gs\gs8.64\bin\gsdll32.dll)"))
    {
        cout << "error : load dll failed!" << endl;
        return -1;
    }
    
    helper.printGsRevision();
    helper.Convert("./test/test.pdf", "./test/out.jpg", 1, 1);

 
    return 0;
}