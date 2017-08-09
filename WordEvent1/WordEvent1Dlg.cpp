
// WordEvent1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WordEvent1.h"
#include "WordEvent1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CWordEvent1Dlg �Ի���




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


// CWordEvent1Dlg ��Ϣ�������

BOOL CWordEvent1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_pAppEventListener = NULL;
	m_pConnectionPoint = NULL;
	m_dwConnectionCookie = 0;
	//��ȡ��ǰ����ִ��·��
	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);      
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0;
	CString strtemp=szFilePath;
	docPath=strtemp.Mid(0,strtemp.GetLength()-7);
	
	//��ʼ�����
	InitialListReport();
	//�����б�༭�����ڱ��༭����
	m_ListEdit.Create(WS_CHILD,CRect(0,0,10,10),this,0);

	this->content=_T("����һ��WORD�༭ǰ�Ĳ�������...");
	this->contentText.SetWindowTextW(this->content);
	//ʵ����ȫ�ֱ���
	TEXT=&contentText;
	TABLE=&m_list;
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}


//��ʼ���������
void CWordEvent1Dlg::InitialListReport()
{

	this->m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES);
	//��ʼ����ͷ
	this->m_list.InsertColumn(0,_T("����"),LVCFMT_LEFT,80);
	this->m_list.InsertColumn(1,_T("����"),LVCFMT_LEFT,80);
	this->m_list.InsertColumn(2,_T("��ѧ"),LVCFMT_LEFT,80);
	this->m_list.InsertColumn(3,_T("Ӣ��"),LVCFMT_LEFT,80);
	this->m_list.InsertColumn(4,_T("����"),LVCFMT_LEFT,80);
	this->m_list.InsertColumn(5,_T("��ʷ"),LVCFMT_LEFT,80);

	//��ʼ������������
	this->m_list.InsertItem(0,_T("��һ"));
	this->m_list.InsertItem(1,_T("��ƽ"));
	this->m_list.InsertItem(2,_T("���"));
	this->m_list.InsertItem(3,_T("�ܲ�"));
	this->m_list.InsertItem(4,_T("��ƽ"));
	this->m_list.InsertItem(5,_T("����"));

	//��ʼ������������
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CWordEvent1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CWordEvent1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/************************************************************************/
/* ����WORD�༭���ؼ�Ҫ����WORD���ӵ����¼�����������İ󶨹�ϵ         */
/************************************************************************/
void CWordEvent1Dlg::OnBnClickedStartsink()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

		//��ȡ�ĵ��༭����
		oDocs=m_wordApplication.GetDocuments();
		//����WORD��ģ��
		COleVariant varTrue(short(1),VT_BOOL),vOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
		CComVariant Template(docPath+_T("\\ѧ����Ϣ.dotx"));    //ʹ��WORD���ĵ�ģ��
		CComVariant NewTemplate(false),DocumentType(0),Visible;

		oDocs.Add(&Template,&NewTemplate,&DocumentType,&Visible);  
		
		//��ȡ������ĵ�
		oDoc=m_wordApplication.GetActiveDocument();
		if (!oDoc.m_lpDispatch) 
		{
			AfxMessageBox(_T("Document��ȡʧ��!"), MB_OK|MB_ICONWARNING);
			return ;
		}
		//�ĵ�Ϊ���޶�ģʽ������
		if(!oDoc.GetTrackRevisions())
			oDoc.SetTrackRevisions(TRUE);

		//Do not try to hook up more than once.
		if (m_pAppEventListener != NULL)
			return;		
		//��ȡWORDӦ���������ӵ�ӿ�
		IConnectionPointContainer *pConnPtContainer= NULL;
		hr = m_wordApplication.m_lpDispatch->QueryInterface(
			IID_IConnectionPointContainer,
			(void **)&pConnPtContainer );
		if (SUCCEEDED(hr)){

			// Find the connection point for events that you are interested in.
			//��ȡ�����Ȥ���¼����ӵ����
			hr = pConnPtContainer->FindConnectionPoint(
				IID_IApplicationEvents2,
				&m_pConnectionPoint
				);
			if (SUCCEEDED(hr)){

				//Create a new CAppEventListener.
				m_pAppEventListener = new CAppEventListener();
				m_pAppEventListener->AddRef();

				// Set up advisory connection.[�����¼�����������COM���ӵ�]
				hr = m_pConnectionPoint->Advise(m_pAppEventListener, 
					&m_dwConnectionCookie);

				// Release the IConnectionPointContainer interface.
				pConnPtContainer->Release(); 

				//���ݺ�������
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
/*�ر�WORD�༭�������ؼ����ͷ�WORD���ӵ����¼�����������İ󶨹�ϵ      */
/************************************************************************/
void CWordEvent1Dlg::OnBnClickedStopsink()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

	this->SetFocus();  //ͨ�����ý��㣬ʹ�ñ༭��ʧȥ���㣬����OnCommand

	CDialog::OnLButtonDown(nFlags, point);
}
/************************************************************************/
/*  ���������ֱ༭�¼�                                                */
/************************************************************************/
BOOL CWordEvent1Dlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	HWND hwnd=(HWND)lParam;
	int ordert=HIWORD(wParam); //ȡ���ֽ�����Ϣ����
	if (ordert==EN_KILLFOCUS)  //ʧȥ����
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	m_EditCout    = pNMItemActivate->iItem;
	m_EditSubCout = pNMItemActivate->iSubItem;
	CRect nRect;

	//��ȡ�б�ؼ��ľ�������
	m_list.GetSubItemRect(m_EditCout,m_EditSubCout,LVIR_LABEL,nRect);
	CRect nListRect;
	m_list.GetWindowRect(&nListRect);

	//ת�����ͻ���
	this->ScreenToClient(nListRect);

	//�ؼ�λ�ý���ƫ��
	nRect.OffsetRect(nListRect.left + 2,nListRect.top + 2);

	CString nItemStr = m_list.GetItemText(m_EditCout,m_EditSubCout);
	m_ListEdit.SetWindowText(nItemStr);
	m_ListEdit.MoveWindow(nRect);
	m_ListEdit.ShowWindow(SW_SHOW);

	//�����б�ؼ��༭�򽹵�
	m_ListEdit.SetFocus();
}

/************************************************************************/
/* ���ؼ��е����ּ�������ݵ�����WORD������[�α�����༭��Ϊͳһģ��]   */
/************************************************************************/
void CWordEvent1Dlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//�������ĵ�ʵ��
	_Application wordApp;
	Documents wordDocs;
	_Document oDoc;

	//****����word applicationʵ��,ʧ�ܵĻ�����false
	if (!wordApp.CreateDispatch(_T("Word.Application"))) 
	{
		  AfxMessageBox(_T("Application����ʧ�ܣ���ȷ����װ��word 2007�����ϰ汾!"), MB_OK|MB_ICONWARNING); //��ʾ������Ϣ
		return; //����
	}   

	//��� documents ʵ�� 
	wordDocs=wordApp.GetDocuments();
	//****����µĿհ��ĵ�������COM��

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

	//���ı���ӵ�word�ĵ�
	Selection oSel;
	oSel = wordApp.GetSelection(); //��� wordSelection ʵ��
	//====================�������ã�������������������������
	_Font   myFont; 
	myFont   =oSel.GetFont();
	ASSERT(LPDISPATCH(myFont)); 
	//��Ϊ�����塢ǳ��ɫ 
	//myFont.SetColorIndex((long)3);
	myFont.SetColor(255);
	myFont.SetSize(24); 
	//��ȡ�ı��������µ�����
	this->contentText.GetWindowTextW(this->content);
	//����༭������
	oSel.TypeText(this->content);

	oSel.TypeParagraph(); //�س���
	oSel.TypeParagraph(); //�س���

	//================������(6*6)=============================
	rng=oSel.GetRange();
	tbls=oDoc.GetTables();
	tbl=tbls.Add(rng,6,6,COleVariant((short)1),COleVariant((short)0));

	tbl.SetApplyStyleHeadingRows(TRUE);
	tbl.SetApplyStyleLastRow(false);
	tbl.SetApplyStyleFirstColumn(true);
	tbl.SetApplyStyleLastColumn(false);
	tbl.SetApplyStyleRowBands(true);
	//======================================================
	//���ñ�ͷ
	oSel.TypeText(_T("����"));
	oSel.MoveRight(COleVariant((short)12),COleVariant((short)1),COleVariant((short)0));//TAB��Ч��
	oSel.TypeText(_T("����"));
	oSel.MoveRight(COleVariant((short)12),COleVariant((short)1),COleVariant((short)0));
	oSel.TypeText(_T("��ѧ"));
	oSel.MoveRight(COleVariant((short)12),COleVariant((short)1),COleVariant((short)0));
	oSel.TypeText(_T("Ӣ��"));
	oSel.MoveRight(COleVariant((short)12),COleVariant((short)1),COleVariant((short)0));
	oSel.TypeText(_T("����"));
	oSel.MoveRight(COleVariant((short)12),COleVariant((short)1),COleVariant((short)0));
	oSel.TypeText(_T("��ʷ"));
	oSel.MoveRight(COleVariant((short)12),COleVariant((short)1),COleVariant((short)0));
	//================��ȡ����е�����=================
	for (int i=0;i<6;i++)
	{
		for(int j=0;j<6;j++)
		{
			CString str = m_list.GetItemText(i,j);
			oSel.TypeText(str);
			oSel.MoveRight(COleVariant((short)12),COleVariant((short)1),COleVariant((short)0));
		}
	}
	//�����������
	CString fileName=this->docPath+_T("\\WORD������������.docx");
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

	//�����ɵı���
	BOOL ReadOnly(false);
	CComVariant Read(ReadOnly);
	BOOL AddToRecentFiles(false) ;
	CComVariant AddToR(AddToRecentFiles);
	CString FileName=this->docPath+_T("\\WORD������������.docx");
	CComVariant Name(FileName);

	COleVariant varZero((short)0);
	COleVariant varTrue(short(1),VT_BOOL);
	COleVariant varFalse(short(0),VT_BOOL);
	CComVariant format(0);
	wordDocs.Open(&Name,varFalse,&Read,&AddToR,vOpt,vOpt,
		vFalse,vOpt,vOpt,&format,vOpt,vTrue,vOpt,vOpt,vOpt,vOpt);
}

/************************************************************************/
/* ��ӦWORD��ȡ�����ݺ�Ľ��洦��                                        */
/************************************************************************/
void _stdcall CALLBACK OnGetWordModifyMsgCallback(CList<RevTextElement> *textList,CList<RevCellElemnet> *cellList)
{
	int textCnt=textList->GetSize();			//��ȡ�޶����ֵĸ���
	int cellCnt=cellList->GetSize();			//��ȡ�޶����ĸ���
	CString content;
	//�����ı�����
	POSITION pos = textList->GetHeadPosition();
	for(int i=0;i<textCnt;i++)
	{
		RevTextElement temp=textList->GetNext(pos);
		content=content+temp.getContent();
	}
	//�����ı����е�����
	::TEXT->SetWindowText(content);

	POSITION pos1 = cellList->GetHeadPosition();
	//����������
	for(int j=0;j<cellCnt;j++)
	{
		 RevCellElemnet cell=cellList->GetNext(pos1);
		 //��ȡ������Ϣ
		 int row=cell.getRow();
		 int col=cell.getCol();
		 //������ͼ�б�����
		 ::TABLE->SetItemText(row-2,col-1,cell.getContent());
	}
}
