// CostClassAb.h: interface for the CCostClassAb class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COSTCLASSAB_H__3386E41E_8D63_46C6_81F7_95DE15FDF529__INCLUDED_)
#define AFX_COSTCLASSAB_H__3386E41E_8D63_46C6_81F7_95DE15FDF529__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PersonQuery.h"

class CCostClassAb : public CPersonQuery  
{
public:
	void OnMenuCost2Restore();
	void OnMenuCost2Del();
	void OnMenuCost2Modify();
	void OnDblClickMshflexgrid1();
	void OnMenuCost2Add();
	void OnClickMshflexgrid1();
	void OnOK();
	CCostClassAb();
	virtual ~CCostClassAb();
	enum{ COST_A_SQLID=27,GRID_HEADER_ID=18,SQL_QUERY_ID=28
	,COST_B_SQLID=31 };
	enum{ GRID_ID=1,GRID_A_ID=2 /* ¥Û¿‡ID*/,GRID_NAME=4,GRID_ORDER=5,GRID_CMT=7,
	GRID_EFFECT=6 };

protected:
	BOOL OnInitDialog();
};

#endif // !defined(AFX_COSTCLASSAB_H__3386E41E_8D63_46C6_81F7_95DE15FDF529__INCLUDED_)
