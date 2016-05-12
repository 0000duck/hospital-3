//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_DIALOGSICKGETMED_H__560E69FC_5483_4B0F_9DB2_DB40633EA567__INCLUDED_)
#define AFX_DIALOGSICKGETMED_H__560E69FC_5483_4B0F_9DB2_DB40633EA567__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogSickGetMed.h : header file
//
#include "qiuXpButton.H"
/////////////////////////////////////////////////////////////////////////////
// CDialogSickGetMed dialog

class CDialogSickGetMed : public CDialog
{
// Construction
public:
	CDialogSickGetMed(CWnd* pParent = NULL);   // standard constructor
	enum { DANJUHAO_COL=1 };

	// Dialog Data
	//{{AFX_DATA(CDialogSickGetMed)
	enum { IDD = IDD_DIALOG_GETMED };
	CQiuXpButton	m_BT2;
	CQiuXpButton	m_BT1;
	CMSHFlexGrid	m_grid;
	//}}AFX_DATA



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogSickGetMed)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogSickGetMed)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnDblClickMshflexgrid1();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGSICKGETMED_H__560E69FC_5483_4B0F_9DB2_DB40633EA567__INCLUDED_)
