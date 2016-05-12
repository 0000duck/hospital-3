// PersonQueryHayb.h: interface for the CPersonQueryHayb class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PERSONQUERYHAYB_H__DF91561B_DC5A_4314_BDDB_F81BC9F111E1__INCLUDED_)
#define AFX_PERSONQUERYHAYB_H__DF91561B_DC5A_4314_BDDB_F81BC9F111E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PersonQueryQpyb.h"

class CPersonQueryHayb : public CPersonQueryQpyb  
{
public:
	enum{ SQL_ID=19};
	void OnOK();
	CPersonQueryHayb();
	virtual ~CPersonQueryHayb();

};

#endif // !defined(AFX_PERSONQUERYHAYB_H__DF91561B_DC5A_4314_BDDB_F81BC9F111E1__INCLUDED_)
