#include <Windows.h>
#include <iostream>
#include "GsHelper.h"
#include <gs/gsdll.h>
using namespace std;

int main()
{
    cout << "hello world" << endl;

    CGsHelper&  helper = CGsHelper::getInstance();
    if (!helper.loadDll(R"(C:\Program Files (x86)\gs\gs8.64\bin\gsdll32.dll)"))
    {
        cout << "error : load dll failed!" << endl;
        return -1;
    }
    
    helper.printGsRevision();
    helper.Convert("./test/test.pdf", "./test/out.pdf", 1, 1, "jpg", 800, 100);

    return 0;
}