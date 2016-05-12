//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#include "comFunc.h"
#if !defined(AFX_DIALOGACCOUNTQUERY_H__F3938574_AE89_403C_B790_B9D4D5EB8620__INCLUDED_)
#define AFX_DIALOGACCOUNTQUERY_H__F3938574_AE89_403C_B790_B9D4D5EB8620__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogAccountQuery.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogAccountQuery dialog

class CDialogAccountQuery : public CDialog
{
// Construction
public:
	CDialogAccountQuery(CWnd* pParent = NULL);   // standard constructor
	CStringArray typeArray;
	enum{GRID_COLS= 6,KH_COL=0,BM_COL=1,XM_COL=2,YE_COL=3 };
	enum{ CHANGE_MAX_KH=5,CHANGE_MAX_XM=2};
// Dialog Data
	//{{AFX_DATA(CDialogAccountQuery)
	enum { IDD = IDD_DIALOG_ACCOUNT_QUERY };
	CComboBox	m_type;
	CMSHFlexGrid	m_grid;
	CString	m_xm;
	CString	m_kh;
	CMSHFlexGrid	m_grid2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogAccountQuery)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogAccountQuery)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnChangeEditQkh();
	afx_msg void OnChangeEditKxm();
	afx_msg void OnDblClickMshflexgrid1();
	afx_msg void OnDblClickMshflexgrid2();
	afx_msg void OnAdd();
	afx_msg void OnSelchangeComboType();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SetGridHead(CMSHFlexGrid &grid);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGACCOUNTQUERY_H__F3938574_AE89_403C_B790_B9D4D5EB8620__INCLUDED_)
