#if !defined(AFX_PROGRESSEX_H__EF899419_F40B_418B_B0B2_190C8F8EAAF5__INCLUDED_)
#define AFX_PROGRESSEX_H__EF899419_F40B_418B_B0B2_190C8F8EAAF5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProgressEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProgressEx window

class CProgressEx : public CProgressCtrl //自定义进度条控件
{
// Construction
public:
	CProgressEx();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressEx)
	//}}AFX_VIRTUAL

// Implementation
public:
	CBrush backBrush;
	INT flagSucceed;
	virtual ~CProgressEx();
	CString strView;

	// Generated message map functions
protected:
	CFont fontOut;
	//{{AFX_MSG(CProgressEx)
	virtual void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRESSEX_H__EF899419_F40B_418B_B0B2_190C8F8EAAF5__INCLUDED_)
