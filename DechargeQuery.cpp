// DechargeQuery.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "DechargeQuery.h"
#include "OperatorSel.h"
#include "CostClassAb.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDechargeQuery dialog


CDechargeQuery::CDechargeQuery(CMSHFlexGrid &p,CWnd* pParent /*=NULL*/)
	: CDialog(CDechargeQuery::IDD, pParent),m_grid(p)
{
	//{{AFX_DATA_INIT(CDechargeQuery)
	m_date1 = COleDateTime::GetCurrentTime();
	m_date2 = COleDateTime::GetCurrentTime();
	m_strSyr = _T("");
	//}}AFX_DATA_INIT
	m_strJsr=m_strRsr=m_strSpr=BLANKSTR;
}


void CDechargeQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDechargeQuery)
	DDX_Control(pDX, IDC_COMBO_B, m_sortB);
	DDX_Control(pDX, IDC_COMBO_A, m_sortA);
	DDX_Control(pDX, IDC_EDIT_YSR, m_ysr);
	DDX_Control(pDX, IDC_EDIT_SPR, m_spr);
	DDX_Control(pDX, IDC_EDIT_JSR, m_jsr);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_date2);
	DDX_Text(pDX, IDC_EDIT_SYR, m_strSyr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDechargeQuery, CDialog)
	//{{AFX_MSG_MAP(CDechargeQuery)
	ON_BN_CLICKED(IDC_BUTTON_JSR, OnButtonJsr)
	ON_BN_CLICKED(IDC_BUTTON_RSR, OnButtonRsr)
	ON_BN_CLICKED(IDC_BUTTON_SPR, OnButtonSpr)
	ON_CBN_SELCHANGE(IDC_COMBO_A, OnSelchangeComboA)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDechargeQuery message handlers

void CDechargeQuery::OnOK() 
{
	UpdateData();

	const char * argu_01="[XT001]";
	CComFunc::comSetGridHeader(m_grid,GRID_HEADER_ID); 
	CComFunc::GetSql(strSql,QUERY_SQL_ID);
	CString strTmp,strSort;
	//m_date1.Format("%Y%m%d");
	//m_date2.Format("%Y%m%d");
	strTmp.Format(" AND d1 between to_date(%s,'yyyymmdd') and to_date(%s,'yyyymmdd') ",
		m_date1.Format("%Y%m%d"),m_date2.Format("%Y%m%d"));
	//类别选项
	int iAsel=m_sortA.GetCurSel();
	int iBsel=m_sortB.GetCurSel();
	if(  iAsel == CB_ERR   )
		strSort=BLANKSTR;
	else{
		if(  !( iBsel ==CB_ERR ) )
		{
			strSort.Format(" AND a.id2=%ld ",atol(arrayB[ iBsel ] ) );

		}
		else strSort.Format(" AND b.id2=%ld ",atol(arrayA[ iAsel] ) );

	}
	strTmp+=strSort;
	//操作人员选择
	if( !m_strJsr.IsEmpty() ) 
	{
		strSort.Format(" AND a.jsr=%ld ",atol(m_strJsr) );
		strTmp+=strSort;
	}
	if( !m_strRsr.IsEmpty())
	{	strSort.Format(" AND a.ysr=%ld ",atol(m_strRsr) );
		strTmp+=strSort;
	}
	if( !m_strSpr.IsEmpty() )
	{
		strSort.Format(" AND a.spr=%ld ",atol(m_strSpr) );
		strTmp+=strSort;
	}
	if( !m_strSyr.IsEmpty() ){

		strSort.Format(" AND a.syr like '%s%%' ",m_strSyr );
		strTmp+=strSort;
	}

	strSql.Replace(argu_01,strTmp );
	int iCol[]={11,13};

	CComFunc::ReadDataForGrid(strSql,m_grid,iCol,2);
/*

	CProgressIndicate pq;
	pq.pDialog= this;

	pq.pThreadFunction =// QueryGhList;
	pq.DoModal();
*/
	CDialog::OnOK();
	
}

void CDechargeQuery::OnButtonJsr() //经手人
{
	COperatorSel os;
	if( os.DoModal() == IDOK)
	{
		m_strJsr=os.strID;
		m_jsr.SetWindowText(os.strName);
	}
	else{
		m_jsr.SetWindowText(BLANKSTR);
		m_strJsr=BLANKSTR;
	}
	
}

void CDechargeQuery::OnButtonRsr() //验收人
{
	COperatorSel os;
	if( os.DoModal() == IDOK)
	{
		m_strRsr=os.strID;
		m_ysr.SetWindowText(os.strName);
	}
	else
	{
		m_strRsr=BLANKSTR;
		m_ysr.SetWindowText(m_strRsr);

	}
	
}

void CDechargeQuery::OnButtonSpr() //审批人
{
	COperatorSel os;
	if( os.DoModal() == IDOK)
	{
		m_strSpr=os.strID;
		m_spr.SetWindowText(os.strName);
	}
	else{
		m_strSpr=BLANKSTR;
		m_spr.SetWindowText(m_strSpr);
	}

	
}

BOOL CDechargeQuery::OnInitDialog() 
{
	CDialog::OnInitDialog();

	arrayA.RemoveAll();
	long i;
	CComFunc::GetSql(strSql,CCostClassAb::COST_A_SQLID);
//初始化类别框
	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(! recSet->adoEOF){
			i=0;
			arrayA.Add(CComFunc::GetSqlItem(i++));
			m_sortA.AddString(CComFunc::GetSqlItem(i));
			recSet->MoveNext();
		}
		recSet->Close();
	}
	catch(_com_error e)
	{
		strSql.Format("出现错误,请检查SQL=%ld 语句...",CCostClassAb::COST_A_SQLID);
		AfxMessageBox(strSql);
		return false;
	}		
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDechargeQuery::OnSelchangeComboA() 
{
	const char * argu_01="[XT001]";
	arrayB.RemoveAll();
	m_sortB.ResetContent();
	CComFunc::GetSql(strSql,CCostClassAb::COST_B_SQLID);
	int i;
	CString str2;
	str2.Format(" ID2=%s AND ",arrayA[m_sortA.GetCurSel()] );

	strSql.Replace(argu_01,str2);
	try{
	
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 

		while(! recSet->adoEOF){
			i=0;
			arrayB.Add(CComFunc::GetSqlItem(i++));
			m_sortB.AddString(CComFunc::GetSqlItem(i));

			recSet->MoveNext();

		}
		recSet->Close();


	}
	catch(_com_error e)
	{
		strSql.Format("出现错误,请检查SQL=%ld 语句...",CCostClassAb::COST_B_SQLID);
		AfxMessageBox(strSql);
		return ;
	}		
}


