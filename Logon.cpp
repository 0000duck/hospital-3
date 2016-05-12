// Logon.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "Logon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogon dialog


CLogon::CLogon(CWnd* pParent /*=NULL*/)
	: CDialog(CLogon::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLogon)
	//}}AFX_DATA_INIT
	backBrush.CreateSolidBrush(RGB(255,255,255)); //创建白色刷子
	bk2.CreateSolidBrush(RGB(0,74,152));
}


void CLogon::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogon)
	DDX_Control(pDX, IDCANCEL, m_re);
	DDX_Control(pDX, IDOK, m_we);
	DDX_Control(pDX, IDC_COMBO2, m_name);
	DDX_Control(pDX, IDC_COMBO1, m_depart);
	DDX_Control(pDX, IDC_EDIT1, m_password);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLogon, CDialog)
	//{{AFX_MSG_MAP(CLogon)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnSelchangeCombo2)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogon message handlers
extern CHis3App theApp;
BOOL CLogon::OnInitDialog() 
{
	CDialog::OnInitDialog();
//	if( theApp.exitCode == 2){ //应用程序进级了升级,要重新启动
//		OnCancel();
//		return false;
//	}

	CString strSql;
	try{
		strSql.Format("select kfmc from storeroom where effect=1 order by kfmc  ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			
			strSql=(char*)_bstr_t(recSet->GetCollect("kfmc").vt==VT_NULL?" ":recSet->GetCollect("kfmc"));
			m_depart.AddString(strSql);
			recSet->MoveNext();

		
		}
		recSet->Close();

	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return false;
	}		
//	SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOSIZE);
	SetWindowText(theApp.strProject);
	CenterWindow();
	//AnimateWindow(m_hWnd,300,AW_SLIDE|AW_HOR_POSITIVE);
	//Invalidate();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLogon::OnSelchangeCombo1() 
{

	CString strSql,str1;
	m_depart.GetLBText(m_depart.GetCurSel(),str1);

	if(str1.IsEmpty())return;

	while(m_name.DeleteString(0)!= CB_ERR);
	try{
		strSql.Format("select name from operator t1,storeroom t2 where  t1.kfbm=t2.kfbm and kfmc='%s' and   t1.effect=1 and t2.effect=1 ",str1);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			
			strSql=(char*)_bstr_t(recSet->GetCollect("name").vt==VT_NULL?" ":recSet->GetCollect("name"));
			m_name.AddString(strSql);
			recSet->MoveNext();

		
		}
		recSet->Close();

	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return ;
	}		
	m_name.SetCurSel(0);
	m_password.SetFocus();
	
}

void CLogon::OnOK() 
{
	// TODO: Add extra validation here
	CString strSql,str1,str2,str3,str4,str5,str6,strTemp;
	if(m_depart.GetCurSel() == CB_ERR || m_name.GetCurSel() == CB_ERR ) return;
	m_depart.GetLBText(m_depart.GetCurSel(),str1);
	m_name.GetLBText(m_name.GetCurSel(),str2);
	m_password.GetWindowText(str3);
	COleDateTime dt=COleDateTime::GetCurrentTime();	

	try{
		strSql.Format("select pass,attribute,t1.kfbm kfbm1,rybm from operator t1,storeroom t2 where  t1.kfbm=t2.kfbm and kfmc='%s' and name='%s' ",str1,str2);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
			
			strSql=(char*)_bstr_t(recSet->GetCollect("pass").vt==VT_NULL?"":recSet->GetCollect("pass"));
			str4=(char*)_bstr_t(recSet->GetCollect("attribute").vt==VT_NULL?"":recSet->GetCollect("attribute"));
			str5=(char*)_bstr_t(recSet->GetCollect("kfbm1").vt==VT_NULL?"":recSet->GetCollect("kfbm1"));
			str6=(char*)_bstr_t(recSet->GetCollect("rybm").vt==VT_NULL?"":recSet->GetCollect("rybm"));
			
		
		}
		recSet->Close();
	
		strTemp.Format("SELECT NVL(ROLE,' ') as ROLE FROM LSQ_ROLE WHERE RYBM='%s' ",str6);
		recSet->Open(_bstr_t(strTemp),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
		
			theApp.strRole=(char*)_bstr_t(recSet->GetCollect("ROLE"));
		}
		else theApp.strRole="";
		recSet->Close();

		if(strSql.Compare(str3) == 0){ //口令相同
			LoginInformation.user=str2;//名称
			LoginInformation.kfmc=str1;//库房名称
			LoginInformation.job=str4;
			LoginInformation.kfbm=str5;//库房编码
			LoginInformation.user_code=str6;//人员编码
/********************添加登录标志***********************************************/			

			strSql.Format("SELECT count(a.rybm),nvl(max(log_nums),1),to_char(sysdate,'yyyymmddhh24miss') \
				from lsq_log_operator a,\
				operator b where a.rybm(+)=b.rybm AND b.rybm='%s' AND KILLFLAG is NULL	",str6); //获得当前人员的登录次数
			recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
			if(!recSet->adoEOF){
				
				str1=(char*)_bstr_t(recSet->GetFields()->GetItem(0L)->Value); //已登录次数
				str2=(char*)_bstr_t(recSet->GetFields()->GetItem(1L)->Value); //最大登录次数
				str3=(char*)_bstr_t(recSet->GetFields()->GetItem(2L)->Value); //字符序列
				recSet->Close();
				if( /*atol(str1) >= atol(str2)*/ false ){
					MessageBox("禁止登录!!当前用户已达到登录次数...请用其它用户名登录!!!",\
						"警告",MB_OK|MB_ICONSTOP);
					m_password.SetWindowText("");
					m_password.SetFocus();
					return;
				}
			}
			else {
				recSet->Close();
				return;
			}

			theApp.strLogID=dt.Format("%H%M%S")+str3;
			
//可以登录的情况下向其加入日志			
			HospitalConnect->BeginTrans();
			strSql.Format("INSERT INTO lsq_log_operator(rybm,name,logtime,logid) values(\
				'%s','%s',sysdate,'%s' ) ",str6,LoginInformation.user,theApp.strLogID );
		
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);

			HospitalConnect->CommitTrans();


/*******************************************************************************/
			CDialog::OnOK();
		}
		else {
			AfxMessageBox("您所输入的密码不正确!!请仔细核对您的密码...");
			m_password.SetWindowText("");
			m_password.SetFocus();
		}


	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return ;
	}	

}

void CLogon::OnSelchangeCombo2() 
{
	m_password.SetFocus();
	// TODO: Add your control notification handler code here
	
}

HBRUSH CLogon::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(nCtlColor ==CTLCOLOR_STATIC)pDC->SetBkMode(TRANSPARENT);
	// TODO: Change any attributes of the DC here
	if(pWnd->m_hWnd == m_password.m_hWnd )pDC->SetTextColor(RGB(255,0,0));
	if( pWnd->m_hWnd== GetDlgItem(IDC_STATIC_BMP)->m_hWnd){
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH )bk2.GetSafeHandle();
		

	}
	return (HBRUSH )backBrush.GetSafeHandle();
	// TODO: Return a different brush if the default is not desired
//	return hbr;
}

void CLogon::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
//	CRect r1,r2;
//	m_depart.GetWindowRect(&r1);
//	ScreenToClient(&r1);
//	GetClientRect(&r2);
//	r1.top-=15;
//	dc.MoveTo(0,r1.top);
//	dc.LineTo(r2.right,r1.top);
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CLogon::OnCancel() 
{
	if( theApp.strLogID.IsEmpty() )
		HospitalConnect->Close();
		
	CDialog::OnCancel();
}

void CLogon::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CDialog::OnLButtonDown(nFlags, point);
	
	PostMessage(WM_NCLBUTTONDOWN, 2, 0);
}
