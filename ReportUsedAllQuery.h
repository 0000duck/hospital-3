#if !defined(AFX_REPORTUSEDALLQUERY_H__6E1CC319_1F7B_469C_BFD6_C92D110D278C__INCLUDED_)
#define AFX_REPORTUSEDALLQUERY_H__6E1CC319_1F7B_469C_BFD6_C92D110D278C__INCLUDED_

#include "qiuXpButton.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportUsedAllQuery.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReportUsedAllQuery dialog

class CReportUsedAllQuery : public CDialog
{
// Construction
public:
	CString strSql;
	int sql_cols,iYear;
	static UINT QueryList(LPVOID ps);
	CReportUsedAllQuery(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReportUsedAllQuery)
	enum { IDD = IDD_DIALOG_BCYB_CX };
	CQiuXpButton	m_b3;
	CQiuXpButton	m_b2;
	CQiuXpButton	m_b1;
	CComboBox	comYear;
	CString	strKh;
	CString	strXm;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportUsedAllQuery)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReportUsedAllQuery)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnExcel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTUSEDALLQUERY_H__6E1CC319_1F7B_469C_BFD6_C92D110D278C__INCLUDED_)
