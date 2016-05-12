// EmpQuery.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "EmpQuery.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEmpQuery dialog


CEmpQuery::CEmpQuery(CWnd* pParent /*=NULL*/)
	: CDialog(CEmpQuery::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEmpQuery)
	m_strKh = _T("");
	m_strXm = _T("");
	m_date1 = COleDateTime::GetCurrentTime();
	m_date2 = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(220,"姚体");

}


void CEmpQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEmpQuery)
	DDX_Control(pDX, IDC_COMBO_DEPART, m_cbDepart);
	DDX_Text(pDX, IDC_EDIT1, m_strKh);
	DDX_Text(pDX, IDC_EDIT2, m_strXm);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_date2);
	//}}AFX_DATA_MAP
	DDX_GridControl(pDX,IDC_CUSTOM_GRID,m_grid);
}


BEGIN_MESSAGE_MAP(CEmpQuery, CDialog)
	//{{AFX_MSG_MAP(CEmpQuery)
	ON_BN_CLICKED(ID_BUTTON_EXCEL, OnButtonExcel)
	//}}AFX_MSG_MAP


END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEmpQuery message handlers

void CEmpQuery::OnButtonExcel() 
{
	CComFunc::toExcel(m_grid);

}

BOOL CEmpQuery::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CComFunc::comSetGridHeader(m_grid,30);
	

	CString TITLE;
	TITLE=CComFunc::GetString(" SELECT ds1 FROM lsq_title_list where ds2='DIALOG' and ds3='TITLE' and ds4='ABA' ");
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);

	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(TITLE);
	SetWindowText(TITLE);

	//获取部门列表框 
	CString strSql;
	CComFunc::GetSql(strSql,47);
	CComFunc::SetComboxType(m_aryDepart,m_cbDepart,strSql);
	m_cbDepart.SetCurSel(0);
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEmpQuery::OnOK() 
{
	UpdateData();
	CString strSql;
	CComFunc::GetSql(strSql,48);//查询语句
	strSql.Replace("[XT001]",m_date1.Format("%Y%m%d") );
	strSql.Replace("[XT002]",m_date2.Format("%Y%m%d") );


	if( ! m_strKh.IsEmpty() )
	{
		m_strKh.Replace("'","");//过滤掉单引号
		m_strKh.Replace(";","");//过滤分号
		strSql+=" AND  T1.sickbm like '"+m_strKh+"%'";

	}

	if( ! m_strXm.IsEmpty() )
	{
		m_strXm.Replace("'","");//过滤掉单引号
		m_strXm.Replace(";","");//过滤分号
		strSql+=" AND T1.sickName like '"+m_strXm+"%'";

	}

	int	iCbSel=m_cbDepart.GetCurSel();
	if( !(iCbSel ==CB_ERR || iCbSel == 0) ) 
	{
		strSql+=" AND  T3.部门编码='"+m_aryDepart[iCbSel]+"'";

	}


	strSql+=" ORDER By T1.riqi,T1.sickbm";	//排序方式

	vector<int> vtCols;
	for(int i=8 ; i<12+8;i++) //从第8列开始,共12列需要统计数字
		vtCols.push_back(i);
	vector<double> vtCount(vtCols.size(),0); //初化为0

	CComFunc::ReadDataForGrid(m_grid,strSql,m_grid.GetColumnCount(),vtCols,vtCount,0);
	m_grid.AutoSize();
}
