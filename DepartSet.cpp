// DepartSet.cpp: implementation of the CDepartSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his3.h"
#include "DepartSet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDepartSet::CDepartSet()
{

}

CDepartSet::~CDepartSet()
{

}

BOOL CDepartSet::OnInitDialog()
{
	CDialog::OnInitDialog();
/*
	CString strout,strSql;
	CComFunc::GetSql(strSql,13); //人员初始化语句
	long i(0);
	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			i=0;
			strout=CComFunc::GetSqlItem(i);
			comArray1.Add(strout);
			i++;
			strout=CComFunc::GetSqlItem(i);
			m_combo1.AddString(strout);
			
			recSet->MoveNext();

		}
		recSet->Close();


	}
	catch(_com_error e)
	{
	//	AfxMessageBox(strSql);
		recSet->Close();
		return false;
	}	
*/	
	CComFunc::comSetGridHeader(m_grid,GRID_HEADER_ID); 
	return true;

}

void CDepartSet::OnOK() //保存
{

}

void CDepartSet::OnAdd() // 新增
{

}
