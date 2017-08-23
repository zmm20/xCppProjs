// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的
#define _AFX_NO_MFC_CONTROLS_IN_DIALOGS         // 移除对话框中的 MFC 控件支持

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include <afx.h>
#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <iostream>


#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

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