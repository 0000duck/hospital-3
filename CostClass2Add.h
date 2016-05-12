#if !defined(AFX_COSTCLASS2ADD_H__5A8D9A8F_A078_49F6_BCB5_45004A372BB7__INCLUDED_)
#define AFX_COSTCLASS2ADD_H__5A8D9A8F_A078_49F6_BCB5_45004A372BB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CostClass2Add.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCostClass2Add dialog

class CCostClass2Add : public CDialog
{
// Construction
public:
	void InitMember();
	CCostClass2Add(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCostClass2Add)
	enum { IDD = IDD_DIALOG_COST_2_ADD };
	CComboBox	m_depart;
	CString	m_name;
	CString	m_rem;
	UINT	m_seq;
	//}}AFX_DATA

	CStringArray arrayDepart;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCostClass2Add)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCostClass2Add)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeCombo1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COSTCLASS2ADD_H__5A8D9A8F_A078_49F6_BCB5_45004A372BB7__INCLUDED_)
