#pragma once
#include "framercontrol1.h"

// CChildDlg 对话框

class CChildDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChildDlg)

public:
	CChildDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChildDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SHOW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    CFramercontrol1 m_dsoframer;
    virtual BOOL OnInitDialog();
};
