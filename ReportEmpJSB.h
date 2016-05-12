// ReportEmpJSB.h: interface for the CReportEmpJSB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REPORTEMPJSB_H__645B7FCB_51DD_42D7_8F03_258A63277D2E__INCLUDED_)
#define AFX_REPORTEMPJSB_H__645B7FCB_51DD_42D7_8F03_258A63277D2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ReportEmpCount.h"
//********************************************************************
//*DATE:2012/06/18
//*DESC：
//*		补充医保基金结算表，将原来旧程序的结算表移至新程序中，涉及其中
//*统筹基金计算方式调整,具体调整在oracle存储过程prc_balance，原来的计算方式如下：
//*  工资总额*4% - 个人年度充值 - 特殊充值 = 统筹基金
//* 现在的计算方式：
//*	 工资总额*4% - 个人年度充值 = 统筹基金
//*即将特殊充值从统筹基金中剥离
/////////////////////////////////////////////////////////////////////////
class CReportEmpJSB : public CReportEmpCount  
{
public:
	static UINT GenerateJSB(LPVOID ps);
	void OnOK();
	BOOL OnInitDialog();
	CReportEmpJSB();
	virtual ~CReportEmpJSB();
	enum{ GRID_ID=27 };
};

#endif // !defined(AFX_REPORTEMPJSB_H__645B7FCB_51DD_42D7_8F03_258A63277D2E__INCLUDED_)
