// ProgressIndicate.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "ProgressIndicate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgressIndicate dialog


CProgressIndicate::CProgressIndicate(CWnd* pParent /*=NULL*/)
	: CDialog(CProgressIndicate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProgressIndicate)
	//}}AFX_DATA_INIT
	ConnectFlag=0;
	m_progress.strView = "请稍候,系统正在处理数据......";
}


void CProgressIndicate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProgressIndicate)
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProgressIndicate, CDialog)
	//{{AFX_MSG_MAP(CProgressIndicate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgressIndicate message handlers


BOOL CProgressIndicate::OnInitDialog() 
{
	CDialog::OnInitDialog();

 	AfxBeginThread(pThreadFunction,(LPVOID)this);
	AfxBeginThread(ScheduleIndicate,this);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}






UINT CProgressIndicate::ScheduleIndicate(LPVOID ps)
{
	int i=1;

	while( ! ((CProgressIndicate*)ps)->ConnectFlag ){
	
		((CProgressIndicate*)ps)->m_progress.SetPos(i++);
		if(i==100) i=0;
		Sleep(5);
	
	}

	return 1;

}

BOOL CProgressIndicate::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE ) return true;
		
	return CDialog::PreTranslateMessage(pMsg);
}
