// PersonQueryJMTC.h: interface for the CPersonQueryJMTC class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PERSONQUERYJMTC_H__4D63A0E7_411F_4859_8159_F6EB76FFEED2__INCLUDED_)
#define AFX_PERSONQUERYJMTC_H__4D63A0E7_411F_4859_8159_F6EB76FFEED2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PersonQueryQpyb.h"

class CPersonQueryJMTC : public CPersonQueryQpyb  
{
public:
	enum{ SQL_ID=19};
	void OnOK();
	CPersonQueryJMTC();
	virtual ~CPersonQueryJMTC();

};

#endif // !defined(AFX_PERSONQUERYJMTC_H__4D63A0E7_411F_4859_8159_F6EB76FFEED2__INCLUDED_)
