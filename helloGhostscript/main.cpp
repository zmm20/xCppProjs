#include <Windows.h>
#include <iostream>
#include "GsHelper.h"
using namespace std;

int main()
{
    cout << "hello world" << endl;

    CGsHelper&  helper = CGsHelper::getInstance();
    // 注意因为加载的是release 版本的dll, 所以exe 也必须以release 方式编译
    if (!helper.loadDll(R"(C:\Program Files (x86)\gs\gs8.64\bin\gsdll32.dll)"))
    {
        cout << "error : load dll failed!" << endl;
        return -1;
    }
    
    helper.printGsRevision();
    helper.Convert("./test/test.pdf", "./test/out.jpg", 1, 1);

 
    return 0;
}