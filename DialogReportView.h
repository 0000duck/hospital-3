//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#include "qiuXpbutton.h"
#if !defined(AFX_DIALOGREPORTVIEW_H__39B9BE34_6825_42F3_A4A7_AFDB11A6BB9F__INCLUDED_)
#define AFX_DIALOGREPORTVIEW_H__39B9BE34_6825_42F3_A4A7_AFDB11A6BB9F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogReportView.h : header file
//
// 收费员 分类收费 汇总表
/////////////////////////////////////////////////////////////////////////////
// CDialogReportView dialog

class CDialogReportView : public CDialog
{
// Construction
public:
	CString strYB;
	static UINT ReportView(LPVOID p);
	CDialogReportView(CWnd* pParent = NULL);   // standard constructor
	CStringArray saRy;
// Dialog Data
	//{{AFX_DATA(CDialogReportView)
	enum { IDD = IDD_DIALOG_REPORT_VIEW };
	CQiuXpButton	m_BT4;
	CComboBox	m_ry;
	CQiuXpButton	m_BT3;
	CQiuXpButton	m_BT2;
	CQiuXpButton	m_BT1;
	COleDateTime	m_date1;
	COleDateTime	m_date2;
	CMSHFlexGrid	m_grid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogReportView)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogReportView)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnToexcel();
	afx_msg void OnYb();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGREPORTVIEW_H__39B9BE34_6825_42F3_A4A7_AFDB11A6BB9F__INCLUDED_)
