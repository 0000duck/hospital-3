//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#include "dialogWait.h"
#include "personQueryqpyb.h"
#if !defined(AFX_REGISTERGH_H__45187490_5B22_4C1A_B073_51C1B7E540E6__INCLUDED_)
#define AFX_REGISTERGH_H__45187490_5B22_4C1A_B073_51C1B7E540E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RegisterGh.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRegisterGh dialog
// ¹ÒºÅ²Ù×÷

class CRegisterGh : public CDialog
{
// Construction
public:
	CRegisterGh(CWnd* pParent = NULL);   // standard constructor
	CStringArray m_ghTypeArray;
	enum{ GH_NORMAL=0,GH_ADD=1};
	enum{ COL_DANJUHAO=0,COL_SEQ=1,COL_TYPE=2,COL_NAME,COL_SEX,COL_AGE,COL_GHY};

//	enum{ TYPE_QPYB=1,TYPE_HAYB=2,TYPE_JMTC=3,TYPE_BCBX=4,TYPE_GYQS=5,TYPE_GS=6,TYPE_LX=7,TYPE_TY=8,TYPE_GC=9 };

	CString strYbCode,strSql;
	CString strBCBXcode,strGYQScode,strOHTERcode; //²¹³ä±£ÏÕ ¹©ÑøÇ×Êô ±àÂë
// Dialog Data
	//{{AFX_DATA(CRegisterGh)
	enum { IDD = IDD_DIALOG_GH };
	CEdit	m_addr;
	CEdit	m_age;
	CEdit	m_name;
	CComboBox	m_se;
	CEdit	m_kh;
	CComboBox	m_ghType;
	CMSHFlexGrid	m_grid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegisterGh)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	short int ybFlag;

	// Generated message map functions
	//{{AFX_MSG(CRegisterGh)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonCancel();
	afx_msg void OnButtonOk();
	afx_msg void OnSelchangeComboGhType();
	afx_msg void OnButtonAdd();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnButtonGridDel();
	afx_msg void OnDblClickMshflexgrid1();
	afx_msg void OnButtonQuery();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void queryAccount();
	bool queryHayb();
	void computeRowView();
	void QueryGh();
	void clearView();
	bool queryPerson();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGISTERGH_H__45187490_5B22_4C1A_B073_51C1B7E540E6__INCLUDED_)
