// ReportUsedAllQuery.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "ReportUsedAllQuery.h"
#include "ProgressIndicate.h"
#include "ReportUsedAll1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportUsedAllQuery dialog


CReportUsedAllQuery::CReportUsedAllQuery(CWnd* pParent /*=NULL*/)
	: CDialog(CReportUsedAllQuery::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReportUsedAllQuery)
	strKh = _T("");
	strXm = _T("");
	//}}AFX_DATA_INIT
	sql_cols=0;
}


void CReportUsedAllQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportUsedAllQuery)
	DDX_Control(pDX, IDEXCEL, m_b3);
	DDX_Control(pDX, IDCANCEL, m_b2);
	DDX_Control(pDX, IDOK, m_b1);
	DDX_Control(pDX, IDC_COMBO_YEAR, comYear);
	DDX_Text(pDX, IDC_EDITC_KH, strKh);
	DDX_Text(pDX, IDC_EDITC_XM, strXm);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReportUsedAllQuery, CDialog)
	//{{AFX_MSG_MAP(CReportUsedAllQuery)
	ON_BN_CLICKED(IDEXCEL, OnExcel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportUsedAllQuery message handlers

BOOL CReportUsedAllQuery::OnInitDialog() 
{
	CDialog::OnInitDialog();
	const int SEL_YEAR_NUM=4;

	CString str1;	
	int iyear=atoi(theApp.strOracleYear);
	for(int x=0; x< SEL_YEAR_NUM; x++)
	{
		str1.Format("%d",iyear--);
		comYear.AddString(str1);
	}
	
	comYear.SetCurSel(--x);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CReportUsedAllQuery::OnOK() 
{
//get Sql
	CString strTmp;
	comYear.GetLBText(comYear.GetCurSel(), strTmp);
	iYear=atoi(strTmp);

	try{
		_CommandPtr cmd;
		_ParameterPtr par;
		cmd.CreateInstance(__uuidof( Command ));
		par.CreateInstance(__uuidof( Parameter));
		
		_variant_t vNULL;
		vNULL.vt = VT_ERROR;
		vNULL.scode = DISP_E_PARAMNOTFOUND;
		
		cmd->put_CommandType(adCmdStoredProc) ;
		par=cmd->CreateParameter(_bstr_t("iYear"),adUnsignedInt,adParamInput,20,_bstr_t(strTmp));
		cmd->Parameters->Append( par );


		par=cmd->CreateParameter(_bstr_t("strSql"),adVarChar,adParamOutput,2000,vNULL );
		cmd->Parameters->Append( par );
		
		cmd->put_CommandText(_bstr_t("SQL_GEN"));
		cmd->ActiveConnection=HospitalConnect;
		cmd->Execute(NULL,NULL,adCmdStoredProc);
		
		strSql=cmd->Parameters->GetItem("strSql")->Value.bstrVal;
		if ( !strTmp.IsEmpty() ) {
		}
		
		cmd.Detach();
		par.Detach();
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
		return;
	}

	
	CProgressIndicate pq;
	pq.pDialog= this;

	pq.pThreadFunction = QueryList;
	pq.DoModal();

	CDialog::OnOK();
}

UINT CReportUsedAllQuery::QueryList(LPVOID ps)
{
	CReportUsedAll *pf=(CReportUsedAll*)theApp.pParentGrid.pGrid;
	CReportUsedAllQuery * pd =(CReportUsedAllQuery *) ((CProgressIndicate *) ps )->pDialog ;
	pd->UpdateData();

	CString str1,strGhtype,strname;
	pf->m_grid.SetRedraw(false);
	
	pf->m_grid.SetRows(2);
	pf->m_grid.AddItem(BLANKSTR,_variant_t(1L) );
	pf->m_grid.SetRows(2);
	
	str1.Format("%s:%d年",pf->TITLE,pd->iYear);

	pf->GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(str1);
	

	int COLS=pf->m_grid.GetCols(0)-1;
	long row,col,i;
	double price(0),add[]={0,0,0,0,0,0,0,0};
	const int SUM_COMPUTE_COL=7;

	try{
		pd->UpdateData();
		if( !pd->strKh.IsEmpty() ) pd->strSql+=" WHERE 卡号 like '"+pd->strKh+"%'";
		if( !pd->strXm.IsEmpty() ){
			//查询是否有引号等特殊字符进行剔除，否则容易引起SQL崩溃
			pd->strSql+=" WHERE 姓名 like '"+pd->strXm+"%'";
		}

		recSet->Open(_bstr_t(pd->strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		row=1;

		while(!recSet->adoEOF){
			col=0;
			price=0;
			for(i=0;i< COLS ;i++)
			{
				str1=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(i))->Value.vt==VT_NULL? _variant_t(BLANKSTR) :recSet->GetFields()->GetItem(_variant_t(i))->Value);

				if( i >= SUM_COMPUTE_COL  )
				{
					if( str1.IsEmpty() )str1="0";
					add[i-SUM_COMPUTE_COL]+=atof(str1);
				}
				
				pf->m_grid.SetTextMatrix(row,i,str1);
			}
			row++;
			pf->m_grid.AddItem(BLANKSTR,_variant_t(row));

			recSet->MoveNext();
			
		}
		recSet->Close();
	}
	catch(_com_error e)
	{
		AfxMessageBox(pd->strSql);
		recSet->Close();
	
		return false;
	}	

	pf->m_grid.SetRow(row);
	pf->m_grid.SetCol(1);
	pf->m_grid.SetCellBackColor(LSQ_BACKCOLOR);
//	strSql.Format(" %ld ",row-1);

	pf->m_grid.SetTextMatrix(row,1,"合计");	
//	pf->m_grid.SetTextMatrix(row,3,strSql);
	for(int count=1;count< COLS;count++){
		pf->m_grid.SetCol(count);
		pf->m_grid.SetCellBackColor(LSQ_BACKCOLOR);
		if( count >= SUM_COMPUTE_COL ){
			str1.Format("%.2f",add[count-SUM_COMPUTE_COL]);
			pf->m_grid.SetTextMatrix(row,count,str1);	

		}
	}
//	CComFunc::SetGridColColor(6,pf->m_grid);

	pf->m_grid.SetRedraw(true);
	
	((CProgressIndicate *)ps)->ConnectFlag =1;
	((CProgressIndicate *)ps)->SendMessage(WM_CLOSE,NULL,NULL);

	pd->SendMessage(WM_CLOSE,NULL,NULL);
	
	return true;
}

void CReportUsedAllQuery::OnExcel() 
{
	CComFunc::ToExcel( &((CReportUsedAll*)theApp.pParentGrid.pGrid)->m_grid);	
	
}
