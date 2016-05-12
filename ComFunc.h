// ComFunc.h: interface for the CComFunc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMFUNC_H__30CA6A5B_6188_40BF_B4C4_88989FF5E104__INCLUDED_)
#define AFX_COMFUNC_H__30CA6A5B_6188_40BF_B4C4_88989FF5E104__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "mshflexgrid.h"
#include "excel9.h"
#include "gridctrl\gridctrl.h"
#include <vector>
#include <algorithm>
using namespace std;

class CComFunc  
{
public:
	static BOOL  SetComboxType(CStringArray & aryID,CComboBox & cbType,const CString &strSql);
	static BOOL comSetGridHeader(CGridCtrl &m_grid,ULONG id);
	static bool GetStringCollect(CString &strSql,CStringArray &ary);
	static void GetBigMoney(const double & dMoney,CString & strReturnValue);
	static void  ReadDataForGrid(CString &strSql,CMSHFlexGrid &m_grid,int  *iCol=NULL,int  iSum=0);
	//读取数据插入到表格中,用vector提供要统计汇总的列号,及存储结果的vector
	static BOOL ReadDataForGrid(CGridCtrl& m_grid, CString & strSql,int gridCols,
		vector<int> &vtCols=vector<int>(),vector<double> &vtCount=vector<double>(),int sn=1,vector<int> &vtAlign=vector<int>() );

	static CDialog * SysWait(CDialog* pt);
	static UINT SetGridColColor(UINT id,CMSHFlexGrid &pGrid );
//	static void ReadDataForGrid(CString &strSql,CMSHFlexGrid &m_grid);
	static CString GetSqlItem(long i);
	static bool BeginCritical(CString strID,bool flag);
	static bool GetSql(CString &strOut,UINT id);
	static bool GetString( CString &strSql,CString *pS,int num);
	enum{ TYPE_QPYB=1,TYPE_HAYB=2,TYPE_JMTC=3,TYPE_BCBX=4,TYPE_GYQS=5,
		TYPE_GS=6,TYPE_LX=7,TYPE_TY=8,TYPE_GC=9 };

	static int GetGhType(CString & strType);
	static void GridSelRow(CMSHFlexGrid &m_grid, ULONG row);
	static void SetExcelCell(_Worksheet &sheetx,int iRow, int iCol, CString &strData);
	static bool AssertPriv(UINT id);
	static UINT THREAD_TO_EXCEL(LPVOID lp);
	static BOOL comSetGridHeader(CMSHFlexGrid &m_grid,ULONG id );
	static void ToExcel(CMSHFlexGrid * pg);
	static void toExcel(CGridCtrl &  m_grid);
	static void writeDebug(CString strout);
	static BOOL WriteSql(CString strSql);
	static CString GetString(CString strSql);
	static UINT ForWait(LPVOID pw);
	CComFunc();
	virtual ~CComFunc();

};

#endif // !defined(AFX_COMFUNC_H__30CA6A5B_6188_40BF_B4C4_88989FF5E104__INCLUDED_)
