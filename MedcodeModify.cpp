// MedcodeModify.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "MedcodeModify.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMedcodeModify dialog


CMedcodeModify::CMedcodeModify(CWnd* pParent /*=NULL*/)
	: CDialog(CMedcodeModify::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMedcodeModify)
	m_bz = _T("");
	m_dw = _T("");
	m_gg = _T("");
	m_maxkc = _T("");
	m_mc = _T("");
	m_minkc = _T("");
	m_py = _T("");
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(220,"姚体");
	arrayItem.RemoveAll();
}


void CMedcodeModify::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMedcodeModify)
	DDX_Control(pDX, IDC_COMBO2, m_combo2);
	DDX_Control(pDX, IDC_COMBO1, m_combo1);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_comboType);
	DDX_Text(pDX, IDC_EDIT_BZ, m_bz);
	DDX_Text(pDX, IDC_EDIT_DW, m_dw);
	DDX_Text(pDX, IDC_EDIT_GG, m_gg);
	DDX_Text(pDX, IDC_EDIT_MAXKC, m_maxkc);
	DDX_Text(pDX, IDC_EDIT_MC, m_mc);
	DDX_Text(pDX, IDC_EDIT_MINKC, m_minkc);
	DDX_Text(pDX, IDC_EDIT_PY1, m_py);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMedcodeModify, CDialog)
	//{{AFX_MSG_MAP(CMedcodeModify)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMedcodeModify message handlers

BOOL CMedcodeModify::OnInitDialog() 
{
	CDialog::OnInitDialog();
	const CString TITLE="药品编码修改";
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(TITLE);
	SetWindowText(TITLE);
	long i(0);
	const int ITEM_COLS=11;
	//略去第一项空字符串
	for(int x=1 ;x<ptrMedcode->m_combo1.GetCount(); ++x ){
		ptrMedcode->m_combo1.GetLBText(x,strSql);
		m_combo1.AddString(strSql);
	}
		int countPoint=0;

	try{
		strSql.Format("SELECT DLBM,XLBM,BM,MC,GG,DW,PY,MAXKC,MINKC,L_TYPE,BZ FROM MEDCODE WHERE BM='%s' ",strBM);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
	//药品基本数据存入 arrayItem
		if(!recSet->adoEOF){
			for(;i<ITEM_COLS;++i){
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(i)->Value );
				arrayItem.Add(strSql);
			}

		}
		recSet->Close();

		strSql.Format("select l_ID,L_name from lsq_med_type t where l_eft=1 order by l_ord ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		m_comboType.AddString(BLANKSTR);
		arrayItem3.Add(BLANKSTR);

		while(!recSet->adoEOF){
			i=0;			
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(i)->Value );
			arrayItem3.Add(strSql);
			++i;
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(i)->Value );
			m_comboType.AddString(strSql);

			recSet->MoveNext();
		}
		recSet->Close();

		strSql.Format("select XLBM,XLMC from medxl WHERE DLBM='%s'",arrayItem[DLBM]);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		x=0;
		while(!recSet->adoEOF){
			i=0;			
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(i)->Value );
			arrayItem2.Add(strSql);
			if( strSql.Compare(arrayItem[XLBM]) ==0  )countPoint= x;
			else ++x;
		
			++i;
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(i)->Value );
			m_combo2.AddString(strSql);
			
			recSet->MoveNext();
		}
		recSet->Close();
		

		
	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return false;
	}		

	m_mc=arrayItem[MC];
	m_gg=arrayItem[GG];
	m_dw=arrayItem[DW];
	m_py=arrayItem[PY];
	m_maxkc=arrayItem[MAXKC];
	m_minkc=arrayItem[MINKC];
	m_bz=arrayItem[BZ];

	int st_1=ptrMedcode->m_combo1.GetCount();
	for(x=1 ;x < st_1 /*BZ+1 */; ++x ){
		if ( ptrMedcode->typeCode[x].Compare(arrayItem[DLBM]) == 0 )break;
	}
	//类别比原来查询的略去一字符串
	m_combo1.SetCurSel(x-1);
	
	m_combo2.SetCurSel(countPoint);
	
	if( arrayItem[L_TYPE].IsEmpty() ) m_comboType.SetCurSel(0); //甲乙丙类别 
	else m_comboType.SetCurSel(atoi(arrayItem[L_TYPE]) );
	
	
	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMedcodeModify::OnOK() 
{
	UpdateData();
	int i1,i2,i3;
	i1=m_combo1.GetCurSel(); //大类
	i2=m_combo2.GetCurSel(); //小类
	i3=m_comboType.GetCurSel();
	if( i1==CB_ERR ||  i2==CB_ERR || i3== CB_ERR || i3== 0)
	{
		AfxMessageBox("请选择药品所属类别");
		return;
	}

//	strSql.Format(" INSERT INTO MEDCODE(DLBM,XLBM,MC,GG,DW,PY,L_TYPE,MAXKC,MINKC,BZ ) VALUES('%s','%s',\
		'%s','%s','%s','%s',%ld,%ld,%ld,'%s') ",ptrMedcode->typeCode[i1],arrayItem2[i2],m_mc,m_gg,m_dw,\
		m_py,atoi(arrayItem3[i3]),atoi(m_maxkc),atoi(m_minkc),m_bz);
	strSql.Format(" UPDATE medcode SET DLBM='%s',XLBM='%s',MC='%s',GG='%s',DW='%s',PY='%s',L_TYPE='%ld',\
		MAXKC='%ld',MINKC='%ld',BZ='%s' WHERE BM='%s' ",ptrMedcode->typeCode[i1+1],arrayItem2[i2],m_mc,m_gg,m_dw,\
		m_py,atoi(arrayItem3[i3]),atoi(m_maxkc),atoi(m_minkc),m_bz,strBM);


	if(  CComFunc::WriteSql(strSql) )	
		CDialog::OnOK();

}

void CMedcodeModify::OnSelchangeCombo1() 
{
	UpdateData();
	int i1=m_combo1.GetCurSel();
	if( i1==CB_ERR ) return; 
	
	arrayItem2.RemoveAll();
	m_combo2.ResetContent();

	try{

		strSql.Format("select XLBM,XLMC from medxl WHERE DLBM='%s'",ptrMedcode->typeCode[i1+1] );
		//ptrMedcode->typeCode中第一项包含空字符,以和选择类别查询时对应,而修改属性中类别没有插入空字符
		//因此在选择编码时应在原序列中+1
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		long i(0);
		while(!recSet->adoEOF){
			i=0;			
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(i)->Value );
			arrayItem2.Add(strSql);
		
			++i;
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(i)->Value );
			m_combo2.AddString(strSql);
			
			recSet->MoveNext();
		}
		recSet->Close();
		

		
	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return ;
	}		
	
}
