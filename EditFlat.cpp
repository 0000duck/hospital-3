// EditFlat.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "EditFlat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditFlat

CEditFlat::CEditFlat()
{
	penColor=RGB(255,0,0);//(92,98,207);
	pen2.CreatePen(PS_SOLID,1,penColor);
}

CEditFlat::~CEditFlat()
{
}


BEGIN_MESSAGE_MAP(CEditFlat, CEdit)
	//{{AFX_MSG_MAP(CEditFlat)
	ON_WM_PAINT()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditFlat message handlers

void CEditFlat::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CRect r1;
	CPen *p2;
	p2=dc.SelectObject(&pen2);
	GetWindowRect(&r1);
	ScreenToClient(&r1);
	dc.Rectangle(&r1);

	// TODO: Add your message handler code here
	dc.SelectObject(p2);
	Invalidate();
	Default();
	
}



void CEditFlat::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if('\'' == nChar )	return;
	CEdit::OnChar(nChar, nRepCnt, nFlags);
}
