#if !defined(AFX_MEDCODEMODIFY_H__A66A87DC_24B4_4EEB_B27D_E84E6F24CDF6__INCLUDED_)
#define AFX_MEDCODEMODIFY_H__A66A87DC_24B4_4EEB_B27D_E84E6F24CDF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MedcodeModify.h : header file
//
#include "medcode.h"
/////////////////////////////////////////////////////////////////////////////
// CMedcodeModify dialog

class CMedcodeModify : public CDialog
{
// Construction
public:
	CMedcodeModify(CWnd* pParent = NULL);   // standard constructor
	CMedcode * ptrMedcode;
	CString strBM,strSql;

	CStringArray arrayItem,arrayItem3,arrayItem2;

// Dialog Data
	//{{AFX_DATA(CMedcodeModify)
	enum { IDD = IDD_DIALOG_MED_CODE_MODIFY };
	CComboBox	m_combo2;
	CComboBox	m_combo1;
	CComboBox	m_comboType;
	CString	m_bz;
	CString	m_dw;
	CString	m_gg;
	CString	m_maxkc;
	CString	m_mc;
	CString	m_minkc;
	CString	m_py;
	//}}AFX_DATA

	enum{ DLBM=0,XLBM,BM,MC,GG,DW,PY,MAXKC,MINKC,L_TYPE,BZ };
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMedcodeModify)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

	CFont fontTitle;
protected:

	// Generated message map functions
	//{{AFX_MSG(CMedcodeModify)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnSelchangeCombo1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEDCODEMODIFY_H__A66A87DC_24B4_4EEB_B27D_E84E6F24CDF6__INCLUDED_)
