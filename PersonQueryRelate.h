// PersonQueryRelate.h: interface for the CPersonQueryRelate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PERSONQUERYRELATE_H__813A88A3_D651_424E_8913_0679437A72A8__INCLUDED_)
#define AFX_PERSONQUERYRELATE_H__813A88A3_D651_424E_8913_0679437A72A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PersonQuery.h"

class CPersonQueryRelate : public CPersonQuery  
{
public:
	void OnDblClickMshflexgrid1();
	void OnOK();
	BOOL OnInitDialog();
	CPersonQueryRelate();
	virtual ~CPersonQueryRelate();

};

#endif // !defined(AFX_PERSONQUERYRELATE_H__813A88A3_D651_424E_8913_0679437A72A8__INCLUDED_)
