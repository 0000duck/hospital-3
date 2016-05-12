// MedQuery.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "MedQuery.h"
#include "reportUsedall.h"
#include "progressIndicate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMedQuery dialog


CMedQuery::CMedQuery(CWnd* pParent /*=NULL*/)
	: CDialog(CMedQuery::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMedQuery)
	m_bm = _T("");
	m_mc = _T("");
	m_py = _T("");
	m_date = COleDateTime::GetCurrentTime();
	m_dateFlag = FALSE;
	//}}AFX_DATA_INIT
}


void CMedQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMedQuery)
	DDX_Control(pDX, IDC_COMBO_KF, m_comboKf);
	DDX_Text(pDX, IDC_EDIT_BM, m_bm);
	DDV_MaxChars(pDX, m_bm, 10);
	DDX_Text(pDX, IDC_EDIT_MC, m_mc);
	DDV_MaxChars(pDX, m_mc, 20);
	DDX_Text(pDX, IDC_EDIT_PY, m_py);
	DDV_MaxChars(pDX, m_py, 10);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date);
	DDX_Check(pDX, IDC_CHECK1, m_dateFlag);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMedQuery, CDialog)
	//{{AFX_MSG_MAP(CMedQuery)
	ON_BN_CLICKED(IDEXCEL, OnExcel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMedQuery message handlers

BOOL CMedQuery::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetWindowText("查询");
	CString strSql;
	try{
		CComFunc::GetSql(strSql,SQLID);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 

		m_comboKf.AddString(BLANKSTR);
		arrayItemKf.Add(BLANKSTR);
		const long FIRST_ITEM=0,SECOND_ITEM=1;
		while(!recSet->adoEOF){
			
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(long(FIRST_ITEM))->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(long(FIRST_ITEM))->Value );
			arrayItemKf.Add(strSql);
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(long(SECOND_ITEM))->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(long(SECOND_ITEM))->Value );
			m_comboKf.AddString(strSql);
		
			recSet->MoveNext();
	
		}
		recSet->Close();
		
	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return false;
	}		
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMedQuery::OnOK() 
{
	UpdateData();

	CProgressIndicate pq;
	pq.pDialog= this;

	pq.pThreadFunction = QueryData;
	pq.DoModal();

	
	CDialog::OnOK();
}

UINT CMedQuery::QueryData(LPVOID ps)
{
	CReportMedQuery *pf=(CReportMedQuery*)theApp.pParentGrid.pGrid;
	CMedQuery * pd =(CMedQuery *) ((CProgressIndicate *) ps )->pDialog ;
	pd->UpdateData();

	CString strSql,str_1,str_2;
	pf->m_grid.SetRedraw(false);
	
	pf->m_grid.AddItem(BLANKSTR,_variant_t(1L) );
	pf->m_grid.SetRows(2);
	
	if( ! pd->m_py.IsEmpty() ){
		str_1.Format(" AND c.py like '%s%%' ",pd->m_py );
	}
	else if ( !pd->m_bm.IsEmpty() ){
		str_1.Format(" AND c.bm='%s' ",pd->m_bm );
	}
	else if ( !pd->m_mc.IsEmpty() ){
		str_1.Format(" AND c.mc like '%s%%' ",pd->m_mc );
	}

	int i=pd->m_comboKf.GetCurSel();
	if( !( i== 0 || i==CB_ERR ) ) str_2.Format(" AND f.kfbm='%s' ",pd->arrayItemKf[i] );

	CComFunc::GetSql(strSql,CMedQuery::MEDQUERYID);
	strSql+=str_1+str_2;
	if( pd->m_dateFlag ){
		strSql+=" AND e.RQ2 <= to_date('"+pd->m_date.Format("%Y%m%d")+"','yyyymmdd')";
	}
//	strSql.Format("SELECT rownum,C.BM,g.l_name ,C.MC,C.GG,C.DW,\
    to_char(E.RQ2,'YYYY-MM-DD'),E.SL ,D.GONGMC,E.JINJIA,E.SELL_PRICE, \
    E.COACH_PRICE,ROUND(E.JINJIA*E.SL,2),ROUND(E.SL*E.SELL_PRICE,2),\
    ROUND(E.SL*(E.SELL_PRICE-E.JINJIA),2),h.xlmc,F.KFMC \
    from medcode c,medlie e,codegys d,storeroom f,lsq_med_type g,medxl h \
    where  e.factorycode=d.gongbm and h.xlbm=c.xlbm and h.dlbm=c.dlbm and  \
    e.ypbm=c.bm and e.kfbm=f.kfbm  and g.l_id(+)=c.l_type and sl !=0 ");
	
	CComFunc::ReadDataForGrid(strSql,pf->m_grid);//根据表格列数读取数据表，表格列数要和SELECT 字段数量相匹配

	pf->m_grid.SetRedraw(true);
	
	((CProgressIndicate *)ps)->ConnectFlag =1;
	((CProgressIndicate *)ps)->SendMessage(WM_CLOSE,NULL,NULL);

	pd->SendMessage(WM_CLOSE,NULL,NULL);
	
	return true;
}

void CMedQuery::OnExcel() 
{
	CComFunc::ToExcel( &((CReportMedQuery*)theApp.pParentGrid.pGrid)->m_grid);	
	
}
