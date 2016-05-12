// DialogAccountQuery.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "DialogAccountQuery.h"
#include "mshflexgrid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogAccountQuery dialog


CDialogAccountQuery::CDialogAccountQuery(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogAccountQuery::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogAccountQuery)
	m_xm = _T("");
	m_kh = _T("");
	//}}AFX_DATA_INIT
}


void CDialogAccountQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogAccountQuery)
	DDX_Control(pDX, IDC_COMBO_TYPE, m_type);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	DDX_Text(pDX, IDC_EDIT_KXM, m_xm);
	DDV_MaxChars(pDX, m_xm, 10);
	DDX_Text(pDX, IDC_EDIT_QKH, m_kh);
	DDV_MaxChars(pDX, m_kh, 12);
	DDX_Control(pDX, IDC_MSHFLEXGRID2, m_grid2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogAccountQuery, CDialog)
	//{{AFX_MSG_MAP(CDialogAccountQuery)
	ON_EN_CHANGE(IDC_EDIT_QKH, OnChangeEditQkh)
	ON_EN_CHANGE(IDC_EDIT_KXM, OnChangeEditKxm)
	ON_BN_CLICKED(IDBUTTON_ADD, OnAdd)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, OnSelchangeComboType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogAccountQuery message handlers

BOOL CDialogAccountQuery::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString strSql;
	typeArray.RemoveAll();

	try{
		strSql="select ds1,ds3 from lsq_upgrade  where ds2=upper('pay_fee')  order by n1";
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			
			strSql=(char*)_bstr_t(recSet->GetCollect("ds1").vt==VT_NULL?" ":recSet->GetCollect("ds1"));
			m_type.AddString(strSql);
			strSql=(char*)_bstr_t(recSet->GetCollect("ds3").vt==VT_NULL?" ":recSet->GetCollect("ds3"));
			typeArray.Add(strSql);
			recSet->MoveNext();
	
		}
		recSet->Close();
		
	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return false;
	}			
	m_type.SetCurSel(0);
	SetGridHead(m_grid);
	SetGridHead(m_grid2);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogAccountQuery::OnOK() 
{
	UpdateData();
	if( m_xm.IsEmpty() && m_kh.IsEmpty() ) return;
	CString strSql,tmpStr;
	long i,row=1;
	const CString EMPLOYEE_ZH="001",RELATE_ZH="002";
	
	m_grid.SetRows(2);
	m_grid.AddItem(BLANKSTR,_variant_t(2L));
	m_grid.RemoveItem(1L);

	tmpStr=typeArray[m_type.GetCurSel()];
	m_grid.SetRedraw(false);

	try{
		if( tmpStr.Compare(EMPLOYEE_ZH) == 0 )
			strSql.Format(" select * from v_employee_account WHERE ");
		else if( tmpStr.Compare(RELATE_ZH) == 0 )
			strSql.Format(" select * from v_Relate_account WHERE ");
		strSql+= " 卡号 like '"+m_kh+"%' and 姓名 like '"+m_xm+"%' " ;

		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
		
			for(i=0; i< GRID_COLS ;i++ )
			{
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ? "":recSet->GetFields()->GetItem(i)->Value );
				m_grid.SetTextMatrix(row,i,strSql);
			}
			row++;
			m_grid.AddItem(BLANKSTR,_variant_t(row) );
			recSet->MoveNext();
	
		}

		recSet->Close();
		m_grid.SetRedraw(true);
	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return ;
	}	
	CComFunc::GridSelRow(m_grid,1);

	
}

void CDialogAccountQuery::OnChangeEditQkh() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	UpdateData();
	if( m_kh.GetLength() >= CHANGE_MAX_KH ) OnOK();
	// TODO: Add your control notification handler code here
	
}

void CDialogAccountQuery::OnChangeEditKxm() 
{
	UpdateData();
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	if( m_xm.GetLength() >= CHANGE_MAX_XM ) OnOK();
	// TODO: Add your control notification handler code here
	
}

void CDialogAccountQuery::SetGridHead(CMSHFlexGrid &grid)
{
	CString HeadTitle[]={"卡号","部门","姓名","余额","支付","类别"} ;
	long    HeadWidth[]={1400,2200,1400,1500,0,0};
	const int HEADROW=0;

	grid.SetRows(2);
	grid.SetCols(0,GRID_COLS);
	grid.SetFixedCols(0);
	grid.SetSelectionMode(1L);
	for(int i=0; i < GRID_COLS ; i++ )
	{
		grid.SetTextMatrix(HEADROW,i,HeadTitle[i]);
		grid.SetColAlignmentHeader(0,i,4L);
	//	m_grid.SetColAlignment(i,4L); //居中
		grid.SetColWidth(i,0,HeadWidth[i] );


	}

}

BEGIN_EVENTSINK_MAP(CDialogAccountQuery, CDialog)
    //{{AFX_EVENTSINK_MAP(CDialogAccountQuery)
	ON_EVENT(CDialogAccountQuery, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	ON_EVENT(CDialogAccountQuery, IDC_MSHFLEXGRID2, -601 /* DblClick */, OnDblClickMshflexgrid2, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CDialogAccountQuery::OnDblClickMshflexgrid1() 
{
	long iSel=m_grid.GetRow();
	if ( iSel == 0 || iSel == m_grid.GetRows()-1 ) return;
	
	long i2Row=m_grid2.GetRows()-1;
	CString tmpStr;
	tmpStr=m_grid.GetTextMatrix(iSel,KH_COL);

	for(int i=1; i < i2Row ; i++ ) //防止选择重复
	{
		if( tmpStr.Compare( m_grid2.GetTextMatrix(i,KH_COL) ) == 0 ) return;
	}
	for( i=0; i< GRID_COLS ; i++ )
	{
		m_grid2.SetTextMatrix(i2Row,i,m_grid.GetTextMatrix(iSel,i) );
	}
	i2Row++;
	m_grid2.AddItem(BLANKSTR,_variant_t(i2Row) );
	
}

void CDialogAccountQuery::OnDblClickMshflexgrid2() 
{
	long iSel=m_grid2.GetRow();
	if( iSel ==0  || iSel== m_grid2.GetRows() -1 ) return;

	m_grid2.RemoveItem(iSel);
}

void CDialogAccountQuery::OnAdd() //将结果插入到选择框中
{
	extern CHis3App theApp;
	CMSHFlexGrid *pg=(CMSHFlexGrid*) theApp.pParentGrid.pGrid;
	long iRows=m_grid2.GetRows();
	long dstRows=pg->GetRows()-1;

	if( iRows <=2 ) return;
	iRows --;
	for(int i=1 ; i <  iRows ; i++ )
	{
		for( int j=0 ; j< GRID_COLS ; j++ )
		{
			pg->SetTextMatrix(dstRows,j,m_grid2.GetTextMatrix(i,j) );
		}
		dstRows++;
		pg->AddItem(BLANKSTR,_variant_t( dstRows) );

	}
	CDialog::OnOK();
}

void CDialogAccountQuery::OnSelchangeComboType() 
{
	m_grid.SetRows(2);
	m_grid.AddItem(BLANKSTR,_variant_t(1L) );
	m_grid.SetRows(2);
}
