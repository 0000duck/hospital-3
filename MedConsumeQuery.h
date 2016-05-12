#if !defined(AFX_MEDCONSUMEQUERY_H__2CC71415_72BD_41D9_8782_17631ED02E6E__INCLUDED_)
#define AFX_MEDCONSUMEQUERY_H__2CC71415_72BD_41D9_8782_17631ED02E6E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MedConsumeQuery.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMedConsumeQuery dialog

class CMedConsumeQuery : public CDialog
{
// Construction
public:
	static UINT QueryData(LPVOID ps);
	CMedConsumeQuery(CWnd* pParent = NULL);   // standard constructor
	enum { SQLID= 37,SQLID2=38,FIRST_ITEM=0, SECOND_ITEM=1 };
	CString strSql;
	CStringArray typecode1,typecode2;
// Dialog Data
	//{{AFX_DATA(CMedConsumeQuery)
	enum { IDD = IDD_DIALOG_QUERY_CONSUME };
	CComboBox	m_combo2;
	CComboBox	m_combo1;
	COleDateTime	m_date1;
	COleDateTime	m_date2;
	CString	m_strBM;
	CString	m_strPY;
	//}}AFX_DATA

	enum{ MEDQUERYID=44};
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMedConsumeQuery)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMedConsumeQuery)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnOk2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEDCONSUMEQUERY_H__2CC71415_72BD_41D9_8782_17631ED02E6E__INCLUDED_)
