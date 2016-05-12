// PersonQueryRelate.cpp: implementation of the CPersonQueryRelate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his3.h"
#include "PersonQueryRelate.h"
#include "comFunc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPersonQueryRelate::CPersonQueryRelate()
{

}

CPersonQueryRelate::~CPersonQueryRelate()
{

}

BOOL CPersonQueryRelate::OnInitDialog()
{
	CDialog::OnInitDialog();
	CComFunc::comSetGridHeader(m_grid,9); //表格头设置

	return true;
}

void CPersonQueryRelate::OnOK()
{
	CString strSql,strID,strMc;
	int iSel=m_depart.GetCurSel();
	long i,cols,row;
	m_id.GetWindowText(strID);
	m_mc.GetWindowText(strMc);
	
	if ( (iSel == CB_ERR || iSel == 0 ) && strID.IsEmpty()  && strMc.IsEmpty() ) return;
	CComFunc::comSetGridHeader(m_grid,9);
	cols=m_grid.GetCols(0);
	CComFunc::GetSql(strSql,6);
	if( ! strID.IsEmpty() ) strSql+=" AND BM like '"+strID+"%'" ;
	if( ! strMc.IsEmpty() ) strSql+=" AND XM like '"+strMc+"%' " ;
	
	strSql+=CComFunc::GetString(" SELECT sql FROM lsq_sql_statemnet WHERE id= 8 ");
	CComFunc::ReadDataForGrid(strSql,m_grid);

}

void CPersonQueryRelate::OnDblClickMshflexgrid1()
{
	CRegisterGh *pGH=(CRegisterGh*)lp;
	long iSel=m_grid.GetRowSel();
	if( iSel == 0 || iSel == m_grid.GetRows()-1 ) return;
	
	pGH->strGYQScode=m_grid.GetTextMatrix(iSel,1);
	pGH->m_kh.SetWindowText(pGH->strGYQScode ); //卡号
	pGH->m_name.SetWindowText(m_grid.GetTextMatrix(iSel,2) ); //姓名
	pGH->m_se.SetCurSel( m_grid.GetTextMatrix(iSel,3).Compare("男")== 0 ? 0:1 ); // 性别
	pGH->m_name.SetReadOnly();
	pGH->m_se.EnableWindow(false);

	CDialog::OnOK();

}
