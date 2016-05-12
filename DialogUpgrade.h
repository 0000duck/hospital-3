#if !defined(AFX_DIALOGUPGRADE_H__890A0E91_8633_4784_BF36_E0857AA07235__INCLUDED_)
#define AFX_DIALOGUPGRADE_H__890A0E91_8633_4784_BF36_E0857AA07235__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogUpgrade.h : header file
//* 软件自动升级模块
//* 2008/1/13

/////////////////////////////////////////////////////////////////////////////
// CDialogUpgrade dialog
#include <afxinet.h>

class CDialogUpgrade : public CDialog
{
// Construction
public:
	static UINT GetHttpFile(LPVOID ps);
	CDialogUpgrade(CWnd* pParent = NULL);   // standard constructor
	CString strURL,strFILE;
// Dialog Data
	//{{AFX_DATA(CDialogUpgrade)
	enum { IDD = IDD_DIALOG_UPGRADE };
	CProgressCtrl	m_pr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogUpgrade)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogUpgrade)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	CFont fo1;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGUPGRADE_H__890A0E91_8633_4784_BF36_E0857AA07235__INCLUDED_)
