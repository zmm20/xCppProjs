#pragma once
#include "framercontrol1.h"

// CChildDlg �Ի���

class CChildDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChildDlg)

public:
	CChildDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChildDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SHOW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    CFramercontrol1 m_dsoframer;
    virtual BOOL OnInitDialog();
};
