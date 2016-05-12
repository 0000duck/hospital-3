// DepartSet.h: interface for the CDepartSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEPARTSET_H__D8ACFCFC_0367_4B72_AFDE_3E595E981282__INCLUDED_)
#define AFX_DEPARTSET_H__D8ACFCFC_0367_4B72_AFDE_3E595E981282__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PrivilegeQuota.h"

class CDepartSet : public CPrivilegeQuota  
{
public:
	void OnAdd();
	void OnOK();
	BOOL OnInitDialog();
	CDepartSet();
	virtual ~CDepartSet();
	enum{ GRID_HEADER_ID=14};

};

#endif // !defined(AFX_DEPARTSET_H__D8ACFCFC_0367_4B72_AFDE_3E595E981282__INCLUDED_)
