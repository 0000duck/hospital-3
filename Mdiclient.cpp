// Mdiclient.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "Mdiclient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMdiclient

CMdiclient::CMdiclient()
{
//	m_bitmapFlag.LoadBitmap(IDB_BITMAP_HOSPITAL);
	CString strFileName;
	strFileName.Format("%s",LoginInformation.path);
	strFileName+="backview.bmp";

	HBITMAP	hbmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), \
		strFileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);

    ////////////////////该断程序用来取得加载的BMP的信息////////////////////////
	if(hbmp == NULL ){
		backView.CreateSolidBrush(RGB(70,140,180));
		
	}
	else{
		m_bitmapFlag.Attach( hbmp );
		backView.CreatePatternBrush(&m_bitmapFlag);
	}
}

CMdiclient::~CMdiclient()
{
}


BEGIN_MESSAGE_MAP(CMdiclient, CWnd)
	//{{AFX_MSG_MAP(CMdiclient)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMdiclient message handlers

void CMdiclient::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
}

BOOL CMdiclient::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
//	backView.CreatePatternBrush(&m_bitmapFlag);
	CBrush *pOldBrush=pDC->SelectObject((CBrush*)&backView);
	CRect rect;
	pDC->GetClipBox(&rect); 
	// 擦除需要的区域
	
	// 用创建的画刷绘制背景区域
	pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(),
		PATCOPY);
	pDC->SelectObject(pOldBrush);
	return TRUE;
	
//	return CWnd::OnEraseBkgnd(pDC);
}
