
// WordEvent1Dlg.h : ͷ�ļ�
//

#pragma once
#include "AppEventListener.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "RevCellElemnet.h"
#include "RevTextElement.h"

void _stdcall CALLBACK OnGetWordModifyMsgCallback(CList<RevTextElement> *textList,CList<RevCellElemnet> *cellList);
// CWordEvent1Dlg �Ի���
class CWordEvent1Dlg : public CDialogEx
{
// ����
public:
	CWordEvent1Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_WORDEVENT1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��	
// ʵ��
protected:
	HICON m_hIcon;
	_Application m_wordApplication;
	CAppEventListener* m_pAppEventListener;
	IConnectionPoint* m_pConnectionPoint;
	DWORD m_dwConnectionCookie;
	// ���ɵ���Ϣӳ�亯��
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
	CListCtrl m_list;			//ѧ����Ϣ�б��
	CEdit contentText;			//�ı��༭����ʵ��
    CString   content;			//�༭WORD���ص�����
    CEdit     m_ListEdit;		//�б�༭    
	CString docPath;			//�����ĵ�·��
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton1();		
};
