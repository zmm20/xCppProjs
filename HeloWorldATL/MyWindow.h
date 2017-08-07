// MyWindow.h : CMyWindow ������
#pragma once
#include "resource.h"       // ������
#include <atlctl.h>
#include "HeloWorldATL_i.h"
#include "_IMyWindowEvents_CP.h"
#include "ChildDlg.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif

using namespace ATL;

extern HMODULE g_hModule;

// CMyWindow
class ATL_NO_VTABLE CMyWindow :
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IMyWindow, &IID_IMyWindow, &LIBID_HeloWorldATLLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IOleControlImpl<CMyWindow>,
	public IOleObjectImpl<CMyWindow>,
	public IOleInPlaceActiveObjectImpl<CMyWindow>,
	public IViewObjectExImpl<CMyWindow>,
	public IOleInPlaceObjectWindowlessImpl<CMyWindow>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CMyWindow>,
	public CProxy_IMyWindowEvents<CMyWindow>,
	public IQuickActivateImpl<CMyWindow>,
#ifndef _WIN32_WCE
	public IDataObjectImpl<CMyWindow>,
#endif
	public IProvideClassInfo2Impl<&CLSID_MyWindow, &__uuidof(_IMyWindowEvents), &LIBID_HeloWorldATLLib>,
	public IObjectSafetyImpl<CMyWindow, INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
	public CComCoClass<CMyWindow, &CLSID_MyWindow>,
	public CComControl<CMyWindow>,
    public IPersistPropertyBagImpl<CMyWindow>
{
public:
	CContainedWindow m_ctlStatic;

#pragma warning(push)
#pragma warning(disable: 4355) // ��this��: ���ڻ���Ա��ʼֵ�趨���б�


	CMyWindow()
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

DECLARE_REGISTRY_RESOURCEID(IDR_MYWINDOW)


BEGIN_COM_MAP(CMyWindow)
	COM_INTERFACE_ENTRY(IMyWindow)
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
    COM_INTERFACE_ENTRY(IPersistPropertyBag)
END_COM_MAP()

BEGIN_PROP_MAP(CMyWindow)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// ʾ����
	// PROP_ENTRY_TYPE("������", dispid, clsid, vtType)
	// PROP_PAGE(CLSID_StockColorPage)
    PROP_ENTRY_TYPE("Port", 1, CLSID_MyWindow, VT_UI2)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CMyWindow)
	CONNECTION_POINT_ENTRY(__uuidof(_IMyWindowEvents))
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CMyWindow)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
	CHAIN_MSG_MAP(CComControl<CMyWindow>)
ALT_MSG_MAP(1)
	// �����滻Ϊ���� Static ����Ϣӳ����
END_MSG_MAP()
// �������ԭ��: 
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lRes = CComControl<CMyWindow>::OnSetFocus(uMsg, wParam, lParam, bHandled);
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
        CreateDialog(g_hModule, MAKEINTRESOURCE(IDD_DIALOG_SHOW), m_ctlStatic.m_hWnd, ShowProc);
		return 0;
	}

	STDMETHOD(SetObjectRects)(LPCRECT prcPos,LPCRECT prcClip)
	{
		IOleInPlaceObjectWindowlessImpl<CMyWindow>::SetObjectRects(prcPos, prcClip);
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
			&IID_IMyWindow,
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

// IMyWindow

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}
    STDMETHOD(get_Port)(USHORT* pVal);
    STDMETHOD(put_Port)(USHORT newVal);

private:
    USHORT m_Port;
};

OBJECT_ENTRY_AUTO(__uuidof(MyWindow), CMyWindow)
