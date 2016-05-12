// DialogSickGetMed.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "DialogSickGetMed.h"
#include "comFunc.h"
#include "SickGetmedView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogSickGetMed dialog


CDialogSickGetMed::CDialogSickGetMed(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogSickGetMed::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogSickGetMed)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogSickGetMed::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogSickGetMed)
	DDX_Control(pDX, IDOK, m_BT2);
	DDX_Control(pDX, IDCANCEL, m_BT1);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogSickGetMed, CDialog)
	//{{AFX_MSG_MAP(CDialogSickGetMed)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogSickGetMed message handlers

void CDialogSickGetMed::OnOK() 
{
	CComFunc::comSetGridHeader(m_grid,2);
	
	CString strSql,str2;
	strSql=CComFunc::GetString( "SELECT sql FROM lsq_sql_statemnet WHERE id=2 ");

	long row=1;
	long cols=0,i;
//	CComFunc::writeDebug(strSql);
	m_grid.SetRedraw(false);
	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect, adOpenDynamic ,adLockOptimistic,adCmdText); 
		cols=recSet->GetFields()->Count;
		while(!recSet->adoEOF){
		//第一列为序号列,自个填入
			str2.Format("%ld",row);
			m_grid.SetTextMatrix(row,0,str2);
			for( i=0 ; i < cols ; i++ )
			{
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ? _variant_t(BLANKSTR) :recSet->GetFields()->GetItem(i)->Value );
				m_grid.SetTextMatrix(row,i+1,strSql);
			}
			row++;
			m_grid.AddItem(BLANKSTR,_variant_t(row) );

			recSet->MoveNext();
	
		}
		recSet->Close();
		
	}
	catch(... )
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		recSet->Close();
		return ;
	}
	
	m_grid.SetRow(1);
	m_grid.SetCol(0);
	m_grid.SetColSel(cols);
	m_grid.SetRowSel(1);
	m_grid.SetRedraw(true);
}

BOOL CDialogSickGetMed::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	OnOK();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(CDialogSickGetMed, CDialog)
    //{{AFX_EVENTSINK_MAP(CDialogSickGetMed)
	ON_EVENT(CDialogSickGetMed, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CDialogSickGetMed::OnDblClickMshflexgrid1() 
{
	int i=m_grid.GetRowSel();

	if( i ==0 || i== m_grid.GetRows()-1 ) return;

	CSickGetMedView hs;
	hs.DANJUHAO=m_grid.GetTextMatrix(i,DANJUHAO_COL);
	if( hs.DoModal() == IDOK ){
		OnOK();		
	};
	
}
