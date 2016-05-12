//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#include "registerGh.h"
#if !defined(AFX_PERSONQUERY_H__B403D974_0757_461C_8EAE_5F7740875899__INCLUDED_)
#define AFX_PERSONQUERY_H__B403D974_0757_461C_8EAE_5F7740875899__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PersonQuery.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPersonQuery dialog

class CPersonQuery : public CDialog
{
// Construction
public:
	CPersonQuery(CWnd* pParent = NULL);   // standard constructor
	CStringArray arrayDepart;
	CString strTYPE; //作为控件传入内部类别说明
	LPVOID lp;
// Dialog Data
	//{{AFX_DATA(CPersonQuery)
	enum { IDD = IDD_DIALOG_PERSON_QUERY };
	CEdit	m_mc;
	CEdit	m_id;
	CComboBox	m_depart;
	CMSHFlexGrid	m_grid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPersonQuery)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPersonQuery)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	virtual void OnChangeEditId();
	virtual void OnChangeEditMc();
	afx_msg void OnSelchangeCombo1();
	virtual void OnDblClickMshflexgrid1();
	virtual void OnClickMshflexgrid1();
	virtual void OnMenuCost2Add();
	virtual void OnMenuCost2Del();
	virtual void OnMenuCost2Modify();
	virtual void OnMenuCost2Restore();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PERSONQUERY_H__B403D974_0757_461C_8EAE_5F7740875899__INCLUDED_)
