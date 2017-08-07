#include "stdafx.h"
#include "ChildDlg.h"
#include "afxdialogex.h"
#include <exception>
#include <string>
// CChildDlg 对话框

IMPLEMENT_DYNAMIC(CChildDlg, CDialogEx)

CChildDlg::CChildDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_SHOW, pParent)
{

}

CChildDlg::~CChildDlg()
{
}

void CChildDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_FRAMERCONTROL1, m_dsoframer);
}


BEGIN_MESSAGE_MAP(CChildDlg, CDialogEx)
END_MESSAGE_MAP()


// CChildDlg 消息处理程序


BOOL CChildDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();


    RECT wndRect;
    CWnd* pParent = GetParent();
    pParent->GetWindowRect(&wndRect);
    // 使窗口充满父窗口
    SetWindowPos(&wndTop, 0, 0, wndRect.right - wndRect.left, wndRect.bottom - wndRect.top, 0);
    // 使控件充满窗口
    m_dsoframer.SetWindowPos(&CWnd::wndTop, 0, 0, wndRect.right - wndRect.left, wndRect.bottom - wndRect.top, 0);


    //std::string ss(R"(C:\Users\zmm\Desktop\test.docx)");
    std::string ss("http://192.168.4.162:8080/office/load?filename=test.docx");
    //m_dsoframer.CreateNew("Word.Document");
    m_dsoframer.Open(ATL::CComVariant(ss.data()), ATL::CComVariant(false), ATL::CComVariant("Word.Document"), vtMissing, vtMissing);
    
    MSWord::_Document* pDoc = nullptr;
    LPDISPATCH pDisp = m_dsoframer.get_ActiveDocument();
    if (!pDisp)
    {
        AfxMessageBox("LPDISPATCH is null");
        return TRUE;
    }

    HRESULT hr = pDisp->QueryInterface<MSWord::_Document>(&pDoc);
    if (FAILED(hr))
    {
        AfxMessageBox("QueryInterface failed");
        return TRUE;
    }
    else if (pDoc == nullptr)
    {
        AfxMessageBox("_Document is null");
        return TRUE;
    }

    MSWord::Range* pRange = nullptr;
    hr = pDoc->get_Content(&pRange);
    if (SUCCEEDED(hr) && pRange != nullptr)
    {
        BSTR bstr;
        pRange->get_Text(&bstr);

        wchar_t* dd = bstr;
        CString ss(dd);
        SysFreeString(bstr);
        AfxMessageBox(ss);
    }
    else
    {
        AfxMessageBox("get_Name failed");
        return TRUE;
    }

    // 测试上传到服务器
    //初始化Http引擎
    BOOL ret = m_dsoframer.HttpInit();
    if (!ret)
    {
        AfxMessageBox("HttpInit failed");
        return TRUE;
    }
    //增加Post变量
    //m_dsoframer.HttpAddPostString("RecordID", "20060102200");
    //m_dsoframer.HttpAddPostString("UserID", "李局长");
    //上传打开的文件
    ret = m_dsoframer.HttpAddPostCurrFile("filename", "test2.docx");
    if (!ret)
    {
        AfxMessageBox("HttpInit failed");
        return TRUE;
    }

    //执行上传动作
    CString respStr = m_dsoframer.HttpPost("http://192.168.4.162:8080/office/save");
    AfxMessageBox(respStr);


    return TRUE;
}