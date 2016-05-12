// CostClassAmodify.h: interface for the CCostClassAmodify class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COSTCLASSAMODIFY_H__23F96D01_9C8B_4D03_B0DB_0CC3EB55EA2C__INCLUDED_)
#define AFX_COSTCLASSAMODIFY_H__23F96D01_9C8B_4D03_B0DB_0CC3EB55EA2C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CostClassAadd.h"

class CCostClassAmodify : public CCostClassAadd  
{
public:
	void OnOK();
	UINT m_id;
	BOOL OnInitDialog();
	CCostClassAmodify();
	virtual ~CCostClassAmodify();

};

#endif // !defined(AFX_COSTCLASSAMODIFY_H__23F96D01_9C8B_4D03_B0DB_0CC3EB55EA2C__INCLUDED_)
