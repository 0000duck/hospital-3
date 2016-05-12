// DialogReportView.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "DialogReportView.h"
#include "comFunc.h"
#include "mshflexgrid.h"
#include "progressindicate.h"
#include "dialogReportView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogReportView dialog


CDialogReportView::CDialogReportView(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogReportView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogReportView)
	m_date1 = COleDateTime::GetCurrentTime();
	m_date2 = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
	strYB=BLANKSTR;
}


void CDialogReportView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogReportView)
	DDX_Control(pDX, IDOK_YB, m_BT4);
	DDX_Control(pDX, IDC_COMBO1, m_ry);
	DDX_Control(pDX, IDBUTTON_TOEXCEL, m_BT3);
	DDX_Control(pDX, IDCANCEL, m_BT2);
	DDX_Control(pDX, IDOK, m_BT1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_date2);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogReportView, CDialog)
	//{{AFX_MSG_MAP(CDialogReportView)
	ON_BN_CLICKED(IDBUTTON_TOEXCEL, OnToexcel)
	ON_BN_CLICKED(IDOK_YB, OnYb)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogReportView message handlers

BOOL CDialogReportView::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CString strSql;
	strSql=CComFunc::GetString( "SELECT sql FROM lsq_sql_statemnet WHERE id=3 ");
	//两列,第一列为编码,第二列为 姓名,获取的为新药房人员信息
	long i;
	saRy.RemoveAll();

	saRy.Add(BLANKSTR);
	m_ry.AddString(BLANKSTR);
	try{

		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect, adOpenDynamic ,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			i=0;
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ? _variant_t(BLANKSTR):recSet->GetFields()->GetItem(i)->Value );
			saRy.Add(strSql);
			i++;
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ? _variant_t(BLANKSTR):recSet->GetFields()->GetItem(i)->Value );
			m_ry.AddString(strSql);

			recSet->MoveNext();
			
		}
		recSet->Close();
		
	}
	catch(... )
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		recSet->Close();
		return  false;
	}

	if( ! CComFunc::comSetGridHeader(m_grid,1) ) return false;
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogReportView::OnOK() 
{
	CProgressIndicate pq;
	pq.pDialog= this;
	theApp.pParentGrid.pGrid=&m_grid;

	pq.pThreadFunction = ReportView;
	pq.DoModal();

}

BOOL CDialogReportView::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN)
		pMsg->wParam = VK_TAB;
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CDialogReportView::OnToexcel() //输出到 excel
{
	CComFunc::ToExcel(&m_grid);
}

UINT CDialogReportView::ReportView(LPVOID p)
{
	CMSHFlexGrid *pGrid=(CMSHFlexGrid*)theApp.pParentGrid.pGrid;
	CDialogReportView * pd =(CDialogReportView *) ((CProgressIndicate *) p )->pDialog ;

	pd->UpdateData();
	pGrid->SetRows(2);
	pGrid->AddItem(BLANKSTR,_variant_t(1L));
	pGrid->SetRows(2);

	CString strSql,str2;
//	strSql=CComFunc::GetString( "SELECT sql FROM lsq_sql_statemnet WHERE id=1 ");
	CComFunc::GetSql(strSql,1);
	strSql.Replace("XT001",pd->m_date1.Format("%Y%m%d") ); // 时间 1
	strSql.Replace("XT002",pd->m_date2.Format("%Y%m%d") ); // 时间 2
	int rySel=pd->m_ry.GetCurSel();
	if( rySel ==0 ||  rySel == CB_ERR ){
		strSql.Replace("XT003"," 收费员 is Not NULL ");
		str2.Format("%s --- %s :期间所有收费情况汇总",pd->m_date1.Format("%Y/%m/%d"),pd->m_date2.Format("%Y/%m/%d") );
	}
	else
	{
		str2="收费员="+pd->saRy[rySel];
		strSql.Replace("XT003",str2 );
		pd->m_ry.GetLBText(rySel,str2);
		str2.Format("%s  %s --- %s: 期间收费情况汇总",str2,pd->m_date1.Format("%Y/%m/%d"),pd->m_date2.Format("%Y/%m/%d"));
	}
	pd->SetWindowText(str2);

	if ( ! pd->strYB.IsEmpty() ){ // 进行医保人员汇总统计
		
		str2=strSql;
		strSql=pd->strYB;
		strSql.Replace("XT001",str2);

	}
	

	long row=1;
	long cols=0,i;
	pGrid->SetRedraw(false);
	double *pSum=NULL;
	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect, adOpenDynamic ,adLockOptimistic,adCmdText); 
		cols=recSet->GetFields()->Count;
		pSum=new double[cols];
		if( pSum == NULL) throw double();
		for( i=0 ; i< cols ; i++ ) pSum[i]=0;
		while(!recSet->adoEOF){
		//第一列为序号列,自个填入
			str2.Format("%ld",row);
			pGrid->SetTextMatrix(row,0,str2);
			for( i=0 ; i < cols ; i++ )
			{
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ? "0":recSet->GetFields()->GetItem(i)->Value );
				pGrid->SetTextMatrix(row,i+1,strSql);
				pSum[i]+=atof(strSql);
			}

			row++;
			pGrid->AddItem(BLANKSTR,_variant_t(row) );

			recSet->MoveNext();
	
		}
		recSet->Close();
		
	}
	catch(... )
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		recSet->Close();
		return false;
	}
	//填写合计
	pGrid->SetTextMatrix(row,1,"合 计");
	for(i=1 ; i< cols ; i++ )
	{
		strSql.Format("%.2f",pSum[i]);
		pGrid->SetTextMatrix(row,i+1,strSql);
	}

	CComFunc::SetGridColColor(1,*pGrid);
	CComFunc::GridSelRow(*pGrid,row);
	pGrid->SetRedraw(true);

	((CProgressIndicate *)p)->ConnectFlag =1;
	((CProgressIndicate *)p)->SendMessage(WM_CLOSE,NULL,NULL);

	return true;

}

void CDialogReportView::OnYb()  // 医保收费统计
{
	CProgressIndicate pq;
	pq.pDialog= this;
	theApp.pParentGrid.pGrid=&m_grid;
	CComFunc::GetSql(strYB,23);// 医保人员汇总语句

	pq.pThreadFunction = ReportView;
	pq.DoModal();

	strYB=BLANKSTR;
}


