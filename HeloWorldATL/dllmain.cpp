// dllmain.cpp: DllMain 的实现。

#include "stdafx.h"
#include "resource.h"
#include "HeloWorldATL_i.h"
#include "dllmain.h"

CHeloWorldATLModule _AtlModule;
HMODULE g_hModule;
// DLL 入口点
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    hInstance;
	g_hModule = hInstance;

    // 如果要支持activeX 控件, 则必须调用下面一句
    //AfxEnableControlContainer();


	return _AtlModule.DllMain(dwReason, lpReserved); 
}
