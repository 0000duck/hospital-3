// PersonQueryHayb.cpp: implementation of the CPersonQueryHayb class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his3.h"
#include "PersonQueryHayb.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPersonQueryHayb::CPersonQueryHayb()
{

}

CPersonQueryHayb::~CPersonQueryHayb()
{

}

void CPersonQueryHayb::OnOK()
{
	CString strSql,strID,strMc;
	m_id.GetWindowText(strID);
	m_mc.GetWindowText(strMc);
	
	CComFunc::comSetGridHeader(m_grid,GRID_ID);
	CComFunc::GetSql(strSql,SQL_ID);
	if( ! strID.IsEmpty() ) strSql+=" AND ¿¨ºÅ like '"+strID+"%'" ;
	if( ! strMc.IsEmpty() ) strSql+=" AND ÐÕÃû like '"+strMc+"%' " ;
	
	CComFunc::ReadDataForGrid(strSql,m_grid);

}
