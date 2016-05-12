// CostBudget.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "CostBudget.h"
#include "costClassAb.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCostBudget dialog


CCostBudget::CCostBudget(CWnd* pParent /*=NULL*/)
	: CDialog(CCostBudget::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCostBudget)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	strWRITESQL="";
	curRow=0;
	curCol=0;//胜于定位编辑m_grid时确定列
	bFlagModify=false;
}


void CCostBudget::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCostBudget)
	DDX_Control(pDX, IDC_COMBO_YEAR, m_year);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_depart);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCostBudget, CDialog)
	//{{AFX_MSG_MAP(CCostBudget)
	ON_BN_CLICKED(IDOK_QUERY, OnQuery)
	ON_CBN_SELCHANGE(IDC_COMBO_YEAR, OnSelchangeComboYear)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, OnSelchangeComboType)
	//}}AFX_MSG_MAP
	ON_EN_KILLFOCUS(IDC_MOVE_EDIT,OnKillMoveEdit)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCostBudget message handlers

BOOL CCostBudget::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CRect r1(0,0,0,0);
	editCtrl.Create(WS_CHILD|ES_AUTOHSCROLL,r1,this,IDC_MOVE_EDIT);
	SetWindowText("年度预算");
//	comCtrl.Create(WS_CHILD,r1,this,T_COMBO1);
//	editCtrl.SetFont(&fontMoveEdit);
	
	long i,row(1);
	CComFunc::GetSql(strSql,CCostClassAb::COST_A_SQLID); //显示类别A
	CComFunc::comSetGridHeader(m_grid,GRID_HEADER_ID); 


	arrayDepart.RemoveAll();
	

	m_depart.AddString(BLANKSTR);
	arrayDepart.Add(BLANKSTR);
	try{
	
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 

		while(! recSet->adoEOF){
			i=0;
			strSql=CComFunc::GetSqlItem(i++);
			arrayDepart.Add(strSql);
			strSql=CComFunc::GetSqlItem(i);
			m_depart.AddString(strSql);

			recSet->MoveNext();

		}
		recSet->Close();


	}
	catch(_com_error e)
	{
		strSql.Format("出现错误,请检查SQL=%ld 语句...",CCostClassAb::COST_A_SQLID);
		AfxMessageBox(strSql);
		return false;
	}		
	long iYear=COleDateTime::GetCurrentTime().GetYear();
	for(i=0; i <3 ; i++ )
	{
		strSql.Format("%ld",iYear-i);
		m_year.AddString(strSql);
	}
	m_year.SetCurSel(0);

	OnQuery() ;	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCostBudget::OnQuery() 
{
	CString str2;
	const char * argu_01="[XT001]"; 
	const char * argu_02="[XT002]"; //SQL语句中查询预算年度参数

	CComFunc::comSetGridHeader(m_grid,GRID_HEADER_ID); 
	CComFunc::GetSql(strSql,SQL_QUERY_ID);
	int i=m_depart.GetCurSel();
	m_year.GetLBText(m_year.GetCurSel(),str2);

	strSql.Replace(argu_02,str2);

	if ( i == CB_ERR  || i == 0 )
		str2.Format(" ");
	//	str2.Format(" AND b.year_01 = %ld ",iYear);
	else 
	{
		str2.Format(" AND a.id2=%s  ",arrayDepart[m_depart.GetCurSel()] );

	//	str2.Format(" AND a.id2=%s AND b.year_01 = %ld ",arrayDepart[m_depart.GetCurSel()],
	//		iYear);

	
	}
	strSql.Replace(argu_01,str2);
	
	CComFunc::ReadDataForGrid(strSql,m_grid);
	gridRowSum();

	m_grid.SetSelectionMode(0);
}

BEGIN_EVENTSINK_MAP(CCostBudget, CDialog)
    //{{AFX_EVENTSINK_MAP(CCostBudget)
	ON_EVENT(CCostBudget, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CCostBudget::OnDblClickMshflexgrid1() 
{
	long row=m_grid.GetRow();
	long col=m_grid.GetCol();
	
	if( row == m_grid.GetRows()-1
		|| col < GRID_EDIT_COL  )return;

	CDC *pCdcGrid=m_grid.GetDC();
	int nWidth=pCdcGrid->GetDeviceCaps(LOGPIXELSX);
	int nHigh=pCdcGrid->GetDeviceCaps(LOGPIXELSY);
	ReleaseDC(pCdcGrid);

	curRow=row;
	curCol=col;
	CString str2;
	CString	strOrigin=m_grid.GetTextMatrix(row,col);
	
	m_grid.SetCol(col);
	long left=m_grid.GetCellLeft();
	long top=m_grid.GetCellTop();
	long right=m_grid.GetCellWidth();
	long bottom=m_grid.GetCellHeight();

	CRect rectGrid,r2;
	const int OFFSET05=2;
	m_grid.GetWindowRect(rectGrid);
	ScreenToClient(rectGrid);
	rectGrid.left+=left*nWidth/1440;
	rectGrid.top+=top*nHigh/1440;
	rectGrid.right=right*nWidth/1440+rectGrid.left-OFFSET05;
	rectGrid.bottom=bottom*nHigh/1440+rectGrid.top-OFFSET05;


	editCtrl.MoveWindow(rectGrid);
	editCtrl.ShowWindow(SW_SHOW);
	editCtrl.SetFocus();
	editCtrl.SetWindowText(strOrigin);
	editCtrl.SetWindowPos(&CWnd::wndTop,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
	editCtrl.SetSel(0,strOrigin.GetLength());			
}

void CCostBudget::OnKillMoveEdit()
{
	editCtrl.ShowWindow(SW_HIDE);
	editCtrl.GetWindowText(strSql);
	if ( curRow == 0 ) return; //防止误填到其它行
	CString str2;
	if (curCol == GRID_EDIT_COL )
		str2.Format("%.2f",atof(strSql));
	else 
		str2=strSql;

	m_grid.SetTextMatrix(curRow,curCol,str2);
	curRow=0;
	bFlagModify=true;
	gridRowSum();
}
void CCostBudget::gridRowSum()//统计预算列总和
{
	long i=m_grid.GetRows(),x;
	if( i == 2) return;
	double dbSum(0),dbTmp(0);
	for(x=1;x<i-1;x++)
	{
		dbTmp=atof(m_grid.GetTextMatrix(x,GRID_EDIT_COL));
		dbSum+=dbTmp;

	}
	strSql.Format("%.2f",dbSum);
	m_grid.SetTextMatrix(x,GRID_EDIT_COL,strSql);
}

void CCostBudget::OnOK() 
{
	long iRows=m_grid.GetRows();
	if ( iRows <=2 || ! bFlagModify ) return;
	const char * argu_01="[XT_ID]";
	const char * argu_02="[XT_YEAR]";
	const char * argu_03="[XT_CMT]";
	const char * argu_04="[XT_FEE]";
	CString strYear;
	m_year.GetLBText(m_year.GetCurSel(),strYear);

	double dbBudget(0),dbTmp(0);
	CString str2,strFee,strID,strCmt("");
	if ( strWRITESQL.IsEmpty() )
			CComFunc::GetSql(strWRITESQL,SQL_WRITE_ID);

	for( int i=1;i<iRows-1;i++)
	{
		str2=strWRITESQL;
		strFee=m_grid.GetTextMatrix(i,GRID_EDIT_COL);
		strID=m_grid.GetTextMatrix(i,GRID_ID);
		strCmt=m_grid.GetTextMatrix(i,GRID_EDIT_COL2);
	
		if( strFee.IsEmpty() ) strFee="0";
		str2.Replace(argu_01,strID);
		str2.Replace(argu_02,strYear);
		str2.Replace(argu_03,strCmt);
		str2.Replace(argu_04,strFee);
		
		if( !CComFunc::WriteSql(str2)   )
		{	
			AfxMessageBox("保存预算失败,请重试!");
			return;
		}
		

	}
	
	AfxMessageBox("预算保存成功!");
	bFlagModify=false;
}

BOOL CCostBudget::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN ) {
		if ( editCtrl.ShowWindow(SW_HIDE) )
		{
			OnKillMoveEdit();
			return true;
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}



void CCostBudget::OnSelchangeComboYear() 
{
	OnQuery();	
}

void CCostBudget::OnSelchangeComboType() 
{
	OnQuery();		// TODO: Add your control notification handler code here
	
}
