// MedConsumeQuery.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "MedConsumeQuery.h"
#include "ProgressIndicate.h"
#include "ReportMedConsume.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMedConsumeQuery dialog


CMedConsumeQuery::CMedConsumeQuery(CWnd* pParent /*=NULL*/)
	: CDialog(CMedConsumeQuery::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMedConsumeQuery)
	m_date1 = COleDateTime::GetCurrentTime();
	m_date2 = COleDateTime::GetCurrentTime();
	m_strBM = _T("");
	m_strPY = _T("");
	//}}AFX_DATA_INIT
	typecode1.RemoveAll();
	typecode2.RemoveAll();
}


void CMedConsumeQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMedConsumeQuery)
	DDX_Control(pDX, IDC_COMBO2, m_combo2);
	DDX_Control(pDX, IDC_COMBO1, m_combo1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_date2);
	DDX_Text(pDX, IDC_EDIT_BM, m_strBM);
	DDX_Text(pDX, IDC_EDIT_PY, m_strPY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMedConsumeQuery, CDialog)
	//{{AFX_MSG_MAP(CMedConsumeQuery)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_BN_CLICKED(IDOK2, OnOk2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMedConsumeQuery message handlers

void CMedConsumeQuery::OnOK() 
{
	UpdateData();

	CProgressIndicate pq;
	pq.pDialog= this;

	pq.pThreadFunction = QueryData;
	pq.DoModal();

	
	
	CDialog::OnOK();
}

UINT CMedConsumeQuery::QueryData(LPVOID ps)
{
	CReportMedConsume *pf=(CReportMedConsume *)theApp.pParentGrid.pGrid; //FormView窗口
	CMedConsumeQuery * pd =(CMedConsumeQuery *) ((CProgressIndicate *) ps )->pDialog ; //条件窗口
	pd->UpdateData();

	CString strSql,str_1,str_2,strRep("");
	pf->m_grid.SetRedraw(false);

	CComFunc::GetSql(strSql,CMedConsumeQuery::MEDQUERYID);
	
	strSql.Replace("[XT001]",pd->m_date1.Format("%Y%m%d") );
	strSql.Replace("[XT002]",pd->m_date2.Format("%Y%m%d") );

	int iSel1=pd->m_combo1.GetCurSel();
	int iSel2=pd->m_combo2.GetCurSel();
	
	if( iSel1 == CB_ERR  || iSel1 == 0 ) //不使用类别选择
	{
		if( ! pd->m_strPY.IsEmpty() )strRep.Format(" AND py like '%s%%' ",pd->m_strPY );
		else if( ! pd->m_strBM.IsEmpty() )strRep.Format(" AND bm='%s' ",pd->m_strBM );

	}
	else {
		
		if( iSel2 == CB_ERR || iSel2 == 0 )
			strRep.Format(" AND DLBM='%s' ",pd->typecode1[iSel1] );
		else
			strRep.Format(" AND DLBM='%s' AND XLBM='%s' ",pd->typecode1[ iSel1 ],pd->typecode2[ iSel2 ] );


	}
	
	strSql.Replace("[XT003]",strRep); //自由参数
	
	CComFunc::comSetGridHeader(pf->m_grid,CReportMedConsume::COL_ID);	
	int iSumCol[]={7,8,9,10};

	CComFunc::ReadDataForGrid(strSql,pf->m_grid,iSumCol,sizeof(iSumCol)/sizeof(int) );//根据表格列数读取数据表，表格列数要和SELECT 字段数量相匹配

	pf->m_grid.SetRedraw(true);
	
	((CProgressIndicate *)ps)->ConnectFlag =1;
	((CProgressIndicate *)ps)->SendMessage(WM_CLOSE,NULL,NULL);

	pd->SendMessage(WM_CLOSE,NULL,NULL);
	
	return true;
}

BOOL CMedConsumeQuery::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetWindowText("HOSPTIAL_QUERY");	
	try{
		CComFunc::GetSql(strSql,SQLID);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		m_combo1.AddString(BLANKSTR);
		typecode1.Add(BLANKSTR);
		while(!recSet->adoEOF){
			
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(long(FIRST_ITEM))->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(long(FIRST_ITEM))->Value );
			typecode1.Add(strSql);
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(long(SECOND_ITEM))->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(long(SECOND_ITEM))->Value );
			m_combo1.AddString(strSql);
			recSet->MoveNext();
	
		}
		recSet->Close();
		
	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		recSet->Close();
		return false;
	}		
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMedConsumeQuery::OnSelchangeCombo1() 
{
	int i1=m_combo1.GetCurSel();
	if( i1==CB_ERR ) return; 
	
	typecode2.RemoveAll();
	m_combo2.ResetContent();

	if( i1== 0 ) return;

	try{

		CComFunc::GetSql(strSql,SQLID2);
		strSql.Replace("XXX",typecode1[i1]);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		long i(0);
		typecode2.Add(BLANKSTR);
		m_combo2.AddString(BLANKSTR);
		while(!recSet->adoEOF){
			i=0;			
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(i)->Value );
			typecode2.Add(strSql);
		
			++i;
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(i)->Value );
			m_combo2.AddString(strSql);
			
			recSet->MoveNext();
		}
		recSet->Close();
		

		
	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		recSet->Close();
		return ;
	}			
}

void CMedConsumeQuery::OnOk2() 
{
	CReportMedConsume *pf=(CReportMedConsume *)theApp.pParentGrid.pGrid; //FormView窗口

	CComFunc::ToExcel(&pf->m_grid);	
	
}
