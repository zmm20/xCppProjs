#include "stdafx.h"
#include "AppEventListener.h"
#include <afxtempl.h>
#include "RevCellElemnet.h"
#include "RevTextElement.h"
//Constructor.
CAppEventListener::CAppEventListener()
{
	m_refCount = 0;
}

//Destructor.
CAppEventListener::~CAppEventListener()
{}

/******************************************************************************
*   IUnknown Interfaces -- All COM objects must implement, either 
*  directly or indirectly, the IUnknown interface.
******************************************************************************/ 

/******************************************************************************
*  QueryInterface -- Determines if this component supports the 
*  requested interface, places a pointer to that interface in ppvObj if it is 
*  available, and returns S_OK. If not, sets ppvObj to NULL and returns 
*  E_NOINTERFACE.
******************************************************************************/ 
STDMETHODIMP CAppEventListener::QueryInterface(REFIID riid, void ** ppvObj)
{
	if (riid == IID_IUnknown){
		*ppvObj = static_cast<IUnknown*>(this);
	}

	else if (riid == IID_IDispatch){
		*ppvObj = static_cast<IDispatch*>(this);
	}

	else if (riid == IID_IApplicationEvents2){
		*ppvObj = static_cast<IDispatch*>(this);
	}

	else{
		*ppvObj = NULL;
		return E_NOINTERFACE;
	}

	static_cast<IUnknown*>(*ppvObj)->AddRef();
	return S_OK;
}

/******************************************************************************
*  AddRef() -- In order to allow an object to delete itself when 
*  it is no longer needed, it is necessary to maintain a count of all 
*  references to this object.  When a new reference is created, this function 
*  increments the count.
******************************************************************************/ 
STDMETHODIMP_(ULONG) CAppEventListener::AddRef()
{
	return ++m_refCount;
}

/******************************************************************************
*  Release() -- When a reference to this object is removed, this 
*  function decrements the reference count.  If the reference count is 0, 
*  this function deletes this object and returns 0.
******************************************************************************/ 
STDMETHODIMP_(ULONG) CAppEventListener::Release()
{
	m_refCount--;

	if (m_refCount == 0)
	{
		delete this;
		return 0;
	}
	return m_refCount;
}

/******************************************************************************
*   IDispatch Interface -- This interface allows this class to be used as an
*   Automation server, allowing its functions to be called by other COM
*   objects.
******************************************************************************/ 

/******************************************************************************
*   GetTypeInfoCount -- This function determines if the class supports type 
*   information interfaces or not. It places 1 in iTInfo if the class supports
*   type information and 0 if it does not.
******************************************************************************/ 
STDMETHODIMP CAppEventListener::GetTypeInfoCount(UINT *iTInfo)
{
	*iTInfo = 0;
	return S_OK;
}

/******************************************************************************
*   GetTypeInfo -- Returns the type information for the class. For classes 
*   that do not support type information, this function returns E_NOTIMPL;
******************************************************************************/ 
STDMETHODIMP CAppEventListener::GetTypeInfo(UINT iTInfo, LCID lcid, 
	ITypeInfo **ppTInfo)
{
	return E_NOTIMPL;
}

/******************************************************************************
*   GetIDsOfNames -- Takes an array of strings and returns an array of DISPIDs
*   that correspond to the methods or properties indicated. If the name is not 
*   recognized, it returns DISP_E_UNKNOWNNAME.
******************************************************************************/ 
STDMETHODIMP CAppEventListener::GetIDsOfNames(REFIID riid,  
	OLECHAR **rgszNames, 
	UINT cNames,  LCID lcid,
	DISPID *rgDispId)
{
	return E_NOTIMPL;
}

/******************************************************************************
*   Invoke -- Takes a dispid and uses it to call another of the methods of this 
*   class. Returns S_OK if the call was successful.
******************************************************************************/ 
STDMETHODIMP CAppEventListener::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid,
	WORD wFlags, DISPPARAMS* pDispParams,
	VARIANT* pVarResult,
	EXCEPINFO* pExcepInfo,
	UINT* puArgErr)
{
	//Validate arguments.
	if ((riid != IID_NULL))
		return E_INVALIDARG;

	HRESULT hr = S_OK;  // Initialize.

	switch(dispIdMember){
	case 0x00000001:  //Startup(); Word is started before this is fired.
		OutputDebugString(_T("Startup\n"));
		break;
	case 0x00000002:  //Quit();
		OutputDebugString( _T("Quit\n"));
		break;
	case 0x00000003:  //DocumentChange();
		OutputDebugString( _T("DocumentChange\n"));
		break;
	case 0x00000004:  //DocumentOpen([in] Document* Doc);
		OutputDebugString( _T("DocumentOpen\n"));
		break;
	case 0x00000005:  // No dispID
		OutputDebugString( _T("No dispID yields 00005. This is wierd!\n"));
		break;
	case 0x00000006:  // DocumentBeforeClose([in] Document* Doc, [in] VARIANT_BOOL* Cancel);
		//重点实现对文档关闭前的处理【获取修改的结果】
		//word2007发送参数是顺序发送，不需要做反转处理
		//该事件有两个参数，不足不处理
		if(pDispParams->cArgs !=2)
			return E_INVALIDARG;
		else
		{
			// The pointer to bool is always by reference.		
			// call the function
			if(pDispParams->rgvarg[0].vt & VT_BYREF)
				DocumentBeforeClose(*(pDispParams->rgvarg[0].ppdispVal),pDispParams->rgvarg[1].pboolVal);
			else
				DocumentBeforeClose(pDispParams->rgvarg[0].pdispVal,pDispParams->rgvarg[1].pboolVal);
		}		
		break;
	case 0x00000007:  // DocumentBeforePrint([in] Document* Doc, [in] VARIANT_BOOL* Cancel);
		OutputDebugString( _T("DocumentBeforePrint\n"));
		break;
	case 0x00000008:  // DocumentBeforeSave([in] Document* Doc, [in] VARIANT_BOOL* SaveAsUI, [in] VARIANT_BOOL* Cancel);
		OutputDebugString( _T("DocumentBeforeSave\n"));
		break;
	case 0x00000009:  // NewDocument([in] Document* Doc);
		OutputDebugString( _T("New Document\n"));
		break;
	case 0x0000000a:  // WindowActivate([in] Document* Doc, [in] Window* Wn);
		OutputDebugString( _T("WindowActivate\n"));
		break;

		// Next 3 illustrate passing parameters to real event handler functions.

	case 0x0000000b:  // WindowDeactivate([in] Document* Doc, [in] Window* Wn);
		// The client(in this case, Word) sends arguments to INVOKE
		// in a parameter array, stacked in reverse order, but you
		// need to send them to the called function in not-reverse order.
		if(pDispParams->cArgs!=2)
			return E_INVALIDARG;
		else
		{
			if(pDispParams->rgvarg[1].vt & VT_BYREF)
			{
				if(pDispParams->rgvarg[0].vt & VT_BYREF)
				{
					WindowDeactivate(*(pDispParams->rgvarg[1].ppunkVal),
						((Window*)*(pDispParams->rgvarg[0].ppunkVal)));
				}
				else
				{
					WindowDeactivate(*(pDispParams->rgvarg[1].ppunkVal),
						((Window*)(pDispParams->rgvarg[0].punkVal)));
				}
			}
			else
			{
				if(pDispParams->rgvarg[0].vt & VT_BYREF)
				{
					WindowDeactivate((pDispParams->rgvarg[1].punkVal),
						((Window*)*(pDispParams->rgvarg[0].ppunkVal)));
				}
				else
				{
					WindowDeactivate((pDispParams->rgvarg[1].punkVal),
						((Window*)(pDispParams->rgvarg[0].punkVal)));
				}

			}
		}
		break;
	case 0x0000000c:  // WindowSelectionChange([in] Selection* Sel);
		if (pDispParams->cArgs != 1)
			return E_INVALIDARG;
		else{
			if (pDispParams->rgvarg[0].vt & VT_BYREF)
				WindowSelectionChange( ((Selection*)*(pDispParams->rgvarg[0].ppunkVal)) );
			else
				WindowSelectionChange((Selection*) pDispParams->rgvarg[0].punkVal );
		}
		break;
	case 0x0000000d:  // WindowBeforeRightClick([in] Selection*  Sel, [in] VARIANT_BOOL* Cancel);
		if(pDispParams->cArgs !=2)
			return E_INVALIDARG;
		else
		{
			if(pDispParams->rgvarg[1].vt & VT_BYREF) // The pointer to bool is always by reference.
			{
				WindowBeforeRightClick( // call the function
					((Selection*)*(pDispParams->rgvarg[1].ppunkVal)),
					pDispParams->rgvarg[0].pboolVal);
			}
			else
			{
				WindowBeforeRightClick(  // Call the function.
					((Selection*)(pDispParams->rgvarg[1].punkVal)),
					pDispParams->rgvarg[0].pboolVal);
			}
		}
		break;
	case 0x0000000e:  // WindowBeforeDoubleClick([in] Selection*  Sel, [in] VARIANT_BOOL* Cancel);
		OutputDebugString( _T("WindowBeforeDoubleClick\n"));
		break;
	default:
		OutputDebugString( _T("An event with a dispID above 000e\n"));
		break;
	}
	return hr;
}

/************************************************************************************
*       Sample event handler functions, called from the above switch.
*       Fill each with the code needed to handle the event according to
*       the needs and design of your application.
************************************************************************************/ 
STDMETHODIMP CAppEventListener::WindowSelectionChange(Selection* Sel)
{
	OutputDebugString(_T("WindowSelectionChange\n"));
	return S_OK;
}
STDMETHODIMP CAppEventListener::WindowBeforeRightClick(Selection* Sel, VARIANT_BOOL* Cancel)
{
	OutputDebugString(_T("WindowBeforeRightClick\n"));
	return S_OK;
}
STDMETHODIMP CAppEventListener::WindowDeactivate(IUnknown* Doc, Window* Wn)
{
	OutputDebugString(_T("WindowDeactivate\n"));
	return S_OK;
}

/************************************************************************/
/* 在编辑的WORD关闭前获取修订的文字及表格数据                           */
/************************************************************************/
STDMETHODIMP CAppEventListener::DocumentBeforeClose(LPDISPATCH Doc, VARIANT_BOOL* Cancel)
{
	OutputDebugString(_T("DocumentBeforeClose\n"));
	//获取DOC对象
	_Document mDoc(Doc);
	//获取所有的修改信息
	Revisions mRevisions(mDoc.GetRevisions());
	if(mRevisions.GetCount()<=0)
	{
		//若文档没有修改则退出修订模式
		mDoc.SetTrackRevisions(FALSE);
		return S_OK;
	}
	//获取文档总的修订个数
	int count = (int)mRevisions.GetCount();

	int cellCnt = 0;
	//获取单元格修订的个数信息
	for(int i=1;i<=count;i++)
	{
		//表格数据单独处理
		//获取修订对象
		Revision temp(mRevisions.Item(i));
		//获取域对象
		Range tRange(temp.GetRange());
		//获取表格对象
		Tables tbles(tRange.GetTables());		
		if(tbles.GetCount()>=1)	
				cellCnt++;
	}
	//分配具体空间(仅文字部分）
	int textCnt = count - cellCnt;
	//创建保存文字的数组【修订类型】【内容】
	int index=0;
	CList<RevTextElement> dataColections(textCnt);
	//---------------------------------------获取修订的文本信息------------------------------//
	for(int i=1;i<=count;i++)
	{
		//获取修订对象
		Revision temp(mRevisions.Item(i));
		//获取域对象
		Range tRange(temp.GetRange());
		//获取表格对象
		Tables tbles(tRange.GetTables());		
		if(tbles.GetCount()>=1)	continue;
		//修订类型		
		RevTextElement dataTmp;
		long rType=temp.GetType();
		Range tRng(temp.GetRange());
		//修订值
		CString tValue = tRng.GetText();
		//保存数据
		dataTmp.setMtype(rType);
		dataTmp.setContent(tValue);
		//保存至集合列表中
		dataColections.AddHead(dataTmp);
		//自增1
		index++;
	}
	//--------------------------------------获取修订的表格信息-----------------------------//
	Tables mTbles(mDoc.GetTables());
	//实例化集合对象
	CList<RevCellElemnet> cellsData(cellCnt);
	if (mTbles.GetCount()>= 1)
	{		
		//依据事先定义的模板，可知需要处理几个表格的数据
		//取出处理的表格对象
		Table mTble(mTbles.Item(1));
		//获取行列信息
		//取出行对象
		Rows mRows(mTble.GetRows());
		int rows =(int) mRows.GetCount();
		//取出列对象
		Columns mClmns(mTble.GetColumns());
		int columns = mClmns.GetCount();
		//首行为列名，不处理
		for (int row = 2; row <= rows; row++)
		{
			//首列是人名，不处理
			for (int column = 2; column <=columns; column++)
			{
				Cell mCell=mTble.Cell(row,column);	//取出单元格
				Range mRng(mCell.GetRange());		//取出单元格的编辑对象
				CString cellValue =mRng.GetText();	//从编辑对象中获取内容
				//去除尾部的tab符
				cellValue = cellValue.Left(cellValue.GetLength()-2);
				//单元格空字符不保存
				if (cellValue.IsEmpty()) continue;
				//保存不为空的单元格数据
				RevCellElemnet data;
				data.setRow(row);
				data.setCol(column);
				data.setContent(cellValue);
				cellsData.AddHead(data);
			}
		}
	}
	//调用回调函数	
	this->wordMsgCallback(&dataColections,&cellsData);
	return S_OK;
}
/************************************************************************/
/* 回调函数处理                                                         */
/************************************************************************/
void CAppEventListener::setGetWordModifyMsgCallback(SendCmd wordMsgCallback)
{	
	this->wordMsgCallback=wordMsgCallback;
}
