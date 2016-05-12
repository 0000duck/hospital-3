// his3.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "his3.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "his3Doc.h"
#include "his3View.h"

#include "splash.h"
#include "logon.h"
#include "registerGh.h"
#include "comfunc.h"
#include "formGhList.h"
#include "dialogReportView.h"
#include "dialogSickGetMed.h"
#include "privilegeQuota.h"
#include "dialogUpgrade.h"
#include "lock.h"
#include "FormGhlist_del.h"
#include "costClassA.h"
#include "costClassAb.h"
#include "costBudget.h"
#include "costConsumeAdd.h"
#include "reportDechargeList.h"
#include "ReportUsedAll1.h"
#include "peculiarAdd.h"
#include "ReportUsedAll.h"
#include "medcode.h"
#include "ReportEmpCount.h"

#include "ReportEmpJSB.h"
#include "ReportMedConsume.h"
#include "planAsWhole.h"
#include "affinityquery.h"
#include "empquery.h"
#include "relateQuery.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHis3App

BEGIN_MESSAGE_MAP(CHis3App, CWinApp)
	//{{AFX_MSG_MAP(CHis3App)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_MENUITEM_GHOPER, OnMenuitemGhoper)
	ON_COMMAND(ID_MENU_REPORT_MZCX, OnMenuReportMzcx)
	ON_COMMAND(ID_MENU_REPORT_VIEW, OnMenuReportView)
	ON_COMMAND(ID_MENU_GH_GETMED, OnMenuGhGetmed)
	ON_COMMAND(ID_MENU_SYS_PRIVI_SET, OnMenuSysPriviSet)
	ON_COMMAND(ID_MENU_BASE_DEPART_SET, OnMenuBaseDepartSet)
	ON_COMMAND(ID_MENU_BASE_DEPART2_SET, OnMenuBaseDepart2Set)
	ON_COMMAND(ID_MENU_LOCK, OnMenuLock)
	ON_COMMAND(ID_MENU_REPORT_DEL_MZCQ, OnMenuReportDelMzcq)
	ON_COMMAND(ID_MENU_COST_CLASS_A, OnMenuCostClassA)
	ON_COMMAND(ID_MENU_COST_CLASS_B, OnMenuCostClassB)
	ON_COMMAND(ID_MENU_COST_BUDGET, OnMenuCostBudget)
	ON_COMMAND(ID_MENU_COST_CONSUME, OnMenuCostConsume)
	ON_COMMAND(ID_MENU_REPORT_DECHARGE, OnMenuReportDecharge)
	ON_COMMAND(ID_MENU_REPORT_BCBX_HZ, OnMenuReportBcbxHz)
	ON_COMMAND(ID_MENUITEM_PECULIAR_ADD, OnMenuitemPeculiarAdd)
	ON_COMMAND(ID_MENUITEM_MED_QUERY, OnMenuitemMedQuery)
	ON_COMMAND(ID_MENU_MEDCODE_MANAGER, OnMenuMedcodeManager)
	ON_COMMAND(ID_MENUITEM_BCYB_ZJB, OnMenuitemBcybZjb)
	ON_COMMAND(ID_MENUITEM_BCYB_JSB, OnMenuitemBcybJsb)
	ON_COMMAND(ID_MENUITEM_MED_CONSUME, OnMenuitemMedConsume)
	ON_COMMAND(ID_MENU_MEDCODE_SORT, OnMenuMedcodeSort)
	ON_COMMAND(ID_MENU_PLANWHOLE, OnMenuPlanwhole)
	ON_COMMAND(ID_MENUITEM_AFFINITY_QUERY, OnMenuitemAffinityQuery)
	ON_COMMAND(ID_MENUITEM_EMP_QUERY, OnMenuitemEmpQuery)
	ON_COMMAND(ID_MENUITEM_RELATE_QUERY, OnMenuitemRelateQuery)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHis3App construction

CHis3App::CHis3App()
{
	// TODO: add construction code here,
	strVer.Format("1.00.01"); //****20090512,已经无效
	CString user,pwd,serviceName;
	user="his";
	pwd="his";
	serviceName="hospital";
	CString ConnectParameter;// 系原来的连接字符串MSDAORA.1
	strConn.Format("Provider=MSDAORA.1;\
		User ID=%s;Password=%s;Data Source=%s ",user,pwd,serviceName);
	// Place all significant initialization in InitInstance
	pGhList=NULL;
	hGhList=NULL;
	pGhList_del=NULL;
	hGhList_del=NULL;
	pDechargeList=NULL;
	hDechargeList=NULL;
	pUsedAll=NULL;
		hUsedAll=NULL;
	strOracleYear="";
	for(int i=0;i< DOC_MAX; ++i)docList[i]=NULL;
	for(i=0 ; i< HWND_MAX; ++i) hwndList[i]=NULL;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CHis3App object

CHis3App theApp;

/////////////////////////////////////////////////////////////////////////////
// CHis3App initialization

BOOL CHis3App::InitInstance()
{



	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.
/*
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_HIS3TYPE,
		RUNTIME_CLASS(CHis3Doc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CHis3View));
	AddDocTemplate(pDocTemplate);
*/
	AfxOleInit() ;
	// 定位应用程序所在目录
	if(!::GetModuleFileName(NULL,LoginInformation.path,MAX_PATH)){
		AfxMessageBox("您的应用程序可能放入的路径太深,请移动到根目录下再试...\n某些功能当前不可用...");
	}
	else
	{
		for(int x=strlen(LoginInformation.path); LoginInformation.path[x-1] != '\\'; x--);
		LoginInformation.path[x]=0;

	}
	//连接数据库
	CSplash startView;
	startView.DoModal();
	if(startView.timer_count != 1){
		if(startView.timer_count == 3)AfxMessageBox("初始化系统 COM 库失败,请检查系统 COM 配置是否有问题...");
		else AfxMessageBox("连接 Oracle 数据库失败,请检查网络和 Oracle 配置是否正确...");//,"Oracle 连接错误",MB_OK|MB_ICONWARNING);
		
		return false;
	}
	if(FAILED(recSet.CreateInstance( __uuidof( Recordset ))))
	{
		AfxMessageBox("初始化Recordset失败...");
		return false ;
	}
//检测是否有可升级程序
	if( !CheckUpgrade() ) return false;
//	strProject=COtherDecharge::GetStringTitle("SELECT ds2 FROM lsq_gh_type WHERE ds3='B' AND ds1='PROJECT' ");

	strOracleYear=CComFunc::GetString("select to_char(sysdate,'yyyy') from dual");

	CLogon log2;
	if(log2.DoModal()==IDCANCEL)return false;

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pMainFrame->UpdateWindow();
	CStatusBar *pStatus=(CStatusBar*)AfxGetApp()->GetMainWnd()->GetDescendantWindow(ID_VIEW_STATUS_BAR);
	int i=1;
	pStatus->SetPaneText(i++," 姓  名 :    "+LoginInformation.user);
	pStatus->SetPaneText(i++," 科  室 :    "+LoginInformation.kfmc);

	

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CHis3App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CHis3App message handlers


void CHis3App::OnMenuitemGhoper()  //挂号就诊
{
	//进行权限判断
	if( ! CComFunc::AssertPriv(1) ) return; 

	CRegisterGh gh;
	gh.DoModal();
	
}

void CHis3App::OnMenuReportMzcx()  // 门诊查询
{
	if(pGhList != NULL ){
		BringWindowToTop(hGhList);
		ShowWindow(hGhList,SW_SHOWMAXIMIZED);
		return;
	};
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHis3Doc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CFormGhList));
	AddDocTemplate(pDocTemplate);
	this->pGhList=pDocTemplate; 
	pGhList->OpenDocumentFile(NULL);
	
}

void CHis3App::OnMenuReportView() 
{
	CDialogReportView rv;
	rv.DoModal();
}

void CHis3App::OnMenuGhGetmed()  //待取药人员列表
{
	if( ! CComFunc::AssertPriv(3) ) return;  //

	CDialogSickGetMed gm;
	gm.DoModal();
}

void CHis3App::OnMenuSysPriviSet()  //应用程序权限分配
{
	if( ! CComFunc::AssertPriv(5) ) return; 
	CPrivilegeQuota pq;
	pq.DoModal();
	
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString strVer;
	strVer.LoadString(IDS_STR_VERSION);
	GetDlgItem(IDC_STATIC_VER)->SetWindowText("淮电医院程序 : "+strVer);
	
	strVer.LoadString(IDS_STR_VERSION2);
	GetDlgItem(IDC_STATIC_VER2)->SetWindowText(strVer);	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

bool CHis3App::CheckUpgrade()
{
	CString strVer,strNew[2],strSql;
	strVer.LoadString(IDS_STR_VERSION); //得到系统当前版本
	strVer.Remove('.');

	strSql=" SELECT ds3,ds1 FROM lsq_upgrade Where ds2='UPGRADE2' ";

	CComFunc::GetString(strSql,strNew,2);
	strNew[0].Remove('.');

	if( atol(strVer) < atol(strNew[0]) ){

		//AfxMessageBox("当前版本较低,需升级...");
		CDialogUpgrade du;
		du.strURL=strNew[1];
		du.strFILE.Format("%s\\down.dat",LoginInformation.path);
		du.DoModal();

		HospitalConnect->Close();

		
		strVer.Format("%s\\up.exe",LoginInformation.path);
		::ShellExecute(NULL,"open",strVer,NULL,NULL,SW_HIDE);
		return false;
	}
	return true;
}

void CAboutDlg::OnOK() 
{
	// TODO: Add extra validation here
/*	try{
		HospitalConnect->BeginTrans();
		CString strSql;
		strSql.Format("SElect * from medlie where id=2479 for update ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenStatic,adLockPessimistic,adCmdText); 
		if(!recSet->adoEOF){
		
		//	strout=(char*)_bstr_t(recSet->GetFields()->GetItem(0L)->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(0L)->Value );
		}
		recSet->Close();

		AfxMessageBox("ok...locked ");
		HospitalConnect->CommitTrans();
	}

	catch(...)
	{
		AfxMessageBox("error...");
		recSet->Close();
		HospitalConnect->RollbackTrans();
		return;
	
	}
*/	
	CDialog::OnOK();
}

void CHis3App::OnMenuBaseDepartSet() //厂部门基础表设置
{
	//进行权限判断
		
}

void CHis3App::OnMenuBaseDepart2Set() // 处室名称设置
{
	// TODO: Add your command handler code here
	
}

void CHis3App::OnMenuLock()  //锁定程序
{
	// TODO: Add your command handler code here
	CLock lk;
	lk.DoModal();
}

void CHis3App::OnMenuReportDelMzcq()  // 门诊删除查询
{
	if( ! CComFunc::AssertPriv(6) ) return; 

	if(pGhList_del != NULL ){
		BringWindowToTop(hGhList_del);
		ShowWindow(hGhList_del,SW_SHOWMAXIMIZED);
		return;
	};
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHis3Doc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CFormGhList_del));
	AddDocTemplate(pDocTemplate);
	this->pGhList_del =pDocTemplate; 
	pGhList_del->OpenDocumentFile(NULL);
	
}

void CHis3App::OnMenuCostClassA() //支出目录设置
{
	// TODO: Add your command handler code here
	if( ! CComFunc::AssertPriv(7) ) return; 
	CCostClassA ca;
	ca.DoModal();
	
}

void CHis3App::OnMenuCostClassB() //支出详细目录设置
{
	if( ! CComFunc::AssertPriv(7) ) return; 
	CCostClassAb ab;
	ab.DoModal();
}

void CHis3App::OnMenuCostBudget() // 年度费用预算
{
	if( ! CComFunc::AssertPriv(7) ) return; 
	CCostBudget bg;
	bg.DoModal();
}

void CHis3App::OnMenuCostConsume() //费用报销
{
	if( ! CComFunc::AssertPriv(8) ) return; 
	CCostConsumeAdd ca;
	ca.DoModal();
}

void CHis3App::OnMenuReportDecharge() // 费用报销查询
{
	if( ! CComFunc::AssertPriv(8) ) return; 
	if(pDechargeList != NULL ){
		BringWindowToTop(hDechargeList);
		ShowWindow(hDechargeList,SW_SHOWMAXIMIZED);
		return;
	};
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHis3Doc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CReportDechargeList));
	AddDocTemplate(pDocTemplate);
	pDechargeList =pDocTemplate; 
	pDechargeList->OpenDocumentFile(NULL);
	
}

void CHis3App::OnMenuReportBcbxHz() //补充保险使用情况汇总
{
	if(pUsedAll != NULL ){
		BringWindowToTop(hUsedAll);
		ShowWindow(hUsedAll,SW_SHOWMAXIMIZED);
		return;
	};
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHis3Doc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CReportUsedAll));
	AddDocTemplate(pDocTemplate);
	this->pUsedAll=pDocTemplate; 
	pUsedAll->OpenDocumentFile(NULL);
	
}

void CHis3App::OnMenuitemPeculiarAdd() //年度额外（特殊）补助
{
	//ID_MENUITEM_PECULIAR_ADD
	if( ! CComFunc::AssertPriv(ID_MENUITEM_PECULIAR_ADD) ) return; 

	CPeculiarAdd ca;
	ca.DoModal();
}

void CHis3App::OnMenuitemMedQuery() // 库存药品查询
{

	if(docList[MED_POINT] != NULL ){
		BringWindowToTop(hwndList[MED_POINT] );
		ShowWindow(hwndList[MED_POINT],SW_SHOWMAXIMIZED);
		return;
	};
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHis3Doc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CReportMedQuery));
	AddDocTemplate(pDocTemplate);
	this->docList[MED_POINT]=pDocTemplate; 
	docList[MED_POINT]->OpenDocumentFile(NULL);
	
}

void CHis3App::OnMenuMedcodeManager() //药品编码管理 
{
	//ID_MENU_MEDCODE_MANAGER
	if( ! CComFunc::AssertPriv(ID_MENU_MEDCODE_MANAGER) ) return; 
	CMedcode mc;
	mc.DoModal();
}

void CHis3App::OnMenuitemBcybZjb() //征集表
{
	if( ! CComFunc::AssertPriv(ID_MENUITEM_BCYB_ZJB) ) return; 

	CReportEmpCount rc;
	rc.DoModal();
}

void CHis3App::OnMenuitemBcybJsb() //结算表
{
	if( ! CComFunc::AssertPriv(ID_MENUITEM_BCYB_JSB) ) return; 

	CReportEmpJSB	js;
	js.DoModal();
}

void CHis3App::OnMenuitemMedConsume() //药品消耗统计
{
	if(docList[MED_CONSUME] != NULL ){
		BringWindowToTop(hwndList[MED_CONSUME] );
		ShowWindow(hwndList[MED_CONSUME],SW_SHOWMAXIMIZED);
		return;
	};
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHis3Doc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CReportMedConsume));
	AddDocTemplate(pDocTemplate);
	this->docList[MED_CONSUME]=pDocTemplate; 
	docList[MED_CONSUME]->OpenDocumentFile(NULL);	
}

void CHis3App::OnMenuMedcodeSort() 
{
	// TODO: Add your command handler code here
	
}


//统筹利息结算
void CHis3App::OnMenuPlanwhole() 
{

	CPlanAsWhole pa;
	pa.DoModal();

		
}

//供养亲属费用报销查询
//2015/12/23
//新增亲属关联职工及部门信息,原有his2中查询没有职工相关信息

void CHis3App::OnMenuitemAffinityQuery() 
{
	CAffinityQuery af;
	af.DoModal();
}
//补充保险人员门诊消费查询
//2015/12/29
//带入职工部门信息,原有门诊查询无法融入部门信息
void CHis3App::OnMenuitemEmpQuery() 
{
	CEmpQuery ep;
	ep.DoModal();
}
//供养亲属人员门诊消费查询
//2015/12/29
//融入关联职工部门信息
void CHis3App::OnMenuitemRelateQuery() 
{
	CRelateQuery rq;
	rq.DoModal();
}
