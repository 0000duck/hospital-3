// CostClassA.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "CostClassA.h"
#include "costClassaAdd.h"
#include "costClassAmodify.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCostClassA dialog


CCostClassA::CCostClassA(CWnd* pParent /*=NULL*/)
	: CDialog(CCostClassA::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCostClassA)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCostClassA::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCostClassA)
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCostClassA, CDialog)
	//{{AFX_MSG_MAP(CCostClassA)
	ON_COMMAND(ID_MENU_COST_ADD, OnMenuCostAdd)
	ON_COMMAND(ID_MENU_COST_MODIFY, OnMenuCostModify)
	ON_COMMAND(ID_MENU_COST_DEL, OnMenuCostDel)
	ON_COMMAND(ID_MENU_COST_RESTORE, OnMenuCostRestore)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCostClassA message handlers

BOOL CCostClassA::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	OnOK();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCostClassA::OnOK() 
{
	CString strSql;

	CComFunc::comSetGridHeader(m_grid,GRID_HEADER_ID); 
	CComFunc::GetSql(strSql,SQL_QUERY_ID);
	
	CComFunc::ReadDataForGrid(strSql,m_grid);
	
}

BEGIN_EVENTSINK_MAP(CCostClassA, CDialog)
    //{{AFX_EVENTSINK_MAP(CCostClassA)
	ON_EVENT(CCostClassA, IDC_MSHFLEXGRID1, -600 /* Click */, OnClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CCostClassA::OnClickMshflexgrid1() //弹出右键菜单
{
//	const int ENDLINES=2;
//	if(m_grid.GetRows() == ENDLINES )return;//判断是否需要显示快捷菜单

	MSG *pms;
	pms=(MSG*)GetCurrentMessage();
	if(pms->message != 0x205) {//0x202为鼠标左键,0x205为鼠标右键消息
		return;
	}
	CMenu pm;
	CPoint p;
	pm.LoadMenu(IDR_MENU_QUICK);
	CMenu* pmenu=pm.GetSubMenu(4);
	GetCursorPos(&p);
	pmenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON ,p.x,p.y,this);  	
	// TODO: Add your control notification handler code here
	
}

void CCostClassA::OnMenuCostAdd() //添加新的支出项目
{
	CCostClassAadd aa;
	if( aa.DoModal()== IDOK)
		OnOK();
	// TODO: Add your command handler code here
	
}

void CCostClassA::OnMenuCostModify() //修改支出项目
{
	long selRow=m_grid.GetRow();
	if( selRow== 0 ||  selRow==m_grid.GetRows()-1 )
	{
		AfxMessageBox("请先选择要修改的行");
		return;//判断是否需要显示快捷菜单
	}

	CCostClassAmodify am;
	am.m_id=atol(m_grid.GetTextMatrix(selRow,GRID_ID));
	am.m_name=m_grid.GetTextMatrix(selRow,GRID_NAME);
	am.m_order=atol(m_grid.GetTextMatrix(selRow,GRID_SEQ));
	am.m_cmt=m_grid.GetTextMatrix(selRow,GRID_CMT);
	if ( am.DoModal()==IDOK) OnOK();

}

void CCostClassA::OnMenuCostDel() //删除分类项目
{
	long selRow=m_grid.GetRow();
	if( selRow== 0 ||  selRow==m_grid.GetRows()-1 )
	{
		AfxMessageBox("请先选择要修改的行");
		return;//判断是否需要显示快捷菜单
	}
	CString strName,strCmt,strPrompt;
	UINT nID;

	nID=atol(m_grid.GetTextMatrix(selRow,GRID_ID));
	strName=m_grid.GetTextMatrix(selRow,GRID_NAME);
	strCmt=m_grid.GetTextMatrix(selRow,GRID_CMT);
	strPrompt.Format("确认要删除：\n\r%s,%s ?? ",strName,strCmt );
	if( AfxMessageBox(strPrompt,MB_OKCANCEL )== IDOK ){
		strName.Format(" UPDATE lsq_cost_class_a SET effect=0 WHERE　id=%ld ",nID );
		if( !CComFunc::WriteSql(strName) )
		{	
			AfxMessageBox("删除操作失败,请重试!");
			return;
		}
		AfxMessageBox("删除成功!");
		OnOK();		
	}

}

void CCostClassA::OnMenuCostRestore() //恢复
{
	long selRow=m_grid.GetRow();
	if( selRow== 0 ||  selRow==m_grid.GetRows()-1 )
	{
		AfxMessageBox("请先选择要修改的行");
		return;//判断是否需要显示快捷菜单
	}
	CString strName,strCmt,strPrompt;
	UINT nID,effect;

	nID=atol(m_grid.GetTextMatrix(selRow,GRID_ID));
	strName=m_grid.GetTextMatrix(selRow,GRID_NAME);
	effect=atol(m_grid.GetTextMatrix(selRow,GRID_EFFECT));
	strCmt=m_grid.GetTextMatrix(selRow,GRID_CMT);
	if (effect > 0 )	return; //正常状态
	strPrompt.Format("确认要恢复：\n\r%s,%s ?? ",strName,strCmt );
	if( AfxMessageBox(strPrompt,MB_OKCANCEL )== IDOK ){
		strName.Format(" UPDATE lsq_cost_class_a SET effect=1 WHERE　id=%ld ",nID );
		if( !CComFunc::WriteSql(strName) )
		{	
			AfxMessageBox("恢复操作失败,请重试!");
			return;
		}
		AfxMessageBox("恢复成功!");
		OnOK();		
	}	// TODO: Add your command handler code here
	
}
