//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_COSTCLASSA_H__5E11CD3E_C3A7_4097_B3A1_43CF8B6CAD18__INCLUDED_)
#define AFX_COSTCLASSA_H__5E11CD3E_C3A7_4097_B3A1_43CF8B6CAD18__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CostClassA.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCostClassA dialog

class CCostClassA : public CDialog
{
// Construction
public:
	CCostClassA(CWnd* pParent = NULL);   // standard constructor
	enum { GRID_HEADER_ID=17,SQL_QUERY_ID=26,
		GRID_ID=1,GRID_NAME,GRID_SEQ,GRID_EFFECT,GRID_CMT};
// Dialog Data
	//{{AFX_DATA(CCostClassA)
	enum { IDD = IDD_DIALOG_CLASS_A };
	CMSHFlexGrid	m_grid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCostClassA)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCostClassA)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClickMshflexgrid1();
	afx_msg void OnMenuCostAdd();
	afx_msg void OnMenuCostModify();
	afx_msg void OnMenuCostDel();
	afx_msg void OnMenuCostRestore();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COSTCLASSA_H__5E11CD3E_C3A7_4097_B3A1_43CF8B6CAD18__INCLUDED_)
