#if !defined(AFX_COSTCONSUMEADD_H__BCA8B726_129D_433A_8B6A_845BD24CE016__INCLUDED_)
#define AFX_COSTCONSUMEADD_H__BCA8B726_129D_433A_8B6A_845BD24CE016__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CostConsumeAdd.h : header file
//日期：2010/2/7
//作者：凌绍清
//用途：改进之前老版本医院管理中的报销支出问题，现在增加预算功能，使之更
//		能反应报销过程中产生的费用超支问题
//
/////////////////////////////////////////////////////////////////////////////
// CCostConsumeAdd dialog

class CCostConsumeAdd : public CDialog
{
// Construction
public:
	void GenericSerial();
	CCostConsumeAdd(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCostConsumeAdd)
	enum { IDD = IDD_DIALOG_COST_BUDGET_ADD };
	CEdit	m_credence;
	CEdit	m_balance2;
	CEdit	m_cScale;
	CEdit	m_sjFee;
	CEdit	m_scale;
	CEdit	m_balance;
	CComboBox	m_departB;
	CComboBox	m_departA;
	COleDateTime	m_date;
	CString	m_jsr;
	CString	m_rss;
	CString	m_spr;
	UINT	m_iFujian;
	UINT	m_iPiaoju;
	double	m_dbFee;
	CString	m_strUser;
	CString	m_strCmt;
	//}}AFX_DATA
	CStringArray arrayA,arrayB; //胜于类别m_departA,m_departB的ID记录
	CString strSql;
	CString m_jsr_id,m_rss_id,m_spr_id;
	double dbBalance;
	enum{ SQL_ID_BALANCE_BUDGET=32,SQL_ID_OPERATOR_SEL=34};
	enum{ SQL_CREDENCE_ID=36};
	CBrush m_Brush;
	bool fPrint;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCostConsumeAdd)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void InitControl();

	// Generated message map functions
	//{{AFX_MSG(CCostConsumeAdd)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboCostA();
	afx_msg void OnSelchangeComboCostB();
	afx_msg void OnRy1();
	afx_msg void OnRy2();
	afx_msg void OnRy3();
	afx_msg void OnOk2();
	virtual void OnOK();
	afx_msg void OnChangeEditScale();
	afx_msg void OnChangeEditZhongfeiyong();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnKillfocusEditUser();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CFont fontTitle;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COSTCONSUMEADD_H__BCA8B726_129D_433A_8B6A_845BD24CE016__INCLUDED_)
