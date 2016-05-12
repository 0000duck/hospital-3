// OperatorSel.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "OperatorSel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COperatorSel dialog


COperatorSel::COperatorSel(CWnd* pParent /*=NULL*/)
	: CDialog(COperatorSel::IDD, pParent)
{
	//{{AFX_DATA_INIT(COperatorSel)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	strID=BLANKSTR;
	strName=BLANKSTR;
}


void COperatorSel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COperatorSel)
	DDX_Control(pDX, IDC_EDIT1, m_name);
	DDX_Control(pDX, IDC_COMBO_DEP_SEL, m_dep);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COperatorSel, CDialog)
	//{{AFX_MSG_MAP(COperatorSel)
	ON_BN_CLICKED(IDB_SEL, OnSel)
	ON_CBN_SELCHANGE(IDC_COMBO_DEP_SEL, OnSelchangeComboDepSel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COperatorSel message handlers

BOOL COperatorSel::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CString strSql;
	CComFunc::GetSql(strSql,13); //人员初始化语句
	long i(0);
	comArray1.RemoveAll();
	comArray1.Add(BLANKSTR);
	m_dep.AddString(BLANKSTR);
	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			i=0;
			comArray1.Add(CComFunc::GetSqlItem(i));
			i++;
			m_dep.AddString(CComFunc::GetSqlItem(i));
			
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
	
//	CComFunc::comSetGridHeader(m_grid,GRID_HEADER_ID); 	
	OnOK();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COperatorSel::OnOK() 
{
	CString strSql,s1(BLANKSTR),s2(BLANKSTR),sx(BLANKSTR);
	int i(0);

	CComFunc::comSetGridHeader(m_grid,GRID_HEADER_ID); 
	CComFunc::GetSql(strSql,SQL_QUERY_ID);
	m_name.GetWindowText(s2);
	i=m_dep.GetCurSel();
	if( i > 0 )
	{
		s1.Format(" AND a.kfbm=%s ",comArray1[i]);
	
	}
	if( !s2.IsEmpty() ){
		sx.Format(" AND b.name like '%s%%' ",s2 );
		
	}
	s1+=sx;
	strSql.Replace("[XT001]",s1 );
	
	CComFunc::ReadDataForGrid(strSql,m_grid);
	
}

void COperatorSel::OnSel() 
{
	long iSel(0);
	iSel=m_grid.GetRow();
	if( iSel == 0 || iSel == m_grid.GetRows()-1 ) return;
	strID=m_grid.GetTextMatrix(iSel,GRID_NAME_ID);
	strName=m_grid.GetTextMatrix(iSel,GRID_NAME);
	CDialog::OnOK();
}

BEGIN_EVENTSINK_MAP(COperatorSel, CDialog)
    //{{AFX_EVENTSINK_MAP(COperatorSel)
	ON_EVENT(COperatorSel, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void COperatorSel::OnDblClickMshflexgrid1() 
{
	OnSel();	
}

void COperatorSel::OnSelchangeComboDepSel() 
{
	OnOK();	
}
