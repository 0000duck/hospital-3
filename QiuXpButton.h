#if !defined(AFX_QIUXPBUTTON_H__68C59E26_AC0B_40A1_8BE8_1571A1929891__INCLUDED_)
#define AFX_QIUXPBUTTON_H__68C59E26_AC0B_40A1_8BE8_1571A1929891__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QiuXpButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQiuXpButton window

class CMemDC : public CDC
{
public:
	CDC*	     m_dc;
	CBitmap      m_bitmap;
	CBitmap*	 m_hOldBitmap;
	RECT         m_rc;
	CMemDC(HDC hDC, LPRECT pRect,COLORREF bk)
	{
		m_dc = new CDC;
		
		ASSERT(hDC != NULL);
		m_dc->m_hAttribDC = hDC;
		m_dc->m_hDC = hDC;
		if (pRect != NULL)
			m_rc = *pRect;
		else
			m_dc->GetClipBox(&m_rc);
		
		CreateCompatibleDC(m_dc);
		::LPtoDP(m_dc->m_hDC, (LPPOINT)&m_rc, sizeof(RECT) / sizeof(POINT));
		m_bitmap.CreateCompatibleBitmap(m_dc, m_rc.right - m_rc.left, m_rc.bottom - m_rc.top);
		m_hOldBitmap = SelectObject(&m_bitmap);
		::DPtoLP(m_dc->m_hDC, (LPPOINT)&m_rc, sizeof(RECT) / sizeof(POINT));
		SetWindowOrg(m_rc.left, m_rc.top);
		if(bk==0)FillSolidRect(&m_rc, m_dc->GetBkColor());
		else FillSolidRect(&m_rc, bk);

	}
	~CMemDC()
	{
		m_dc->BitBlt(m_rc.left, m_rc.top, m_rc.right - m_rc.left, m_rc.bottom - m_rc.top,
			this, m_rc.left, m_rc.top, SRCCOPY);
		SelectObject(m_hOldBitmap);
		delete m_dc;
	}
};

class CQiuXpButton : public CButton
{
// Construction
public:
	CQiuXpButton();
	
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQiuXpButton)
	//}}AFX_VIRTUAL

// Implementation
public:
	COLORREF backColor2;
	virtual ~CQiuXpButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CQiuXpButton)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

protected:
	CPen m_BoundryPen;
	
	CPen m_InsideBoundryPenLeft;
	CPen m_InsideBoundryPenRight;
	CPen m_InsideBoundryPenTop;
	CPen m_InsideBoundryPenBottom;

	CPen m_InsideBoundryPenLeftSel;
	CPen m_InsideBoundryPenRightSel;
	CPen m_InsideBoundryPenTopSel;
	CPen m_InsideBoundryPenBottomSel;

	CBrush m_FillActive;
	CBrush m_FillInactive;
	
	BOOL m_bOver;
	BOOL m_bTracking;
	BOOL m_bSelected;
	BOOL m_bFocus;

	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
private:
	void DoGradientFill(CDC *pDC, CRect* rect);
	void DrawInsideBorder(CDC *pDC, CRect* rect);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QIUXPBUTTON_H__68C59E26_AC0B_40A1_8BE8_1571A1929891__INCLUDED_)
