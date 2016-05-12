//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_OPERATORSEL_H__9DF38D78_536C_498A_9CDB_6FC02C319AEE__INCLUDED_)
#define AFX_OPERATORSEL_H__9DF38D78_536C_498A_9CDB_6FC02C319AEE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OperatorSel.h : header file
// 操作人员选择，胜于其它应用中操作人的选择
// 2010-02-21

/////////////////////////////////////////////////////////////////////////////
// COperatorSel dialog

class COperatorSel : public CDialog
{
// Construction
public:
	COperatorSel(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COperatorSel)
	enum { IDD = IDD_OPERATOR_SEL };
	CEdit	m_name;
	CComboBox	m_dep;
	CMSHFlexGrid	m_grid;
	//}}AFX_DATA
	CStringArray comArray1;
	CString strID,strName;
	enum{GRID_HEADER_ID=20,SQL_QUERY_ID=33,GRID_NAME=3,GRID_NAME_ID=2 };

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COperatorSel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COperatorSel)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSel();
	afx_msg void OnDblClickMshflexgrid1();
	afx_msg void OnSelchangeComboDepSel();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPERATORSEL_H__9DF38D78_536C_498A_9CDB_6FC02C319AEE__INCLUDED_)
