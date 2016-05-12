// CostClass2Add.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "CostClass2Add.h"
#include "costClassAb.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCostClass2Add dialog


CCostClass2Add::CCostClass2Add(CWnd* pParent /*=NULL*/)
	: CDialog(CCostClass2Add::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCostClass2Add)
	m_name = _T("");
	m_rem = _T("");
	m_seq = 0;
	//}}AFX_DATA_INIT
}


void CCostClass2Add::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCostClass2Add)
	DDX_Control(pDX, IDC_COMBO1, m_depart);
	DDX_Text(pDX, IDC_EDIT_MC, m_name);
	DDX_Text(pDX, IDC_EDIT_REM, m_rem);
	DDX_Text(pDX, IDC_EDIT_SEQ, m_seq);
	DDV_MinMaxUInt(pDX, m_seq, 0, 10000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCostClass2Add, CDialog)
	//{{AFX_MSG_MAP(CCostClass2Add)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCostClass2Add message handlers

BOOL CCostClass2Add::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetWindowText("成本类别2新增");	

	long i,row(1);
	CString strSql;
	CComFunc::GetSql(strSql,CCostClassAb::COST_A_SQLID);

	arrayDepart.RemoveAll();
	
	try{
	
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 

		while(! recSet->adoEOF){
			i=0;
			strSql=CComFunc::GetSqlItem(i);//(char*)_bstr_t(recSet->GetFields()->GetItem(long(i))->Value.vt == VT_NULL ? _variant_t(BLANKSTR):recSet->GetFields()->GetItem(long(i))->Value );
			arrayDepart.Add(strSql);
			i++;
			strSql=CComFunc::GetSqlItem(i);//(char*)_bstr_t(recSet->GetFields()->GetItem(long(i))->Value.vt == VT_NULL ? _variant_t(BLANKSTR):recSet->GetFields()->GetItem(long(i))->Value );
			m_depart.AddString(strSql);

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

	InitMember();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCostClass2Add::OnOK() 
{
	UpdateData();	// TODO: Add extra validation here
	if ( m_name.IsEmpty() ) {
		AfxMessageBox("请填写分类项目名称");
		return;
	}
	CString strSql;
	strSql.Format("insert into lsq_cost_class_b(id,id2,name,seq,rem ) values \
		( (select NVL(max(ID),0)+1 FROM lsq_cost_class_b ),%ld,'%s',%ld,'%s' ) ",
		atol(arrayDepart[m_depart.GetCurSel()]),m_name,m_seq,m_rem );

	if( !CComFunc::WriteSql(strSql) )
	{	
		AfxMessageBox("添加项目分类2错误,请重试!");
		return;
	}
	AfxMessageBox("项目分类2新增成功!");
	InitMember();
	UpdateData(false);
	
}

void CCostClass2Add::OnSelchangeCombo1() 
{
	CString strSql;
	strSql.Format(" select NVL(max(SEQ),0)+1 FROM lsq_cost_class_b WHERE id2=%ld ",
		atol(arrayDepart[m_depart.GetCurSel()]) );
	m_seq=atol(CComFunc::GetString(strSql));
	UpdateData(false);
}

void CCostClass2Add::InitMember()
{
	m_name="";
	m_rem="";
	m_depart.SetCurSel(0);
	OnSelchangeCombo1();
}
