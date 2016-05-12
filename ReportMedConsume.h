//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_REPORTMEDCONSUME_H__024BE60E_159A_406C_A1FE_971AEAE4D4F9__INCLUDED_)
#define AFX_REPORTMEDCONSUME_H__024BE60E_159A_406C_A1FE_971AEAE4D4F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportMedConsume.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReportMedConsume form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CReportMedConsume : public CFormView
{
protected:
	CReportMedConsume();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CReportMedConsume)

// Form Data
public:
	//{{AFX_DATA(CReportMedConsume)
	enum { IDD = IDD_FORM_MED_CONSUME };
	CMSHFlexGrid	m_grid;
	//}}AFX_DATA

// Attributes
public:
	CFont fontTitle;
	CString TITLE;
	enum{ COL_ID=28 };

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportMedConsume)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CReportMedConsume();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CReportMedConsume)
	afx_msg void OnDestroy();
	afx_msg void OnDblClickMshflexgrid1();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTMEDCONSUME_H__024BE60E_159A_406C_A1FE_971AEAE4D4F9__INCLUDED_)
