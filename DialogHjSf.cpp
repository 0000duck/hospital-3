// DialogHjSf.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "DialogHjSf.h"

#include "medStockList.h"
#include "ExesList.h"
#include "dialogAccountQuery.h"
#include "comfunc.h"
#include "excel9.h"
#include <afxole.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogHjSf dialog

extern CHis3App theApp;

CDialogHjSf::CDialogHjSf(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogHjSf::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogHjSf)
	//}}AFX_DATA_INIT
	selRow= NOSEL; //作为未选择状态
	selModify= NOSEL ;// 作为编辑框使用
	flagEdit= NOSEL ; // 1, 作为第一个grid,2,作为第二个grid,3,作为第三个grid
	strDoctorCode=BLANKSTR;
	strBM=BLANKSTR;
	strGHTYPE=BLANKSTR;

	dbRatio=0;
	dbZF=0;

	fontZY.CreatePointFont(160,"黑体");
}


void CDialogHjSf::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogHjSf)
	DDX_Control(pDX, IDC_EDIT_CHINA_MED, m_ZY_PRICE);
	DDX_Control(pDX, IDC_EDIT_YUER, m_yuer);
	DDX_Control(pDX, IDC_EDIT_RATIO, m_Ratio);
	DDX_Control(pDX, IDC_EDIT_WORKUNIT, m_workunit);
	DDX_Control(pDX, IDC_EDIT_TC, m_tc);
	DDX_Control(pDX, IDC_EDIT_JGC, m_jgc);
	DDX_Control(pDX, IDC_EDIT_IC, m_ic);
	DDX_Control(pDX, IDC_EDIT_GWY, m_gwy);
	DDX_Control(pDX, IDC_EDIT_DBJZ, m_dbjz);
	DDX_Control(pDX, IDC_EDIT_COST, m_cost);
	DDX_Control(pDX, IDC_EDIT_CASH, m_cash);
	DDX_Control(pDX, IDC_EDIT_ACCOUNT, m_account);
	DDX_Control(pDX, IDC_EDITHJ_AGE, m_age);
	DDX_Control(pDX, IDC_EDIT_YS, m_ys);
	DDX_Control(pDX, IDC_EDIT_TYPE, m_type);
	DDX_Control(pDX, IDC_EDIT_SEX, m_sex);
	DDX_Control(pDX, IDC_EDIT_PY, m_py);
	DDX_Control(pDX, IDC_EDIT_NUM, m_num);
	DDX_Control(pDX, IDC_EDIT_NAME, m_name);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid1);
	DDX_Control(pDX, IDC_MSHFLEXGRID2, m_grid2);
	DDX_Control(pDX, IDC_MSHFLEXGRID3, m_grid3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogHjSf, CDialog)
	//{{AFX_MSG_MAP(CDialogHjSf)
	ON_WM_CTLCOLOR()
	ON_COMMAND(ID_MENUITEM_HJ_ALL_DEL, OnMenuitemHjAllDel)
	ON_COMMAND(ID_MENUITEM_HJ_SEL_DEL, OnMenuitemHjSelDel)
	ON_EN_CHANGE(IDC_EDIT_PY, OnChangeEditPy)
	ON_EN_KILLFOCUS(IDC_EDIT_NUM, OnKillfocusEditNum)
	ON_COMMAND(ID_MENUITEM_G2A_DEL, OnMenuitemG2aDel)
	ON_COMMAND(ID_MENUITEM_G2S_DEL, OnMenuitemG2sDel)
	ON_COMMAND(ID_MENUITEM_MED_MODIFY, OnMenuitemMedModify)
	ON_COMMAND(ID_MENUITEM_OTHER_MODIFY, OnMenuitemOtherModify)
	ON_COMMAND(ID_MENUITEM_ACCOUNT_ADEL, OnMenuitemAccountAdel)
	ON_COMMAND(ID_MENUITEM_ACCOUNT_MODIFY, OnMenuitemAccountModify)
	ON_COMMAND(ID_MENUITEM_ACCOUNT_SDEL, OnMenuitemAccountSdel)
	ON_EN_CHANGE(IDC_EDIT_DBJZ, OnChangeEditDbjz)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, OnButtonPrint)
	ON_EN_CHANGE(IDC_EDIT_REAL_SS, OnChangeEditRealSs)
	//}}AFX_MSG_MAP
	ON_EN_KILLFOCUS( IDC_EDIT_CTRL_MOVE,OnKillfocusMoveEdit)
	ON_EN_CHANGE(IDC_EDIT_IC, OnChangeEditDbjz)
	ON_EN_CHANGE(IDC_EDIT_TC, OnChangeEditDbjz)
	ON_EN_CHANGE(IDC_EDIT_GWY, OnChangeEditDbjz)
	ON_EN_CHANGE(IDC_EDIT_JGC, OnChangeEditDbjz)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogHjSf message handlers

BOOL CDialogHjSf::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString strSql;
	const int SQL_1=45;
	m_ZY_PRICE.SetFont(&fontZY);
//	m_ZY_PRICE.SetWindowText("4391.9");
	CComFunc::GetSql(strSql,SQL_1);
	CComFunc::GetStringCollect(strSql,arySort01);








	long isel=pGH->m_grid.GetRow();
	m_type.SetWindowText(pGH->m_grid.GetTextMatrix(isel,pGH->COL_TYPE) );
	m_name.SetWindowText(pGH->m_grid.GetTextMatrix(isel,pGH->COL_NAME) );
	m_sex.SetWindowText(pGH->m_grid.GetTextMatrix(isel,pGH->COL_SEX) );
	m_age.SetWindowText(pGH->m_grid.GetTextMatrix(isel,pGH->COL_AGE) );

	CString sp2[2];
	strDANJUHAO=pGH->m_grid.GetTextMatrix(isel,pGH->COL_DANJUHAO ) ;
	strSql.Format("SELECT sickbm,ghtype FROM itemregistertou WHERE danjuhao='%s' ",strDANJUHAO );
	if(! CComFunc::GetString(strSql,sp2,2) )
	{
		AfxMessageBox("调出系统编码.类型信息出错!!请检查系统!!");
		return false;
	}
	strGHTYPE=sp2[1]; //内部挂号类型
	strBM=sp2[0]; 


	theApp.pParentGrid.pGrid=&m_grid1; //划价药品表格
	theApp.pParentGrid.p2=&m_grid2;
	SetGridHeader();

	fontMoveEdit.CreatePointFont(120,"宋体");
	CRect r1(0,0,0,0);
	editCtrl.Create(WS_CHILD,r1,this,IDC_EDIT_CTRL_MOVE);
	editCtrl.SetFont(&fontMoveEdit);
//	enum{ TYPE_QPYB=1,TYPE_HAYB=2,TYPE_JMTC=3,TYPE_BCBX=4,TYPE_GYQS=5,TYPE_GS=6,TYPE_LX=7,TYPE_TY=8,TYPE_GC=9 };
	isel=CComFunc::GetGhType(strGHTYPE) ;
	switch(isel )
	{
	case CComFunc::TYPE_GS:
	case CComFunc::TYPE_LX:
	case CComFunc::TYPE_TY: //此四种类型有报销比例
	case CComFunc::TYPE_GC:
		strSql.Format(" SELect sql from lsq_sql_statemnet where id=9 ");
		strSql=CComFunc::GetString(strSql);
		sp2[0].Format(" SELECT pro FROM (%s) WHERE LB='%s' AND BM='%s' ",strSql,strGHTYPE,strBM);
		dbRatio=atof(CComFunc::GetString(sp2[0]) );

		strSql.Format("%.2f%%",dbRatio);
		dbRatio/=100;
		break;
	case CComFunc::TYPE_BCBX:
		strSql.Format(" select sql from lsq_sql_statemnet where id=5 ");
		strSql=CComFunc::GetString(strSql);
		sp2[0].Format(" Select 结存金额 from (%s) Where 卡号='%s' ",strSql,strBM);
		dbZF=atof(CComFunc::GetString(sp2[0]) );
		strSql.Format("%.2f",dbZF);
		m_yuer.SetWindowText(strSql);
		goto SD;
	case CComFunc::TYPE_GYQS:
		strSql.Format(" select sql from lsq_sql_statemnet where id=6 ");
		strSql=CComFunc::GetString(strSql);
		sp2[0].Format(" Select yuer from (%s) Where bm='%s' ",strSql,strBM);
		dbZF=atof(CComFunc::GetString(sp2[0]) );
		strSql.Format("%.2f",dbZF);
		m_yuer.SetWindowText(strSql);

	default:
SD:		dbRatio=0;
		strSql.Format("不予报销");
	}
	m_Ratio.SetWindowText(strSql);

	if( !(isel == CComFunc::TYPE_QPYB || isel == CComFunc::TYPE_HAYB 
		|| isel == CComFunc::TYPE_JMTC ) )
		EnableControl(true); //禁用IC卡支付等控件

	if( 0 != isel )	m_grid3.EnableWindow(false);


	pw->PostMessage(WM_CLOSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CDialogHjSf::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if( pWnd->m_hWnd == m_cost.m_hWnd || pWnd->m_hWnd == m_cash.m_hWnd 
		|| pWnd->m_hWnd == GetDlgItem(IDC_EDIT_REAL_ZL)->m_hWnd  )
		pDC->SetTextColor(LSQ_RED);
	if( pWnd->m_hWnd == GetDlgItem(IDC_STATIC_IC)->m_hWnd)
		pDC->SetTextColor(LSQ_BLUE3);
	if( pWnd->m_hWnd == m_ZY_PRICE.m_hWnd  )
		pDC->SetTextColor(RGB(0,128,255));

	return hbr;
}

BOOL CDialogHjSf::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN){
		HWND tmpHwnd=GetFocus()->m_hWnd;
		if( tmpHwnd == GetDlgItem(IDC_EDIT_PY)->m_hWnd){ //查询药品
			CRect r1;
			GetDlgItem(IDC_EDIT_PY)->GetWindowRect(r1);
			
			CMedStockList medlist;
			medlist.r1=r1;
			theApp.pParentGrid.pGrid = &m_grid1;
			if(medlist.DoModal() == IDOK ){
			
				selRow=m_grid1.GetRows()-2 ;
				GetDlgItem(IDC_EDIT_MC)->SetWindowText( m_grid1.GetTextMatrix(selRow,COL_MC));//药品名
				m_num.SetWindowText("1"); //默认数量设为1
				m_num.SetSel(0,-1 );
				m_num.SetFocus();
				ComputeMoney();
			}
			else selRow= NOSEL ;

			return true;


		}
		else if ( tmpHwnd == GetDlgItem(IDC_EDIT_NUM)->m_hWnd && selRow != NOSEL )  //输入药品数量,并判断是否是刚才选择的行
		{
			GetMedNum();			
			ComputeMoney();
			return true;
		}
		else if ( tmpHwnd == GetDlgItem(IDC_EDIT_YS )->m_hWnd ) //调出医生姓名
		{
			QueryDoctor();

		}
		pMsg->wParam = VK_TAB;


	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CDialogHjSf::SetGridHeader()
{
	CComFunc::comSetGridHeader(m_grid1,3);
	CComFunc::comSetGridHeader(m_grid2,4);
	CComFunc::comSetGridHeader(m_grid3,5);
	
}

void CDialogHjSf::ComputeMoney() //计算金额
{
	double dbMoney,dbSl,dbPrice,dbSum(0),dbZYprice(0);
	double dbAccount(0),dbZyCost(0);
	CString tmpStr;
	long i;
	long iRows=m_grid1.GetRows();
	if( iRows <=2 ) goto GRID2;
	iRows--;

	for( i=1; i< iRows ; i++ )
	{
		dbSl=atof( m_grid1.GetTextMatrix(i,COL_SL) ); 
		dbPrice=atof( m_grid1.GetTextMatrix(i,COL_PRICE) );
		dbMoney=dbSl*dbPrice;
		/*********/
		tmpStr=m_grid1.GetTextMatrix(i,COL_ZY);
		dbZyCost=atof( m_grid1.GetTextMatrix(i,COL_ZY_COST) )*dbSl;// 成本 

		for(int ix=0;ix<arySort01.GetSize(); ++ix )
		{
			if( tmpStr.Compare(arySort01[ix])== 0 ){
				dbZYprice+=dbZyCost;
				break;
			}

		}
		/*********/

		dbSum+=dbMoney;
		tmpStr.Format("%.2f",dbMoney);
		m_grid1.SetTextMatrix(i,COL_MONEY,tmpStr);

	}
	dbAccount+=dbSum; //药品费用
	tmpStr.Format("%.2f",dbSum);
	m_grid1.SetTextMatrix(i,COL_MONEY,tmpStr);
	tmpStr.Format("总计：%ld",i-1 );
	m_grid1.SetTextMatrix(i,COL_MC,tmpStr);

GRID2:
	iRows=m_grid2.GetRows();
	if( iRows > 2 ){
		iRows--;
		dbPrice=0;
		for( i=1; i< iRows ; i++ )
		{
			dbPrice+=atof( m_grid2.GetTextMatrix(i,EXES_MONEY) );
			
		}
		dbAccount+=dbPrice; //其它费用
		tmpStr.Format("%.2f",dbPrice);
		m_grid2.SetTextMatrix(i,EXES_MONEY,tmpStr);
		tmpStr.Format("总计：%ld",i-1 );
		m_grid2.SetTextMatrix(i,EXES_MC_COL,tmpStr);
	}
	else {
		m_grid2.SetTextMatrix(1L,EXES_MONEY,BLANKSTR);
		m_grid2.SetTextMatrix(1L,EXES_MC_COL,BLANKSTR);
	}

	dbPrice=0;
	iRows=m_grid3.GetRows();
	if( iRows > 2 ) {
		iRows--;
		for( i=1; i< iRows ; i++ )
		{
			dbPrice+=atof( m_grid3.GetTextMatrix(i,ACCOUNT_ZFJE) );
			
		}
		tmpStr.Format("%.2f",dbPrice);
		m_grid3.SetTextMatrix(i,ACCOUNT_ZFJE,tmpStr);
		m_account.SetWindowText(tmpStr);
	
		tmpStr.Format("总计：%ld",i-1 );
		m_grid3.SetTextMatrix(i,ACCOUNT_ID,tmpStr);

		
	}
	else {
		m_grid3.SetTextMatrix(1L,ACCOUNT_ZFJE,BLANKSTR);
		m_grid3.SetTextMatrix(1L,ACCOUNT_ID,BLANKSTR);
	}

 //////////
	tmpStr.Format("%.2f",dbZYprice);
	m_ZY_PRICE.SetWindowText(tmpStr);
	//////
	tmpStr.Format("%.2f",dbAccount);
	m_cost.SetWindowText(tmpStr); //总费用

	tmpStr.Format("%.2f",dbAccount*dbRatio);
	m_workunit.SetWindowText(tmpStr);	
	
	tmpStr.Format("%.2f",dbPrice);
	m_account.SetWindowText(tmpStr); //帐户支付
	computeBalance();
}

BEGIN_EVENTSINK_MAP(CDialogHjSf, CDialog)
    //{{AFX_EVENTSINK_MAP(CDialogHjSf)
	ON_EVENT(CDialogHjSf, IDC_MSHFLEXGRID1, -600 /* Click */, OnClickMshflexgrid1, VTS_NONE)
	ON_EVENT(CDialogHjSf, IDC_MSHFLEXGRID2, -601 /* DblClick */, OnDblClickMshflexgrid2, VTS_NONE)
	ON_EVENT(CDialogHjSf, IDC_MSHFLEXGRID2, -600 /* Click */, OnClickMshflexgrid2, VTS_NONE)
	ON_EVENT(CDialogHjSf, IDC_MSHFLEXGRID3, -601 /* DblClick */, OnDblClickMshflexgrid3, VTS_NONE)
	ON_EVENT(CDialogHjSf, IDC_MSHFLEXGRID3, -600 /* Click */, OnClickMshflexgrid3, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CDialogHjSf::OnClickMshflexgrid1() 
{
	const int ENDLINES=2;
	if(m_grid1.GetRows() == ENDLINES )return;//判断是否需要显示快捷菜单

	MSG *pms;
	pms=(MSG*)GetCurrentMessage();
	if(pms->message != 0x205) {//0x202为鼠标左键,0x205为鼠标右键消息
		return;
	}
	CMenu pm;
	CPoint p;
	pm.LoadMenu(IDR_MENU_QUICK);
	CMenu* pmenu=pm.GetSubMenu(0);
	GetCursorPos(&p);
	pmenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON ,p.x,p.y,this);  	


}

void CDialogHjSf::OnMenuitemHjAllDel() 
{
	m_grid1.SetRows(2);
	m_grid1.AddItem(BLANKSTR,_variant_t(1L));
	m_grid1.SetRows(2);

	ComputeMoney();
}

void CDialogHjSf::OnMenuitemHjSelDel() 
{
	
	long iStart,iEnd;
	iStart=m_grid1.GetRow();
	iEnd=m_grid1.GetRowSel();
	
	if ( iEnd == m_grid1.GetRows()-1 ) iEnd-- ; //最后一行不能删除
	int iRows= iEnd-iStart;

	while ( iRows -- >= 0 )
	{
		m_grid1.RemoveItem(iStart);

	}

	ComputeMoney();
	
}

void CDialogHjSf::OnChangeEditPy() 
{
	PostMessage(WM_KEYDOWN,VK_RETURN); //有按键时发送回车消息

	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CDialogHjSf::OnKillfocusEditNum() 
{
	long iRows=m_grid1.GetRows()-2; //获取最后一行位置
	CString strView("1.00");
	
	if( m_grid1.GetTextMatrix(iRows,COL_SL).IsEmpty() ){

		m_grid1.SetTextMatrix(iRows,COL_SL,strView);
		ComputeMoney();
	}


}

void CDialogHjSf::GetMedNum()
{
	CString str2,str1;
	double dbKC=atof( m_grid1.GetTextMatrix(selRow,COL_KC ) );
	GetDlgItem(IDC_EDIT_NUM)->GetWindowText(str1);
	
	str2.Format("%.2f",atof(str1));
	
	if( atof(str2) > dbKC ){
		AfxMessageBox("取药数量大于目前库存数量，系统自动设定取药数为库存量！！");
		str2.Format("%.2f",dbKC);
	}
	
	m_grid1.SetTextMatrix(selRow,COL_SL,str2);
	GetDlgItem(IDC_EDIT_NUM)->SetWindowText(BLANKSTR);

	selRow=NOSEL ;

	GetDlgItem(IDC_EDIT_MC)->SetWindowText( BLANKSTR);//清空药品名

	GetDlgItem(IDC_EDIT_PY)->SetFocus();

}

void CDialogHjSf::OnDblClickMshflexgrid2() 
{
	CExesList el;
	theApp.pParentGrid.pGrid=&m_grid2;
	if( el.DoModal() == IDOK) ComputeMoney();

}

void CDialogHjSf::OnClickMshflexgrid2() 
{
	const int ENDLINES=2;
	if(m_grid2.GetRows() == ENDLINES )return;//判断是否需要显示快捷菜单

	MSG *pms;
	pms=(MSG*)GetCurrentMessage();
	if(pms->message != 0x205) {//0x202为鼠标左键,0x205为鼠标右键消息
		return;
	}
	CMenu pm;
	CPoint p;
	pm.LoadMenu(IDR_MENU_QUICK);
	CMenu* pmenu=pm.GetSubMenu(1);
	GetCursorPos(&p);
	pmenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON ,p.x,p.y,this);  	
	
}

void CDialogHjSf::OnMenuitemG2aDel() 
{
	m_grid2.SetRows(2);
	m_grid2.AddItem("",_variant_t(1L));
	m_grid2.SetRows(2);
	
	ComputeMoney();
}

void CDialogHjSf::OnMenuitemG2sDel() 
{
	long iStart,iEnd;
	iStart=m_grid2.GetRow();
	iEnd=m_grid2.GetRowSel();
	
	if ( iEnd == m_grid2.GetRows()-1 ) iEnd-- ; //最后一行不能删除
	int iRows= iEnd-iStart;

	while ( iRows -- >= 0 )
	{
		m_grid2.RemoveItem(iStart);

	}

	ComputeMoney();
	
}

void CDialogHjSf::OnDblClickMshflexgrid3() 
{
	CDialogAccountQuery qy;
	theApp.pParentGrid.pGrid=&m_grid3;
	if( qy.DoModal() == IDOK )
	{
		CString tmpStr;
		double dbPrice(0);
		long iRows=m_grid3.GetRows()-1;
		for( long i=1; i< iRows ; i++ )
		{
			dbPrice+=atof( m_grid3.GetTextMatrix(i,ACCOUNT_ZFJE) );
			
		}
		tmpStr.Format("%.2f",dbPrice);
		m_grid3.SetTextMatrix(i,ACCOUNT_ZFJE,tmpStr);
		m_account.SetWindowText(tmpStr);
		
	}
}

void CDialogHjSf::OnMenuitemMedModify() //药品数量修改
{
	ShowEdit( m_grid1,COL_SL );
	flagEdit= MED_GRID;
	
}

void CDialogHjSf::OnKillfocusMoveEdit() //编辑框修改数据时进行记录
{
	if( selModify == NOSEL ) return;
	CString tmpStr,slStr;
	editCtrl.GetWindowText(tmpStr);
	
	switch ( flagEdit ){
	
	case MED_GRID: 	
		slStr.Format("%.2f",atof(tmpStr) );
		if( atof( slStr ) > atof( m_grid1.GetTextMatrix(selModify,COL_KC) ) ) 
		{
			AfxMessageBox("取药数量超越库存数量,系统自动设定为最大可取数!");
			slStr.Format("%.2f",atof( m_grid1.GetTextMatrix(selModify,COL_KC)) );
			
		}
		m_grid1.SetTextMatrix(selModify,COL_SL,slStr);
		selModify=NOSEL;
		break;

	case OTHER_GRID:
		slStr.Format("%.2f",atof(tmpStr) );
		m_grid2.SetTextMatrix(selModify,EXES_MONEY,slStr);
		selModify=NOSEL;
		break;

	case ACCOUNT_GRID:
	
		slStr.Format("%.2f",atof(tmpStr) ); //输入的支付金额
		CString t01Str,t02Str;
		m_cash.GetWindowText(t01Str);
		m_account.GetWindowText(t02Str);
		double dbCash=atof(t01Str); //应支付现金
		dbCash+=atof(t02Str);

		double dbAccount(0);
		for( int i=1 ; i < m_grid3.GetRows()-1 ; i++ )
		{
			dbAccount+=atof( m_grid3.GetTextMatrix(i,ACCOUNT_ZFJE ) );
		}
		dbAccount-= atof(m_grid3.GetTextMatrix(selModify,ACCOUNT_ZFJE));
		dbCash-=dbAccount; 

		if( atof( slStr ) >  dbCash ) 
		{
			AfxMessageBox("支付金额不能大于消费现金!");
			slStr.Format("%.2f",dbCash );
			
		}
		m_grid3.SetTextMatrix(selModify,ACCOUNT_ZFJE,slStr);
		selModify=NOSEL;
		break;


	}

	editCtrl.ShowWindow(SW_HIDE);
	editCtrl.SetWindowText(BLANKSTR);
	ComputeMoney();

}

void CDialogHjSf::OnMenuitemOtherModify() 
{
	ShowEdit(m_grid2,EXES_MONEY);
	flagEdit=OTHER_GRID;
}

void CDialogHjSf::ShowEdit(CMSHFlexGrid &grid,int operCol)
{
	if(grid.GetRow() == grid.GetRows()-1 )return; //最后一行为合计行

	CDC *pCdcGrid=grid.GetDC();
	int nWidth=pCdcGrid->GetDeviceCaps(LOGPIXELSX);
	int nHigh=pCdcGrid->GetDeviceCaps(LOGPIXELSY);
	ReleaseDC(pCdcGrid);

	selModify=grid.GetRow();
	CString str2;
	CString	strOrigin=grid.GetTextMatrix(selModify,operCol);

	grid.SetCol(operCol);

	long left=grid.GetCellLeft();
	long top=grid.GetCellTop();
	long right=grid.GetCellWidth();
	long bottom=grid.GetCellHeight();

	CRect rectGrid,r2;
	grid.GetWindowRect(rectGrid);
	ScreenToClient(rectGrid);
	rectGrid.left+=left*nWidth/1440;
	rectGrid.top+=top*nHigh/1440;
	rectGrid.right=right*nWidth/1440+rectGrid.left-1;
	rectGrid.bottom=bottom*nHigh/1440+rectGrid.top-1;

	editCtrl.MoveWindow(rectGrid);
	editCtrl.ShowWindow(SW_SHOW);
	editCtrl.SetFocus();
	editCtrl.SetWindowText(strOrigin);
	editCtrl.SetWindowPos(&CWnd::wndTop,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
	editCtrl.SetSel(0,strOrigin.GetLength());	

}

void CDialogHjSf::QueryDoctor()
{
	CString tmpStr,strSql;
	m_ys.GetWindowText(strDoctorCode );
	strSql.Format("select name from operator where rybm='%s' and effect=1 ",strDoctorCode);
	tmpStr=CComFunc::GetString(strSql);

	if(  tmpStr.IsEmpty()  ) {
		strDoctorCode=BLANKSTR;
		m_ys.SetWindowText(strDoctorCode );
		m_ys.SetFocus();
		return;
	}
	m_ys.SetWindowText(tmpStr);

	


}

void CDialogHjSf::OnClickMshflexgrid3() 
{
	const int ENDLINES=2;
	if(m_grid3.GetRows() == ENDLINES )return;//判断是否需要显示快捷菜单

	MSG *pms;
	pms=(MSG*)GetCurrentMessage();
	if(pms->message != 0x205) {//0x202为鼠标左键,0x205为鼠标右键消息
		return;
	}
	CMenu pm;
	CPoint p;
	pm.LoadMenu(IDR_MENU_QUICK);
	CMenu* pmenu=pm.GetSubMenu(2);
	GetCursorPos(&p);
	pmenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON ,p.x,p.y,this);  	
	
}

void CDialogHjSf::OnMenuitemAccountAdel() 
{
	m_grid3.SetRows(2);
	m_grid3.AddItem(BLANKSTR,_variant_t(1L));
	m_grid3.SetRows(2);
	
}

void CDialogHjSf::OnMenuitemAccountModify() 
{
	ShowEdit( m_grid3,ACCOUNT_ZFJE );
	flagEdit= ACCOUNT_GRID;
	
}

void CDialogHjSf::OnMenuitemAccountSdel() 
{
	long iStart,iEnd;
	iStart=m_grid3.GetRow();
	iEnd=m_grid3.GetRowSel();
	
	if ( iEnd == m_grid3.GetRows()-1 ) iEnd-- ; //最后一行不能删除
	int iRows= iEnd-iStart;

	while ( iRows -- >= 0 )
	{
		m_grid3.RemoveItem(iStart);

	}

	ComputeMoney();
	
}

void CDialogHjSf::computeBalance()
{
	double dbCost(0),dbCash(0); //分别为 总金额.现金支付
	double dbTc(0),dbIc(0),dbDbjz(0),dbGwy(0),dbJgc(0),dbAccount(0); //分别为 统筹.IC卡.大病救助.公务员.建国前.帐户
	double db1,db2;
	CString str,str2;
	
	m_cost.GetWindowText(str);
	dbCost=atof(str);

	m_tc.GetWindowText(str);
	dbTc=atof(str);

	m_ic.GetWindowText(str);
	dbIc=atof(str);

	m_dbjz.GetWindowText(str);
	dbDbjz=atof(str);

	m_gwy.GetWindowText(str);
	dbGwy=atof(str);

	m_jgc.GetWindowText(str);
	dbJgc=atof(str);

	m_account.GetWindowText(str);
	dbAccount=atof(str);
	

	

	dbCash=dbCost*(1-dbRatio ) - dbTc- dbIc-dbDbjz-dbGwy-dbJgc-dbAccount;

	if( dbCash < 0 ) 
	{
		AfxMessageBox("支付金额大于消费总额!!请修改应支付额!!");
	}
	if( dbZF > 0 ) {
		if( dbZF - dbCash >= 0 ){
			str.Format("%.2f",dbZF-dbCash );
			str2.Format("%.2f",dbCash);
			dbCash=0;
		}
		else{
			dbCash-=dbZF;
			str2.Format("%.2f",dbZF);
			str.Format("%.2f",0 );
		}
		m_yuer.SetWindowText(str);
		m_account.SetWindowText(str2);

	}

	str.Format("%.2f",dbCash);
	m_cash.SetWindowText(str);

	OnChangeEditRealSs() ;
}

void CDialogHjSf::OnChangeEditDbjz() 
{
	computeBalance();
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CDialogHjSf::OnOK() 
{
	if( strDoctorCode.IsEmpty() ){

		AfxMessageBox("请确定输入医生代码");
		return;
	}
	const CString EMPACCOUNT="001";
	const CString RELACCOUNT="002";
	CString strSql;
	CString strDoctor;
	CString strarr[10];
	m_ys.GetWindowText(strDoctor);
	long medID;

	double dbCost(0),dbCash(0); //分别为 总金额.现金支付
	double dbTc(0),dbIc(0),dbDbjz(0),dbGwy(0),dbJgc(0),dbAccount(0); //分别为 统筹.IC卡.大病救助.公务员.建国前.帐户
	double dbMed(0),dbMedprofit(0),dbOther(0);

	CString str;
	
	m_cost.GetWindowText(str);
	dbCost=atof(str);

	m_tc.GetWindowText(str);
	dbTc=atof(str);

	m_ic.GetWindowText(str);
	dbIc=atof(str);

	m_dbjz.GetWindowText(str);
	dbDbjz=atof(str);

	m_gwy.GetWindowText(str);
	dbGwy=atof(str);

	m_jgc.GetWindowText(str);
	dbJgc=atof(str);

	m_account.GetWindowText(str);
	dbAccount=atof(str);

	m_cash.GetWindowText(str);
	dbCash=atof(str);

	if( dbCash < 0 ) 
	{
		AfxMessageBox("支付金额大于消费总额!!请修改应支付额!!");
		return;
	}
	
	try{
		HospitalConnect->BeginTrans();
		
		//ITEMTI 中的 DJ 在划价中 是药品零售价,PDJ 是进货价, SELLDJ 是国家标准批发价
		/*			{"ID","药品编码","药品名称","规格","单位","生产期","有效期",\
		"产地BM","产地","库存量","售价","进价","指导价","取药数"}; //共14列
		*/
		for( long row=1;row< m_grid1.GetRows()-1; row++)
		{
			strarr[0]=m_grid1.GetTextMatrix(row,COL_ID);//ID
			strarr[1]=m_grid1.GetTextMatrix(row,COL_SL);//数量
			strarr[2]=m_grid1.GetTextMatrix(row,COL_PRICE);//价格
			strarr[3]=m_grid1.GetTextMatrix(row,COL_FACTORY);//厂址
			strarr[4]=m_grid1.GetTextMatrix(row,COL_JINJIA); //进价
			
			dbMed+=atof( strarr[1] )*atof(strarr[2]); //药品费
			dbMedprofit+= atof( strarr[1] ) * (atof( strarr[2] ) -atof( strarr[4] ) ); //利润


			medID=atol(strarr[0]);
			
			strSql.Format(" INSERT  into ITEMTI (ID,SL,DJ,RIQI,DANJUHAO,KFBM,YPBM,\
			  RQ1,RQ2,factory,PDJ,SELLDJ) values(%ld,%.2f,%.2f,trunc(sysdate,'dd'),'%s',(SELECT KFBM FROM MEDLIE WHERE id=%ld ),\
			  (select YPBM FROM medlie WHERE id=%ld ),(SELECT rq1 FROM medlie where id=%ld ),(select rq2 from medlie where id=%ld ),'%s',\
			  (select jinjia from medlie  where id=%ld ),(select coach_price from medlie where id=%ld ) ) ",medID,atof(strarr[1]),
			  atof(strarr[2]),strDANJUHAO,medID,medID,medID,medID,strarr[3],medID,medID );
					//在挂号划价中 PDJ 为购进价 SELLDJ 为指导价
					//在其它转为时 SELLDJ 为进价,PDJ 为指导价
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
			//锁定记录,防止其它事务进行更改
			strSql.Format(" select sl from medlie where id=%ld for update ",atol(strarr[0]) ); 
			strSql=CComFunc::GetString(strSql);
//			str.Format("ID: %ld",atol(strarr[0] ));
//			AfxMessageBox(str);
			if(  atol(strSql) < atol(strarr[1]))
			{
				str.Format(" 药品: %s 规格: %s ,取药数量: %.2f 大于库存数量,实际库存量: %.2f ,请重新选择药品!",m_grid1.GetTextMatrix(row,COL_MC),
					m_grid1.GetTextMatrix(row,COL_GG),atof(strarr[1]),atof(strSql) );
				AfxMessageBox(str);
				HospitalConnect->RollbackTrans();
				return;
			}

			strSql.Format(" UPDATE medlie Set sl= sl -( %.2f ) WHERE id=%ld ",atof( strarr[1] ),atol(strarr[0]) );
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);

		}
		
		for(row=1;row<m_grid2.GetRows()-1;row++)
		{
			strarr[0]=m_grid2.GetTextMatrix(row,EXES_ID);
			strarr[1]=m_grid2.GetTextMatrix(row,EXES_MONEY);
			dbOther+=atof( strarr[1] );

			strSql.Format("insert into ItemRegisterTiZL (ZLMC,dj,danjuhao ) values(\
			'%s',%.2f,'%s' )",strarr[0],atof(strarr[1]),strDANJUHAO);
										 
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
				 
													 
		}
		strSql.Format("update ITEMREGISTERTOU set DOCTOR='%s' ,DOCTORNAME='%s',\
			划价员='%s',划价员名='%s',KFBM='%s',收费员='%s',收费员名='%s',cash=%.2f,\
			medMoney=%.2f,treateMoney=%.2f,profit=%.2f,p1=%.2f,p2=%.2f,p3=%.2f,p4=%.2f, \
			p5=%.2f ,p6=%.2f	where DANJUHAO='%s' ",strDoctorCode,\
			strDoctor,LoginInformation.user_code,LoginInformation.user,LoginInformation.kfbm,\
			LoginInformation.user_code,LoginInformation.user,dbCash,\
			dbMed,dbOther,dbMedprofit,dbJgc,dbGwy,dbIc,dbDbjz,dbTc,dbAccount,strDANJUHAO);
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);

		for( row=1 ; row <m_grid3.GetRows()-1 ; row++ ){ //帐户消耗,用于体检上
			strarr[0]=m_grid3.GetTextMatrix(row,ACCOUNT_ID);
			strarr[1]=m_grid3.GetTextMatrix(row,ACCOUNT_YE);
			strarr[2]=m_grid3.GetTextMatrix(row,ACCOUNT_ZFJE);
			strarr[3]=m_grid3.GetTextMatrix(row,ACCOUNT_TYPE);
			strarr[4]=m_grid3.GetTextMatrix(row,ACCOUNT_MC); //姓名
			strSql.Format(" Insert into LSQ_ACCOUNT_USE (id,n1,n2,serial,flag,mc) values ( \
				'%s',%.2f,%.2f,'%s','%s','%s' ) ",strarr[0],atof(strarr[1]),atof(strarr[2]),\
				strDANJUHAO,strarr[3],strarr[4] );
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);

			if( strarr[3].Compare(EMPACCOUNT) == 0  ){
				strSql.Format(" Update 职工基本情况表 Set 结存金额=结存金额-( %.2f ) Where 卡号='%s' ",
					atof(strarr[2]),strarr[0] );

			}
			else if( strarr[3].Compare(RELACCOUNT) == 0 )
			{
				strSql.Format(" Update codeqingshu Set yuer=yuer-(%.2f) where bm='%s' ",
					atof(strarr[2]),strarr[0] );

			}
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);

		}

		int itype=CComFunc::GetGhType( strGHTYPE ) ;

		if(  itype == CComFunc::TYPE_BCBX ){
			strSql.Format(" Update 职工基本情况表 Set 结存金额=结存金额-( %.2f ) Where 卡号='%s' ",dbAccount,strBM);
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		}
		else if( itype == CComFunc::TYPE_GYQS )
		{
			strSql.Format(" Update codeqingshu Set yuer=yuer-(%.2f) where bm='%s' ",dbAccount,strBM );
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
			
		}
			

		
		HospitalConnect->CommitTrans();
		
	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		AfxMessageBox("保存药品出错...");
		HospitalConnect->RollbackTrans();
		return;
	}
	CComFunc::BeginCritical(strDANJUHAO,false);
	
	CDialog::OnOK();
}



void CDialogHjSf::OnButtonPrint() 
{
#define _O(x) COleVariant(x)
_Application app;
Workbooks books;
_Workbook book;
Worksheets sheets;
_Worksheet sheet;
COleVariant vOpt(DISP_E_PARAMNOTFOUND,VT_ERROR);

AfxOleGetMessageFilter()->EnableBusyDialog(FALSE);  //禁止出现COM调用长时间无响应对应框
AfxOleGetMessageFilter()->SetBusyReply(SERVERCALL_RETRYLATER); 
AfxOleGetMessageFilter()->EnableNotRespondingDialog(TRUE); 
AfxOleGetMessageFilter()->SetMessagePendingDelay(-1);
	BeginWaitCursor();

	CString strFileName;
	strFileName.Format("%s",LoginInformation.path);
	strFileName+=CComFunc::GetString("SELECT ds1 FROM lsq_upgrade WHERE ds2='HUAJIA_PRINT_FILE' ");

	int itype=CComFunc::GetGhType(strGHTYPE);
	if( strGHTYPE.Compare("QPTD") == 0 || strGHTYPE.Compare("QHMT")==0 ) itype=0 ; //新增此句意为
	//*如果为清河门特,清浦门特可打印，原清河门特
	//*与其它基本保险都被列入不能打印之列
	if( itype== CComFunc::TYPE_HAYB || itype== CComFunc::TYPE_QPYB ||itype== CComFunc::TYPE_JMTC )
	{
		strFileName.LoadString(IDS_HUAJIA_PROMPT);
		AfxMessageBox(strFileName);	
		return; 
	}

	app.CreateDispatch("excel.application");
	if(!app){
		AfxMessageBox("请注意系统中必须装有EXCEL97 或者 EXCEL2000 ,否则此功能不能使用...");
		return;
	}
	books=app.GetWorkbooks();
	book=books.Open(strFileName,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt);
	sheets=book.GetWorksheets();

	sheet=sheets.GetItem(_O("MED_Origin_DATA")); //可以指定sheet索引号或sheet名

	
	Range vRange;
	app.SetVisible(false); //显示
	app.Run(COleVariant("thisWorkBook.clearContent"),vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,
		vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,
		vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt );  //清除要输入表的内容

//* EXCEL 第一行输入顺序为 药品行数 治疗项目行数 收费员 
	const int START_RECORD=2; // 药品 治疗情况跨过前起始行
	int iUseCol[]={COL_MC,COL_GG,COL_DW,COL_SL,COL_PRICE,10 /*甲乙丙*/ };  //*药品要输出的列
	int iUseCol2[]={EXES_MC_COL,EXES_MONEY };          //* 治疗项目要输出的列
	int y,x;
	int iMedRows=m_grid1.GetRows()-2; //药品实际行数
	int iZlRows=m_grid2.GetRows() - 2; //治疗项目实际行数
	CString strMedtmp;
	CString strInsert[20]; //* 分别按列填入必要的信息
	
	for ( x=0; x< iMedRows  ; x++)    //* 药品原始信息输出
	{
		for(  y=0; y < sizeof(iUseCol) /sizeof(int) ; y++)
		{
			CComFunc::SetExcelCell(sheet,x+START_RECORD,y,m_grid1.GetTextMatrix(x+1,iUseCol[y]));
		}
	}

	for ( x=0 ; x < iZlRows; x++ )  //* 治疗费信息输出
	{
		for( y=0 ; y < sizeof(iUseCol2)/ sizeof(int) ; y ++)
		{
			CComFunc::SetExcelCell(sheet,x+START_RECORD+iMedRows,y,m_grid2.GetTextMatrix(x+1,iUseCol2[y]));
	
		}
	}

	x=0;
	strMedtmp.Format("%ld",iMedRows  ); 
	strInsert[x++]=strMedtmp;				//* 药品行数 0
	strMedtmp.Format("%ld",iZlRows );
	strInsert[x++]=strMedtmp;				//* 治疗行数 1
	
	m_name.GetWindowText( strInsert[x++]) ;					//* 病人姓名 2
	strInsert[x++]=LoginInformation.user;	//* 收费员名 3
	
	m_type.GetWindowText( strInsert[x++] );					//* 人员类别 4   如 社会就诊\补充保险
	
	strInsert[x++]=strDANJUHAO;				//* 挂号单据 5
	m_cost.GetWindowText(strMedtmp);
	strInsert[x++]=strMedtmp;				//* 总金额   6

	strInsert[x++]= GetChinesePrice(atof(strMedtmp)); //* 总金额大写 7

	strMedtmp=m_grid1.GetTextMatrix(m_grid1.GetRows()-1,COL_MONEY );
	strInsert[x++]=strMedtmp;				//* 药品费  8

	strMedtmp=m_grid2.GetTextMatrix(m_grid2.GetRows()-1,EXES_MONEY );		
	strInsert[x++]=strMedtmp;				//*　治疗费  9
	

	strInsert[x++]=BLANKSTR;  //帐户余额 10


	m_cash.GetWindowText(strInsert[x++]);
 //现金  11

	m_yuer.GetWindowText(strInsert[x++]);
			//* 本次户余  12

	for ( y=0 ; y < x ; y++)
		CComFunc::SetExcelCell(sheet,1,y,strInsert[y]);  //从EXCEL的第二行第一列开始输出,


	
	app.Run(COleVariant("thisWorkBook.Print_Invoice"),vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,
		vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,
		vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt );  //调用excel中thisworkbook.print_invoice宏
	
	sheet.ReleaseDispatch();
	sheets.ReleaseDispatch();
	book.ReleaseDispatch();
	books.ReleaseDispatch();
	app.ReleaseDispatch();
	app.DetachDispatch();

	EndWaitCursor();	
	
}

CString CDialogHjSf::GetChinesePrice(double dMoney)
{
     CString strMoney;

     strMoney.Format ("%.2f" , dMoney);

	 if( strMoney.GetLength() >15 ){
		 
		 return "￥"+strMoney; //数值太大
	 }

     CString strUnit = "元拾佰仟万拾佰仟亿拾佰仟";

     CString strNumber = "零壹贰叁肆伍陆柒捌玖";

     CString strOtherUnit = "整角分";

 

     //将数字分整数部份与小数部份处理

     int nPos = strMoney.Find (".");

     int nLength = strMoney.GetLength ();

     if(nPos < 0)

         nPos = nLength;

     CString strReturnValue;

     int nCount = 0;

     bool bZero = false;

     bool bNeedLevel = false;    //对段的识别，用于是否需要出现段名，如亿，万等

     //对整数部份进行反相识别处理

     for(int i = nPos - 1;i >= 0;i --)

     {

         TCHAR ch = strMoney.GetAt (i);

         if(nCount % 4 == 0 && nCount > 0)

         {

               //如果处理的数字为第四位（万），或第八位（亿）等，则要求置段

              bNeedLevel = true;

         }

         if(ch == '0')

         {

               //只对拾佰仟位的０进行识别，主要考虑到拾的特殊性，即如１０读壹拾，不会读壹拾零

              if(nCount % 4 != 0)

                   bZero = true;

         }

         else

         {

              CString strTemp(strReturnValue);

              strReturnValue = strNumber.Mid ((ch - 0x30) * 2 , 2);

              if(nCount > 0)

              {

                  strReturnValue += strUnit.Mid (nCount * 2 , 2);

                   if(nCount % 4 != 0 && bNeedLevel)

                   {

                         //这里判断是否需要读段名，如万，亿等

                       strReturnValue += strUnit.Mid (int(nCount / 4) * 8 , 2);

                   }

                   bNeedLevel = false;

              }

              if(bZero)

              {

                   //只有比当前处理的位要低中有数字才补零

                   if(!strTemp.IsEmpty ())

                       strReturnValue += strNumber.Left (2);

                   bZero = false;

              }

              strReturnValue += strTemp;

         }

         nCount ++;

     }

     strReturnValue += strUnit.Left (2);
	 if(strReturnValue.GetLength()<=2) strReturnValue="";
	 //防止整数部分为零

     bool bAllZero = true;

     //下面实现对小数点后面的处理

     //先判断是否为全零，则不需要继续读

     if(nPos < nLength)

     {

         if(nLength > 2)

              nLength = 2;

         for(int i = 0;i < nLength;i ++)

              if(strMoney.GetAt (nPos + i + 1) != '0')

                   bAllZero = false;

     }

     if(bAllZero)

     {

         strReturnValue += strOtherUnit.Left (2);

     }

     else

     {

          //对分角的处理

         for(int i = 0;i < nLength;i ++)

         {

              TCHAR ch = strMoney.GetAt (nPos + 1 + i);

              if(ch == '0' && i > 0)

              {

              }

              else

              {

                   strReturnValue += strNumber.Mid ((ch - 0x30) * 2 , 2);

                   if(ch != '0')

                       strReturnValue += strOtherUnit.Mid ((i + 1) * 2 , 2);

              }

         }

     }

     return strReturnValue;

}

void CDialogHjSf::EnableControl(bool f)
{
	m_ic.SetReadOnly(f);
	m_tc.SetReadOnly(f);
	m_jgc.SetReadOnly(f);
	m_gwy.SetReadOnly(f);
	m_dbjz.SetReadOnly(f);
}

void CDialogHjSf::OnCancel() 
{
	CComFunc::BeginCritical(strDANJUHAO,false);	
	CDialog::OnCancel();
}

void CDialogHjSf::OnChangeEditRealSs() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	CString str1,str2;
	GetDlgItem(IDC_EDIT_REAL_SS)->GetWindowText(str1);
	m_cash.GetWindowText(str2);
	str1.Format("%.2f",atof(str1)-atof(str2) );
	GetDlgItem(IDC_EDIT_REAL_ZL)->SetWindowText(str1);

}
