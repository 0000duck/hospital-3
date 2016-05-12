// CostClassAb.cpp: implementation of the CCostClassAb class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his3.h"
#include "CostClassAb.h"
#include "costClass2Add.h"
#include "costclass2Modify.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCostClassAb::CCostClassAb()
{

}

CCostClassAb::~CCostClassAb()
{

}

BOOL CCostClassAb::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	SetWindowText("成本类别2分类");
	m_id.ShowWindow(SW_HIDE);
	m_mc.ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_1)->SetWindowText("大类");

//	CComFunc::comSetGridHeader(m_grid,8); //表格头设置

	long i,row(1);
	CString strSql;
	CComFunc::GetSql(strSql,COST_A_SQLID);

	arrayDepart.RemoveAll();
	

	m_depart.AddString(BLANKSTR);
	arrayDepart.Add(BLANKSTR);
	try{
	
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 

		while(! recSet->adoEOF){
			i=0;
			strSql=CComFunc::GetSqlItem(i);
			//strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(long(i))->Value.vt == VT_NULL ? _variant_t(BLANKSTR):recSet->GetFields()->GetItem(long(i))->Value );
			arrayDepart.Add(strSql);
			i++;
			strSql=CComFunc::GetSqlItem(i);
			//strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(long(i))->Value.vt == VT_NULL ? _variant_t(BLANKSTR):recSet->GetFields()->GetItem(long(i))->Value );
			m_depart.AddString(strSql);

			recSet->MoveNext();

		}
		recSet->Close();


	}
	catch(_com_error e)
	{
		strSql.Format("出现错误,请检查SQL=%ld 语句...",COST_A_SQLID);
		AfxMessageBox(strSql);
		return false;
	}		

	OnOK();
	return TRUE;  
}

void CCostClassAb::OnOK()
{
	CString strSql,str2;
	const char * argu_01="[xt001]";

	CComFunc::comSetGridHeader(m_grid,GRID_HEADER_ID); 
	CComFunc::GetSql(strSql,SQL_QUERY_ID);
	int i=m_depart.GetCurSel();
	if ( i == CB_ERR  || i == 0 )
		str2=" ";
	else 
	{
		str2.Format(" AND a.id=%s ",arrayDepart[m_depart.GetCurSel()] );

	
	}
	strSql.Replace(argu_01,str2);
	
	CComFunc::ReadDataForGrid(strSql,m_grid);

}

void CCostClassAb::OnClickMshflexgrid1()
{
	MSG *pms;
	pms=(MSG*)GetCurrentMessage();
	if(pms->message != 0x205) {//0x202为鼠标左键,0x205为鼠标右键消息
		return;
	}
	CMenu pm;
	CPoint p;
	pm.LoadMenu(IDR_MENU_QUICK);
	CMenu* pmenu=pm.GetSubMenu(5);
	GetCursorPos(&p);
	pmenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON ,p.x,p.y,this);  	

}

void CCostClassAb::OnMenuCost2Add()
{
	CCostClass2Add ab;
	ab.DoModal();
}

void CCostClassAb::OnDblClickMshflexgrid1()
{

}

void CCostClassAb::OnMenuCost2Modify()//修改
{
	long selRow=m_grid.GetRow();
	if( selRow== 0 ||  selRow==m_grid.GetRows()-1 )
	{
		AfxMessageBox("请先选择要修改的行");
		return;//判断是否需要显示快捷菜单
	}
	CCostClass2Modify cm;
	cm.strName=m_grid.GetTextMatrix(selRow,GRID_NAME);
	cm.m_id=atol(m_grid.GetTextMatrix(selRow,GRID_ID) );
	cm.m_aid=atol(m_grid.GetTextMatrix(selRow,GRID_A_ID) );
	cm.iSeq=atol(m_grid.GetTextMatrix(selRow,GRID_ORDER));
	cm.strRem=m_grid.GetTextMatrix(selRow,GRID_CMT);

	if ( cm.DoModal()==IDOK) OnOK();
}

void CCostClassAb::OnMenuCost2Del()
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
		strName.Format(" UPDATE lsq_cost_class_b SET effect=0 WHERE　id=%ld ",nID );
		if( !CComFunc::WriteSql(strName) )
		{	
			AfxMessageBox("删除操作失败,请重试!");
			return;
		}
		AfxMessageBox("删除成功!");
		OnOK();		
	}

}

void CCostClassAb::OnMenuCost2Restore()
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
		strName.Format(" UPDATE lsq_cost_class_b SET effect=1 WHERE　id=%ld ",nID );
		if( !CComFunc::WriteSql(strName) )
		{	
			AfxMessageBox("恢复操作失败,请重试!");
			return;
		}
		AfxMessageBox("恢复成功!");
		OnOK();		
	}	// TODO: Add your command handler code here
}
