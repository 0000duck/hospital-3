#if !defined(AFX_PLANASWHOLE_H__5A372B5F_7EEE_44DE_8E3C_71AA5582042A__INCLUDED_)
#define AFX_PLANASWHOLE_H__5A372B5F_7EEE_44DE_8E3C_71AA5582042A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlanAsWhole.h : header file
// 统筹利息结算

/////////////////////////////////////////////////////////////////////////////
// CPlanAsWhole dialog

class CPlanAsWhole : public CDialog
{
// Construction
public:
	CPlanAsWhole(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPlanAsWhole)
	enum { IDD = IDD_DIALOG_PLANASWHOLE };
	CComboBox	m_cmYear;
	CString	m_szAcc;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlanAsWhole)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPlanAsWhole)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLANASWHOLE_H__5A372B5F_7EEE_44DE_8E3C_71AA5582042A__INCLUDED_)
