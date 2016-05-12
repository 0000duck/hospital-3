#if !defined(AFX_AFFINITYQUERY_H__BE222AFC_D56A_47D0_932C_E4CBB8A1CB43__INCLUDED_)
#define AFX_AFFINITYQUERY_H__BE222AFC_D56A_47D0_932C_E4CBB8A1CB43__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AffinityQuery.h : header file
//
#include "gridctrl\gridctrl.h"
/////////////////////////////////////////////////////////////////////////////
// CAffinityQuery dialog
//供养亲属费用费用查询
class CAffinityQuery : public CDialog
{
// Construction
public:
	CAffinityQuery(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAffinityQuery)
	enum { IDD = IDD_DIALOG_AFFINITY_QUERY };
	CComboBox	m_cbDepart;
	CComboBox	m_cbType;
	CString	m_strKh;
	CString	m_strXm;
	COleDateTime	m_date1;
	COleDateTime	m_date2;
	//}}AFX_DATA
	
	CGridCtrl m_grid;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAffinityQuery)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	CFont fontTitle;
// Implementation
protected:
	CStringArray m_aryDepart;

	// Generated message map functions
	//{{AFX_MSG(CAffinityQuery)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButtonExcel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AFFINITYQUERY_H__BE222AFC_D56A_47D0_932C_E4CBB8A1CB43__INCLUDED_)
