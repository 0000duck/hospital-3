#if !defined(AFX_COMBOXEX_H__6D22A8A7_F06C_41D3_B69F_D073D0F74705__INCLUDED_)
#define AFX_COMBOXEX_H__6D22A8A7_F06C_41D3_B69F_D073D0F74705__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComBoxEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CComBoxEx window

class CComBoxEx : public CComboBox
{
// Construction
public:
	CComBoxEx();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComBoxEx)
	//}}AFX_VIRTUAL

// Implementation
public:
	CPen pen2;
	virtual ~CComBoxEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CComBoxEx)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMBOXEX_H__6D22A8A7_F06C_41D3_B69F_D073D0F74705__INCLUDED_)
