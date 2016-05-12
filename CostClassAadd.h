#if !defined(AFX_COSTCLASSAADD_H__400265A6_88C4_4D2B_AAD8_5661487387D6__INCLUDED_)
#define AFX_COSTCLASSAADD_H__400265A6_88C4_4D2B_AAD8_5661487387D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CostClassAadd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCostClassAadd dialog

class CCostClassAadd : public CDialog
{
// Construction
public:
	CCostClassAadd(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCostClassAadd)
	enum { IDD = IDD_DIALOG_COST_ADD };
	CString	m_cmt;
	CString	m_name;
	long	m_order;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCostClassAadd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCostClassAadd)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COSTCLASSAADD_H__400265A6_88C4_4D2B_AAD8_5661487387D6__INCLUDED_)
