// Test.cpp : CTest µÄÊµÏÖ
#include "stdafx.h"
#include "Test.h"
#include <fstream>

// CTest

using namespace std;
STDMETHODIMP CTest::test1()
{
    
    ofstream out(R"__(C:\Users\zmm\AppData\Local\Temp\log1.txt)__");
    out << "hello" << endl;

    return S_OK;
}
