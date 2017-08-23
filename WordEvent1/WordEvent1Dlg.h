
// WordEvent1Dlg.h : 头文件
//

#pragma once
#include "AppEventListener.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "RevCellElemnet.h"
#include "RevTextElement.h"

void _stdcall CALLBACK OnGetWordModifyMsgCallback(CList<RevTextElement> *textList,CList<RevCellElemnet> *cellList);
// CWordEvent1Dlg 对话框
class CWordEvent1Dlg : public CDialogEx
{
// 构造
public:
	CWordEvent1Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_WORDEVENT1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持	
// 实现
protected:
	HICON m_hIcon;
	_Application m_wordApplication;
	CAppEventListener* m_pAppEventListener;
	IConnectionPoint* m_pConnectionPoint;
	DWORD m_dwConnectionCookie;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	void InitialListReport();

public:
	afx_msg void OnBnClickedStartsink();
	afx_msg void OnBnClickedStopsink();
	int       m_EditCout;
	int       m_EditSubCout;
	CListCtrl m_list;			//学生信息列表框
	CEdit contentText;			//文本编辑与现实框
    CString   content;			//编辑WORD返回的内容
    CEdit     m_ListEdit;		//列表编辑    
	CString docPath;			//操作文档路径
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton1();		
};
