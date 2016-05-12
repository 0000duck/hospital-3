// ReportEmpCount.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "ReportEmpCount.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportEmpCount dialog


CReportEmpCount::CReportEmpCount(CWnd* pParent /*=NULL*/)
	: CDialog(CReportEmpCount::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReportEmpCount)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CReportEmpCount::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportEmpCount)
	DDX_Control(pDX, IDC_COMBO_YEAR, m_comYear);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReportEmpCount, CDialog)
	//{{AFX_MSG_MAP(CReportEmpCount)
	ON_BN_CLICKED(IDEXCEL, OnExcel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportEmpCount message handlers

CReportEmpCount::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	fontTitle.CreatePointFont(220,"Т¦Ме");
	
	CString	strTitle=CComFunc::GetString("SELECT ds1 FROM lsq_mixed WHERE ds3='TITLE' AND ds4='AAA' ");
	SetWindowText(strTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	CString strTmp;
	int year=COleDateTime::GetCurrentTime().GetYear();

	for(long i=0; i<5; ++i ){
		strTmp.Format("%d",year-i );
		m_comYear.AddString(strTmp);
	}
	m_comYear.SetCurSel(0);


	//GRID_ID=26
	CComFunc::comSetGridHeader(m_grid,GRID_ID);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CReportEmpCount::OnOK() 
{
	UpdateData();
	CString strSql,strYear;
	int icol[]={2,3,4,5,6,7,8},isum=7;

	CComFunc::comSetGridHeader(m_grid,GRID_ID);

	m_comYear.GetLBText(m_comYear.GetCurSel(),strYear);
	

	CComFunc::GetSql(strSql,SQL_ID);

	strSql.Replace("[YEAR]",strYear);

	CComFunc::ReadDataForGrid(strSql,m_grid,icol,isum);

}

void CReportEmpCount::OnExcel() 
{
	CComFunc::ToExcel(&m_grid);	
	
}
