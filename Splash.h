#if !defined(AFX_SPLASH_H__2EFFA290_3C76_481F_85B5_6A81DD1996DA__INCLUDED_)
#define AFX_SPLASH_H__2EFFA290_3C76_481F_85B5_6A81DD1996DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Splash.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSplash dialog
#include "progressEx.h"

class CSplash : public CDialog
{
// Construction
public:
	static UINT schedule(LPVOID ps);
	HBITMAP hbmp;
	BITMAP bmp;
	UINT timer_count;
	bool ConnectFlag;
	CSplash(CWnd* pParent = NULL);   // standard constructor
	CBitmap m_bitmap;
	static UINT  ConnectData(LPVOID ps);

// Dialog Data
	//{{AFX_DATA(CSplash)
	enum { IDD = IDD_DIALOG_SPLASH };
	CProgressEx	m_progress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplash)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSplash)
	virtual BOOL OnInitDialog();
	virtual void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLASH_H__2EFFA290_3C76_481F_85B5_6A81DD1996DA__INCLUDED_)
