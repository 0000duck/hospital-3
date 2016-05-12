//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_FORMGHLIST_DEL_H__3491706D_1DD8_41AA_BDC3_07707106E39B__INCLUDED_)
#define AFX_FORMGHLIST_DEL_H__3491706D_1DD8_41AA_BDC3_07707106E39B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FormGhList_del.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFormGhList_del form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CFormGhList_del : public CFormView
{
protected:
	CFormGhList_del();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CFormGhList_del)

// Form Data
public:
	//{{AFX_DATA(CFormGhList_del)
	enum { IDD = IDD_FORM_GHLIST_DEL };
	CMSHFlexGrid	m_grid;
	//}}AFX_DATA

// Attributes
public:
	CFont fontTitle;
	CString TITLE;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormGhList_del)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CFormGhList_del();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CFormGhList_del)
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDblClickMshflexgrid1();
	afx_msg void OnClickMshflexgrid1();
	afx_msg void OnMenuitemReportExcel();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMGHLIST_DEL_H__3491706D_1DD8_41AA_BDC3_07707106E39B__INCLUDED_)
