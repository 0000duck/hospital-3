// ReportDechargeList.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "ReportDechargeList.h"
#include "dechargeQuery.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportDechargeList

IMPLEMENT_DYNCREATE(CReportDechargeList, CFormView)

CReportDechargeList::CReportDechargeList()
	: CFormView(CReportDechargeList::IDD)
{
	//{{AFX_DATA_INIT(CReportDechargeList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(220,"姚体");
	TITLE="费用报销明细查询";
}

CReportDechargeList::~CReportDechargeList()
{
}

void CReportDechargeList::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportDechargeList)
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReportDechargeList, CFormView)
	//{{AFX_MSG_MAP(CReportDechargeList)
	ON_WM_DESTROY()
	ON_COMMAND(ID_MENUITEM_REPORT_EXCEL, OnMenuitemReportExcel)
	ON_COMMAND(ID_MENUITEM_REPORT_DEL, OnMenuitemReportDel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportDechargeList diagnostics

#ifdef _DEBUG
void CReportDechargeList::AssertValid() const
{
	CFormView::AssertValid();
}

void CReportDechargeList::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CReportDechargeList message handlers

void CReportDechargeList::OnDestroy() 
{
	CFormView::OnDestroy();
	
	theApp.pDechargeList=NULL;
	theApp.hDechargeList=NULL;
}

void CReportDechargeList::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();

	theApp.hDechargeList=GetParentFrame()->m_hWnd;
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);

	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(TITLE);
	GetParentFrame()->ShowWindow(SW_SHOWMAXIMIZED);
	GetDocument()->SetTitle(TITLE);

	CComFunc::comSetGridHeader(m_grid,GRID_HEADER_ID);	
	
	
}

void CReportDechargeList::OnDraw(CDC* pDC) 
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

BEGIN_EVENTSINK_MAP(CReportDechargeList, CFormView)
    //{{AFX_EVENTSINK_MAP(CReportDechargeList)
	ON_EVENT(CReportDechargeList, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	ON_EVENT(CReportDechargeList, IDC_MSHFLEXGRID1, -600 /* Click */, OnClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CReportDechargeList::OnDblClickMshflexgrid1() 
{
	CDechargeQuery dq(m_grid);
	dq.DoModal();
}

void CReportDechargeList::OnClickMshflexgrid1() 
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

void CReportDechargeList::OnMenuitemReportExcel() 
{
	CComFunc::ToExcel(&m_grid);	
	
}

void CReportDechargeList::OnMenuitemReportDel() 
{
	const int ENDLINES=2;
	const int DIG01=11,DIG02=13;
	unsigned long rows=m_grid.GetRows() ;
	if( rows == ENDLINES  ){
		AfxMessageBox("请先选择所要删除的行");
		return;//判断是否需要显示快捷菜单
	}
	unsigned long curRows=m_grid.GetRow();
	
	CString str01=m_grid.GetTextMatrix(curRows,1);//ID
	CString str02;
	str02.Format(" 请确认要删除：\n %s , %s ,%s ",m_grid.GetTextMatrix(curRows,4),
		m_grid.GetTextMatrix(curRows,11),m_grid.GetTextMatrix(curRows,14) );
	if( AfxMessageBox(str02,MB_YESNO|MB_ICONQUESTION) == IDNO )return;
	str02.Format(" delete from lsq_cost_balance_budget where ds1='%s' ",str01);
	if( ! CComFunc::WriteSql(str02) )
	{
		AfxMessageBox("删除出错，请刷新重试");
		return;
	}
	double db01,db02,db03,db04;
	db01=atof(m_grid.GetTextMatrix(curRows,DIG01) );
	db02=atof(m_grid.GetTextMatrix(curRows,DIG02) );
	db03=atof(m_grid.GetTextMatrix(rows-1,DIG01) );
	db04=atof(m_grid.GetTextMatrix(rows-1,DIG02) );
	db03-=db01;
	db04-=db02;
	str01.Format("%.2f",db03);
	str02.Format("%.2f",db04);
	m_grid.SetTextMatrix(rows-1,DIG01,str01);
	m_grid.SetTextMatrix(rows-1,DIG02,str02);

	m_grid.RemoveItem(curRows);
}
