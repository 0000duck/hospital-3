// ReportEmpJSB.cpp: implementation of the CReportEmpJSB class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his3.h"
#include "ReportEmpJSB.h"
#include "ProgressIndicate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReportEmpJSB::CReportEmpJSB()
{
}

CReportEmpJSB::~CReportEmpJSB()
{

}

BOOL CReportEmpJSB::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	fontTitle.CreatePointFont(220,"姚体");
	
	CString	strTitle=CComFunc::GetString("SELECT ds1 FROM lsq_mixed WHERE ds3='TITLE' AND ds4='AAB' ");
	SetWindowText(strTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	CString strTmp;
	int year=COleDateTime::GetCurrentTime().GetYear();

	for(long i=0; i<5; ++i ){
		strTmp.Format("%d",year-- );
		m_comYear.AddString(strTmp);
	}
	m_comYear.SetCurSel(0);


	//GRID_ID=27
	CComFunc::comSetGridHeader(m_grid,GRID_ID);

	
	return TRUE;  // return TRUE unless you set the focus to a control

}

void CReportEmpJSB::OnOK() //基金结算表
{
	UpdateData();

	CProgressIndicate pq;
	pq.pDialog= this;

	pq.pThreadFunction = GenerateJSB;
	pq.DoModal();

	CString strSql="SELECT * FROM v_balance_count";
	CComFunc::comSetGridHeader(m_grid,GRID_ID);
	CComFunc::ReadDataForGrid(strSql,m_grid);	

}

UINT CReportEmpJSB::GenerateJSB(LPVOID ps)
{
	CReportEmpJSB * pd =(CReportEmpJSB *) ((CProgressIndicate *) ps )->pDialog ;
	pd->UpdateData();

	long succ;
	CString str1,strYear;

	pd->m_comYear.GetLBText(pd->m_comYear.GetCurSel(),strYear);

	_CommandPtr cmd;
	_ParameterPtr par;
	cmd.CreateInstance(__uuidof( Command ));
	par.CreateInstance(__uuidof( Parameter));

	_variant_t vNULL;
	vNULL.vt = VT_ERROR;
	vNULL.scode = DISP_E_PARAMNOTFOUND;
	try{
		cmd->put_CommandType(adCmdStoredProc) ;
		par=cmd->CreateParameter(_bstr_t("year"),adInteger,adParamInput,4,atol(strYear));
		cmd->Parameters->Append( par );

		par=cmd->CreateParameter(_bstr_t("ret"),adInteger,adParamOutput,0,vNULL);
		cmd->Parameters->Append( par);

		cmd->put_CommandText(_bstr_t("prc_balance"));
		cmd->ActiveConnection=HospitalConnect;
		cmd->Execute(NULL,NULL,adCmdStoredProc);
		
		succ=(long)cmd->Parameters->GetItem("ret")->Value;

		cmd.Detach();
		par.Detach();
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
		goto _EXIT;
	}	
	
_EXIT:	
	((CProgressIndicate *)ps)->ConnectFlag =1;
	((CProgressIndicate *)ps)->SendMessage(WM_CLOSE,NULL,NULL);
	
	return true;


}


