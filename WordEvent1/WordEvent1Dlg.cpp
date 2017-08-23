
// WordEvent1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WordEvent1.h"
#include "WordEvent1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWordEvent1Dlg 对话框




CWordEvent1Dlg::CWordEvent1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWordEvent1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWordEvent1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_EDIT1, contentText);
}

BEGIN_MESSAGE_MAP(CWordEvent1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_STARTSINK, &CWordEvent1Dlg::OnBnClickedStartsink)
	ON_BN_CLICKED(ID_STOPSINK, &CWordEvent1Dlg::OnBnClickedStopsink)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CWordEvent1Dlg::OnNMDblclkList1)
	ON_BN_CLICKED(IDC_BUTTON1, &CWordEvent1Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CWordEvent1Dlg 消息处理程序

BOOL CWordEvent1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_pAppEventListener = NULL;
	m_pConnectionPoint = NULL;
	m_dwConnectionCookie = 0;
	//获取当前程序执行路径
	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);      
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0;
	CString strtemp=szFilePath;
	docPath=strtemp.Mid(0,strtemp.GetLength()-7);
	
	//初始化表格
	InitialListReport();
	//创建列表编辑框用于表格编辑数据
	m_ListEdit.Create(WS_CHILD,CRect(0,0,10,10),this,0);

	this->content=_T("这是一段WORD编辑前的测试文字...");
	this->contentText.SetWindowTextW(this->content);
	//实例化全局变量
	TEXT=&contentText;
	TABLE=&m_list;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


//初始化表格数据
void CWordEvent1Dlg::InitialListReport()
{

	this->m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES);
	//初始化列头
	this->m_list.InsertColumn(0,_T("姓名"),LVCFMT_LEFT,80);
	this->m_list.InsertColumn(1,_T("语文"),LVCFMT_LEFT,80);
	this->m_list.InsertColumn(2,_T("数学"),LVCFMT_LEFT,80);
	this->m_list.InsertColumn(3,_T("英语"),LVCFMT_LEFT,80);
	this->m_list.InsertColumn(4,_T("政治"),LVCFMT_LEFT,80);
	this->m_list.InsertColumn(5,_T("历史"),LVCFMT_LEFT,80);

	//初始化行首列数据
	this->m_list.InsertItem(0,_T("李一"));
	this->m_list.InsertItem(1,_T("张平"));
	this->m_list.InsertItem(2,_T("孙二"));
	this->m_list.InsertItem(3,_T("周波"));
	this->m_list.InsertItem(4,_T("刘平"));
	this->m_list.InsertItem(5,_T("李六"));

	//初始化其他列数据
	for(int i=0;i<7;i++)
	{
		for(int j=1;j<6;j++)
		{
			int grade=i*2+60+j;
			this->m_list.SetItemText(i,j,_T(""));
		}
	}
}

void CWordEvent1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWordEvent1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CWordEvent1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/************************************************************************/
/* 启动WORD编辑，关键要建立WORD连接点与事件监听器对象的绑定关系         */
/************************************************************************/
void CWordEvent1Dlg::OnBnClickedStartsink()
{
	// TODO: 在此添加控件通知处理程序代码
	// Common OLE-variants. These are easy variants to use for calling arguments.
	COleVariant
		covTrue((short)TRUE),
		covFalse((short)FALSE),
		covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	COleException e;

	Documents oDocs;  // oDocs is the Documents Collection.
	_Document oDoc;  // oDoc is the Document object.
	CString str;
	HRESULT hr = S_OK;

	try
	{
		// Start Word and get an Application object.
		if(!m_wordApplication.CreateDispatch(_T("Word.Application")))
		{
			//str.Format("Problem instantiating Word. Error is %ld <0x%08lx>", e.m_sc, e.m_sc);
			str=_T("Problem instantiating Word");
			AfxMessageBox(str,MB_SETFOREGROUND);
			return;
		}
		else // Success.
		{
			//Make the application visible. 
			m_wordApplication.SetVisible(TRUE);
		}

		//获取文档编辑对象
		oDocs=m_wordApplication.GetDocuments();
		//设置WORD打开模板
		COleVariant varTrue(short(1),VT_BOOL),vOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
		CComVariant Template(docPath+_T("\\学生信息.dotx"));    //使用WORD的文档模板
		CComVariant NewTemplate(false),DocumentType(0),Visible;

		oDocs.Add(&Template,&NewTemplate,&DocumentType,&Visible);  
		
		//获取激活的文档
		oDoc=m_wordApplication.GetActiveDocument();
		if (!oDoc.m_lpDispatch) 
		{
			AfxMessageBox(_T("Document获取失败!"), MB_OK|MB_ICONWARNING);
			return ;
		}
		//文档为非修订模式则设置
		if(!oDoc.GetTrackRevisions())
			oDoc.SetTrackRevisions(TRUE);

		//Do not try to hook up more than once.
		if (m_pAppEventListener != NULL)
			return;		
		//获取WORD应用宿主连接点接口
		IConnectionPointContainer *pConnPtContainer= NULL;
		hr = m_wordApplication.m_lpDispatch->QueryInterface(
			IID_IConnectionPointContainer,
			(void **)&pConnPtContainer );
		if (SUCCEEDED(hr)){

			// Find the connection point for events that you are interested in.
			//获取你感兴趣的事件连接点对象
			hr = pConnPtContainer->FindConnectionPoint(
				IID_IApplicationEvents2,
				&m_pConnectionPoint
				);
			if (SUCCEEDED(hr)){

				//Create a new CAppEventListener.
				m_pAppEventListener = new CAppEventListener();
				m_pAppEventListener->AddRef();

				// Set up advisory connection.[关联事件监听对象与COM连接点]
				hr = m_pConnectionPoint->Advise(m_pAppEventListener, 
					&m_dwConnectionCookie);

				// Release the IConnectionPointContainer interface.
				pConnPtContainer->Release(); 

				//传递函数处理
				m_pAppEventListener->setGetWordModifyMsgCallback(OnGetWordModifyMsgCallback);
			}
		}
	}
	catch(COleException* e)
	{
		//str.Format("Error in Try..Catch was 0x%08lx", e->m_sc);
		str.Format(_T("Error in Try..Catch was 0x%d"),e->m_sc);
		AfxMessageBox(str, MB_SETFOREGROUND);
		return;
	}
}

/************************************************************************/
/*关闭WORD编辑操作，关键是释放WORD连接点与事件监听器对象的绑定关系      */
/************************************************************************/
void CWordEvent1Dlg::OnBnClickedStopsink()
{
	// TODO: 在此添加控件通知处理程序代码
	//If the connection point has been advised, unadvise it and clean up.
	if (m_pConnectionPoint != NULL){
		m_pConnectionPoint->Unadvise( m_dwConnectionCookie );
		m_dwConnectionCookie = 0;
		m_pConnectionPoint->Release();
		m_pConnectionPoint = NULL;
	}

	if (m_pAppEventListener != NULL){
		m_pAppEventListener->Release();
		m_pAppEventListener = NULL;
	}

	m_wordApplication.ReleaseDispatch();
}

void CWordEvent1Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{

	this->SetFocus();  //通过设置焦点，使得编辑框失去焦点，进入OnCommand

	CDialog::OnLButtonDown(nFlags, point);
}
/************************************************************************/
/*  处理表格文字编辑事件                                                */
/************************************************************************/
BOOL CWordEvent1Dlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	HWND hwnd=(HWND)lParam;
	int ordert=HIWORD(wParam); //取高字节是消息来的
	if (ordert==EN_KILLFOCUS)  //失去焦点
	{
		if (m_ListEdit.m_hWnd == hwnd)
		{
			CString nstr;
			m_ListEdit.GetWindowText(nstr);
			m_ListEdit.ShowWindow(SW_HIDE);
			m_ListEdit.SetWindowText(_T(""));
			m_list.SetItemText(m_EditCout,m_EditSubCout,nstr);
		}
	}

	return CDialog::OnCommand(wParam, lParam);
}


void CWordEvent1Dlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	m_EditCout    = pNMItemActivate->iItem;
	m_EditSubCout = pNMItemActivate->iSubItem;
	CRect nRect;

	//获取列表控件的矩形区域
	m_list.GetSubItemRect(m_EditCout,m_EditSubCout,LVIR_LABEL,nRect);
	CRect nListRect;
	m_list.GetWindowRect(&nListRect);

	//转换到客户区
	this->ScreenToClient(nListRect);

	//控件位置进行偏移
	nRect.OffsetRect(nListRect.left + 2,nListRect.top + 2);

	CString nItemStr = m_list.GetItemText(m_EditCout,m_EditSubCout);
	m_ListEdit.SetWindowText(nItemStr);
	m_ListEdit.MoveWindow(nRect);
	m_ListEdit.ShowWindow(SW_SHOW);

	//设置列表控件编辑框焦点
	m_ListEdit.SetFocus();
}

/************************************************************************/
/* 将控件中的文字及表格数据导出到WORD报表中[次报表与编辑的为统一模板]   */
/************************************************************************/
void CWordEvent1Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	//创建新文档实例
	_Application wordApp;
	Documents wordDocs;
	_Document oDoc;

	//****创建word application实例,失败的话返回false
	if (!wordApp.CreateDispatch(_T("Word.Application"))) 
	{
		  AfxMessageBox(_T("Application创建失败，请确保安装了word 2007或以上版本!"), MB_OK|MB_ICONWARNING); //显示错误信息
		return; //返回
	}   

	//获得 documents 实例 
	wordDocs=wordApp.GetDocuments();
	//****添加新的空白文档（调用COM）

	CComVariant tpl(_T("")),Visble,DocType(0),NewTemplate(false);
	oDoc=wordDocs.Add(&tpl,&NewTemplate,&DocType,&Visble);

	Range rng;
	Table tbl;
	Tables tbls;
	
	COleVariant vTrue((short)TRUE),
		vFalse((short)FALSE),
		vTmp,
		vOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	COleVariant   vUnit((long)5),   vCount((long)1),   vExtend((long)1);

	//把文本添加到word文档
	Selection oSel;
	oSel = wordApp.GetSelection(); //获得 wordSelection 实例
	//====================字体设置＝＝＝＝＝＝＝＝＝＝＝＝＝
	_Font   myFont; 
	myFont   =oSel.GetFont();
	ASSERT(LPDISPATCH(myFont)); 
	//改为大字体、浅蓝色 
	//myFont.SetColorIndex((long)3);
	myFont.SetColor(255);
	myFont.SetSize(24); 
	//获取文本框里最新的内容
	this->contentText.GetWindowTextW(this->content);
	//输出编辑的内容
	oSel.TypeText(this->content);

	oSel.TypeParagraph(); //回车符
	oSel.TypeParagraph(); //回车符

	//================插入表格(6*6)=============================
	rng=oSel.GetRange();
	tbls=oDoc.GetTables();
	tbl=tbls.Add(rng,6,6,COleVariant((short)1),COleVariant((short)0));

	tbl.SetApplyStyleHeadingRows(TRUE);
	tbl.SetApplyStyleLastRow(false);
	tbl.SetApplyStyleFirstColumn(true);
	tbl.SetApplyStyleLastColumn(false);
	tbl.SetApplyStyleRowBands(true);
	//======================================================
	//设置表头
	oSel.TypeText(_T("姓名"));
	oSel.MoveRight(COleVariant((short)12),COleVariant((short)1),COleVariant((short)0));//TAB键效果
	oSel.TypeText(_T("语文"));
	oSel.MoveRight(COleVariant((short)12),COleVariant((short)1),COleVariant((short)0));
	oSel.TypeText(_T("数学"));
	oSel.MoveRight(COleVariant((short)12),COleVariant((short)1),COleVariant((short)0));
	oSel.TypeText(_T("英语"));
	oSel.MoveRight(COleVariant((short)12),COleVariant((short)1),COleVariant((short)0));
	oSel.TypeText(_T("政治"));
	oSel.MoveRight(COleVariant((short)12),COleVariant((short)1),COleVariant((short)0));
	oSel.TypeText(_T("历史"));
	oSel.MoveRight(COleVariant((short)12),COleVariant((short)1),COleVariant((short)0));
	//================获取表格中的数据=================
	for (int i=0;i<6;i++)
	{
		for(int j=0;j<6;j++)
		{
			CString str = m_list.GetItemText(i,j);
			oSel.TypeText(str);
			oSel.MoveRight(COleVariant((short)12),COleVariant((short)1),COleVariant((short)0));
		}
	}
	//保存输出报表
	CString fileName=this->docPath+_T("\\WORD交互操作报表.docx");
	oDoc.SaveAs((COleVariant)fileName, //VARIANT* FileName
		vOpt,    //VARIANT* FileFormat
		vOpt,    //VARIANT* LockComments
		vOpt,    //VARIANT* Password
		vOpt,    //VARIANT* AddToRecentFiles
		vOpt,    //VARIANT* WritePassword
		vOpt,    //VARIANT* ReadOnlyRecommended
		vOpt,    //VARIANT* EmbedTrueTypeFonts
		vOpt,    //VARIANT* SaveNativePictureFormat
		vOpt,    //VARIANT* SaveFormsData
		vOpt,    //VARIANT* SaveAsAOCELetter
		vOpt,	 // * Encoding, 
		vOpt,	 //VARIANT * InsertLineBreaks, 
		vOpt,   //VARIANT * AllowSubstitutions, 
		vOpt,	 //VARIANT * LineEnding, 
		vOpt	 //VARIANT * AddBiDiMarks)
		);

	//打开生成的报表
	BOOL ReadOnly(false);
	CComVariant Read(ReadOnly);
	BOOL AddToRecentFiles(false) ;
	CComVariant AddToR(AddToRecentFiles);
	CString FileName=this->docPath+_T("\\WORD交互操作报表.docx");
	CComVariant Name(FileName);

	COleVariant varZero((short)0);
	COleVariant varTrue(short(1),VT_BOOL);
	COleVariant varFalse(short(0),VT_BOOL);
	CComVariant format(0);
	wordDocs.Open(&Name,varFalse,&Read,&AddToR,vOpt,vOpt,
		vFalse,vOpt,vOpt,&format,vOpt,vTrue,vOpt,vOpt,vOpt,vOpt);
}

/************************************************************************/
/* 响应WORD获取到数据后的界面处理                                        */
/************************************************************************/
void _stdcall CALLBACK OnGetWordModifyMsgCallback(CList<RevTextElement> *textList,CList<RevCellElemnet> *cellList)
{
	int textCnt=textList->GetSize();			//获取修订文字的个数
	int cellCnt=cellList->GetSize();			//获取修订表格的个数
	CString content;
	//处理文本数据
	POSITION pos = textList->GetHeadPosition();
	for(int i=0;i<textCnt;i++)
	{
		RevTextElement temp=textList->GetNext(pos);
		content=content+temp.getContent();
	}
	//更新文本框中的数据
	::TEXT->SetWindowText(content);

	POSITION pos1 = cellList->GetHeadPosition();
	//处理表格数据
	for(int j=0;j<cellCnt;j++)
	{
		 RevCellElemnet cell=cellList->GetNext(pos1);
		 //获取行列信息
		 int row=cell.getRow();
		 int col=cell.getCol();
		 //更新视图列表数据
		 ::TABLE->SetItemText(row-2,col-1,cell.getContent());
	}
}
