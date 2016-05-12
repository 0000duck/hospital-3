#if !defined(AFX_PROGRESSINDICATE_H__10333A8C_0C48_4961_84B1_738E51DFF837__INCLUDED_)
#define AFX_PROGRESSINDICATE_H__10333A8C_0C48_4961_84B1_738E51DFF837__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProgressIndicate.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProgressIndicate dialog
#include "progressEx.h"
class CProgressIndicate : public CDialog
{
// Construction
public:
	UINT (* pThreadFunction)(LPVOID);
	LPVOID  pDialog;
	static UINT ScheduleIndicate(LPVOID ps);
//	int i;
	UINT ConnectFlag;
	CProgressIndicate(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProgressIndicate)
	enum { IDD = IDD_DIALOG_INDICATE };
	CProgressEx	m_progress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressIndicate)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProgressIndicate)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRESSINDICATE_H__10333A8C_0C48_4961_84B1_738E51DFF837__INCLUDED_)
