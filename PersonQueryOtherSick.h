// PersonQueryOtherSick.h: interface for the CPersonQueryOtherSick class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PERSONQUERYOTHERSICK_H__A1AFDC5C_1C09_4875_B39C_E3A52F03F681__INCLUDED_)
#define AFX_PERSONQUERYOTHERSICK_H__A1AFDC5C_1C09_4875_B39C_E3A52F03F681__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PersonQuery.h"

class CPersonQueryOtherSick : public CPersonQuery  
{
public:
	void OnDblClickMshflexgrid1();
	void OnOK();
	BOOL OnInitDialog();
	CPersonQueryOtherSick();
	virtual ~CPersonQueryOtherSick();

};

#endif // !defined(AFX_PERSONQUERYOTHERSICK_H__A1AFDC5C_1C09_4875_B39C_E3A52F03F681__INCLUDED_)
