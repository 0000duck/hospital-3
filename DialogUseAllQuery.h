#if !defined(AFX_DIALOGUSEALLQUERY_H__7D31AAEB_CACD_4A38_8414_C573C59B9FB7__INCLUDED_)
#define AFX_DIALOGUSEALLQUERY_H__7D31AAEB_CACD_4A38_8414_C573C59B9FB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogUseAllQuery.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogUseAllQuery dialog

class CDialogUseAllQuery : public CDialog
{
// Construction
public:
	CDialogUseAllQuery(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogUseAllQuery)
	enum { IDD = IDD_DIALOG_BCYB_CX };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogUseAllQuery)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogUseAllQuery)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGUSEALLQUERY_H__7D31AAEB_CACD_4A38_8414_C573C59B9FB7__INCLUDED_)
