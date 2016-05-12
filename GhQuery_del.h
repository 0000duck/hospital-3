// GhQuery_del.h: interface for the CGhQuery_del class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GHQUERY_DEL_H__A27B2CAE_E0A1_4FE8_8BFE_83BAD819EFFD__INCLUDED_)
#define AFX_GHQUERY_DEL_H__A27B2CAE_E0A1_4FE8_8BFE_83BAD819EFFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GhQuery.h"

class CGhQuery_del : public CGhQuery  
{
public:
	static UINT Query(LPVOID ps);
	void OnOK();
	CGhQuery_del();
	virtual ~CGhQuery_del();

};

#endif // !defined(AFX_GHQUERY_DEL_H__A27B2CAE_E0A1_4FE8_8BFE_83BAD819EFFD__INCLUDED_)
