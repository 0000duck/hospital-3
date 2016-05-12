// DialogUseAllQuery.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "DialogUseAllQuery.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogUseAllQuery dialog


CDialogUseAllQuery::CDialogUseAllQuery(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogUseAllQuery::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogUseAllQuery)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogUseAllQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogUseAllQuery)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogUseAllQuery, CDialog)
	//{{AFX_MSG_MAP(CDialogUseAllQuery)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogUseAllQuery message handlers
