// MedcodeAdd.cpp: implementation of the CMedcodeAdd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his3.h"
#include "MedcodeAdd.h"
#include "MedConsumeQuery.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMedcodeAdd::CMedcodeAdd()
{

}

CMedcodeAdd::~CMedcodeAdd()
{

}

BOOL CMedcodeAdd::OnInitDialog()
{
	CDialog::OnInitDialog();
	const CString TITLE="新增药品规格";
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(TITLE);
	SetWindowText(TITLE);
	long i(0);
	const int ITEM_COLS=11;

	int countPoint=0;


	try{
		CComFunc::GetSql(strSql,CMedcode::SQLID);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(long(CMedcode::FIRST_ITEM))->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(long(CMedcode::FIRST_ITEM))->Value );
			arrayItem1.Add(strSql);
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(long(CMedcode::SECOND_ITEM))->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(long(CMedcode::SECOND_ITEM))->Value );
			m_combo1.AddString(strSql);
			recSet->MoveNext();
	
		}
		recSet->Close();
		

		strSql.Format("select l_ID,L_name from lsq_med_type t where l_eft=1 order by l_ord ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 

		while(!recSet->adoEOF){
			i=0;			
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(i)->Value );
			arrayItem3.Add(strSql);
			++i;
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(i)->Value );
			m_comboType.AddString(strSql);

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
	              // EXCEPTION: OCX Property 
}

void CMedcodeAdd::OnOK()
{
	UpdateData();

	int i1,i2,i3;
	i1=m_combo1.GetCurSel();
	i2=m_combo2.GetCurSel();
	i3=m_comboType.GetCurSel();
	if( i1==CB_ERR || i2==CB_ERR || i3== CB_ERR )
	{
		AfxMessageBox("请选择药品所属类别");
		return;
	}
	const CString MEDBM=CComFunc::GetString("SELECT G_BM FROM V_GENERIC_MEDBM ");

	strSql.Format(" INSERT INTO MEDCODE(BM,DLBM,XLBM,MC,GG,DW,PY,L_TYPE,MAXKC,MINKC,BZ ) VALUES('%s','%s','%s',\
		'%s','%s','%s','%s',%ld,%ld,%ld,'%s') ",MEDBM,arrayItem1[i1],arrayItem2[i2],m_mc,m_gg,m_dw,\
		m_py,atoi(arrayItem3[i3]),atoi(m_maxkc),atoi(m_minkc),m_bz);


	if(  CComFunc::WriteSql(strSql) )	
		CDialog::OnOK();


}

void CMedcodeAdd::OnSelchangeCombo1()
{
	UpdateData();
	int i1=m_combo1.GetCurSel();
	if(  i1==CB_ERR) return;
	
	arrayItem2.RemoveAll();
	m_combo2.ResetContent();
	try{

//		strSql.Format("select XLBM,XLMC from medxl WHERE DLBM='%s'",arrayItem1[i1] );

		CComFunc::GetSql(strSql,CMedConsumeQuery::SQLID2);
		strSql.Replace("XXX",arrayItem1[i1]);

		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		long i(0);
		while(!recSet->adoEOF){
			i=0;			
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(i)->Value );
			arrayItem2.Add(strSql);
		
			++i;
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(i)->Value );
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
