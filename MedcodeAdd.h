// MedcodeAdd.h: interface for the CMedcodeAdd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEDCODEADD_H__1A6B0DAD_F969_434E_A185_C35FCADF76FF__INCLUDED_)
#define AFX_MEDCODEADD_H__1A6B0DAD_F969_434E_A185_C35FCADF76FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MedcodeModify.h"

class CMedcodeAdd : public CMedcodeModify  
{
public:
	void OnSelchangeCombo1();
	void OnOK();
	BOOL OnInitDialog();
	CMedcodeAdd();
	virtual ~CMedcodeAdd();
private:
	CStringArray arrayItem1;


};

#endif // !defined(AFX_MEDCODEADD_H__1A6B0DAD_F969_434E_A185_C35FCADF76FF__INCLUDED_)
