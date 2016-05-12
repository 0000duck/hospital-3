#if !defined(AFX_RELATEQUERY_H__0053D9B3_79D1_421B_9975_1CF0CCA25226__INCLUDED_)
#define AFX_RELATEQUERY_H__0053D9B3_79D1_421B_9975_1CF0CCA25226__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RelateQuery.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRelateQuery dialog
#include "gridctrl\gridctrl.h"

class CRelateQuery : public CDialog
{
// Construction
public:
	CRelateQuery(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRelateQuery)
	enum { IDD = IDD_DIALOG_RELATE_QUERY };
	CComboBox	m_cbDepart;
	COleDateTime	m_date1;
	COleDateTime	m_date2;
	CString	m_strKh;
	CString	m_strXm;
	//}}AFX_DATA
	CGridCtrl m_grid;
	CFont fontTitle;
	CStringArray m_aryDepart;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRelateQuery)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRelateQuery)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButtonExcel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RELATEQUERY_H__0053D9B3_79D1_421B_9975_1CF0CCA25226__INCLUDED_)
