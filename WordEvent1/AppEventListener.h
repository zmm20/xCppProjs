#pragma once
#include "oaidl.h"
#include "msword.h"
#include "RevCellElemnet.h"
#include "RevTextElement.h"

//声明CallBack 类型的函数指针
typedef void(WINAPI* SendCmd)(CList<RevTextElement> *textList,CList<RevCellElemnet> *cellList);

const IID IID_IApplicationEvents2 = 
{0x000209fe,0x0000,0x0000,{0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};
// Parsed UUID for WordApplicationEvents2 dispinterface.
class CAppEventListener : public IDispatch
{
private:
	int m_refCount;		
public:
	//Constructor.
	CAppEventListener();
	//Destructor
	~CAppEventListener();

	/***** IUnknown Methods *****/ 
	STDMETHODIMP QueryInterface(REFIID riid, void ** ppvObj);
	STDMETHODIMP_(ULONG) AddRef();
	STDMETHODIMP_(ULONG) Release();

	/***** IDispatch Methods *****/ 
	STDMETHODIMP GetTypeInfoCount(UINT *iTInfo);
	STDMETHODIMP GetTypeInfo(UINT iTInfo, LCID lcid, 
		ITypeInfo **ppTInfo);
	STDMETHODIMP GetIDsOfNames(REFIID riid,  
		OLECHAR **rgszNames, 
		UINT cNames,  LCID lcid,
		DISPID *rgDispId);
	STDMETHODIMP Invoke(DISPID dispIdMember, REFIID riid, LCID lcid,
		WORD wFlags, DISPPARAMS* pDispParams,
		VARIANT* pVarResult, EXCEPINFO* pExcepInfo,
		UINT* puArgErr);

	// The following three examples are patterns for the
	//  declaration, definition, and implementation of
	//  event handler methods.
	STDMETHODIMP WindowSelectionChange(Selection* Sel);
	STDMETHODIMP WindowBeforeRightClick(Selection* Sel,
		VARIANT_BOOL* Cancel);
	STDMETHODIMP WindowDeactivate(IUnknown* Doc, 
		Window* Wn);
	// End of examples.

	SendCmd wordMsgCallback;	
	//自定义事件处理
	STDMETHODIMP DocumentBeforeClose(LPDISPATCH Doc, VARIANT_BOOL* Cancel);
public:	
	void  setGetWordModifyMsgCallback(SendCmd wordMsgCallback);
};
