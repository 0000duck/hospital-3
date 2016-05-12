#if !defined(AFX_DIALOGWAIT_H__A71EAF5F_8409_4AA4_90DA_093B1C695FD2__INCLUDED_)
#define AFX_DIALOGWAIT_H__A71EAF5F_8409_4AA4_90DA_093B1C695FD2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogWait.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogWait dialog

class CDialogWait : public CDialog
{
// Construction
public:
	void ExitWait();
	CDialogWait(CWnd* pParent = NULL);   // standard constructor
	CString strPrompt;
// Dialog Data
	//{{AFX_DATA(CDialogWait)
	enum { IDD = IDD_DIALOG_WAIT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogWait)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFont ft;
	CBrush bh;
	// Generated message map functions
	//{{AFX_MSG(CDialogWait)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGWAIT_H__A71EAF5F_8409_4AA4_90DA_093B1C695FD2__INCLUDED_)
