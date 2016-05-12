//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_PECULIARADD_H__DB990382_8498_4259_A267_DD0BBE94E108__INCLUDED_)
#define AFX_PECULIARADD_H__DB990382_8498_4259_A267_DD0BBE94E108__INCLUDED_

#include "qiuXpButton.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PeculiarAdd.h : header file
//*DATE:2012/05/20
//*DESC:
//*		新增对部分人员特殊补助操作,补助数据来源于外部EXCEL表格,首先导入补助
//*数据至[lsq_emp_other_price]中,然后调用存储过程[prc_emp_buZu_call]进行实际充值,
//*原始信息存入[LSQ_EMP_HEADSHIP_CHARGE]中

/////////////////////////////////////////////////////////////////////////////
// CPeculiarAdd dialog

class CPeculiarAdd : public CDialog
{
// Construction
public:
	CPeculiarAdd(CWnd* pParent = NULL);   // standard constructor
	enum{ HEADER_ID=25,SQL_ID=42};
// Dialog Data
	//{{AFX_DATA(CPeculiarAdd)
	enum { IDD = IDD_DIALOG_BUZU };
	CQiuXpButton	m_22;
	CQiuXpButton	m_1;
	CQiuXpButton	m_B_EXCEL_IN;
	CQiuXpButton	m_b1;
	CComboBox	comYear;
	CMSHFlexGrid	m_grid;
	CString	m_strKH;
	CString	m_strXM;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPeculiarAdd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPeculiarAdd)
	virtual BOOL OnInitDialog();
	afx_msg void OnExcelIn();
	afx_msg void OnExecuteAdd();
	afx_msg void OnQuery();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PECULIARADD_H__DB990382_8498_4259_A267_DD0BBE94E108__INCLUDED_)
