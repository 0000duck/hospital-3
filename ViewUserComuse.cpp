// ViewUserComuse.cpp: implementation of the CViewUserComuse class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his3.h"
#include "ViewUserComuse.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CViewUserComuse::CViewUserComuse()
{

}

CViewUserComuse::~CViewUserComuse()
{

}

void CViewUserComuse::OnOK()
{

}

BOOL CViewUserComuse::OnInitDialog()
{
	CSickGetMedView::OnInitDialog();
	GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDOK)->EnableWindow(false);
	return true;
}
