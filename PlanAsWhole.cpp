// PlanAsWhole.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "PlanAsWhole.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlanAsWhole dialog


CPlanAsWhole::CPlanAsWhole(CWnd* pParent /*=NULL*/)
	: CDialog(CPlanAsWhole::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPlanAsWhole)
	m_szAcc = _T("");
	//}}AFX_DATA_INIT
}


void CPlanAsWhole::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlanAsWhole)
	DDX_Control(pDX, IDC_COMBO_YEAR, m_cmYear);
	DDX_Text(pDX, IDC_EDIT_ACCURAL, m_szAcc);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPlanAsWhole, CDialog)
	//{{AFX_MSG_MAP(CPlanAsWhole)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlanAsWhole message handlers

BOOL CPlanAsWhole::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CString strTmp;
	int year=COleDateTime::GetCurrentTime().GetYear();

	for(long i=0; i<3; ++i ){
		strTmp.Format("%d",year-- );
		m_cmYear.AddString(strTmp);
	}
	m_cmYear.SetCurSel(0);
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPlanAsWhole::OnOK() 
{
	UpdateData();
	CString strTmp;

	m_cmYear.GetLBText(m_cmYear.GetCurSel(),strTmp);
	long iYear=atol(strTmp);
	double dbAccural=atof(m_szAcc);

	strTmp.Format("请确认要进行 %d 年,年度统筹利率: %.2f%% 结算吗?",iYear,dbAccural);
	if( AfxMessageBox(strTmp,MB_YESNO)== IDNO )return;


	long succ;
	CString str1,strYear;

	_CommandPtr cmd;
	_ParameterPtr par;
	cmd.CreateInstance(__uuidof( Command ));
	par.CreateInstance(__uuidof( Parameter));

	_variant_t vNULL;
	vNULL.vt = VT_ERROR;
	vNULL.scode = DISP_E_PARAMNOTFOUND;
	try{
		cmd->put_CommandType(adCmdStoredProc) ;
		par=cmd->CreateParameter(_bstr_t("iyear"),adInteger,adParamInput,4,iYear);
		cmd->Parameters->Append( par );

		par=cmd->CreateParameter(_bstr_t("accural"),adDouble,adParamInput,8,dbAccural);
		cmd->Parameters->Append( par);

		par=cmd->CreateParameter(_bstr_t("ret"),adInteger,adParamOutput,0,vNULL);
		cmd->Parameters->Append( par);

		cmd->put_CommandText(_bstr_t("prc_plan_as_whole"));  //统筹利息结算过程(num,num,num)
		cmd->ActiveConnection=HospitalConnect;
		cmd->Execute(NULL,NULL,adCmdStoredProc);
		
		succ=(long)cmd->Parameters->GetItem("ret")->Value;

		cmd.Detach();
		par.Detach();
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
		return ;
	}	
	switch (succ)
	{
	case 0: AfxMessageBox("结算成功");
			break;
	case 1: AfxMessageBox("当前所选年份已经结算过统筹利息");
			break;
	default: AfxMessageBox("出现其它未知错误,请检查系统环境");
	}

}
