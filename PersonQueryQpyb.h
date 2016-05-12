// PersonQueryQpyb.h: interface for the CPersonQueryQpyb class.
//* 清浦医保人员列表查询
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PERSONQUERYQPYB_H__0B8F63FB_3007_44BE_9F37_FB5FE95B101F__INCLUDED_)
#define AFX_PERSONQUERYQPYB_H__0B8F63FB_3007_44BE_9F37_FB5FE95B101F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PersonQuery.h"
#include "comFunc.h"

class CPersonQueryQpyb : public CPersonQuery  
{
public:
	enum{ GRID_ID=13,SQL_ID =18 };
	void OnDblClickMshflexgrid1();
	void OnOK();
	BOOL OnInitDialog();
	CPersonQueryQpyb();
	virtual ~CPersonQueryQpyb();

};

#endif // !defined(AFX_PERSONQUERYQPYB_H__0B8F63FB_3007_44BE_9F37_FB5FE95B101F__INCLUDED_)
