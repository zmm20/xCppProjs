// MyWndCtl2.h : CMyWndCtl2 的声明
#pragma once
#include "resource.h"       // 主符号
#include <atlctl.h>
#include "HeloWorldATL3_i.h"
#include "_IMyWndCtl2Events_CP.h"
#include "ChildDlg.h"
#include <memory>
#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif

using namespace ATL;
extern HMODULE g_hModule;


// CMyWndCtl2
class ATL_NO_VTABLE CMyWndCtl2 :
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IMyWndCtl2, &IID_IMyWndCtl2, &LIBID_HeloWorldATL3Lib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IOleControlImpl<CMyWndCtl2>,
	public IOleObjectImpl<CMyWndCtl2>,
	public IOleInPlaceActiveObjectImpl<CMyWndCtl2>,
	public IViewObjectExImpl<CMyWndCtl2>,
	public IOleInPlaceObjectWindowlessImpl<CMyWndCtl2>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CMyWndCtl2>,
	public CProxy_IMyWndCtl2Events<CMyWndCtl2>,
	public IQuickActivateImpl<CMyWndCtl2>,
#ifndef _WIN32_WCE
	public IDataObjectImpl<CMyWndCtl2>,
#endif
	public IProvideClassInfo2Impl<&CLSID_MyWndCtl2, &__uuidof(_IMyWndCtl2Events), &LIBID_HeloWorldATL3Lib>,
	public IObjectSafetyImpl<CMyWndCtl2, INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
	public CComCoClass<CMyWndCtl2, &CLSID_MyWndCtl2>,
	public CComControl<CMyWndCtl2>
{
public:
	CContainedWindow m_ctlStatic;
    std::unique_ptr<CChildDlg> m_pDlg;

#pragma warning(push)
#pragma warning(disable: 4355) // “this”: 用于基成员初始值设定项列表


	CMyWndCtl2()
		: m_ctlStatic(_T("Static"), this, 1)
	{
		m_bWindowOnly = TRUE;
	}

#pragma warning(pop)

DECLARE_OLEMISC_STATUS(OLEMISC_RECOMPOSEONRESIZE |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_INSIDEOUT |
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST
)

DECLARE_REGISTRY_RESOURCEID(IDR_MYWNDCTL2)


BEGIN_COM_MAP(CMyWndCtl2)
	COM_INTERFACE_ENTRY(IMyWndCtl2)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IQuickActivate)
#ifndef _WIN32_WCE
	COM_INTERFACE_ENTRY(IDataObject)
#endif
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY_IID(IID_IObjectSafety, IObjectSafety)
END_COM_MAP()

BEGIN_PROP_MAP(CMyWndCtl2)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// 示例项
	// PROP_ENTRY_TYPE("属性名", dispid, clsid, vtType)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CMyWndCtl2)
	CONNECTION_POINT_ENTRY(__uuidof(_IMyWndCtl2Events))
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CMyWndCtl2)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
	CHAIN_MSG_MAP(CComControl<CMyWndCtl2>)
ALT_MSG_MAP(1)
	// 将此替换为超类 Static 的消息映射项
END_MSG_MAP()
// 处理程序原型: 
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lRes = CComControl<CMyWndCtl2>::OnSetFocus(uMsg, wParam, lParam, bHandled);
		if (m_bInPlaceActive)
		{
			if(!IsChild(::GetFocus()))
				m_ctlStatic.SetFocus();
		}
		return lRes;
	}

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		RECT rc;
		GetWindowRect(&rc);
		rc.right -= rc.left;
		rc.bottom -= rc.top;
		rc.top = rc.left = 0;
		m_ctlStatic.Create(m_hWnd, rc);
        //CreateDialog(g_hModule, MAKEINTRESOURCE(IDD_DIALOG_SHOW), m_ctlStatic.m_hWnd, ShowProc);

        m_pDlg.reset(new CChildDlg(CWnd::FromHandle(m_ctlStatic.m_hWnd)));
        m_pDlg->Create(IDD_DIALOG_SHOW, CWnd::FromHandle(m_ctlStatic.m_hWnd));
        m_pDlg->ShowWindow(SW_SHOW);
		return 0;
	}

	STDMETHOD(SetObjectRects)(LPCRECT prcPos,LPCRECT prcClip)
	{
		IOleInPlaceObjectWindowlessImpl<CMyWndCtl2>::SetObjectRects(prcPos, prcClip);
		int cx, cy;
		cx = prcPos->right - prcPos->left;
		cy = prcPos->bottom - prcPos->top;
		::SetWindowPos(m_ctlStatic.m_hWnd, NULL, 0,
			0, cx, cy, SWP_NOZORDER | SWP_NOACTIVATE);
		return S_OK;
	}

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* const arr[] =
		{
			&IID_IMyWndCtl2,
		};

		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IMyWndCtl2

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}
};

OBJECT_ENTRY_AUTO(__uuidof(MyWndCtl2), CMyWndCtl2)
