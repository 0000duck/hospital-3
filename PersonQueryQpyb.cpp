// PersonQueryQpyb.cpp: implementation of the CPersonQueryQpyb class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his3.h"
#include "PersonQueryQpyb.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPersonQueryQpyb::CPersonQueryQpyb()
{

}

CPersonQueryQpyb::~CPersonQueryQpyb()
{

}

BOOL CPersonQueryQpyb::OnInitDialog()
{
	CDialog::OnInitDialog();
	CComFunc::comSetGridHeader(m_grid,GRID_ID); //表格头设置

	return true;

}

void CPersonQueryQpyb::OnOK()
{
	CString strSql,strID,strMc;
//	int iSel=m_depart.GetCurSel();
	m_id.GetWindowText(strID);
	m_mc.GetWindowText(strMc);
	
	CComFunc::comSetGridHeader(m_grid,GRID_ID);
	CComFunc::GetSql(strSql,SQL_ID);
	if( ! strID.IsEmpty() ) strSql+=" AND ID like '"+strID+"%'" ;
	if( ! strMc.IsEmpty() ) strSql+=" AND name like '"+strMc+"%' " ;
	
	CComFunc::ReadDataForGrid(strSql,m_grid);

}

void CPersonQueryQpyb::OnDblClickMshflexgrid1()
{
	CRegisterGh *pGH=(CRegisterGh*)lp;
	long iSel=m_grid.GetRowSel();
	if( iSel == 0 || iSel == m_grid.GetRows()-1 ) return;
	
	pGH->strYbCode=m_grid.GetTextMatrix(iSel,1);
	pGH->m_kh.SetWindowText(pGH->strYbCode ); //卡号
	pGH->m_name.SetWindowText(m_grid.GetTextMatrix(iSel,2) ); //姓名
	pGH->m_se.SetCurSel( m_grid.GetTextMatrix(iSel,3).Compare("男")== 0 ? 0:1 ); // 性别
	pGH->m_name.SetReadOnly();
	pGH->m_se.EnableWindow(false);

	CDialog::OnOK();

}
