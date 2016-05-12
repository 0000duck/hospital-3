//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#include "comFunc.h"
#if !defined(AFX_EXESLIST_H__8A62D411_C98A_4FB3_8D90_C0BE5D87A243__INCLUDED_)
#define AFX_EXESLIST_H__8A62D411_C98A_4FB3_8D90_C0BE5D87A243__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExesList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExesList dialog
// 治疗费列表,供前端用户划价选择

class CExesList : public CDialog
{
// Construction
public:
	CExesList(CWnd* pParent = NULL);   // standard constructor
	enum{ EXES_COLS=3 };
// Dialog Data
	//{{AFX_DATA(CExesList)
	enum { IDD = IDD_DIALOG_OTHER_EXES };
	CComboBox	m_type;
	CMSHFlexGrid	m_dst;
	CMSHFlexGrid	m_src;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExesList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CExesList)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboType();
	afx_msg void OnButtonAAdd();
	afx_msg void OnButtonADel();
	afx_msg void OnButtonSAdd();
	afx_msg void OnButtonSDel();
	afx_msg void OnDblClickMshflexgridDst();
	afx_msg void OnDblClickMshflexgridSrc();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SetGridHead();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXESLIST_H__8A62D411_C98A_4FB3_8D90_C0BE5D87A243__INCLUDED_)
