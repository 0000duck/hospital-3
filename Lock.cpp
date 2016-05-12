// Lock.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "Lock.h"
#include "comFunc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLock dialog


CLock::CLock(CWnd* pParent /*=NULL*/)
	: CDialog(CLock::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLock)
	m_password = _T("");
	//}}AFX_DATA_INIT
}


void CLock::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLock)
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_password);
	DDV_MaxChars(pDX, m_password, 32);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLock, CDialog)
	//{{AFX_MSG_MAP(CLock)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLock message handlers

void CLock::OnOK() 
{
	CString strSql;
	UpdateData();
	if( m_password.IsEmpty() ) return;
	strSql.Format(" select pass from operator  where rybm='%s' ",LoginInformation.user_code );
	strSql=CComFunc::GetString(strSql);
	
	if( strSql.Compare( m_password ) == 0 )	CDialog::OnOK();
	else {
		m_password=BLANKSTR;
		AfxMessageBox("¿ÚÁî´íÎó!");
		UpdateData(false);
	}
}

BOOL CLock::OnInitDialog() 
{
	CDialog::OnInitDialog();
		
	GetDlgItem(IDC_STATIC_KS)->SetWindowText(LoginInformation.kfmc);
	GetDlgItem(IDC_STATIC_XM)->SetWindowText(LoginInformation.user);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CLock::PreTranslateMessage(MSG* pMsg) 
{
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CLock::OnClose() 
{
//	AfxMessageBox("close..");		
//	CDialog::OnClose();
}
