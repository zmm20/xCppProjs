#pragma once

// 计算机生成了由 Microsoft Visual C++ 创建的 IDispatch 包装器类

// 注意:  不要修改此文件的内容。  如果此类由
//  Microsoft Visual C++ 重新生成，您的修改将被覆盖。

/////////////////////////////////////////////////////////////////////////////
// CFramercontrol1 包装器类

class CFramercontrol1 : public CWnd
{
protected:
	DECLARE_DYNCREATE(CFramercontrol1)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x460182, 0x9E5E, 0x11D5, { 0xB7, 0xC8, 0xB8, 0x26, 0x90, 0x41, 0xDD, 0x57 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// 特性
public:
enum
{
    dsoBorderNone = 0,
    dsoBorderFlat = 1,
    dsoBorder3D = 2,
    dsoBorder3DThin = 3
}dsoBorderStyle;
enum
{
    dsoDialogNew = 0,
    dsoDialogOpen = 1,
    dsoDialogSave = 2,
    dsoDialogSaveCopy = 3,
    dsoDialogPrint = 4,
    dsoDialogPageSetup = 5,
    dsoDialogProperties = 6
}dsoShowDialogType;
enum
{
    dsoFileNew = 0,
    dsoFileOpen = 1,
    dsoFileClose = 2,
    dsoFileSave = 3,
    dsoFileSaveAs = 4,
    dsoFilePrint = 5,
    dsoFilePageSetup = 6,
    dsoFileProperties = 7,
    dsoFilePrintPreview = 8
}dsoFileCommandType;


// 操作
public:

// _FramerControl

// Functions
//

	void Activate()
	{
		InvokeHelper(0x10001, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH get_ActiveDocument()
	{
		LPDISPATCH result;
		InvokeHelper(0x10002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void CreateNew(LPCTSTR ProgIdOrTemplate)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x10003, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ProgIdOrTemplate);
	}
	void Open(VARIANT Document, VARIANT ReadOnly, VARIANT ProgId, VARIANT WebUsername, VARIANT WebPassword)
	{
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x10004, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &Document, &ReadOnly, &ProgId, &WebUsername, &WebPassword);
	}
	void Save(VARIANT SaveAsDocument, VARIANT OverwriteExisting, VARIANT WebUsername, VARIANT WebPassword)
	{
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x10005, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &SaveAsDocument, &OverwriteExisting, &WebUsername, &WebPassword);
	}
	void _PrintOutOld(VARIANT PromptToSelectPrinter)
	{
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x10008, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &PromptToSelectPrinter);
	}
	void Close()
	{
		InvokeHelper(0x10009, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void put_Caption(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_Caption()
	{
		CString result;
		InvokeHelper(0x1000a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_Titlebar(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x1000b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_Titlebar()
	{
		BOOL result;
		InvokeHelper(0x1000b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_Toolbars(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x1000c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_Toolbars()
	{
		BOOL result;
		InvokeHelper(0x1000c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_ModalState(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x1000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_ModalState()
	{
		BOOL result;
		InvokeHelper(0x1000d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void ShowDialog(long DlgType)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1000e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DlgType);
	}
	void put_EnableFileCommand(long Item, BOOL newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BOOL ;
		InvokeHelper(0x1000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, Item, newValue);
	}
	BOOL get_EnableFileCommand(long Item)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1000f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, Item);
		return result;
	}
	void put_BorderStyle(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(DISPID_BORDERSTYLE, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_BorderStyle()
	{
		long result;
		InvokeHelper(DISPID_BORDERSTYLE, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_BorderColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(DISPID_BORDERCOLOR, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	unsigned long get_BorderColor()
	{
		unsigned long result;
		InvokeHelper(DISPID_BORDERCOLOR, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, NULL);
		return result;
	}
	void put_BackColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(DISPID_BACKCOLOR, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	unsigned long get_BackColor()
	{
		unsigned long result;
		InvokeHelper(DISPID_BACKCOLOR, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, NULL);
		return result;
	}
	void put_ForeColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(DISPID_FORECOLOR, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	unsigned long get_ForeColor()
	{
		unsigned long result;
		InvokeHelper(DISPID_FORECOLOR, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, NULL);
		return result;
	}
	void put_TitlebarColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x10010, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	unsigned long get_TitlebarColor()
	{
		unsigned long result;
		InvokeHelper(0x10010, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, NULL);
		return result;
	}
	void put_TitlebarTextColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x10011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	unsigned long get_TitlebarTextColor()
	{
		unsigned long result;
		InvokeHelper(0x10011, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, NULL);
		return result;
	}
	void ExecOleCommand(long OLECMDID, VARIANT Options, VARIANT * vInParam, VARIANT * vInOutParam)
	{
		static BYTE parms[] = VTS_I4 VTS_VARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x10012, DISPATCH_METHOD, VT_EMPTY, NULL, parms, OLECMDID, &Options, vInParam, vInOutParam);
	}
	void put_Menubar(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x10013, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_Menubar()
	{
		BOOL result;
		InvokeHelper(0x10013, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_HostName(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x10014, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_HostName()
	{
		CString result;
		InvokeHelper(0x10014, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString get_DocumentFullName()
	{
		CString result;
		InvokeHelper(0x10015, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void PrintOut(VARIANT PromptUser, VARIANT PrinterName, VARIANT Copies, VARIANT FromPage, VARIANT ToPage, VARIANT OutputFile)
	{
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x10016, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &PromptUser, &PrinterName, &Copies, &FromPage, &ToPage, &OutputFile);
	}
	void PrintPreview()
	{
		InvokeHelper(0x10017, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void PrintPreviewExit()
	{
		InvokeHelper(0x10018, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	BOOL get_IsReadOnly()
	{
		BOOL result;
		InvokeHelper(0x10019, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL get_IsDirty()
	{
		BOOL result;
		InvokeHelper(0x1001a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL HttpInit()
	{
		BOOL result;
		InvokeHelper(0x1001b, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL HttpAddPostString(LPCTSTR strName, LPCTSTR strValue)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x1001c, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, strName, strValue);
		return result;
	}
	CString HttpPost(LPCTSTR bstr)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1001d, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, bstr);
		return result;
	}
	BOOL SetTrackRevisions(long vbool)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1001f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, vbool);
		return result;
	}
	BOOL SetCurrUserName(LPCTSTR strCurrUserName)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x10020, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, strCurrUserName);
		return result;
	}
	BOOL HttpAddPostCurrFile(LPCTSTR strFileID, LPCTSTR strFileName)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x10021, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, strFileID, strFileName);
		return result;
	}
	BOOL SetCurrTime(LPCTSTR strValue)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x10022, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, strValue);
		return result;
	}
	LPDISPATCH get_GetApplication()
	{
		LPDISPATCH result;
		InvokeHelper(0x10023, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	BOOL SetFieldValue(LPCTSTR strFieldName, LPCTSTR strValue, LPCTSTR strCmdOrSheetName)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x10024, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, strFieldName, strValue, strCmdOrSheetName);
		return result;
	}
	CString GetFieldValue(LPCTSTR strFieldName, LPCTSTR strCmdOrSheetName)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x10025, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strFieldName, strCmdOrSheetName);
		return result;
	}
	BOOL SetMenuDisplay(long lMenuFlag)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x10026, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, lMenuFlag);
		return result;
	}
	BOOL ProtectDoc(long lProOrUn, long lProType, LPCTSTR strProPWD)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BSTR ;
		InvokeHelper(0x10027, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, lProOrUn, lProType, strProPWD);
		return result;
	}
	BOOL ShowRevisions(long nNewValue)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x10028, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, nNewValue);
		return result;
	}
	BOOL InSertFile(LPCTSTR strFieldPath, long lPos)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x10029, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, strFieldPath, lPos);
		return result;
	}
	long LoadOriginalFile(VARIANT strFieldPath, VARIANT strFileType)
	{
		long result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x10030, DISPATCH_METHOD, VT_I4, (void*)&result, parms, &strFieldPath, &strFileType);
		return result;
	}
	long SaveAs(VARIANT strFileName, VARIANT dwFileFormat)
	{
		long result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x10031, DISPATCH_METHOD, VT_I4, (void*)&result, parms, &strFileName, &dwFileFormat);
		return result;
	}
	void DeleteLocalFile(LPCTSTR strFilePath)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x10032, DISPATCH_METHOD, VT_EMPTY, NULL, parms, strFilePath);
	}
	CString GetTempFilePath()
	{
		CString result;
		InvokeHelper(0x10033, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long ShowView(long dwViewType)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x10034, DISPATCH_METHOD, VT_I4, (void*)&result, parms, dwViewType);
		return result;
	}
	long FtpConnect(LPCTSTR strURL, long lPort, LPCTSTR strUser, LPCTSTR strPwd)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x10035, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strURL, lPort, strUser, strPwd);
		return result;
	}
	long FtpGetFile(LPCTSTR strRemoteFile, LPCTSTR strLocalFile)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x10036, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strRemoteFile, strLocalFile);
		return result;
	}
	long FtpPutFile(LPCTSTR strLocalFile, LPCTSTR strRemoteFile, long blOverWrite)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 ;
		InvokeHelper(0x10037, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strLocalFile, strRemoteFile, blOverWrite);
		return result;
	}
	long FtpDisConnect()
	{
		long result;
		InvokeHelper(0x10038, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString DownloadFile(LPCTSTR strRemoteFile, LPCTSTR strLocalFile)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x10039, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strRemoteFile, strLocalFile);
		return result;
	}
	long HttpAddPostFile(LPCTSTR strFileID, LPCTSTR strFileName)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x10040, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strFileID, strFileName);
		return result;
	}
	long GetRevCount()
	{
		long result;
		InvokeHelper(0x10041, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString GetRevInfo(long lIndex, long lType)
	{
		CString result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x10042, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, lIndex, lType);
		return result;
	}
	long SetValue(LPCTSTR strValue, LPCTSTR strName)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x10043, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strValue, strName);
		return result;
	}
	long SetDocVariable(LPCTSTR strVarName, LPCTSTR strValue, long lOpt)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 ;
		InvokeHelper(0x10044, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strVarName, strValue, lOpt);
		return result;
	}
	long SetPageAs(LPCTSTR strLocalFile, long lPageNum, long lType)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 ;
		InvokeHelper(0x10045, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strLocalFile, lPageNum, lType);
		return result;
	}
	long ReplaceText(LPCTSTR strSearchText, LPCTSTR strReplaceText, long lGradation)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 ;
		InvokeHelper(0x10049, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strSearchText, strReplaceText, lGradation);
		return result;
	}
	CString GetEnvironmentVariable(LPCTSTR EnvironmentName)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x10050, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, EnvironmentName);
		return result;
	}
	CString GetOfficeVersion(LPCTSTR strName)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x10051, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strName);
		return result;
	}

// Properties
//



};
