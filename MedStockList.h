//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#include "editFlat.h"
#include "qiuXpButton.h"
#include "comboxEx.h"
#if !defined(AFX_MEDSTOCKLIST_H__99564F32_62EE_47A0_ACD7_1CA681BA6781__INCLUDED_)
#define AFX_MEDSTOCKLIST_H__99564F32_62EE_47A0_ACD7_1CA681BA6781__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MedStockList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMedStockList dialog

class CMedStockList : public CDialog
{
// Construction
public:
	CString strSelKfName;
	CString strSelKF;
	UINT flagMoveKF;
	CBrush brushBack;
	CRect r1;
	long curRow;
	CMedStockList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMedStockList)
	enum { IDD = IDD_MED_STOCKLIST };
	CEditFlat	c_message;
	CEditFlat	c_py;
	CMSHFlexGrid	m_grid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMedStockList)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMedStockList)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnChangeEditPy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDblClickMshflexgrid1();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEDSTOCKLIST_H__99564F32_62EE_47A0_ACD7_1CA681BA6781__INCLUDED_)
