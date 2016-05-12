// GhQuery.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "GhQuery.h"
#include "progressIndicate.h"
#include "formGhList.h"
#include "comFunc.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGhQuery dialog


CGhQuery::CGhQuery(CWnd* pParent /*=NULL*/)
	: CDialog(CGhQuery::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGhQuery)
	m_xm = _T("");
	m_date1 = COleDateTime::GetCurrentTime();
	m_date2 = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
	sfyCode=ysCode=BLANKSTR;
}


void CGhQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGhQuery)
	DDX_Control(pDX, IDC_EDIT_YS, c_ys);
	DDX_Control(pDX, IDC_EDIT_SFY, c_sfy);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_type);
	DDX_Text(pDX, IDC_EDIT_XM, m_xm);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_date2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGhQuery, CDialog)
	//{{AFX_MSG_MAP(CGhQuery)
	ON_EN_SETFOCUS(IDC_EDIT_YS, OnSetfocusEditYs)
	ON_EN_SETFOCUS(IDC_EDIT_SFY, OnSetfocusEditSfy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGhQuery message handlers

BOOL CGhQuery::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CString strSql;
	strArrType.RemoveAll();
	
	try{
		//strSql="select ds1,ds3 from lsq_upgrade  where ds2=upper('gh_type') and ( n3=1 or n2=1 ) order by n1";
		CComFunc::GetSql(strSql,22);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		m_type.AddString(BLANKSTR);
		strArrType.Add(BLANKSTR);
		while(!recSet->adoEOF){
			
			strSql=(char*)_bstr_t(recSet->GetCollect("ds1").vt==VT_NULL?" ":recSet->GetCollect("ds1"));
			m_type.AddString(strSql);
			strSql=(char*)_bstr_t(recSet->GetCollect("ds3").vt==VT_NULL?" ":recSet->GetCollect("ds3"));
			strArrType.Add(strSql);
			recSet->MoveNext();
	
		}
		recSet->Close();
		
	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return false;
	}		

	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGhQuery::OnOK() 
{

	CProgressIndicate pq;
	pq.pDialog= this;

	pq.pThreadFunction = QueryGhList;
	pq.DoModal();

	CDialog::OnOK();
}

UINT CGhQuery::QueryGhList(LPVOID ps)
{
	CFormGhList *pf=(CFormGhList*)theApp.pParentGrid.pGrid;
	CGhQuery * pd =(CGhQuery *) ((CProgressIndicate *) ps )->pDialog ;
	pd->UpdateData();

	pf->m_grid.SetRedraw(false);
	
	pf->m_grid.SetRows(2);
	pf->m_grid.AddItem(BLANKSTR,_variant_t(1L) );
	pf->m_grid.SetRows(2);
	
	CString strSql,str1,strGhtype,strname;

	long row,col,i;
	double price(0),add[]={0,0,0,0,0,0,0,0,0,0,0,0,0};

	if( pd->m_type.GetCurSel() == CB_ERR || pd->m_type.GetCurSel() == 0 )strGhtype = BLANKSTR; //挂号类型
	else {
		pd->m_type.GetLBText( pd->m_type.GetCurSel(),strGhtype);

	}
	strname=pd->m_xm; //病人姓名
	int COLS=pf->m_grid.GetCols(0);;
	const int SUM_COMPUTE_COL=9;
	try{
//	CString HeadTitle[]={"DAN","就诊日期","编码","姓名","医生","划价员","收费员",\
		"发药员","挂号类别","挂号费","药品费","其它费用","合计","药品利润",\
		"建国前工人","大病救助","统筹支付","IC卡支付","公务员补助","现金" };
		strSql.Format("%s : %s  -- %s ",pf->TITLE,pd->m_date1.Format("%Y/%m/%d"),pd->m_date2.Format("%Y/%m/%d") );
		pf->GetDlgItem(IDC_STATIC_TITLE)->SetWindowText( strSql );

		CComFunc::GetSql(strSql,12); 
		str1.Format( " WHERE riqi BETWEEN to_date('%s','yyyymmdd') \
			and to_date('%s','yyyymmdd')  ",pd->m_date1.Format("%Y%m%d"),pd->m_date2.Format("%Y%m%d"));
		strSql+=str1;

		if(! pd->sfyCode.IsEmpty() )strSql+=" AND 收费员='"+pd->sfyCode+"'";
			
		if( ! pd->ysCode.IsEmpty() ) strSql+=" AND doctor='"+pd->ysCode+"'";


		if( ! strGhtype.IsEmpty() )	strSql+=" AND Ghtype='"+pd->strArrType[pd->m_type.GetCurSel()]+"'";	
		if(! strname.IsEmpty() )strSql+=" AND SICKNAME like '"+strname+"%'";
		strSql+="  ORDER by riqi,danjuhao";

		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		row=1;
		while(!recSet->adoEOF){
			col=0;
			price=0;
			for(i=0;i< COLS ;i++)
			{
				str1=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(i))->Value.vt==VT_NULL? _variant_t(BLANKSTR) :recSet->GetFields()->GetItem(_variant_t(i))->Value);

				if( i > SUM_COMPUTE_COL  )
				{
					if( str1.IsEmpty() )str1="0";
					add[i-SUM_COMPUTE_COL]+=atof(str1);
				}
		/*		if( i == pf->SUM_COL ){
				
					pf->m_grid.SetRow(row);
					pf->m_grid.SetCol(i);
					pf->m_grid.SetCellBackColor(LSQ_BACKCOLOR);

				}
		*/		pf->m_grid.SetTextMatrix(row,i,str1);
			}
			row++;
			pf->m_grid.AddItem(BLANKSTR,_variant_t(row));

			recSet->MoveNext();
			
		}
		recSet->Close();
	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
	
		return false;
	}	

	pf->m_grid.SetRow(row);
	pf->m_grid.SetCol(1);
	pf->m_grid.SetCellBackColor(LSQ_BACKCOLOR);
	strSql.Format(" %ld ",row-1);

	pf->m_grid.SetTextMatrix(row,1,"合计");	
	pf->m_grid.SetTextMatrix(row,3,strSql);
	for(long count=1;count< COLS;count++){
		pf->m_grid.SetCol(count);
		pf->m_grid.SetCellBackColor(LSQ_BACKCOLOR);
		if( count >= SUM_COMPUTE_COL ){
			str1.Format("%.2f",add[count-SUM_COMPUTE_COL]);
			pf->m_grid.SetTextMatrix(row,count,str1);	

		}
	}
	CComFunc::SetGridColColor(6,pf->m_grid);

	pf->m_grid.SetRedraw(true);
	
	((CProgressIndicate *)ps)->ConnectFlag =1;
	((CProgressIndicate *)ps)->SendMessage(WM_CLOSE,NULL,NULL);

	pd->SendMessage(WM_CLOSE,NULL,NULL);
	
	return true;
}

BOOL CGhQuery::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN)
		pMsg->wParam =VK_TAB;
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CGhQuery::OnSetfocusEditYs() 
{
	GetDlgItem(IDOK)->SetFocus();
	CUserQuery uq;
	uq.lp=this;
	uq.sfyORys=2;
	uq.DoModal();
		
}

void CGhQuery::OnSetfocusEditSfy() 
{
	GetDlgItem(IDOK)->SetFocus();
	CUserQuery uq;
	uq.lp=this;
	uq.sfyORys=1;
	uq.DoModal();
	
}
