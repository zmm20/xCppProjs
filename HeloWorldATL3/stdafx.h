// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef STRICT
#define STRICT
#endif

#include "targetver.h"

#define _ATL_APARTMENT_THREADED

#define _ATL_NO_AUTOMATIC_NAMESPACE

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// ĳЩ CString ���캯��������ʽ��

#include <afxwin.h>
#include <afxext.h>
#include <afxole.h>
#include <afxodlgs.h>
#include <afxrich.h>
#include <afxhtml.h>
#include <afxcview.h>
#include <afxwinappex.h>
#include <afxframewndex.h>
#include <afxmdiframewndex.h>

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdisp.h>        // MFC �Զ�����
#endif // _AFX_NO_OLE_SUPPORT

#include <comsvcs.h>

#define ATL_NO_ASSERT_ON_DESTROY_NONEXISTENT_WINDOW

#include "resource.h"
#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>
#include <afxcontrolbars.h>


//#import "E:\Temp\vc\Office2007Lib\mso.dll" rename_namespace("Office")
#import "libid:2DF8D04C-5BFA-101B-BDE5-00AA0044DE52" rename_namespace("Office")
using namespace Office;

//#import "E:\Temp\vc\Office2007Lib\VBE6EXT.olb" rename_namespace("VBE6")
#import "libid:0002E157-0000-0000-C000-000000000046" rename_namespace("VBE6")
using namespace VBE6;

//#import "E:\Temp\vc\Office2007Lib\MSWORD.olb" rename("ExitWindows","ExitWindowsEx"),rename_namespace("MSWord")
#import "libid:00020905-0000-0000-C000-000000000046" rename("ExitWindows","ExitWindowsEx"),rename_namespace("MSWord")
using namespace MSWord;