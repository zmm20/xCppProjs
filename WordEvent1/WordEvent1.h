
// WordEvent1.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CWordEvent1App:
// �йش����ʵ�֣������ WordEvent1.cpp
//

class CWordEvent1App : public CWinApp
{
public:
	CWordEvent1App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CWordEvent1App theApp;