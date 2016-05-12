#if !defined(AFX_GHQUERY_H__6536CB7F_C36A_4BC8_BD17_79045C46D99E__INCLUDED_)
#define AFX_GHQUERY_H__6536CB7F_C36A_4BC8_BD17_79045C46D99E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GhQuery.h : header file
//
#include "userQuery.h"

/////////////////////////////////////////////////////////////////////////////
// CGhQuery dialog
//挂号列表人查询
class CGhQuery : public CDialog
{
// Construction
public:
	static UINT  QueryGhList(LPVOID ps);
	CGhQuery(CWnd* pParent = NULL);   // standard constructor
	CStringArray strArrType;
	CString sfyCode,ysCode;
// Dialog Data
	//{{AFX_DATA(CGhQuery)
	enum { IDD = IDD_DIALOG_GH_QUERY };
	CEdit	c_ys;
	CEdit	c_sfy;
	CComboBox	m_type;
	CString	m_xm;
	COleDateTime	m_date1;
	COleDateTime	m_date2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGhQuery)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGhQuery)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSetfocusEditYs();
	afx_msg void OnSetfocusEditSfy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GHQUERY_H__6536CB7F_C36A_4BC8_BD17_79045C46D99E__INCLUDED_)
