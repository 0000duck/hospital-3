// ReportMedConsume.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "ReportMedConsume.h"
#include "MedConsumeQuery.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportMedConsume

IMPLEMENT_DYNCREATE(CReportMedConsume, CFormView)

CReportMedConsume::CReportMedConsume()
	: CFormView(CReportMedConsume::IDD)
{
	//{{AFX_DATA_INIT(CReportMedConsume)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(220,"Т¦Ме");

}

CReportMedConsume::~CReportMedConsume()
{
}

void CReportMedConsume::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportMedConsume)
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReportMedConsume, CFormView)
	//{{AFX_MSG_MAP(CReportMedConsume)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportMedConsume diagnostics

#ifdef _DEBUG
void CReportMedConsume::AssertValid() const
{
	CFormView::AssertValid();
}

void CReportMedConsume::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CReportMedConsume message handlers

void CReportMedConsume::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
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

void CReportMedConsume::OnDestroy() 
{
	CFormView::OnDestroy();
	

	theApp.docList[theApp.MED_CONSUME]=NULL;
	theApp.hwndList[theApp.MED_CONSUME]=NULL;

	
}

void CReportMedConsume::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
extern CHis3App theApp;
theApp.hwndList[CHis3App::MED_CONSUME]=GetParentFrame()->m_hWnd;
	TITLE=CComFunc::GetString(" SELECT ds1 FROM lsq_title_list where ds2='DIALOG' and ds3='TITLE' and ds4='AAP' ");
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);

	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(TITLE);
	GetParentFrame()->ShowWindow(SW_SHOWMAXIMIZED);
	GetDocument()->SetTitle(TITLE);

	CComFunc::comSetGridHeader(m_grid,COL_ID);	
	
}

BEGIN_EVENTSINK_MAP(CReportMedConsume, CFormView)
    //{{AFX_EVENTSINK_MAP(CReportMedConsume)
	ON_EVENT(CReportMedConsume, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CReportMedConsume::OnDblClickMshflexgrid1() 
{
	CMedConsumeQuery mq;
	theApp.pParentGrid.pGrid=this;

	mq.DoModal();
}
