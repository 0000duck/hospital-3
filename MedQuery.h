#if !defined(AFX_MEDQUERY_H__AC71A011_BB03_4A4E_BF06_584A826546D4__INCLUDED_)
#define AFX_MEDQUERY_H__AC71A011_BB03_4A4E_BF06_584A826546D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MedQuery.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMedQuery dialog

class CMedQuery : public CDialog
{
// Construction
public:
	static UINT QueryData(LPVOID ps);
	CMedQuery(CWnd* pParent = NULL);   // standard constructor
	enum{ SQLID= 40,MEDQUERYID };
// Dialog Data
	//{{AFX_DATA(CMedQuery)
	enum { IDD = IDD_DIALOG_MEDQUERY };
	CComboBox	m_comboKf;
	CString	m_bm;
	CString	m_mc;
	CString	m_py;
	COleDateTime	m_date;
	BOOL	m_dateFlag;
	//}}AFX_DATA
//private:
	CStringArray arrayItemKf;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMedQuery)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMedQuery)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnExcel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEDQUERY_H__AC71A011_BB03_4A4E_BF06_584A826546D4__INCLUDED_)
