// GhQuery_del.cpp: implementation of the CGhQuery_del class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his3.h"
#include "GhQuery_del.h"
#include "progressIndicate.h"
#include "formghlist_del.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGhQuery_del::CGhQuery_del()
{

}

CGhQuery_del::~CGhQuery_del()
{

}



void CGhQuery_del::OnOK()
{
	CProgressIndicate pq;
	pq.pDialog= this;

	pq.pThreadFunction = Query;
	pq.DoModal();

	CDialog::OnOK();

}

UINT CGhQuery_del::Query(LPVOID ps)
{
	CFormGhList_del *pf=(CFormGhList_del*)theApp.pParentGrid.pGrid;
	CGhQuery_del * pd =(CGhQuery_del *) ((CProgressIndicate *) ps )->pDialog ;
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
	int COLS=pf->m_grid.GetCols(0)-1;;
	const int SUM_COMPUTE_COL=13;
	try{
//	CString HeadTitle[]={"DAN","就诊日期","编码","姓名","医生","划价员","收费员",\
		"发药员","挂号类别","挂号费","药品费","其它费用","合计","药品利润",\
		"建国前工人","大病救助","统筹支付","IC卡支付","公务员补助","现金" };
		strSql.Format("%s : %s  -- %s ",pf->TITLE,pd->m_date1.Format("%Y/%m/%d"),pd->m_date2.Format("%Y/%m/%d") );
		pf->GetDlgItem(IDC_STATIC_TITLE)->SetWindowText( strSql );

		CComFunc::GetSql(strSql,24); 
		str1.Format( " WHERE riqi BETWEEN to_date('%s','yyyymmdd') \
			and to_date('%s','yyyymmdd')  ",pd->m_date1.Format("%Y%m%d"),pd->m_date2.Format("%Y%m%d"));
		strSql+=str1;

		if(! pd->sfyCode.IsEmpty() )	strSql+=" AND 收费员='"+pd->sfyCode+"'";
		
		if( ! pd->ysCode.IsEmpty() ) strSql+=" AND doctor='"+pd->ysCode+"'";



		if( ! strGhtype.IsEmpty() )	strSql+=" AND Ghtype='"+pd->strArrType[pd->m_type.GetCurSel()]+"'";	
		if(! strname.IsEmpty() )strSql+=" AND SICKNAME like '"+strname+"%'";
		strSql+="  ORDER by riqi,danjuhao";
		
		CComFunc::GetSql(str1,25);
		str1.Replace("XT001",strSql);

		strSql=str1;
//		CComFunc::writeDebug(strSql);

		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		row=1;

		while(!recSet->adoEOF){
			col=0;
			price=0;
			str1.Format("%ld",row);
			pf->m_grid.SetTextMatrix(row,0,str1);
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
		*/		pf->m_grid.SetTextMatrix(row,i+1,str1);
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
	((CProgressIndicate *)ps)->ConnectFlag =1;
	((CProgressIndicate *)ps)->SendMessage(WM_CLOSE,NULL,NULL);

	pd->SendMessage(WM_CLOSE,NULL,NULL);
	
		return false;
	}	

	pf->m_grid.SetRow(row);
	pf->m_grid.SetCol(1);
	pf->m_grid.SetCellBackColor(LSQ_BACKCOLOR);
	strSql.Format(" %ld ",row-1);

	pf->m_grid.SetTextMatrix(row,1,"合计");	
	pf->m_grid.SetTextMatrix(row,3,strSql);
	for(long count=1;count< COLS+1;count++){
		pf->m_grid.SetCol(count);
		pf->m_grid.SetCellBackColor(LSQ_BACKCOLOR);
		if( count > SUM_COMPUTE_COL ){
			str1.Format("%.2f",add[count-SUM_COMPUTE_COL-1]);
			pf->m_grid.SetTextMatrix(row,count,str1);	

		}
	}
	CComFunc::SetGridColColor(16,pf->m_grid);

	pf->m_grid.SetRedraw(true);
	
	((CProgressIndicate *)ps)->ConnectFlag =1;
	((CProgressIndicate *)ps)->SendMessage(WM_CLOSE,NULL,NULL);

	pd->SendMessage(WM_CLOSE,NULL,NULL);
	
	return true;
}
