// ComFunc.cpp: implementation of the CComFunc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his3.h"
#include "ComFunc.h"
#include "progressEx.h"
#include "dialogWait.h"
#include "gridctrl\gridctrl.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CComFunc::CComFunc()
{

}

CComFunc::~CComFunc()
{

}

CString CComFunc::GetString(CString strSql)
{
	CString strout(BLANKSTR);
	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
		
			strout=(char*)_bstr_t(recSet->GetFields()->GetItem(0L)->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(0L)->Value );
		}
		recSet->Close();

		return strout;

	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
		return strout;
	}	

}

BOOL CComFunc::WriteSql(CString strSql)
{
	try{

		HospitalConnect->BeginTrans();
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		HospitalConnect->CommitTrans();

	}
	catch(_com_error e)
	{
		HospitalConnect->RollbackTrans();
		AfxMessageBox(e.Description());
		return false;
	}
	return true;

}

void CComFunc::writeDebug(CString strout)
{
	CFile fDebug;

	if( ! fDebug.Open("F:\\log.txt",CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite  ) )
		AfxMessageBox("建立调试文件失败...");
	else fDebug.SeekToEnd();

	COleDateTime curDate=COleDateTime::GetCurrentTime();
	CString strFmt;
	CString strRet("\r\n");
	CString strSpan('-',40);
	strFmt.Format("%s\r\n",curDate.Format("%Y-%m-%d %H:%M:%S") );
	fDebug.Write(strFmt,strFmt.GetLength());
	strSpan+=strRet;
	fDebug.Write(strSpan,strSpan.GetLength());

	fDebug.Write(strout,strout.GetLength());
	fDebug.Write(strRet+strRet,strRet.GetLength()*2 );


	fDebug.Close();

}
#define IDC_PROGRESS_EXCEL WM_USER+1001
void CComFunc::ToExcel(CMSHFlexGrid *pg)
{
/*
	CProgressEx *pp=new CProgressEx();

	CRect r1(0,0,400,25);
	pp->Create(WS_CHILD |PBS_SMOOTH|WS_BORDER ,r1,AfxGetMainWnd()->GetForegroundWindow(),IDC_PROGRESS_EXCEL);
	pp->UpdateWindow();
	pp->ShowWindow(SW_SHOW);
	pp->CenterWindow();
	pp->Invalidate();
	pp->SetRange32(0,pg->GetRows() );
	pp->strView="正在准备导出...请稍等!!";
	
	theApp.pParentGrid.pGrid=pg;
	AfxBeginThread(THREAD_TO_EXCEL,pp);
*/
	_Application app2;
	Workbooks books2;
	_Workbook book2;
	Worksheets sheets2;
	_Worksheet sheet2;
	 COleVariant vOpt2(DISP_E_PARAMNOTFOUND,VT_ERROR);

	CProgressEx pp;
	CRect r1(0,0,400,25);
	pp.Create(WS_CHILD |PBS_SMOOTH|WS_BORDER ,r1,AfxGetMainWnd()->GetForegroundWindow(),IDC_PROGRESS_EXCEL);
	pp.UpdateWindow();
	pp.ShowWindow(SW_SHOW);
	pp.CenterWindow();
	pp.Invalidate();
	pp.SetRange32(0,pg->GetRows() );
	pp.strView="正在准备导出...请稍等!!";

//	if( ! app2 ){
	app2.CreateDispatch("excel.application");
	if(!app2){
		AfxMessageBox("请注意系统中必须装有EXCEL97 或者 EXCEL2000 ,否则此功能不能使用...");
		return;
	}
	books2=app2.GetWorkbooks();
	//		book2=books2.Open(strFileName,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt);
	book2=books2.Add(vOpt2);
	sheets2=book2.GetWorksheets();
	sheet2=sheets2.GetItem(COleVariant((short)1));
//	}

//


	Range vRange;
	Font font;
	long x,y;
	CString str1,str2;
	
	app2.SetVisible(false);
	pp.strView="";


	for (x=0; x<pg->GetRows(); x++)
	{
		for( y=0 ; y< pg->GetCols(0) ; y++ )
		{
			if( y<26)str1.Format("%c%ld",'A'+y , x+1 );
			else str1.Format("%c%c%ld",'A'+ ( y/26 -1) ,'A'+y % 26,x+1 );
			vRange=sheet2.GetRange(_variant_t(str1),_variant_t(str1)); // 医疗机构
		//	font=vRange.GetFont();
		//	font.SetName(_O(FONTNAME));
		//	font.SetSize(_O((short)STANDARDFONT));
			vRange.SetValue(COleVariant(pg->GetTextMatrix(x,y)));
		}
		
		pp.strView.Format("%2.0f%%",double(x)/pg->GetRows()*100);
		pp.SetPos(x);
	}
	app2.SetVisible(true);
		
	pp.DestroyWindow();
	sheet2.ReleaseDispatch();

	sheets2.ReleaseDispatch();
//	book.Close(_O((short)0),vOpt,vOpt); //关闭EXCEL,不保存文件

	book2.ReleaseDispatch();
//	books2.Close();
	books2.ReleaseDispatch();
	app2.ReleaseDispatch();	

}
/*  根据提供的ID号从数据库中读取相应的列头,设置列标题 
*
*/
BOOL CComFunc::comSetGridHeader(CMSHFlexGrid &m_grid, ULONG id)
{

	m_grid.Clear();
	m_grid.SetRows(2);
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	long GRID_COLS=0, i=0;
	CString strSql;
	try{
		strSql.Format("select mc,width,align from lsq_grid_col  where id=%ld order by rank ",id);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect, adOpenDynamic ,adLockOptimistic,adCmdText); 

		m_grid.SetCols(0,GRID_COLS);
		while(!recSet->adoEOF){
			GRID_COLS++;
			m_grid.SetCols(0,GRID_COLS);
	
			strSql=(char*)_bstr_t(recSet->GetCollect("MC").vt==VT_NULL? _variant_t( BLANKSTR):recSet->GetCollect("MC"));
			m_grid.SetTextMatrix(HEADER_ROW,i,strSql);
			strSql=(char*)_bstr_t(recSet->GetCollect("width").vt==VT_NULL? _variant_t( BLANKSTR):recSet->GetCollect("width"));
			m_grid.SetColWidth(i,0,atol(strSql) );
			strSql=(char*)_bstr_t(recSet->GetCollect("align").vt==VT_NULL? _variant_t( BLANKSTR):recSet->GetCollect("align"));
			m_grid.SetColAlignment(i,atoi(strSql));
			
			i++;
			recSet->MoveNext();
	
		}
		recSet->Close();
		
	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return false;
	}		

	m_grid.SetFixedCols(0);
	long  col(0),row(0);
	m_grid.SetSelectionMode(1L);
	m_grid.SetRow(0);

	for(i =0 ; i< GRID_COLS; i++){
		m_grid.SetCol( i );
		m_grid.SetCellAlignment((short)4); //居中对齐
	
	}	
	CComFunc::GridSelRow(m_grid,1);
	return true;

}

UINT CComFunc::THREAD_TO_EXCEL(LPVOID lp)
{
	_Application app2;
	Workbooks books2;
	_Workbook book2;
	Worksheets sheets2;
	_Worksheet sheet2;
	 COleVariant vOpt2(DISP_E_PARAMNOTFOUND,VT_ERROR);

	 app2.CreateDispatch("excel.application");
	if(!app2){
		AfxMessageBox("请注意系统中必须装有EXCEL97以上版本 ,否则此功能不能使用...");
		return false;
	}
	books2=app2.GetWorkbooks();
	book2=books2.Add(vOpt2);
	sheets2=book2.GetWorksheets();
	sheet2=sheets2.GetItem(COleVariant((short)1));


	Range vRange;
	Font font;
	long x,y;
	CString str1,str2;
	
	app2.SetVisible(false);
	((CProgressEx *)lp)->strView="";
	CMSHFlexGrid *pg=(CMSHFlexGrid *)theApp.pParentGrid.pGrid;
	

	for (x=0; x<pg->GetRows(); x++)
	{
		for( y=0 ; y< pg->GetCols(0) ; y++ )
		{
			if( y<26)str1.Format("%c%ld",'A'+y , x+1 );
			else str1.Format("%c%c%ld",'A'+ ( y/26 -1) ,'A'+y % 26,x+1 );
			vRange=sheet2.GetRange(_variant_t(str1),_variant_t(str1)); // 医疗机构
			vRange.SetValue(COleVariant(pg->GetTextMatrix(x,y)));
		}
		
		((CProgressEx *)lp)->strView.Format("%2.0f%%",double(x)/pg->GetRows()*100);
		((CProgressEx *)lp)->SetPos(x);
	}
	app2.SetVisible(true);
		
	((CProgressEx *)lp)->DestroyWindow();

	sheet2.ReleaseDispatch();

	sheets2.ReleaseDispatch();
//	book.Close(_O((short)0),vOpt,vOpt); //关闭EXCEL,不保存文件

	book2.ReleaseDispatch();
	books2.ReleaseDispatch();
	app2.ReleaseDispatch();	


	return true;
}

bool CComFunc::AssertPriv(UINT id)
{
	CString str,str2;
/*	str.Format(" SELECT ID FROM his3_priv_quota WHERE BM=%ld and ID= %ld AND effect=1" ,atol(LoginInformation.user_code),id);
*/	
	GetSql(str,20);
	str2.Format("%ld",atol(LoginInformation.user_code ));
	str.Replace("XT001", str2 );
	str2.Format("%ld",id);
	str.Replace("XT002",str2);
	str2=GetString(str);

	if( CComFunc::GetString(str).IsEmpty() ){
		str.LoadString(IDS_PRIV_PROMPT);
		AfxMessageBox(str);
		return false;
	}
	return true;
}

void CComFunc::SetExcelCell(_Worksheet &sheetx, int iRow, int iCol, CString &strData)
{

	/* 设置EXCEL单元格字符串 
		sheetx  要操作的工作表
		iRow	要操作工作表所在的行
		iCol	要操作的工作表所在列
		strData 要写入的字符串
	*/
#define _O(x) COleVariant(x)
	
	CString strCell;
	Range vRange;
	strCell.Format("%c%d",iCol+'A',iRow+1);
	vRange=sheetx.GetRange(_O(strCell),_O(strCell));
	vRange.SetValue(_O(strData));

}

void CComFunc::GridSelRow(CMSHFlexGrid &m_grid, ULONG row)
{
	long cols=m_grid.GetCols(0);
	m_grid.SetCol(0);
	m_grid.SetRow(row);
	m_grid.SetRowSel(row);
	m_grid.SetColSel(cols-1);
}
/*
// 根据提供的内部挂号类型,返回程序中使用的相应
// 的数字标识
*/
int CComFunc::GetGhType(CString &strType)
{
	int iRet =0 ;

	if( strType.Compare("QPYB") == 0 || strType.Compare("QPTD") == 0  || strType.Compare("QHMT") == 0 ){ //因为编码前缀不同
		
		iRet=TYPE_QPYB; // 清浦医保
			
	}
	else if( strType.Compare("基本保险") == 0 || strType.Compare("特定门诊") == 0 ||
		strType.Compare("家庭病床")==0  || 
		strType.Compare("GMMT_201001")==0 )
		//20090916,因淮电要求新增“居民门特”类别，内部代号为：GMMT_090916,操作与市基本医保差不多
		//20100105,因淮电要求新增"清河门诊"类别，内部代号为：GMMT_201001,操作与市医保差不多
	{
		iRet=TYPE_HAYB; //市医保基本
	}
	else if( strType.Compare("居民统筹") == 0  || strType.Compare("GMMT_090916") == 0 ){

		iRet=TYPE_JMTC; //市医保居民统筹
	}
	else if ( strType.Compare("补充保险") == 0  )
	{
		iRet=TYPE_BCBX;
	}
	else if ( strType.Compare("供养亲属") == 0  )
	{
		iRet=TYPE_GYQS;
	}
	else if ( strType.Compare("工伤人员") == 0  )
	{
		iRet=TYPE_GS;
	}
	else if ( strType.Compare("离休人员") == 0  )
	{
		iRet=TYPE_LX;
	}
	else if ( strType.Compare("退养人员") == 0  )
	{
		iRet=TYPE_TY;
	}
	else if ( strType.Compare("建国前老工人") == 0  )
	{
		iRet=TYPE_GC;
	}
	else 
		iRet=0;

	return iRet;

}

bool CComFunc::GetString(CString & strSql, CString *pS, int num)
{

	for(int i=0; i<num; i++ ) pS[i]=BLANKSTR;

	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 

		if(!recSet->adoEOF){
			for( i=0; i< num ;i++ )
				pS[i]=(char*)_bstr_t(recSet->GetFields()->GetItem(long(i))->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(long(i))->Value );
		}
			
		recSet->Close();

		return true;

	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
		return false;
	}	

}

bool CComFunc::GetSql(CString &strOut, UINT id)
{

	CString strSql;
	strOut=BLANKSTR;
	strSql.Format( " SELECT sql FROM lsq_sql_statemnet WHERE id= %ld ",id);

	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
		
			strOut=(char*)_bstr_t(recSet->GetFields()->GetItem(0L)->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(0L)->Value );
		}
		recSet->Close();

		return true;

	}
	catch(_com_error e)
	{
		strOut=BLANKSTR;
		AfxMessageBox(strSql);
		recSet->Close();
		return false;
	}	
}

bool CComFunc::BeginCritical(CString strID, bool flag)
{
	int ib;
	CString strSql;
	if( flag ){
		try{
			_CommandPtr cmd;
			_ParameterPtr par;
			cmd.CreateInstance(__uuidof( Command ));
			par.CreateInstance(__uuidof( Parameter));
			
			_variant_t vNULL;
			vNULL.vt = VT_ERROR;
			vNULL.scode = DISP_E_PARAMNOTFOUND;
			
			cmd->put_CommandType(adCmdStoredProc) ;
			par=cmd->CreateParameter(_bstr_t("success"),adUnsignedInt,adParamOutput,20,vNULL);
			cmd->Parameters->Append( par );
			
			par=cmd->CreateParameter(_bstr_t("paraID"),adVarChar,adParamInput,50,_bstr_t( strID ) );
			cmd->Parameters->Append( par );
			
			cmd->put_CommandText(_bstr_t("PRC_gh_check"));
			cmd->ActiveConnection=HospitalConnect;
			cmd->Execute(NULL,NULL,adCmdStoredProc);
			
			ib=cmd->Parameters->GetItem("success")->Value.uintVal;
			cmd.Detach();
			par.Detach();
			if ( ib ) return true;
			else return false;
			
		}
		catch(_com_error e)
		{
			AfxMessageBox(e.ErrorMessage());
			return false;
		}
		



	}
	else{ //解除冲突
	
		strSql.Format(" Delete From lsq_share Where serial='%s' ",strID);
		if( !CComFunc::WriteSql(strSql) )AfxMessageBox("解决共享冲突时出现错误!!");
		return true;
		

	}
}

CString CComFunc::GetSqlItem(long i)
{
	CString str(BLANKSTR);
	str=(char*)_bstr_t(recSet->GetFields()->GetItem(long(i))->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(long(i))->Value );
	return str;
}
/*
// 通过传入的SQL语句,自动获取数据填充表格
*/
/*
void CComFunc::ReadDataForGrid(CString &strSql, CMSHFlexGrid &m_grid)
{
	long row(0),i;
	long cols=m_grid.GetCols(0);
	try{

		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		row=1;
		m_grid.SetRedraw(false);
		while(! recSet->adoEOF){

			strSql.Format("%ld",row); //显示序列号,重新计算,数据库选择时的行号已被打乱
			m_grid.SetTextMatrix(row,0,strSql);
			for( i=1; i< cols ; i++ )
			{
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(long(i))->Value.vt == VT_NULL ? _variant_t(BLANKSTR):recSet->GetFields()->GetItem(long(i))->Value );
				m_grid.SetTextMatrix(row,i,strSql);
			}
			row++;
			m_grid.AddItem(BLANKSTR,_variant_t(row));
			recSet->MoveNext();

		}
		recSet->Close();
		GridSelRow(m_grid,1);
		m_grid.SetRedraw(true);
	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return ;
	}
}
*/
//**********************************************************
//# 根据表格ID值,将表格相应的列设置颜色
//
//***********************************************************

UINT CComFunc::SetGridColColor( UINT id,CMSHFlexGrid &pGrid)
{
	//数组第一列存放 列号,第二列存放 颜色值

	CUIntArray arrCol,arrBack,arrFore;
	CString strSql;
	int iRgb[3];
	long i(0),x,iLine(0);
	strSql.Format(" Select rank,cR,cG,cB,cR2,cG2,cB2 from lsq_grid_col WHERE id=%ld and color =1  order by rank ",id );
	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			i=0;
			strSql= (char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(i)->Value ) ;
			arrCol.Add( atol(strSql) );
			for(x=0; x< 3; x++ ) //背景色
			{
				++i;
				strSql= (char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(i)->Value ) ;
				iRgb[x]=atol(strSql);
			}
			arrBack.Add( RGB(iRgb[0],iRgb[1],iRgb[2] ) );

			for(x=0; x< 3; x++ ) //前景色
			{
				++i;
				strSql= (char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(i)->Value ) ;
				iRgb[x]=atol(strSql);
			}
			arrFore.Add( RGB(iRgb[0],iRgb[1],iRgb[2] ) );

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
	long colorCols=arrCol.GetSize() ; //需要设置色彩的列数

	if( colorCols > 0 ){
		long row=pGrid.GetRows()-1 ;
		while( row > 0 ){
			
			pGrid.SetRow(row);
			for( i=0 ; i<  colorCols ; i++ )
			{
				pGrid.SetCol( arrCol[i] -1 ); //数据库中记录的第一列从零开始
				pGrid.SetCellBackColor(arrBack[i] );
				pGrid.SetCellForeColor(arrFore[i] );
			}
			row -- ;
		}
	}

	return true;
}

UINT CComFunc::ForWait(LPVOID pw)
{
	CDialogWait dw;
	dw.DoModal();

	return true;
}

CDialog * CComFunc::SysWait(CDialog* pt)
{
	CDialogWait *pw=new CDialogWait;
	pw->Create(IDD_DIALOG_WAIT,pt);
	pw->ShowWindow(SW_SHOW);
//	pw->UpdateData();
	return (CDialog*)pw;
}

void CComFunc::ReadDataForGrid(CString &strSql, CMSHFlexGrid &m_grid, int *iCol, int iSum)
{
	long row(0),i;
	long cols=m_grid.GetCols(0);
	double *dbSum=NULL;
	CString strTmp;


	if( iSum > 0 )	{
		dbSum=new double[iSum];
		for(i=0 ; i < iSum; i++ )dbSum[i]=0.0;
	}

	try{

		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		row=1;
		m_grid.SetRedraw(false);
		while(! recSet->adoEOF){

			strSql.Format("%ld",row); //显示序列号,重新计算,数据库选择时的行号已被打乱
			m_grid.SetTextMatrix(row,0,strSql);
			for( i=1; i< cols ; i++ )
			{
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(long(i))->Value.vt == VT_NULL ? _variant_t(BLANKSTR):recSet->GetFields()->GetItem(long(i))->Value );
				m_grid.SetTextMatrix(row,i,strSql);
				for(int x=0; x<iSum ; x++ )
				{
					if( iCol[x] == i )dbSum[x]+=atof(strSql);

				}
			}
			row++;
			m_grid.AddItem(BLANKSTR,_variant_t(row));
			recSet->MoveNext();

		}
		recSet->Close();
		for(i=0 ; i< iSum ; i++ )//填写汇总行
		{	
			strTmp.Format("%.2f",dbSum[i]);
			m_grid.SetTextMatrix(row,iCol[i],strTmp);
			

		}
		if(iSum > 0 ) delete[] dbSum;
		GridSelRow(m_grid,1);
		m_grid.SetRedraw(true);
	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		recSet->Close();
		return ;
	}
}

void CComFunc::GetBigMoney(const double &dMoney, CString &strReturnValue)
{
     CString strMoney;

     strMoney.Format ("%.2f" , dMoney);

	 if( strMoney.GetLength() >15 ){
		 strReturnValue="￥"+strMoney;
		 return ; //数值太大
	 }

     CString strUnit = "元拾佰仟万拾佰仟亿拾佰仟";

     CString strNumber = "零壹贰叁肆伍陆柒捌玖";

     CString strOtherUnit = "整角分";

 

     //将数字分整数部份与小数部份处理

     int nPos = strMoney.Find (".");
     int nLength = strMoney.GetLength ();
     if(nPos < 0)
         nPos = nLength;
 //    CString strReturnValue;
     int nCount = 0;
     bool bZero = false;
     bool bNeedLevel = false;    //对段的识别，用于是否需要出现段名，如亿，万等
     //对整数部份进行反相识别处理

     for(int i = nPos - 1;i >= 0;i --)
     {
         TCHAR ch = strMoney.GetAt (i);
         if(nCount % 4 == 0 && nCount > 0)
         {
               //如果处理的数字为第四位（万），或第八位（亿）等，则要求置段
              bNeedLevel = true;
         }
         if(ch == '0')
         {
               //只对拾佰仟位的０进行识别，主要考虑到拾的特殊性，即如１０读壹拾，不会读壹拾零
              if(nCount % 4 != 0)

                   bZero = true;
         }
         else
         {

              CString strTemp(strReturnValue);

              strReturnValue = strNumber.Mid ((ch - 0x30) * 2 , 2);

              if(nCount > 0)

              {

                  strReturnValue += strUnit.Mid (nCount * 2 , 2);

                   if(nCount % 4 != 0 && bNeedLevel)

                   {

                         //这里判断是否需要读段名，如万，亿等

                       strReturnValue += strUnit.Mid (int(nCount / 4) * 8 , 2);

                   }

                   bNeedLevel = false;

              }

              if(bZero)

              {

                   //只有比当前处理的位要低中有数字才补零

                   if(!strTemp.IsEmpty ())

                       strReturnValue += strNumber.Left (2);

                   bZero = false;

              }

              strReturnValue += strTemp;

         }

         nCount ++;

     }

     strReturnValue += strUnit.Left (2);
	 if(strReturnValue.GetLength()<=2) strReturnValue="";
	 //防止整数部分为零

     bool bAllZero = true;

     //下面实现对小数点后面的处理

     //先判断是否为全零，则不需要继续读

     if(nPos < nLength)

     {

         if(nLength > 2)

              nLength = 2;

         for(int i = 0;i < nLength;i ++)

              if(strMoney.GetAt (nPos + i + 1) != '0')

                   bAllZero = false;

     }

     if(bAllZero)

     {

         strReturnValue += strOtherUnit.Left (2);

     }

     else

     {

          //对分角的处理

         for(int i = 0;i < nLength;i ++)

         {

              TCHAR ch = strMoney.GetAt (nPos + 1 + i);

              if(ch == '0' && i > 0)

              {

              }

              else

              {

                   strReturnValue += strNumber.Mid ((ch - 0x30) * 2 , 2);

                   if(ch != '0')

                       strReturnValue += strOtherUnit.Mid ((i + 1) * 2 , 2);

              }

         }

     }

  //   return strReturnValue;
}

bool CComFunc::GetStringCollect(CString &strSql, CStringArray &ary)
{

	ary.RemoveAll();
	const int i=0;

	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 

		while(!recSet->adoEOF){
				ary.Add( (char*)_bstr_t(recSet->GetFields()->GetItem(long(i))->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(long(i))->Value ) );
				recSet->MoveNext();
		}
			
		recSet->Close();

		return true;

	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
		return false;
	}	

}

//针对 CGridCtrl 进行表格设计,属于重载函数,与原有的CMSHGRID相区别
BOOL CComFunc::comSetGridHeader(CGridCtrl &m_grid, ULONG id)
{

	m_grid.SetRowCount(2);
	m_grid.SetFixedColumnSelection(false);
	m_grid.SetFixedRowSelection(false);
	m_grid.SetSingleRowSelection(true); //单行选择模式
	m_grid.SetSingleColSelection(false);//单列选择模式关闭
	m_grid.SetFixedRowCount(1);


	
	long GRID_COLS=0, i=0;
	CString strSql;
	try{
		strSql.Format("select mc,width,align from lsq_grid_col  where id=%ld order by rank ",id);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect, adOpenDynamic ,adLockOptimistic,adCmdText); 

		//m_grid.SetCols(0,GRID_COLS); 
		m_grid.SetColumnCount(GRID_COLS);
		while(!recSet->adoEOF){
			GRID_COLS++;
			m_grid.SetColumnCount(GRID_COLS);
	
			strSql=(char*)_bstr_t(recSet->GetCollect("MC").vt==VT_NULL? _variant_t( BLANKSTR):recSet->GetCollect("MC"));
			m_grid.SetItemText(0,i,strSql);
			strSql=(char*)_bstr_t(recSet->GetCollect("width").vt==VT_NULL? _variant_t( BLANKSTR):recSet->GetCollect("width"));
			if( atol(strSql) ==0 ) //宽度为0则隐藏
				m_grid.SetColumnWidth(i,0 );
			strSql=(char*)_bstr_t(recSet->GetCollect("align").vt==VT_NULL? _variant_t( BLANKSTR):recSet->GetCollect("align"));
			m_grid.SetItemFormat(0,i,atoi(strSql));
			
			i++;
			recSet->MoveNext();
	
		}
		recSet->Close();
		
	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return false;
	}	
	
	m_grid.AutoSize();


	return true;
}
// 参数：表格控件引用，SQL语句，表格列数，要汇总的列，汇总数据存入位置，序号所在列，单元格对齐数据
// 2015/12/28
BOOL CComFunc::ReadDataForGrid(CGridCtrl& m_grid, CString & strSql,int gridCols,vector<int> &vtCols,vector<double> &vtCount,int sn,
	vector<int> &vtAlign )
{

	m_grid.SetRedraw(false);
	m_grid.SetListMode();
	m_grid.SetSingleRowSelection(true);

	m_grid.SetFrameFocusCell(false);
	m_grid.SetTrackFocusCell(false);
	m_grid.SetRowCount(1);

	vector<double>::size_type iCols=vtCols.size();
	vector<int>::iterator  iteTmp;
	int iAry;
	vector<int>::size_type iNum=vtAlign.size(); //测试是否有对齐数据
	long i(1);

	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		long col(0);
		//以下变量用于合并单元格
		//vector<	int>  iBegin(gridCols,1),iCounting(gridCols,1);
		//CStringArray aryBegin;
		//aryBegin.SetSize(gridCols);

		while(!recSet->adoEOF){
			m_grid.InsertRow("xx");

			while( col < gridCols ){

				strSql=CComFunc::GetSqlItem(col) ;

				m_grid.SetItemFormat(i,col,iNum==0?0 : vtAlign[col] );	
				//根据所要求的列设定顺序号
				if( col == sn ){
					strSql.Format("%d",i);
					m_grid.SetItemFormat(i,col,37U);

				}
				
				m_grid.SetItemText(i,col,strSql);
				
				//根据要求对相应的列进行求和累加
				if( ( iteTmp= std::find(vtCols.begin(),vtCols.end(),col) )  !=vtCols.end()  && iCols > 0 )
				{

					iAry=iteTmp-vtCols.begin();
					vtCount[iAry]+=atof(strSql);
					m_grid.SetItemFormat(i,col,DT_RIGHT);
				}

				col++;
		}

		col=0;
		i++;

		recSet->MoveNext();

	}
		recSet->Close();

	}

	catch(_com_error e)

	{

		AfxMessageBox(TEXT("数据库连接出错！"));

		AfxMessageBox(e.Description());
		return false;
	}

	//添加最后一行汇总行
	m_grid.InsertRow("xx");
	m_grid.SetItemText(i,0,"合计");
	int idx;
	for(idx=0;idx<vtCols.size();idx++)
	{
		strSql.Format("%.2f",vtCount[idx]);
		m_grid.SetItemText(i,vtCols[idx],strSql);
		m_grid.SetItemFormat(i,vtCols[idx],DT_RIGHT);
	}
	m_grid.SetRedraw(true);
	return true;
}

void CComFunc::toExcel(CGridCtrl &  m_grid)
{
	_Application app2;
	Workbooks books2;
	_Workbook book2;
	Worksheets sheets2;
	_Worksheet sheet2;


	 COleVariant vOpt2(DISP_E_PARAMNOTFOUND,VT_ERROR);

	 if (! app2.CreateDispatch(_T("Excel.Application"),NULL))   
	 {   
		 AfxMessageBox(_T("创建Excel服务失败,你可能没有安装EXCEL，请检查!"));   
		 return ;  
	 } 

	 books2=app2.GetWorkbooks();
	book2=books2.Add(vOpt2);
	sheets2=book2.GetWorksheets();
	sheet2=sheets2.GetItem(COleVariant((short)1));


	Range vRange;
	long x,y;
	CString str1,str2;
	


	for (x=0; x< m_grid.GetRowCount() ; x++)
	{
		for( y=0 ; y< m_grid.GetColumnCount() ; y++ )
		{
			if( y<26)str1.Format("%c%ld",'A'+y , x+1 );
			else str1.Format("%c%c%ld",'A'+ ( y/26 -1) ,'A'+y % 26,x+1 );
			vRange=sheet2.GetRange(_variant_t(str1),_variant_t(str1)); 
			vRange.SetValue(COleVariant(m_grid.GetItemText(x,y) ));
		}
	}
		
	app2.SetVisible(true);
	sheet2.ReleaseDispatch();

	sheets2.ReleaseDispatch();

	book2.ReleaseDispatch();

	books2.ReleaseDispatch();
	app2.ReleaseDispatch();	
	app2=NULL;
}
//根据SQL语句内容填写组合框及ID
BOOL CComFunc::SetComboxType(CStringArray &aryID, CComboBox &cbType, const CString &strSql)
{

	try{
		aryID.RemoveAll();
		cbType.ResetContent();
		aryID.Add("");
		cbType.AddString("");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			
			aryID.Add(GetSqlItem(0));
			cbType.AddString(GetSqlItem(1));
			recSet->MoveNext();
	
		}
		recSet->Close();
		
	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return false;
	}		
	return true;
}
