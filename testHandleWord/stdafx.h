// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��
#define _AFX_NO_MFC_CONTROLS_IN_DIALOGS         // �Ƴ��Ի����е� MFC �ؼ�֧��

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include <afx.h>
#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <iostream>


#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

#include <atlbase.h>
#include <atlstr.h>

//#import "C:\Program Files (x86)\Common Files\Microsoft Shared\OFFICE12\MSO.DLL" raw_interfaces_only, raw_native_types, no_namespace, named_guids, auto_search
#import "libid:2DF8D04C-5BFA-101B-BDE5-00AA0044DE52" auto_rename auto_search raw_interfaces_only rename_namespace("MSOffice")
using namespace MSOffice;

//#import "E:\Temp\vc\Office2007Lib\VBE6EXT.olb" rename_namespace("VBE6")
#import "libid:0002E157-0000-0000-C000-000000000046" auto_rename auto_search raw_interfaces_only rename_namespace("VBE6")
using namespace VBE6;

// microsoft word object library
#import "libid:00020905-0000-0000-C000-000000000046" auto_rename auto_search raw_interfaces_only rename_namespace("MSWord")
using namespace MSWord;