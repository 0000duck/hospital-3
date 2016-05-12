// ExesList.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "ExesList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExesList dialog


CExesList::CExesList(CWnd* pParent /*=NULL*/)
	: CDialog(CExesList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExesList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CExesList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExesList)
	DDX_Control(pDX, IDC_COMBO_TYPE, m_type);
	DDX_Control(pDX, IDC_MSHFLEXGRID_DST, m_dst);
	DDX_Control(pDX, IDC_MSHFLEXGRID_SRC, m_src);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CExesList, CDialog)
	//{{AFX_MSG_MAP(CExesList)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, OnSelchangeComboType)
	ON_BN_CLICKED(IDC_BUTTON_A_ADD, OnButtonAAdd)
	ON_BN_CLICKED(IDC_BUTTON_A_DEL, OnButtonADel)
	ON_BN_CLICKED(IDC_BUTTON_S_ADD, OnButtonSAdd)
	ON_BN_CLICKED(IDC_BUTTON_S_DEL, OnButtonSDel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExesList message handlers

BOOL CExesList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString strSql;
	try{
	//	strSql="select * from v_exes_type ";
		CComFunc::GetSql(strSql,21);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(0L)->Value.vt == VT_NULL ? "":recSet->GetFields()->GetItem(0L)->Value );
			m_type.AddString(strSql);
			recSet->MoveNext();
	
		}

		recSet->Close();
		
	}
	catch(_com_error e)
	{
		AfxMessageBox("初始化出现错误,请检查SQL语句...");
		return false;
	}		

	SetGridHead();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CExesList::OnSelchangeComboType() 
{

	CString strSql,tmpStr1;
	long i,srcRow(1);
	m_type.GetLBText(m_type.GetCurSel(),tmpStr1);

	m_src.SetRows(2);
	m_src.AddItem(BLANKSTR,_variant_t(2L));
	m_src.RemoveItem(1);

	try{
		strSql.Format(" select 费用编码,费用名称,标准金额 from 费用项目表 Where 费用大类='%s' ",tmpStr1); 
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
		
			for(i=0; i< EXES_COLS ;i++ )
			{
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ? "":recSet->GetFields()->GetItem(i)->Value );
				m_src.SetTextMatrix(srcRow,i,strSql);
			}
			srcRow++;
			m_src.AddItem(BLANKSTR,_variant_t(srcRow) );
			recSet->MoveNext();
	
		}

		recSet->Close();
		
	}
	catch(_com_error e)
	{
		AfxMessageBox("初始化出现错误,请检查SQL语句...");
		return ;
	}		

	
}

void CExesList::SetGridHead()
{
/*	CString HeadTitle[]={"ID","项目名称","费用"} ;
	long    HeadWidth[]={0,2000,1000};
	const int HEADROW=0;

	m_src.SetRows(2);
	m_dst.SetRows(2);
	m_src.SetCols(0,EXES_COLS);
	m_dst.SetCols(0,EXES_COLS);
	m_src.SetSelectionMode(1L);
	m_dst.SetSelectionMode(1L);
	for(int i=0; i <EXES_COLS ; i++ )
	{
		m_src.SetTextMatrix(HEADROW,i,HeadTitle[i]);
		m_src.SetColAlignment(i,4L); //居中
		m_src.SetColWidth(i,0,HeadWidth[i] );

		m_dst.SetTextMatrix(HEADROW,i,HeadTitle[i]);
		m_dst.SetColAlignment(i,4L);
		m_dst.SetColWidth(i,0,HeadWidth[i] );

	}
*/
	CComFunc::comSetGridHeader(m_src,4);
	CComFunc::comSetGridHeader(m_dst,4);

}

void CExesList::OnButtonAAdd() 
{
	long idx=0,	idx2=0,x1;
	if( m_src.GetRows() <= 2 ) return; 
	idx2=m_dst.GetRows()-1 ;

	for(idx=1; idx < m_src.GetRows()-1 ; idx++ )
	{
		for( x1=0 ; x1< EXES_COLS ; x1++ )
			m_dst.SetTextMatrix(idx2,x1,m_src.GetTextMatrix(idx,x1) );
		idx2++;
		m_dst.AddItem(BLANKSTR,_variant_t( idx2 ) );

	}
}

void CExesList::OnButtonADel() //全部删除
{
	m_dst.SetRows(2);
	m_dst.AddItem(BLANKSTR,_variant_t(2L));
	m_dst.RemoveItem(1);
	
}

void CExesList::OnButtonSAdd() 
{
	long iStart,iEnd,idx,x1;
	iStart=m_src.GetRow();
	iEnd=m_src.GetRowSel();
	if ( iEnd == m_src.GetRows()-1 ) iEnd-- ; //最后一行为空行
	
	idx=m_dst.GetRows()-1 ;
	while (iStart <= iEnd )
	{
		for( x1=0 ; x1< EXES_COLS ; x1++ )
			m_dst.SetTextMatrix(idx,x1,m_src.GetTextMatrix(iStart,x1) );
		idx++;
		m_dst.AddItem(BLANKSTR,_variant_t( idx ) );
		iStart++;
	}

		
}

void CExesList::OnButtonSDel() 
{
	long iStart,iEnd;
	iStart=m_dst.GetRow();
	iEnd=m_dst.GetRowSel();
	
	if ( iEnd == m_dst.GetRows()-1 ) iEnd-- ; //最后一行不能删除
	int iRows= iEnd-iStart;

	while ( iRows -- >= 0 )
	{
		m_dst.RemoveItem(iStart);

	}
	
}

BEGIN_EVENTSINK_MAP(CExesList, CDialog)
    //{{AFX_EVENTSINK_MAP(CExesList)
	ON_EVENT(CExesList, IDC_MSHFLEXGRID_DST, -601 /* DblClick */, OnDblClickMshflexgridDst, VTS_NONE)
	ON_EVENT(CExesList, IDC_MSHFLEXGRID_SRC, -601 /* DblClick */, OnDblClickMshflexgridSrc, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CExesList::OnDblClickMshflexgridDst() 
{
	OnButtonSDel();	
}

void CExesList::OnDblClickMshflexgridSrc() 
{

	OnButtonSAdd();
}

void CExesList::OnOK() //插入所选的信息
{
	extern CHis3App theApp;
	long rows=m_dst.GetRows()-1;

	if (rows > 1  ) {
		CMSHFlexGrid * pg=(CMSHFlexGrid *)theApp.pParentGrid.pGrid;

		long endRow=pg->GetRows()-1,i,x;

		for( i=1; i< rows ; i++ ){
			for (x =0 ; x< EXES_COLS; x++ )
				pg->SetTextMatrix(endRow,x,m_dst.GetTextMatrix(i,x) );
			endRow++;
			pg->AddItem(BLANKSTR,_variant_t(endRow) );
		}

	}


	
	CDialog::OnOK();
}

void CExesList::OnCancel()  //退出
{
	
	CDialog::OnCancel();
}
