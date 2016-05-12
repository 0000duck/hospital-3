// QiuXpButton.cpp : implementation file
//

#include "stdafx.h"
#include "QiuXpButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQiuXpButton

CQiuXpButton::CQiuXpButton()
{
	m_BoundryPen.CreatePen(PS_INSIDEFRAME | PS_SOLID, 1, RGB(0, 0, 0));
	m_InsideBoundryPenLeft.CreatePen(PS_INSIDEFRAME | PS_SOLID, 3, RGB(250, 196, 88)); 
	m_InsideBoundryPenRight.CreatePen(PS_INSIDEFRAME | PS_SOLID, 3, RGB(251, 202, 106));
	m_InsideBoundryPenTop.CreatePen(PS_INSIDEFRAME | PS_SOLID, 2, RGB(252, 210, 121));
	m_InsideBoundryPenBottom.CreatePen(PS_INSIDEFRAME | PS_SOLID, 2, RGB(229, 151, 0));
	
	m_FillActive.CreateSolidBrush(RGB(223, 222, 236));
	m_FillInactive.CreateSolidBrush(RGB(222, 223, 236));
	
	m_InsideBoundryPenLeftSel.CreatePen(PS_INSIDEFRAME | PS_SOLID, 3, RGB(153, 198, 252)); 
	m_InsideBoundryPenTopSel.CreatePen(PS_INSIDEFRAME | PS_SOLID, 2, RGB(162, 201, 255));
	m_InsideBoundryPenRightSel.CreatePen(PS_INSIDEFRAME | PS_SOLID, 3, RGB(162, 189, 252));
	m_InsideBoundryPenBottomSel.CreatePen(PS_INSIDEFRAME | PS_SOLID, 2, RGB(162, 201, 255));

/*	m_InsideBoundryPenLeftSel.CreatePen(PS_INSIDEFRAME | PS_SOLID, 3, RGB(255, 0, 0)); 
	m_InsideBoundryPenTopSel.CreatePen(PS_INSIDEFRAME | PS_SOLID, 2, RGB(0, 0, 255));
	m_InsideBoundryPenRightSel.CreatePen(PS_INSIDEFRAME | PS_SOLID, 3, RGB(0, 255, 0));
	m_InsideBoundryPenBottomSel.CreatePen(PS_INSIDEFRAME | PS_SOLID, 2, RGB(162, 201, 255));
*/

	m_bOver = m_bSelected = m_bTracking = m_bFocus = FALSE;
	backColor2=0;
}

CQiuXpButton::~CQiuXpButton()
{
}


BEGIN_MESSAGE_MAP(CQiuXpButton, CButton)
	//{{AFX_MSG_MAP(CQiuXpButton)
	ON_WM_CREATE()
	ON_WM_DRAWITEM()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQiuXpButton message handlers

int CQiuXpButton::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	ModifyStyle(0, BS_OWNERDRAW);

	return 0;
}

void CQiuXpButton::DoGradientFill(CDC *pDC, CRect* rect)
{
	CBrush pBrush[64];
	int nWidth = rect->Width();		//rect.right - rect.left;
	int nHeight = rect->Height();	//.bottom - rect.top;
	CRect rct;
	const int COLORMAX=145;
/*	
	for (int i = 0; i < 64; i ++)
	{
		if (m_bOver)
		{
			if (m_bFocus)
				pBrush[i].CreateSolidBrush(RGB(255 - (i / 4), 255 - (i / 4), 255 - (i / 3)));
			else
				pBrush[i].CreateSolidBrush(RGB(255 - (i / 4), 255 - (i / 4), 255 - (i / 5)));
		}
		else
		{
			if (m_bFocus)
				pBrush[i].CreateSolidBrush(RGB(255 - (i / 3), 255 - (i / 3), 255 - (i / 4)));
			else
				pBrush[i].CreateSolidBrush(RGB(255 - (i / 3), 255 - (i / 3), 255 - (i / 5)));
		}
	}
*/
	for (int i = 0; i < 64; i ++)
		if (m_bOver)
		//	pBrush[i].CreateSolidBrush(RGB(COLORMAX - (i * 2), COLORMAX- (i * 2), COLORMAX- (i * 2)));
			pBrush[i].CreateSolidBrush(RGB(0, COLORMAX-(i*2),0));
		else
		//	pBrush[i].CreateSolidBrush(RGB(255 - (i / 4), 255 - (i / 4), 255 - (i / 5)));
			pBrush[i].CreateSolidBrush(RGB(255,255,255));


	
	for (i = rect->top; i <= nHeight + 2; i ++) 
	{
		rct.SetRect(rect->left, i, nWidth + 2, i + 1);
		pDC->FillRect(&rct, &pBrush[((i * 63) / nHeight)]);
	}
	
	for (i = 0; i < 64; i ++)
		pBrush[i].DeleteObject();
}

void CQiuXpButton::DrawInsideBorder(CDC *pDC, CRect* rect)
{
	CPen *left, *right, *top, *bottom;
	
	if (m_bSelected && !m_bOver)
	{
		left = & m_InsideBoundryPenLeftSel;
		right = &m_InsideBoundryPenRightSel;
		top = &m_InsideBoundryPenTopSel;
		bottom = &m_InsideBoundryPenBottomSel;
	}
	else
	{
		left = &m_InsideBoundryPenLeft;
		right = &m_InsideBoundryPenRight;
		top = &m_InsideBoundryPenTop;
		bottom = &m_InsideBoundryPenBottom;
	}
	
	CPoint oldPoint = pDC->MoveTo(rect->left, rect->bottom - 1);
	CPen* hOldPen = pDC->SelectObject(left);
	pDC->LineTo(rect->left, rect->top + 1);
	pDC->SelectObject(*right);
	pDC->MoveTo(rect->right - 1, rect->bottom - 1);
	pDC->LineTo(rect->right - 1, rect->top);
	pDC->SelectObject(*top);
	pDC->MoveTo(rect->left - 1, rect->top);
	pDC->LineTo(rect->right - 1, rect->top);
	pDC->SelectObject(*bottom);
	pDC->MoveTo(rect->left, rect->bottom);
	pDC->LineTo(rect->right - 1, rect->bottom);
	pDC->SelectObject(hOldPen);
	pDC->MoveTo(oldPoint);
}

void CQiuXpButton::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	DrawItem(lpDrawItemStruct);
//	CButton::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CQiuXpButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (!m_bTracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE | TME_HOVER;
		tme.dwHoverTime = 1;
		m_bTracking = _TrackMouseEvent(&tme);
	}

	CButton::OnMouseMove(nFlags, point);
}

LRESULT CQiuXpButton::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	m_bOver = FALSE;
	m_bTracking = FALSE;
	InvalidateRect(NULL, FALSE);
	return 0;
}

LRESULT CQiuXpButton::OnMouseHover(WPARAM wParam, LPARAM lParam)
{
	m_bOver = TRUE;
	InvalidateRect(NULL);
	return 0;
}

void CQiuXpButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	const unsigned int  COL_WHITE=RGB(255,255,255);   //* °×É«ÑÕÉ«Öµ
	HDC dc = lpDrawItemStruct->hDC;
	CRect &rect = (CRect&) lpDrawItemStruct->rcItem;
	CMemDC pDC(dc, NULL,backColor2);


	UINT state = lpDrawItemStruct->itemState;
	POINT pt ;
	TCHAR szText[MAX_PATH + 1];
	::GetWindowText(m_hWnd, szText, MAX_PATH);
	pt.x = 5;
	pt.y = 5;
	CPen* hOldPen = pDC.SelectObject(&m_BoundryPen);
	pDC.RoundRect(&rect, pt);
	
	if (state & ODS_FOCUS)
	{
		m_bFocus = TRUE;
		m_bSelected = TRUE;
	}
	else
	{
		m_bFocus = FALSE;
		m_bSelected = FALSE;
	}

	if (state & ODS_SELECTED || state & ODS_DEFAULT)
	{
		m_bFocus = TRUE;
	}
	pDC.SelectObject(hOldPen);
	
	rect.DeflateRect(CSize(GetSystemMetrics(SM_CXEDGE), GetSystemMetrics(SM_CYEDGE)));
	
	CBrush* hOldBrush;
	if (m_bOver)
	{
		hOldBrush = pDC.SelectObject(&m_FillActive);
		DoGradientFill(&pDC, &rect);
	}
	else
	{
		hOldBrush = pDC.SelectObject(&m_FillInactive);
		DoGradientFill(&pDC, &rect);
	}
	
	if (m_bOver || m_bSelected)
	{
		DrawInsideBorder(&pDC, &rect);
	}
	
	pDC.SelectObject(hOldBrush);
	
	if (szText!=NULL)
	{
		CFont* hFont = GetFont();
		CFont* hOldFont = pDC.SelectObject(hFont);
		CSize Extent = pDC.GetTextExtent(szText, lstrlen(szText));
		CPoint pt( rect.CenterPoint().x - Extent.cx / 2, rect.CenterPoint().y - Extent.cy / 2);
		if (state & ODS_SELECTED) 
			pt.Offset(1, 1);
		int nMode = pDC.SetBkMode(TRANSPARENT);
		if (state & ODS_DISABLED)
			pDC.DrawState(pt, Extent, szText, DSS_DISABLED, TRUE, 0, (HBRUSH)NULL);
		else
		{
			if ( m_bOver ) pDC.SetTextColor(COL_WHITE);
			pDC.DrawState(pt, Extent, szText, DSS_NORMAL, TRUE, 0, (HBRUSH)NULL);}

		pDC.SelectObject(hOldFont);
		pDC.SetBkMode(nMode);
	}
}

