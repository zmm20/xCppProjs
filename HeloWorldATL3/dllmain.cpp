// dllmain.cpp: DllMain ��ʵ�֡�

#include "stdafx.h"
#include "resource.h"
#include "HeloWorldATL3_i.h"
#include "dllmain.h"

CHeloWorldATL3Module _AtlModule;
HMODULE g_hModule;

class CHeloWorldATL3App : public CWinApp
{
public:

// ��д
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CHeloWorldATL3App, CWinApp)
END_MESSAGE_MAP()

CHeloWorldATL3App theApp;

BOOL CHeloWorldATL3App::InitInstance()
{
    g_hModule = theApp.m_hInstance;

    // ���Ҫ֧��activeX �ؼ�, ������������һ��
    AfxEnableControlContainer();

	return CWinApp::InitInstance();
}

int CHeloWorldATL3App::ExitInstance()
{
	return CWinApp::ExitInstance();
}
