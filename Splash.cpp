// Splash.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "Splash.h"
#include "mmsystem.h"

#include "progressIndicate.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplash dialog
_ConnectionPtr HospitalConnect;
_RecordsetPtr recSet;
const int ONESECOND=1000;



#define   IDC_PROGRESS_EXCEL WM_USER+1211

CSplash::CSplash(CWnd* pParent /*=NULL*/)
	: CDialog(CSplash::IDD, pParent)
{
	timer_count=0;
	ConnectFlag=false;
	//{{AFX_DATA_INIT(CSplash)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSplash::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSplash)
	DDX_Control(pDX, IDC_PROGRESS_SPLASH, m_progress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSplash, CDialog)
	//{{AFX_MSG_MAP(CSplash)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

BOOL CSplash::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString strFileName;
	strFileName.Format("%s",LoginInformation.path);
	strFileName+="splash.bmp";

	hbmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), \
		strFileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);

    ////////////////////该断程序用来取得加载的BMP的信息////////////////////////

    m_bitmap.Attach( hbmp );

 //   DIBSECTION ds;

   // BITMAPINFOHEADER &bminfo = ds.dsBmih; 

    m_bitmap.GetObject( sizeof(BITMAP), &bmp );
	

	CRect rtOld,rtProgress;

	GetWindowRect(rtOld);

	CPoint point = rtOld.TopLeft();//pl(bmp.bmWidth-100,bmp.bmHeight-50),pr(bmp.bmWidth-10,bmp.bmHeight-20);

	CRect rtNew = CRect(point,CSize(bmp.bmWidth,bmp.bmHeight));   

	MoveWindow(rtNew);
//调整流动条控件位置	
	rtProgress.left=20;
	rtProgress.top=bmp.bmHeight-52;
	rtProgress.right=bmp.bmWidth-20;
	rtProgress.bottom=rtProgress.top+30;
	m_progress.MoveWindow(rtProgress);


	::SetWindowPos(GetSafeHwnd() , HWND_TOPMOST ,  rtNew.left ,rtNew.top , rtNew.Width() , rtNew.Height(), SWP_NOSIZE );

	
	CenterWindow();
	AnimateWindow(m_hWnd,300,AW_SLIDE|AW_CENTER);
	
	Invalidate(); 

	AfxBeginThread(ConnectData,(LPVOID)this);
	
	AfxBeginThread(schedule,(LPVOID)this);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CSplash::OnPaint() 
{
//	CPaintDC dc(this); // device context for painting
	
	CPaintDC pv(this); // device context for painting
	
	BITMAP bmp;
	m_bitmap.GetObject(sizeof(BITMAP),&bmp);
	
//	HBITMAP bit=::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_SPLASH));
	HBITMAP bit=hbmp;
	HDC hdc=::CreateCompatibleDC(NULL);
	SelectObject(hdc,bit);

	::StretchBlt(pv.m_hDC,0,0,bmp.bmWidth,bmp.bmHeight,hdc,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
	::DeleteDC(hdc);
	::DeleteObject(bit);	// TODO: Add your message handler code here


	// Do not call CDialog::OnPaint() for painting messages
}



BOOL CSplash::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN )return true;
		
	return CDialog::PreTranslateMessage(pMsg);
}

extern CHis3App theApp;
UINT CSplash::ConnectData(LPVOID ps)
{
	AfxOleInit(); //初始化COM库
	if(FAILED(HospitalConnect.CreateInstance(__uuidof(Connection))))
	{
		((CSplash *)ps)->ConnectFlag=true;
		((CSplash *)ps)->timer_count=3; //连接COM失败标志
		((CSplash *)ps)->SendMessage(WM_CLOSE,0,0);
	
		return 0;
	}

	try{
		
		HospitalConnect->Open(_bstr_t(theApp.strConn),"","",adModeUnknown);
		((CSplash *)ps)->ConnectFlag=true;
		((CSplash *)ps)->timer_count=1; //连接成功标志
		((CSplash *)ps)->SendMessage(WM_CLOSE,0,0);
	
		return 1;
	}
	catch(_com_error e)
	{
		((CSplash *)ps)->ConnectFlag=true; //作为进度条线程停止标志
		((CSplash *)ps)->timer_count=2; //连接失败标志

		((CSplash *)ps)->SendMessage(WM_CLOSE,0,0);
	

		return 2;
	
	}


}

UINT CSplash::schedule(LPVOID ps)
{
	int i=0;
	while(!((CSplash*)ps)->ConnectFlag ){
	
		((CSplash*)ps)->m_progress.SetPos(i++);
		if(i==100) i=0;
		Sleep(30);
	
	}

	return 1;

}
