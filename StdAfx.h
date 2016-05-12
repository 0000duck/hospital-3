// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__C44411B7_D813_4A2B_B285_6E084B14C7FD__INCLUDED_)
#define AFX_STDAFX_H__C44411B7_D813_4A2B_B285_6E084B14C7FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#undef   WINVER    

#define   WINVER   0X5000
   


#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#import "c:\program files\common files\system\ado\msado15.dll" no_namespace rename("EOF","adoEOF")
#include "icrsint.h"
#endif // _AFX_NO_AFXCMN_SUPPORT


struct logon_information{
	CString user;
	CString kfmc;
	CString kfbm;
	CString job;
	CString user_code;
	char path[MAX_PATH];
};
extern logon_information LoginInformation;
extern _ConnectionPtr HospitalConnect;
extern _RecordsetPtr recSet;
const COLORREF LSQ_RED=RGB(255,0,0),LSQ_BACKCOLOR=RGB(192,192,192);
const COLORREF LSQ_BLUE=RGB(0,0,255),LSQ_BLUE2=RGB(0,128,255),LSQ_BLUE3=RGB(0,64,128);
const COLORREF LSQ_BACKCOLOR2=RGB(172,172,172);
const CString BLANKSTR("");
const long HEADER_ROW=0;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


#endif // !defined(AFX_STDAFX_H__C44411B7_D813_4A2B_B285_6E084B14C7FD__INCLUDED_)
