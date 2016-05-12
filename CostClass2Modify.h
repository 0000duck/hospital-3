// CostClass2Modify.h: interface for the CCostClass2Modify class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COSTCLASS2MODIFY_H__B2FFA133_7C50_45EA_B462_8FACD235F885__INCLUDED_)
#define AFX_COSTCLASS2MODIFY_H__B2FFA133_7C50_45EA_B462_8FACD235F885__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CostClass2Add.h"

class CCostClass2Modify : public CCostClass2Add  
{
public:
	void OnOK();
	BOOL OnInitDialog();
	CCostClass2Modify();
	virtual ~CCostClass2Modify();
	UINT m_id,m_aid,iSeq;
	CString strName,strRem;
};

#endif // !defined(AFX_COSTCLASS2MODIFY_H__B2FFA133_7C50_45EA_B462_8FACD235F885__INCLUDED_)
