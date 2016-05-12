// PersonQuery.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "PersonQuery.h"
#include "comFunc.h"
#include "personQueryRelate.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPersonQuery dialog


CPersonQuery::CPersonQuery(CWnd* pParent /*=NULL*/)
	: CDialog(CPersonQuery::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPersonQuery)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	strTYPE=BLANKSTR;
	lp=NULL;
}


void CPersonQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPersonQuery)
	DDX_Control(pDX, IDC_EDIT_MC, m_mc);
	DDX_Control(pDX, IDC_EDIT_ID, m_id);
	DDX_Control(pDX, IDC_COMBO1, m_depart);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPersonQuery, CDialog)
	//{{AFX_MSG_MAP(CPersonQuery)
	ON_EN_CHANGE(IDC_EDIT_ID, OnChangeEditId)
	ON_EN_CHANGE(IDC_EDIT_MC, OnChangeEditMc)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_COMMAND(ID_MENU_COST_2_ADD, OnMenuCost2Add)
	ON_COMMAND(ID_MENU_COST_2_DEL, OnMenuCost2Del)
	ON_COMMAND(ID_MENU_COST_2_MODIFY, OnMenuCost2Modify)
	ON_COMMAND(ID_MENU_COST_2_RESTORE, OnMenuCost2Restore)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPersonQuery message handlers

void CPersonQuery::OnOK() 
{
	CString strSql,strID,strMc;
	int iSel=m_depart.GetCurSel();

	m_id.GetWindowText(strID);
	m_mc.GetWindowText(strMc);

	if ( (iSel == CB_ERR || iSel == 0 ) && strID.IsEmpty()  && strMc.IsEmpty() ) return;
	CComFunc::comSetGridHeader(m_grid,8);
	CComFunc::GetSql(strSql,5);
	if ( ! ( iSel == CB_ERR || iSel ==0 ) ) strSql+= " AND t.部门编码='"+arrayDepart[iSel]+"'";
	if( ! strID.IsEmpty() ) strSql+=" AND 卡号 like '"+strID+"%'" ;
	if( ! strMc.IsEmpty() ) strSql+=" AND 姓名 like '"+strMc+"%' " ;
	strSql+=CComFunc::GetString(" SELECT sql FROM lsq_sql_statemnet WHERE id= 7 "); //排序
	
	CComFunc::ReadDataForGrid(strSql,m_grid);

	
}

BOOL CPersonQuery::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CComFunc::comSetGridHeader(m_grid,8); //表格头设置

	long i,row(1);
	CString strSql;
	arrayDepart.RemoveAll();


	m_depart.AddString(BLANKSTR);
	arrayDepart.Add(BLANKSTR);
	try{
	
		strSql.Format(" SELECT 部门编码,部门名称 from 厂部门表 where effect=1 order by rank ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 

		while(! recSet->adoEOF){
			i=0;
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(long(i))->Value.vt == VT_NULL ? _variant_t(BLANKSTR):recSet->GetFields()->GetItem(long(i))->Value );
			arrayDepart.Add(strSql);
			i++;
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(long(i))->Value.vt == VT_NULL ? _variant_t(BLANKSTR):recSet->GetFields()->GetItem(long(i))->Value );
			m_depart.AddString(strSql);

			recSet->MoveNext();

		}
		recSet->Close();


	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return false;
	}		

	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPersonQuery::OnChangeEditId() 
{
	CString str;
	m_id.GetWindowText(str);
	if( str.GetLength() < 5) return;
	OnOK();
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CPersonQuery::OnChangeEditMc() 
{
	CString str;
	m_mc.GetWindowText(str);
	if( str.GetLength() < 2) return;
	OnOK();
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CPersonQuery::OnSelchangeCombo1() 
{
	OnOK();
}

BEGIN_EVENTSINK_MAP(CPersonQuery, CDialog)
    //{{AFX_EVENTSINK_MAP(CPersonQuery)
	ON_EVENT(CPersonQuery, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	ON_EVENT(CPersonQuery, IDC_MSHFLEXGRID1, -600 /* Click */, OnClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CPersonQuery::OnDblClickMshflexgrid1() //选中的行
{
	CRegisterGh *pGH=(CRegisterGh*)lp;
	long iSel=m_grid.GetRowSel();
	if( iSel == 0 || iSel == m_grid.GetRows()-1 ) return;
	
	pGH->strBCBXcode=m_grid.GetTextMatrix(iSel,2);
	pGH->m_kh.SetWindowText(pGH->strBCBXcode ); //卡号
	pGH->m_name.SetWindowText(m_grid.GetTextMatrix(iSel,3) ); //姓名
	pGH->m_se.SetCurSel( m_grid.GetTextMatrix(iSel,4).Compare("男")== 0 ? 0:1 ); // 性别
	pGH->m_name.SetReadOnly();
	pGH->m_se.EnableWindow(false);

	CDialog::OnOK();

}

void CPersonQuery::OnClickMshflexgrid1() 
{
	// TODO: Add your control notification handler code here
	
}

void CPersonQuery::OnMenuCost2Add() 
{
	// TODO: Add your command handler code here
	
}

void CPersonQuery::OnMenuCost2Del() 
{
	// TODO: Add your command handler code here
	
}

void CPersonQuery::OnMenuCost2Modify() 
{
	// TODO: Add your command handler code here
	
}

void CPersonQuery::OnMenuCost2Restore() 
{
	// TODO: Add your command handler code here
	
}
