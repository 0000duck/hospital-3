// Medcode.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "Medcode.h"
#include "medcodeModify.h"

#include "medcodeAdd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMedcode dialog


CMedcode::CMedcode(CWnd* pParent /*=NULL*/)
	: CDialog(CMedcode::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMedcode)
	m_bm = _T("");
	m_py = _T("");
	//}}AFX_DATA_INIT
	
}


void CMedcode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMedcode)
	DDX_Control(pDX, IDC_COMBO2, m_combo2);
	DDX_Control(pDX, IDC_COMBO1, m_combo1);
	DDX_Text(pDX, IDC_EDIT_BM, m_bm);
	DDX_Text(pDX, IDC_EDIT_PY, m_py);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMedcode, CDialog)
	//{{AFX_MSG_MAP(CMedcode)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_BN_CLICKED(IDOK_MODIFY, OnModify)
	ON_BN_CLICKED(IDOK_ADD, OnAdd)
	ON_COMMAND(ID_MENUITEM_BCYB_ZJB, OnMenuitemBcybZjb)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMedcode message handlers

BOOL CMedcode::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetWindowText("药品编码管理");
	typeCode.RemoveAll();
	
	
	try{
		CComFunc::GetSql(strSql,SQLID);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		m_combo1.AddString(BLANKSTR);
		typeCode.Add(BLANKSTR);
		while(!recSet->adoEOF){
			
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(long(FIRST_ITEM))->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(long(FIRST_ITEM))->Value );
			typeCode.Add(strSql);
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(long(SECOND_ITEM))->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(long(SECOND_ITEM))->Value );
			m_combo1.AddString(strSql);
			recSet->MoveNext();
	
		}
		recSet->Close();
		
	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return false;
	}		

	CComFunc::comSetGridHeader(m_grid,COL_ID);	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMedcode::OnSelchangeCombo1() 
{
	int iSel=m_combo1.GetCurSel();
	
	typeCode_1.RemoveAll();
	m_combo2.ResetContent();

	if( iSel ==0 ){

		return;
	}


	try{
		CComFunc::GetSql(strSql,SQLID2 );
		strSql.Replace("XXX",typeCode[iSel] );

		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
	
		m_combo2.AddString(BLANKSTR);
		typeCode_1.Add(BLANKSTR);
		
		while(!recSet->adoEOF){
			
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(long(FIRST_ITEM))->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(long(FIRST_ITEM))->Value );
			typeCode_1.Add(strSql);
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(long(SECOND_ITEM))->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(long(SECOND_ITEM))->Value );
			m_combo2.AddString(strSql);
			recSet->MoveNext();
	
		}
		recSet->Close();
		
	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return ;
	}		


}

void CMedcode::OnOK() 
{
	UpdateData();
	//构造SQL语句
	CComFunc::GetSql(strSql,SQLID3);

	int i1=m_combo1.GetCurSel();
	int i2=m_combo2.GetCurSel();

	if( i1 != 0 && i1!=CB_ERR ){
		strSql+=" AND t.DLBM='"+typeCode[i1]+"'";
	}
	if( i2 !=0 && i2 != CB_ERR ){
		strSql+=" AND t.XLBM='"+typeCode_1[i2]+"'";
	}

	if( ! m_bm.IsEmpty() ){

		strSql+=" AND bm='"+m_bm+"'";
	}else if ( ! m_py.IsEmpty() )
	{
		strSql+=" AND py like '"+m_py+"%'";

	}
	
	CComFunc::comSetGridHeader(m_grid,COL_ID);	

	CComFunc::ReadDataForGrid(strSql,m_grid);
	
}

void CMedcode::OnModify() 
{
	unsigned long iSel=m_grid.GetRowSel();
	unsigned long iRows=m_grid.GetRows();
	if( iRows<3 || iSel == iRows-1 || iSel == 0  ) {
		AfxMessageBox("请选择要修改的行...");
		return;
	}


	CMedcodeModify mm;
	mm.strBM=m_grid.GetTextMatrix(iSel,BM_POS); //药品编码
	mm.ptrMedcode=this; //子对话框类型数据复制于父对话框
	if( mm.DoModal() == IDOK)  OnOK();

}

void CMedcode::OnAdd() 
{
	CMedcodeAdd ma;
	ma.DoModal();
	
}

void CMedcode::OnMenuitemBcybZjb() //补充医保基金征集表
{
	
}
