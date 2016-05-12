// DialogUpgrade.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "DialogUpgrade.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogUpgrade dialog


CDialogUpgrade::CDialogUpgrade(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogUpgrade::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogUpgrade)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	strFILE=BLANKSTR;
	strURL=BLANKSTR;
	fo1.CreatePointFont(220,"姚体");
}


void CDialogUpgrade::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogUpgrade)
	DDX_Control(pDX, IDC_PROGRESS1, m_pr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogUpgrade, CDialog)
	//{{AFX_MSG_MAP(CDialogUpgrade)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogUpgrade message handlers

BOOL CDialogUpgrade::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	AfxBeginThread(GetHttpFile,this);
//	CString strTitle("系统正在升级,请稍候...");

	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fo1);
//	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strTitle);
	
	::SetWindowPos(GetSafeHwnd() , HWND_TOPMOST,NULL,NULL,NULL,NULL,SWP_NOSIZE );
//		::SetWindowPos(GetSafeHwnd() , HWND_TOPMOST ,  rtNew.left ,rtNew.top , rtNew.Width() , rtNew.Height(), SWP_NOSIZE );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

UINT CDialogUpgrade::GetHttpFile(LPVOID ps)
{
	CDialogUpgrade* p=(CDialogUpgrade*)ps;

	CInternetSession session;
	CInternetFile* file = NULL;
	long len(0),pos(0);
	ULONG lens(0);
	const int BUF_MAX=1024;
	BYTE a[BUF_MAX];	
	CString str;
	p->m_pr.SetRange(0,100);


	try
	{ 
		str.LoadString(IDS_STR_UPGRADE_1);
		p->GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(str);
		// 试着连接到指定URL
		file = (CInternetFile*) session.OpenURL(p->strURL,1,INTERNET_FLAG_TRANSFER_BINARY); 
		
		str.LoadString(IDS_STR_UPGRADE_2);
		
		p->GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(str);
		lens=file->GetLength();
		
	}
	catch (CInternetException* m_pException)
	{
		// 如果有错误的话，置文件为空
		file = NULL; 
		AfxMessageBox("1.打开升级文件位置出现错误,未能找到要升级的文件...");
		m_pException->Delete();
		return FALSE;
	}
	// 用dataStore来保存读取的文件
	CStdioFile dataStore;
	
	p->m_pr.SetRange32(0,lens/BUF_MAX);
	if (file)
	{
		BOOL bIsOk = dataStore.Open(p->strFILE,
			CFile::modeCreate | CFile::modeWrite | CFile::typeBinary  );
		
		if (!bIsOk){
			AfxMessageBox("2.建立新文件出现错误...");
			return FALSE;
		}
		// 读写文件，直到为空

		while( (len=file->Read(a,BUF_MAX)) != 0 ){
			dataStore.Write(a,len);
			p->m_pr.SetPos(pos++);
			
		}
		dataStore.Close();
		file->Close();

		delete file;

	}
	else
	{
		AfxMessageBox("3.建立新文件出现错误...");
		return FALSE;
	}

	p->PostMessage(WM_CLOSE);

	
	return TRUE;
}



HBRUSH CDialogUpgrade::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if( pWnd->m_hWnd == GetDlgItem(IDC_STATIC_TITLE)->m_hWnd)
		pDC->SetTextColor(LSQ_RED);
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
