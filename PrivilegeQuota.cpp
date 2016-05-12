// PrivilegeQuota.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "PrivilegeQuota.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrivilegeQuota dialog


CPrivilegeQuota::CPrivilegeQuota(CWnd* pParent /*=NULL*/)
	: CDialog(CPrivilegeQuota::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrivilegeQuota)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	MODIFY_FLAG = 0;
}


void CPrivilegeQuota::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrivilegeQuota)
	DDX_Control(pDX, IDC_COMBO2, m_combo2);
	DDX_Control(pDX, IDC_COMBO1, m_combo1);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrivilegeQuota, CDialog)
	//{{AFX_MSG_MAP(CPrivilegeQuota)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnSelchangeCombo2)
	ON_BN_CLICKED(IDOK_ADD, OnAdd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrivilegeQuota message handlers

BOOL CPrivilegeQuota::OnInitDialog() 
{
	CDialog::OnInitDialog();
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
	
	CComFunc::comSetGridHeader(m_grid,GRID_HEADER_ID); 
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPrivilegeQuota::OnSelchangeCombo1() 
{

	CComFunc::comSetGridHeader(m_grid,GRID_HEADER_ID);
	int iSel=m_combo1.GetCurSel();
	CString strSql,strout;
	CComFunc::GetSql(strSql,14);
	strSql+=" AND t.kfbm='"+comArray1[iSel]+"' ORDER by t.name";

	m_combo2.ResetContent();
	comArray2.RemoveAll();
	long i(0);
	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			i=0;
			strout=CComFunc::GetSqlItem(i);
			comArray2.Add(strout);
			i++;
			strout=CComFunc::GetSqlItem(i);
			m_combo2.AddString(strout);
			
			recSet->MoveNext();

		}
		recSet->Close();


	}
	catch(_com_error e)
	{
	//	AfxMessageBox(strSql);
		recSet->Close();
		return ;
	}	
	MODIFY_FLAG=0;
}

void CPrivilegeQuota::OnSelchangeCombo2() 
{
	int iSel=m_combo2.GetCurSel();
	CString strSql,strout;
	CComFunc::GetSql(strSql,15);
	strSql.Replace("XT001",comArray2[iSel]);

	CComFunc::comSetGridHeader(m_grid,GRID_HEADER_ID); 
	long i(0);
	long cols=m_grid.GetCols(0);
	long row(1);

	CComFunc::ReadDataForGrid(strSql,m_grid);
/*	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		recSet->GetFields()->GetCount();
		while(!recSet->adoEOF){
			for(i=0 ; i< cols ; i++ )
			{
				strout=CComFunc::GetSqlItem(i);
				m_grid.SetTextMatrix(row,i,strout);		
		
			}

			row++;
			m_grid.AddItem(BLANKSTR,_variant_t(row));
			recSet->MoveNext();

		}
		recSet->Close();


	}
	catch(_com_error e)
	{
		recSet->Close();
		return ;
	}	
*/
	MODIFY_FLAG=0;
}

BEGIN_EVENTSINK_MAP(CPrivilegeQuota, CDialog)
    //{{AFX_EVENTSINK_MAP(CPrivilegeQuota)
	ON_EVENT(CPrivilegeQuota, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CPrivilegeQuota::OnDblClickMshflexgrid1()  //进行授权操作
{
	long iSel=m_grid.GetRow();
	long flagCol=m_grid.GetCols(0)-1;
	CString str;
	CComFunc::GetSql(str,16);
	CString strOK=CComFunc::GetString(str);
	CComFunc::GetSql(str,17);
	CString strCANCEL=CComFunc::GetString(str);

	if( iSel == 0 || iSel == m_grid.GetRows()-1 ) return;
	
	int i=atoi( m_grid.GetTextMatrix(iSel,flagCol));
	if( i == 1 ) {
		i=0;
		m_grid.SetTextMatrix(iSel,flagCol-1,strCANCEL);
	}else
	{
		i=1;
		m_grid.SetTextMatrix(iSel,flagCol-1,strOK);
	}
	str.Format("%ld",i);
	m_grid.SetTextMatrix(iSel,flagCol,str);
	MODIFY_FLAG=1;//设置修改状态
	

}

void CPrivilegeQuota::OnOK() 
{
	if( MODIFY_FLAG == 0 ) {

		return; //未作修改
	}
	long rows=m_grid.GetRows()-1; //最后空一行
	CString strBM=comArray2[ m_combo2.GetCurSel() ];
	CString strSql;
	long iPriv;
	int iStatus;
	try{
		HospitalConnect->BeginTrans();
		
		for(long i=1 ; i< rows ; i++)
		{
			iPriv=atol( m_grid.GetTextMatrix(i,1) ) ;/* 权限ID */ 
			iStatus=atoi( m_grid.GetTextMatrix(i,4) ); /* 权限状态*/
			strSql.Format(" SELECT count(*) FROM his3_PRIV_quota WHERE bm='%s' AND id=%ld ",strBM , iPriv );
			strSql=CComFunc::GetString(strSql);
			
			if ( atol(strSql) == 0) {
				strSql.Format("INSERT INTO his3_PRIV_quota ( id,BM,effect ) values(%ld,'%s',%d ) ",iPriv,strBM ,iStatus);
			}
			else {
				strSql.Format(" UPDATE his3_priv_QUOTA Set effect =%d WHERE id=%ld AND bm='%s' ",iStatus,iPriv,strBM);
			}
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
			
		}
		HospitalConnect->CommitTrans();
		AfxMessageBox("权限已保存");
	}
	catch(...)
	{
		HospitalConnect->RollbackTrans();
		AfxMessageBox("保存权限出现错误,请检测数据库是否正常!!");
		return;
		
	}
}

void CPrivilegeQuota::OnAdd() 
{
	// TODO: Add your control notification handler code here
	
}
