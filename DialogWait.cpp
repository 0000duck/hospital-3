// DialogWait.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "DialogWait.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogWait dialog


CDialogWait::CDialogWait(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogWait::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogWait)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	ft.CreatePointFont(300,"宋体");
	bh.CreateSolidBrush(LSQ_BACKCOLOR2);
}


void CDialogWait::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogWait)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogWait, CDialog)
	//{{AFX_MSG_MAP(CDialogWait)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogWait message handlers

void CDialogWait::PostNcDestroy() 
{
	
	CDialog::PostNcDestroy();

	delete this;
}

void CDialogWait::ExitWait()
{
	DestroyWindow();
}

BOOL CDialogWait::OnInitDialog() 
{
	CDialog::OnInitDialog();
	strPrompt.LoadString(IDS_STR_WAIT_PROMPT);

	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&ft);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strPrompt);

	CenterWindow();
	AnimateWindow(m_hWnd,300,AW_SLIDE|AW_CENTER); //这句作用很大,如果没有这一句,控件不能正常显示出来

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



HBRUSH CDialogWait::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if( pWnd->m_hWnd == GetDlgItem(IDC_STATIC_TITLE)->m_hWnd  )
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(LSQ_RED);
		return (HBRUSH) bh.GetSafeHandle();

	}

	
	return hbr;
}

BOOL CDialogWait::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN )return true;
	
	return CDialog::PreTranslateMessage(pMsg);
}
