// PersonQueryJMTC.cpp: implementation of the CPersonQueryJMTC class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his3.h"
#include "PersonQueryJMTC.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPersonQueryJMTC::CPersonQueryJMTC()
{

}

CPersonQueryJMTC::~CPersonQueryJMTC()
{

}

void CPersonQueryJMTC::OnOK()
{
	CString strSql,strID,strMc;
	m_id.GetWindowText(strID);
	m_mc.GetWindowText(strMc);
	
	CComFunc::comSetGridHeader(m_grid,GRID_ID);
	CComFunc::GetSql(strSql,SQL_ID);
	strSql+=" AND ¿¨ºÅ like '600000000%' ";
	if( ! strID.IsEmpty() ) strSql+=" AND ¿¨ºÅ like '"+strID+"%'" ;
	if( ! strMc.IsEmpty() ) strSql+=" AND ÐÕÃû like '"+strMc+"%' " ;
	
	CComFunc::ReadDataForGrid(strSql,m_grid);

}
