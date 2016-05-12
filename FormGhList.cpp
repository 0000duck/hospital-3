// FormGhList.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "FormGhList.h"
#include "comFunc.H"
#include "ghQuery.h"
#include "viewUserComuse.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormGhList

IMPLEMENT_DYNCREATE(CFormGhList, CFormView)

CFormGhList::CFormGhList()
	: CFormView(CFormGhList::IDD)
{
	//{{AFX_DATA_INIT(CFormGhList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(220,"姚体");

}

CFormGhList::~CFormGhList()
{
}

void CFormGhList::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFormGhList)
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFormGhList, CFormView)
	//{{AFX_MSG_MAP(CFormGhList)
	ON_WM_CTLCOLOR()
	ON_COMMAND(ID_MENU_GH_LISTTOEXCEL, OnMenuGhListtoexcel)
	ON_COMMAND(ID_MENU_GH_VIEWLIST, OnMenuGhViewlist)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_MENU_GH_DELETE, OnMenuGhDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormGhList diagnostics

#ifdef _DEBUG
void CFormGhList::AssertValid() const
{
	CFormView::AssertValid();
}

void CFormGhList::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFormGhList message handlers

void CFormGhList::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
extern CHis3App theApp;
	theApp.hGhList=GetParentFrame()->m_hWnd;
	TITLE=CComFunc::GetString(" SELECT ds1 FROM lsq_title_list where ds2='DIALOG' and ds3='TITLE' and ds4='AAL' ");
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);

	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(TITLE);
	GetParentFrame()->ShowWindow(SW_SHOWMAXIMIZED);
	GetDocument()->SetTitle(TITLE);
	// TODO: Add your specialized code here and/or call the base class
	CComFunc::comSetGridHeader(m_grid,6);	
	
}

void CFormGhList::OnDraw(CDC* pDC) 
{
	CRect r1,r2,rectTitle,rectButton;
	long titleHigh;

	GetClientRect(&r2);
	GetDlgItem(IDC_STATIC_TITLE)->GetWindowRect(rectTitle);
	ScreenToClient(rectTitle);
	rectTitle.right=r2.right;
	rectTitle.left= r2.left;
	titleHigh=rectTitle.bottom-rectTitle.top;
	rectTitle.top=  r2.top;
	rectTitle.bottom = r2.top+ titleHigh;
	GetDlgItem(IDC_STATIC_TITLE)->MoveWindow(0,0,r2.right-r2.left,titleHigh);

	GetDlgItem(IDC_MSHFLEXGRID1)->GetWindowRect(&r1);
	ScreenToClient(&r1);
	GetDlgItem(IDC_MSHFLEXGRID1)->MoveWindow(0,r2.top+titleHigh,r2.right,r2.bottom-titleHigh);	
	
}

BEGIN_EVENTSINK_MAP(CFormGhList, CFormView)
    //{{AFX_EVENTSINK_MAP(CFormGhList)
	ON_EVENT(CFormGhList, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	ON_EVENT(CFormGhList, IDC_MSHFLEXGRID1, -600 /* Click */, OnClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CFormGhList::OnDblClickMshflexgrid1()  //查询
{
	CGhQuery gq;
	theApp.pParentGrid.pGrid=this;
	gq.DoModal();
}

HBRUSH CFormGhList::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	if( pWnd->m_hWnd == GetDlgItem(IDC_STATIC_TITLE)->m_hWnd)
		pDC->SetTextColor(LSQ_RED);
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CFormGhList::OnClickMshflexgrid1()  //右键菜单
{
	const int ENDLINES=2;
	if(m_grid.GetRows() == ENDLINES )return;//判断是否需要显示快捷菜单

	MSG *pms;
	pms=(MSG*)GetCurrentMessage();
	if(pms->message != 0x205) {//0x202为鼠标左键,0x205为鼠标右键消息
		return;
	}
	CMenu pm;
	CPoint p;
	pm.LoadMenu(IDR_MENU_QUICK);
	CMenu* pmenu=pm.GetSubMenu(3);
	GetCursorPos(&p);
	pmenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON ,p.x,p.y,this);  	
}

void CFormGhList::OnMenuGhListtoexcel() // 输出 EXCEL
{
	CComFunc::ToExcel(&m_grid);	
}

void CFormGhList::OnMenuGhViewlist()  // 查看消费详情
{
	long selRow=m_grid.GetRow();
	if( selRow== 0 ||  selRow==m_grid.GetRows()-1 )return;//判断是否需要显示快捷菜单
	
	CViewUserComuse vu;
	vu.DANJUHAO=m_grid.GetTextMatrix(selRow,DANJUHAO_COL);
	vu.DoModal();
			
}

void CFormGhList::OnClose() 
{
	CFormView::OnClose();
}

void CFormGhList::OnDestroy() 
{
	CFormView::OnDestroy();
	theApp.hGhList=NULL;
	theApp.pGhList=NULL;
	
	// TODO: Add your message handler code here
	
}

void CFormGhList::OnMenuGhDelete() //删除已划价项目
{
	if( ! CComFunc::AssertPriv(4) ) return;  // 删除权限

	long selRow=m_grid.GetRow();
	if( selRow== 0 ||  selRow==m_grid.GetRows()-1 )return;//判断是否需要显示快捷菜单
	
	CString strSql;
	strSql.Format(" 确定要删除 : [ %s , %s ],收费员: %s  ,费用总额: %s ",m_grid.GetTextMatrix(selRow,8),m_grid.GetTextMatrix(selRow,3),
		m_grid.GetTextMatrix(selRow,6),m_grid.GetTextMatrix(selRow,12) );


	int flag=0;
	if( AfxMessageBox(strSql,MB_YESNO) == IDYES ){
		//调用存储过程进行恢复数据
			CDialog *pw;
			pw=CComFunc::SysWait(NULL);

		strSql=m_grid.GetTextMatrix(selRow,0);//获取单据号
		try{
			_CommandPtr cmd;
			_ParameterPtr par;
			cmd.CreateInstance(__uuidof( Command ));
			par.CreateInstance(__uuidof( Parameter));
			
			_variant_t vNULL;
			vNULL.vt = VT_ERROR;
			vNULL.scode = DISP_E_PARAMNOTFOUND;
			
			cmd->put_CommandType(adCmdStoredProc) ;
			par=cmd->CreateParameter(_bstr_t("success"),adUnsignedInt,adParamOutput,20,vNULL);
			cmd->Parameters->Append( par );
			
			par=cmd->CreateParameter(_bstr_t("paraID"),adVarChar,adParamInput,20,_bstr_t( strSql ) );
			cmd->Parameters->Append( par );
						
			par=cmd->CreateParameter(_bstr_t("rybm"),adVarChar,adParamInput,20,_bstr_t( LoginInformation.user_code  ) );
			cmd->Parameters->Append( par );

			cmd->put_CommandText(_bstr_t("PRC_delete_gh"));
			cmd->ActiveConnection=HospitalConnect;
			cmd->Execute(NULL,NULL,adCmdStoredProc);
			
			flag=cmd->Parameters->GetItem("success")->Value.uintVal;
			
			cmd.Detach();
			par.Detach();
			if ( flag ) {
				pw->PostMessage(WM_CLOSE);
				AfxMessageBox("删除已挂号收费人员信息失败,请重试!!");
				return;
			}
		}
		catch(_com_error e)
		{
			pw->PostMessage(WM_CLOSE);
			AfxMessageBox(e.ErrorMessage());
			return;
		}
		m_grid.RemoveItem(selRow);

		pw->PostMessage(WM_CLOSE);
	}


	
}
