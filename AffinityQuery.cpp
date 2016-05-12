// AffinityQuery.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "AffinityQuery.h"
#include "comFunc.h"
#include <vector>



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAffinityQuery dialog


CAffinityQuery::CAffinityQuery(CWnd* pParent /*=NULL*/)
	: CDialog(CAffinityQuery::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAffinityQuery)
	m_strKh = _T("");
	m_strXm = _T("");
	m_date1 = COleDateTime::GetCurrentTime();
	m_date2 = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(220,"姚体");

}


void CAffinityQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAffinityQuery)
	DDX_Control(pDX, IDC_COMBO_DEPART, m_cbDepart);
	DDX_Control(pDX, IDC_COMBO1, m_cbType);
	DDX_Text(pDX, IDC_EDIT1, m_strKh);
	DDX_Text(pDX, IDC_EDIT2, m_strXm);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_date2);
	//}}AFX_DATA_MAP
	DDX_GridControl(pDX,IDC_CUSTOM_GRID,m_grid);
}


BEGIN_MESSAGE_MAP(CAffinityQuery, CDialog)
	//{{AFX_MSG_MAP(CAffinityQuery)
	ON_BN_CLICKED(ID_BUTTON_EXCEL, OnButtonExcel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAffinityQuery message handlers

BOOL CAffinityQuery::OnInitDialog() 
{
	CDialog::OnInitDialog();
	//供养亲属费用报销

	CComFunc::comSetGridHeader(m_grid,29);
	

	CString TITLE;
	TITLE=CComFunc::GetString(" SELECT ds1 FROM lsq_title_list where ds2='DIALOG' and ds3='TITLE' and ds4='AAZ' ");
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

//查询数据
void CAffinityQuery::OnOK() 
{
	UpdateData();
	CString strSql;
	CComFunc::GetSql(strSql,46);//查询语句
	strSql.Replace("[XT001]",m_date1.Format("%Y%m%d") );
	strSql.Replace("[XT002]",m_date2.Format("%Y%m%d") );
	
	int iCbSel=m_cbType.GetCurSel();
	if( !(iCbSel ==CB_ERR || iCbSel == 0) ) 
	{
		CString strType;
		m_cbType.GetLBText(iCbSel,strType);
		strSql+=" AND  l1.dechargetype='"+strType+"'";

	}

	if( ! m_strKh.IsEmpty() )
	{
		m_strKh.Replace("'","");//过滤掉单引号
		m_strKh.Replace(";","");//过滤分号
		strSql+=" AND l1.kahao1 like '"+m_strKh+"%'";

	}

	if( ! m_strXm.IsEmpty() )
	{
		m_strXm.Replace("'","");//过滤掉单引号
		m_strXm.Replace(";","");//过滤分号
		strSql+=" AND l2.xm like '"+m_strXm+"%'";

	}

	iCbSel=m_cbDepart.GetCurSel();
	if( !(iCbSel ==CB_ERR || iCbSel == 0) ) 
	{
		strSql+=" AND  l3.部门编码='"+m_aryDepart[iCbSel]+"'";

	}


	strSql+=" ORDER By l1.riqi,l2.xm";	//排序方式

	vector<int> vtCols;
	vtCols.push_back(14);
	vtCols.push_back(16);
	vtCols.push_back(17);	
	vtCols.push_back(18); //账户余额列
	vector<double> vtCount(vtCols.size(),0); //初化为0

	CComFunc::ReadDataForGrid(m_grid,strSql,m_grid.GetColumnCount(),vtCols,vtCount,0);
	m_grid.AutoSize();
}

//输出excel
void CAffinityQuery::OnButtonExcel() 
{
	CComFunc::toExcel(m_grid);
}
