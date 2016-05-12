// ProgressEx.cpp : implementation file
//

#include "stdafx.h"

#include "ProgressEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgressEx

CProgressEx::CProgressEx()
{
	strView="正在连接 Oracle 服务器...";
	fontOut.CreatePointFont(150,"黑体");
	flagSucceed=1;

	backBrush.CreateSolidBrush(RGB(214,211,206));
}

CProgressEx::~CProgressEx()
{
}


BEGIN_MESSAGE_MAP(CProgressEx, CProgressCtrl)
	//{{AFX_MSG_MAP(CProgressEx)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgressEx message handlers

void CProgressEx::OnPaint() 
{

	CPaintDC dc(this); // device context for painting
	int iPos,iLow,iHigh;
	iPos=GetPos();
	
	dc.SelectObject(&fontOut);
	dc.SetTextColor(RGB(58,110,165));
	
	GetRange(iLow,iHigh);
	int iRange=iHigh-iLow;
	CRect rectPaint,r1;
	CBrush pB;
	pB.CreateSolidBrush(RGB(189,0,0));

	dc.SetBkMode(TRANSPARENT);

	GetClientRect(rectPaint);
	
	r1=rectPaint;
	


	rectPaint.right=(long)(rectPaint.left+((float)iPos/(float)iRange)*rectPaint.right);
//	dc.FillSolidRect(&rectPaint,RGB(189,0,0)); //设定画出的颜色
	dc.FillRect(&rectPaint,&pB);

	rectPaint.left=rectPaint.right;
	rectPaint.right=r1.right;
//	dc.FillSolidRect(&rectPaint,RGB(214,211,206));//此种颜色和原
	pB.CreateSolidBrush(RGB(214,211,206));
	dc.FillRect(&rectPaint,&pB);
	dc.DrawText(strView,r1,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	
	
	// TODO: Add your message handler code here
	// Do not call CProgressCtrl::OnPaint() for painting messages
}






