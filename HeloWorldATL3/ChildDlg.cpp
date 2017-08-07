#include "stdafx.h"
#include "ChildDlg.h"

BOOL CALLBACK ShowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_INITDIALOG:
    {
        HWND hParent = GetParent(hWnd);
        RECT wndRect;

        GetWindowRect(hParent, &wndRect);
        SetWindowPos(hWnd, HWND_TOP, 0, 0, wndRect.right - wndRect.left, wndRect.bottom - wndRect.top, 0);
        ShowWindow(hWnd, SW_SHOW);

        MessageBox(hWnd, "test2", "title", MB_OK);
        break;
    }
    default:
        return FALSE;
    }
    return TRUE;
}
// ChildDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChildDlg.h"
#include "afxdialogex.h"


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
    GetWindowRect(&wndRect);
    //BOOL ret = m_dsoframer.SetWindowPos(&wndTop, 0, 0, wndRect.right - wndRect.left, wndRect.bottom - wndRect.top, 0);
    //if (FAILED(ret))
    //{
    //    AfxMessageBox("error: SetWindowPos");
    //}



    return TRUE;
}
