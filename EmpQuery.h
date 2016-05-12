#if !defined(AFX_EMPQUERY_H__5AEA1211_5466_4186_9D85_96711579EE7F__INCLUDED_)
#define AFX_EMPQUERY_H__5AEA1211_5466_4186_9D85_96711579EE7F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EmpQuery.h : header file
//
#include "gridctrl\gridctrl.h"

/////////////////////////////////////////////////////////////////////////////
// CEmpQuery dialog
//补充保险门诊消费查询,融入部门信息
//2015/12/29

class CEmpQuery : public CDialog
{
// Construction
public:
	CEmpQuery(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEmpQuery)
	enum { IDD = IDD_DIALOG_EMP_QUERY };
	CComboBox	m_cbDepart;
	CString	m_strKh;
	CString	m_strXm;
	COleDateTime	m_date1;
	COleDateTime	m_date2;
	//}}AFX_DATA
	CGridCtrl m_grid;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEmpQuery)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	CFont fontTitle;

// Implementation
protected:
	CStringArray m_aryDepart;

	// Generated message map functions
	//{{AFX_MSG(CEmpQuery)
	afx_msg void OnButtonExcel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EMPQUERY_H__5AEA1211_5466_4186_9D85_96711579EE7F__INCLUDED_)
