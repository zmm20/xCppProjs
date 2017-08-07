// dllmain.cpp: DllMain 的实现。

#include "stdafx.h"
#include "resource.h"
#include "HeloWorldATL2_i.h"
#include "dllmain.h"

CHeloWorldATL2Module _AtlModule;

class CHeloWorldATL2App : public CWinApp
{
public:

// 重写
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CHeloWorldATL2App, CWinApp)
END_MESSAGE_MAP()

CHeloWorldATL2App theApp;

BOOL CHeloWorldATL2App::InitInstance()
{
	return CWinApp::InitInstance();
}

int CHeloWorldATL2App::ExitInstance()
{
	return CWinApp::ExitInstance();
}
