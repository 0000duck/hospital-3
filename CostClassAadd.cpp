// CostClassAadd.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "CostClassAadd.h"
#include "comfunc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCostClassAadd dialog


CCostClassAadd::CCostClassAadd(CWnd* pParent /*=NULL*/)
	: CDialog(CCostClassAadd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCostClassAadd)
	m_cmt = _T("");
	m_name = _T("");
	m_order = 0;
	//}}AFX_DATA_INIT
}


void CCostClassAadd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCostClassAadd)
	DDX_Text(pDX, IDC_EDIT_CMT, m_cmt);
	DDX_Text(pDX, IDC_EDIT_NAME1, m_name);
	DDX_Text(pDX, IDC_EDIT_ORDER, m_order);
	DDV_MinMaxLong(pDX, m_order, 0, 100000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCostClassAadd, CDialog)
	//{{AFX_MSG_MAP(CCostClassAadd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCostClassAadd message handlers

void CCostClassAadd::OnOK() 
{
	UpdateData();
	if( m_name.IsEmpty() ){
		AfxMessageBox("项目分类名称不能为空");
		return;
	
	}
	CString strSql;
	strSql.Format(" INSERT INTO lsq_cost_class_a(id,name,seq,rem) values(\
		(select NVL(max(ID),0)+1 FROM lsq_cost_class_a ),'%s',%ld,'%s')",\
		m_name,m_order,m_cmt);
	if( !CComFunc::WriteSql(strSql) )
	{	
		AfxMessageBox("添加项目分类错误,请重试!");
		return;
	}
	AfxMessageBox("项目分类新增成功!");
	m_name="";
	m_cmt="";
	m_order=0;
	UpdateData(false);


}

BOOL CCostClassAadd::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
