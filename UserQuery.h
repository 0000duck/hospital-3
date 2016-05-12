// UserQuery.h: interface for the CUserQuery class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USERQUERY_H__8A5B98FC_6586_45F8_A935_4DDED69BAEFC__INCLUDED_)
#define AFX_USERQUERY_H__8A5B98FC_6586_45F8_A935_4DDED69BAEFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PersonQuery.h"
#include "ghQuery.h"
/*
// 医院操作人员查询
//
*/
class CUserQuery : public CPersonQuery  
{
public:
	int sfyORys;
	void OnDblClickMshflexgrid1();
	void OnChangeEditMc();
	void OnChangeEditId();
	void OnOK();
	BOOL OnInitDialog();
	CUserQuery();
	virtual ~CUserQuery();

};

#endif // !defined(AFX_USERQUERY_H__8A5B98FC_6586_45F8_A935_4DDED69BAEFC__INCLUDED_)
