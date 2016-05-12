// UserQuery.cpp: implementation of the CUserQuery class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his3.h"
#include "UserQuery.h"
#include "comFunc.H"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUserQuery::CUserQuery()
{
	sfyORys=0;
}

CUserQuery::~CUserQuery()
{

}

BOOL CUserQuery::OnInitDialog()
{
	CDialog::OnInitDialog();
	CComFunc::comSetGridHeader(m_grid,11); //表格头设置

	long i,row(1);
	CString strSql;
	arrayDepart.RemoveAll();


	m_depart.AddString(BLANKSTR);
	arrayDepart.Add(BLANKSTR);
	try{
	
		strSql.Format(" SELECT kfbm,kfmc  from storeRoom where effect=1 order by ord ");
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
	GetDlgItem(IDC_STATIC_1)->SetWindowText("科  室");
	GetDlgItem(IDC_STATIC_2)->SetWindowText("编  码");

	
	
	return TRUE;  // return TRUE unle
}

void CUserQuery::OnOK()
{
	CString strSql,strID,strMc;
	int iSel=m_depart.GetCurSel();
	long i,cols,row;
	m_id.GetWindowText(strID);
	m_mc.GetWindowText(strMc);

//	if ( (iSel == CB_ERR || iSel == 0 ) && strID.IsEmpty()  && strMc.IsEmpty() ) return;
	CComFunc::comSetGridHeader(m_grid,11);
	cols=m_grid.GetCols(0);
	try{
		CComFunc::GetSql(strSql,11);
		if ( ! ( iSel == CB_ERR || iSel ==0 ) ) strSql+= " AND t.kfbm='"+arrayDepart[iSel]+"'";
		if( ! strID.IsEmpty() ) strSql+=" AND rybm like '"+strID+"%'" ;
		if( ! strMc.IsEmpty() ) strSql+=" AND name like '"+strMc+"%' " ;

		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		row=1;
		m_grid.SetRedraw(false);
		while(! recSet->adoEOF){

			strSql.Format("%ld",row); //显示序列号,重新计算,数据库选择时的行号已被打乱
			m_grid.SetTextMatrix(row,0,strSql);
			for( i=1; i< cols ; i++ )
			{
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(long(i))->Value.vt == VT_NULL ? _variant_t(BLANKSTR):recSet->GetFields()->GetItem(long(i))->Value );
				m_grid.SetTextMatrix(row,i,strSql);
			}
			row++;
			m_grid.AddItem(BLANKSTR,_variant_t(row));
			recSet->MoveNext();

		}
		recSet->Close();
		CComFunc::GridSelRow(m_grid,1);
		m_grid.SetRedraw(true);
	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return ;
	}		

}

void CUserQuery::OnChangeEditId()
{
	OnOK();	
}

void CUserQuery::OnChangeEditMc()
{
	OnOK();
}

void CUserQuery::OnDblClickMshflexgrid1()
{
	CGhQuery *pGH=(CGhQuery*)lp;
	long iSel=m_grid.GetRowSel();
	if( iSel == 0 || iSel == m_grid.GetRows()-1 ) return;
	
	if( sfyORys == 1 )
	{
		pGH->sfyCode=m_grid.GetTextMatrix(iSel,2);//卡号
		pGH->c_sfy.SetWindowText( m_grid.GetTextMatrix(iSel,3)); 
	}
	else if( sfyORys == 2)
	{
		pGH->ysCode=m_grid.GetTextMatrix(iSel,2);//卡号
		pGH->c_ys.SetWindowText( m_grid.GetTextMatrix(iSel,3)); 
		
	}
	CDialog::OnOK();

}
