#if !defined(AFX_LOCK_H__EE60F803_3B09_4B7F_AE7B_008C1160BD54__INCLUDED_)
#define AFX_LOCK_H__EE60F803_3B09_4B7F_AE7B_008C1160BD54__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Lock.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLock dialog

class CLock : public CDialog
{
// Construction
public:
	CLock(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLock)
	enum { IDD = IDD_DIALOG_LOCK };
	CString	m_password;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLock)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLock)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOCK_H__EE60F803_3B09_4B7F_AE7B_008C1160BD54__INCLUDED_)
