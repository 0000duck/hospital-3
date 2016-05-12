// SickGetMedView.h: interface for the CSickGetMedView class.
//* 设计:	2008/11/1	凌绍清
//* 用于显示待取药列表,点击保存后将发药员的代号及名字存放
//* 挂号列表单中
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SICKGETMEDVIEW_H__BE6B7065_1493_495F_8AD7_4D22189FA8C0__INCLUDED_)
#define AFX_SICKGETMEDVIEW_H__BE6B7065_1493_495F_8AD7_4D22189FA8C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DialogHjSf.h"
#include "comFunc.H"

class CSickGetMedView : public CDialogHjSf  
{
public:
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	BOOL PreTranslateMessage(MSG* pMsg);
	void OnOK();
	BOOL OnInitDialog();
	CSickGetMedView();
	virtual ~CSickGetMedView();
	CString DANJUHAO;
	CString GHTYPE;

	
	DECLARE_EVENTSINK_MAP()
	DECLARE_MESSAGE_MAP()

private:
	void unbundle();
	void InitData();
};

#endif // !defined(AFX_SICKGETMEDVIEW_H__BE6B7065_1493_495F_8AD7_4D22189FA8C0__INCLUDED_)
