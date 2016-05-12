#if !defined(AFX_LOGON_H__2BDDA08A_E2C4_4353_9582_FE2F9538DF4E__INCLUDED_)
#define AFX_LOGON_H__2BDDA08A_E2C4_4353_9582_FE2F9538DF4E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Logon.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CLogon dialog
#include "qiuxpbutton.h"
#include "comboxex.h"
#include "editFlat.h"
class CLogon : public CDialog
{
// Construction
public:
	CBrush backBrush,bk2;
	CLogon(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLogon)
	enum { IDD = IDD_DIALOG_LOGON };
	CQiuXpButton	m_re;
	CQiuXpButton	m_we;
	CComBoxEx	m_name;
	CComBoxEx	m_depart;
	CEditFlat	m_password;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogon)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLogon)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombo1();
	virtual void OnOK();
	afx_msg void OnSelchangeCombo2();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	virtual void OnCancel();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGON_H__2BDDA08A_E2C4_4353_9582_FE2F9538DF4E__INCLUDED_)
