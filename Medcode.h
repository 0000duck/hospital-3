//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_MEDCODE_H__7A218AAF_58C8_4F9F_9A5F_BEAE0CA46D52__INCLUDED_)
#define AFX_MEDCODE_H__7A218AAF_58C8_4F9F_9A5F_BEAE0CA46D52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Medcode.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMedcode dialog

class CMedcode : public CDialog
{
// Construction
public:
	CMedcode(CWnd* pParent = NULL);   // standard constructor
	enum { SQLID= 37,COL_ID=24 ,SQLID2=38,FIRST_ITEM=0, SECOND_ITEM=1,SQLID3=39 ,
	BM_POS=4 };
// Dialog Data
	//{{AFX_DATA(CMedcode)
	enum { IDD = IDD_DIALOG_MED_CODE };
	CComboBox	m_combo2;
	CComboBox	m_combo1;
	CString	m_bm;
	CString	m_py;
	CMSHFlexGrid	m_grid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMedcode)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
public:
	CStringArray typeCode,typeCode_1;
	CString strSql;
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMedcode)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombo1();
	virtual void OnOK();
	afx_msg void OnModify();
	afx_msg void OnAdd();
	afx_msg void OnMenuitemBcybZjb();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEDCODE_H__7A218AAF_58C8_4F9F_9A5F_BEAE0CA46D52__INCLUDED_)
