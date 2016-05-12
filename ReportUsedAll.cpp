// ReportUsedAll1.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "ReportUsedAll.h"
#include "medquery.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportMedQuery

IMPLEMENT_DYNCREATE(CReportMedQuery, CFormView)

CReportMedQuery::CReportMedQuery()
	: CFormView(CReportMedQuery::IDD)
{
	//{{AFX_DATA_INIT(CReportMedQuery)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(220,"Т¦Ме");
}

CReportMedQuery::~CReportMedQuery()
{
}

void CReportMedQuery::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportMedQuery)
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReportMedQuery, CFormView)
	//{{AFX_MSG_MAP(CReportMedQuery)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportMedQuery diagnostics

#ifdef _DEBUG
void CReportMedQuery::AssertValid() const
{
	CFormView::AssertValid();
}

void CReportMedQuery::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CReportMedQuery message handlers

void CReportMedQuery::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
extern CHis3App theApp;
theApp.hwndList[CHis3App::MED_POINT]=GetParentFrame()->m_hWnd;
	TITLE=CComFunc::GetString(" SELECT ds1 FROM lsq_title_list where ds2='DIALOG' and ds3='TITLE' and ds4='AAO' ");
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);

	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(TITLE);
	GetParentFrame()->ShowWindow(SW_SHOWMAXIMIZED);
	GetDocument()->SetTitle(TITLE);

	CComFunc::comSetGridHeader(m_grid,COL_ID);	
	
}

void CReportMedQuery::OnDraw(CDC* pDC) 
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

void CReportMedQuery::OnDestroy() 
{
	CFormView::OnDestroy();
	
	theApp.docList[theApp.MED_POINT]=NULL;
	theApp.hwndList[theApp.MED_POINT]=NULL;

	
	
}

BEGIN_EVENTSINK_MAP(CReportMedQuery, CFormView)
    //{{AFX_EVENTSINK_MAP(CReportMedQuery)
	ON_EVENT(CReportMedQuery, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CReportMedQuery::OnDblClickMshflexgrid1() 
{

	CMedQuery mq;
	theApp.pParentGrid.pGrid=this;
	mq.DoModal();
}

