// dllmain.cpp: DllMain ��ʵ�֡�

#include "stdafx.h"
#include "resource.h"
#include "HeloWorldATL_i.h"
#include "dllmain.h"

CHeloWorldATLModule _AtlModule;
HMODULE g_hModule;
// DLL ��ڵ�
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    hInstance;
	g_hModule = hInstance;

    // ���Ҫ֧��activeX �ؼ�, ������������һ��
    //AfxEnableControlContainer();


	return _AtlModule.DllMain(dwReason, lpReserved); 
}
