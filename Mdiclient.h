#if !defined(AFX_MDICLIENT_H__482F53DC_D339_48F6_A001_7E43D932BBEF__INCLUDED_)
#define AFX_MDICLIENT_H__482F53DC_D339_48F6_A001_7E43D932BBEF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Mdiclient.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMdiclient window

class CMdiclient : public CWnd
{
// Construction
public:
	CMdiclient();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMdiclient)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMdiclient();

	// Generated message map functions
protected:
	CBitmap m_bitmapFlag;
	CBrush backView;
	//{{AFX_MSG(CMdiclient)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDICLIENT_H__482F53DC_D339_48F6_A001_7E43D932BBEF__INCLUDED_)
