#if !defined(AFX_EDITFLAT_H__261F2EC7_83EA_4608_94CA_677B160F7900__INCLUDED_)
#define AFX_EDITFLAT_H__261F2EC7_83EA_4608_94CA_677B160F7900__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditFlat.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditFlat window

class CEditFlat : public CEdit
{
// Construction
public:
	CEditFlat();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditFlat)
	//}}AFX_VIRTUAL

// Implementation
public:
	COLORREF penColor;
	CPen pen2;
	virtual ~CEditFlat();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEditFlat)
	afx_msg void OnPaint();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITFLAT_H__261F2EC7_83EA_4608_94CA_677B160F7900__INCLUDED_)
