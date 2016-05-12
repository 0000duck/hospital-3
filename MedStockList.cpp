// MedStockList.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "MedStockList.h"

#include "comFunc.H"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMedStockList dialog
#define COLS 11
#define DOWN_ARROR 0x28
#define UP_ARROR 0x26

CMedStockList::CMedStockList(CWnd* pParent /*=NULL*/)
	: CDialog(CMedStockList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMedStockList)
	//}}AFX_DATA_INIT
	curRow=0;
	brushBack.CreateSolidBrush(RGB(58,110,165));
	flagMoveKF=0;
}


void CMedStockList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMedStockList)
	DDX_Control(pDX, IDC_EDIT_MESSAGE, c_message);
	DDX_Control(pDX, IDC_EDIT_PY, c_py);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMedStockList, CDialog)
	//{{AFX_MSG_MAP(CMedStockList)
	ON_EN_CHANGE(IDC_EDIT_PY, OnChangeEditPy)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMedStockList message handlers

BOOL CMedStockList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CRect r2;
	GetWindowRect(r2);

	long x,y;
	y=r2.bottom-r2.top;
	x=r2.right-r2.left;

	r2.top=r1.bottom;
	r2.bottom=r2.top+y;
	r2.left=r1.left;
	r2.right=r2.left+x;

	MoveWindow(r2);
	CComFunc::comSetGridHeader(m_grid,15);
	OnOK();
	c_py.SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMedStockList::OnOK() 
{
	UpdateData();
/*
	CString HeadTitle[]={"ID","药品编码","药品名称","规格","单位","生产期","有效期",\
		"产地BM","产地","库存量","售价","进价","指导价"，“甲乙丙”}; //共 13 列

	long  headWidth[]={0,00,1800,1400,600,0,1400,0,1400,800,800,0,0};
														//6
	CString getTitle[]={"ID","BM","MC","GG","DW","RQ1","RQ2","GONGBM","GONGMC","SL",\
		"SELL_PRICE","JINJIA","COACH_PRICE"};

*/
	m_grid.SetRows(2);
	m_grid.AddItem(BLANKSTR,_variant_t(1L));
	m_grid.RemoveItem(1);

	CString strSql,str1;
	int y1,y2,m1,m2 ;
	long row,col,i;
	long GRIDCOLS=m_grid.GetCols(0);

	c_py.GetWindowText(str1);
	if(str1.IsEmpty())return;
	try{
		
		strSql.Format("select * from V_MEDLIST where kfbm='%s' and py like '%s%%'  order by mc,get_date ",LoginInformation.kfbm,str1 );
		
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
	
		row=1;
		double dX;
		m_grid.SetRedraw(false);
		while(!recSet->adoEOF){
			col=0;
			for(i=0;i< GRIDCOLS ;i++)
			{
			    str1=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(i)->Value );
				if( 6 == i ){
					strSql=(char*)_bstr_t(recSet->GetCollect("CURDATE"));
					y1=atoi(str1.Left(4));
					m1=atoi(str1.Mid(5,2)); //日期
					
					y2=atoi(strSql.Left(4)); //当前日期
					m2=atoi(strSql.Mid(5,2));

				//	if( (y1 == y2 && m1-3<m2) || (y1-1 == y2 && 12+m1-3<m2) ) { //大于三个月的特显
					if( (y1-y2)*12+m1-3 <= m2 ){
						m_grid.SetRow(row);
						m_grid.SetCol(col);
						m_grid.SetCellBackColor(RGB(255,128,0));
					}

				}
				if( 10 == i){
					dX=atof(str1);
					str1.Format("%.2f",dX);
				}
				m_grid.SetTextMatrix(row,col++,str1);
			}
			row++;
			m_grid.AddItem(" ",_variant_t(row));
			recSet->MoveNext();

		}
		recSet->Close();
		m_grid.SetRedraw(true);
	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
		return;
	}
	strSql.Format("共查询到:  %ld  条信息",row-1);
	c_message.SetWindowText(strSql);
//将第一行选中	
	CComFunc::GridSelRow(m_grid,1);
	c_py.SetFocus();
	
}

void CMedStockList::OnChangeEditPy() 
{
	OnOK();
	
}
BOOL CMedStockList::PreTranslateMessage(MSG* pMsg) 
{

	if(pMsg->message == WM_KEYDOWN )
		if(pMsg->wParam == VK_RETURN )OnDblClickMshflexgrid1();
		else if( pMsg->wParam==VK_DOWN)
			m_grid.SetFocus();

	return CDialog::PreTranslateMessage(pMsg);
}

BEGIN_EVENTSINK_MAP(CMedStockList, CDialog)
    //{{AFX_EVENTSINK_MAP(CMedStockList)
	ON_EVENT(CMedStockList, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()




HBRUSH CMedStockList::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
/*
	pDC->SetBkMode(TRANSPARENT);
	if(nCtlColor == CTLCOLOR_EDIT || pWnd->m_hWnd == c_message.m_hWnd
		|| nCtlColor== CTLCOLOR_STATIC ){
		pDC->SetTextColor(RGB(255,255,0));
		pDC->SetBkColor(RGB(58,110,165));
	}
	return brushBack;
*/
	return hbr;
}
#define COLOR_FOR_EDIT RGB(0,36,72)
void CMedStockList::OnDblClickMshflexgrid1() 
{
	extern CHis3App theApp;
	
	CMSHFlexGrid * pGrid=(CMSHFlexGrid *) theApp.pParentGrid.pGrid;
	long row=pGrid->GetRows()-1;
	curRow=m_grid.GetRowSel();
	if( 0 == curRow || curRow == m_grid.GetRows()-1 )return ;			
//	CString HeadTitle[]={"ID","药品编码","药品名称","规格","单位","生产期","有效期","产地BM","产地","库存量","售价","进价","指导价"，’甲乙,类别-1代码}; //共 15列

	int idxTitle[]={0,2,3,4,11,8,9,10};
	for(int i=0;i< sizeof(idxTitle)/sizeof(int) ;i++){
		pGrid->SetTextMatrix(row,i,m_grid.GetTextMatrix(curRow,idxTitle[i]));
		
	}
	//药品类别新增列为 隐藏13,14列
	for(i=10; i< 12 ; i++ )
		pGrid->SetTextMatrix(row,i,m_grid.GetTextMatrix(curRow,i+3) );

	pGrid->SetRow(row);
	pGrid->SetCol(0);
	pGrid->SetColSel( sizeof(idxTitle)/sizeof(int) );
	pGrid->SetRowSel(row);

	row++;
	pGrid->AddItem(BLANKSTR,_variant_t(row));
	CDialog::OnOK();
				
					
				
}




