// FormGhList_del.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "FormGhList_del.h"
#include "ghQuery_del.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormGhList_del

IMPLEMENT_DYNCREATE(CFormGhList_del, CFormView)

CFormGhList_del::CFormGhList_del()
	: CFormView(CFormGhList_del::IDD)
{
	//{{AFX_DATA_INIT(CFormGhList_del)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(220,"姚体");
}

CFormGhList_del::~CFormGhList_del()
{
}

void CFormGhList_del::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFormGhList_del)
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFormGhList_del, CFormView)
	//{{AFX_MSG_MAP(CFormGhList_del)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_COMMAND(ID_MENUITEM_REPORT_EXCEL, OnMenuitemReportExcel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormGhList_del diagnostics

#ifdef _DEBUG
void CFormGhList_del::AssertValid() const
{
	CFormView::AssertValid();
}

void CFormGhList_del::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFormGhList_del message handlers

void CFormGhList_del::OnDestroy() 
{
	CFormView::OnDestroy();

	theApp.hGhList_del=NULL;
	theApp.pGhList_del=NULL;
	
	
}

void CFormGhList_del::OnDraw(CDC* pDC) 
{
	CRect r1,r2,rectTitle,rectButton;
	long titleHigh;

	GetClientRect(&r2);
	GetDlgItem(IDC_STATIC_TITLE)->GetWindowRect(rectTitle);
	ScreenToClient(rectTitle);
	rectTitle.right=r2.right;
	rectTitle.left= r2.left;
	titleHigh=rectTitle.bottom-rectTitle.top;
	rectTitle.top=  r2.top;
	rectTitle.bottom = r2.top+ titleHigh;
	GetDlgItem(IDC_STATIC_TITLE)->MoveWindow(0,0,r2.right-r2.left,titleHigh);

	GetDlgItem(IDC_MSHFLEXGRID1)->GetWindowRect(&r1);
	ScreenToClient(&r1);
	GetDlgItem(IDC_MSHFLEXGRID1)->MoveWindow(0,r2.top+titleHigh,r2.right,r2.bottom-titleHigh);	
	
	
}

HBRUSH CFormGhList_del::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if( pWnd->m_hWnd == GetDlgItem(IDC_STATIC_TITLE)->m_hWnd)
		pDC->SetTextColor(LSQ_RED);
	
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CFormGhList_del::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();

	extern CHis3App theApp;
	theApp.hGhList_del=GetParentFrame()->m_hWnd;
	TITLE=CComFunc::GetString(" SELECT ds1 FROM lsq_title_list where ds2='DIALOG' and ds3='TITLE' and ds4='AAM' ");
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);

	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(TITLE);
	GetParentFrame()->ShowWindow(SW_SHOWMAXIMIZED);
	GetDocument()->SetTitle(TITLE);
	// TODO: Add your specialized code here and/or call the base class
	CComFunc::comSetGridHeader(m_grid,16);	
	
	
}

BEGIN_EVENTSINK_MAP(CFormGhList_del, CFormView)
    //{{AFX_EVENTSINK_MAP(CFormGhList_del)
	ON_EVENT(CFormGhList_del, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	ON_EVENT(CFormGhList_del, IDC_MSHFLEXGRID1, -600 /* Click */, OnClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CFormGhList_del::OnDblClickMshflexgrid1() 
{
	CGhQuery_del gq;
	theApp.pParentGrid.pGrid=this;
	gq.DoModal();
	
}

void CFormGhList_del::OnClickMshflexgrid1() 
{
	const int ENDLINES=2;
	if(m_grid.GetRows() == ENDLINES )return;//判断是否需要显示快捷菜单

	MSG *pms;
	pms=(MSG*)GetCurrentMessage();
	if(pms->message != 0x205) {//0x202为鼠标左键,0x205为鼠标右键消息
		return;
	}
	CMenu pm;
	CPoint p;
	pm.LoadMenu(IDR_MENU_QUICK);
	CMenu* pmenu=pm.GetSubMenu(6);
	GetCursorPos(&p);
	pmenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON ,p.x,p.y,this);  	
	
}

void CFormGhList_del::OnMenuitemReportExcel() 
{
	CComFunc::ToExcel(&m_grid);	
	
}
