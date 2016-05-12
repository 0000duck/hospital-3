//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_COSTBUDGET_H__32DB9224_9C1F_4DB5_AA4F_142673F49FFE__INCLUDED_)
#define AFX_COSTBUDGET_H__32DB9224_9C1F_4DB5_AA4F_142673F49FFE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CostBudget.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCostBudget dialog

class CCostBudget : public CDialog
{
// Construction
public:
	void OnKillMoveEdit();
	CString strSql;
	CCostBudget(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCostBudget)
	enum { IDD = IDD_DIALOG_COST_BUDGET };
	CComboBox	m_year;
	CComboBox	m_depart;
	CMSHFlexGrid	m_grid;
	//}}AFX_DATA
	enum {GRID_HEADER_ID= 19,SQL_QUERY_ID = 29,GRID_EDIT_COL=5,
		GRID_EDIT_COL2=6,
		IDC_MOVE_EDIT= (WM_USER)+105,
		GRID_ID=1 ,SQL_WRITE_ID =30 };
	CStringArray arrayDepart;
	CString strWRITESQL;
	long curCol;
	long curRow;
	bool bFlagModify; //用于行修改标志，如果有单元格被修改，则置为 True

	CEdit editCtrl;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCostBudget)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void gridRowSum();

	// Generated message map functions
	//{{AFX_MSG(CCostBudget)
	virtual BOOL OnInitDialog();
	afx_msg void OnQuery();
	afx_msg void OnDblClickMshflexgrid1();
	virtual void OnOK();
	afx_msg void OnSelchangeComboYear();
	afx_msg void OnSelchangeComboType();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COSTBUDGET_H__32DB9224_9C1F_4DB5_AA4F_142673F49FFE__INCLUDED_)
