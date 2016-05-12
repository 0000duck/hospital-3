// his3Doc.cpp : implementation of the CHis3Doc class
//

#include "stdafx.h"
#include "his3.h"

#include "his3Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHis3Doc

IMPLEMENT_DYNCREATE(CHis3Doc, CDocument)

BEGIN_MESSAGE_MAP(CHis3Doc, CDocument)
	//{{AFX_MSG_MAP(CHis3Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHis3Doc construction/destruction

CHis3Doc::CHis3Doc()
{
	// TODO: add one-time construction code here

}

CHis3Doc::~CHis3Doc()
{
}

BOOL CHis3Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CHis3Doc serialization

void CHis3Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CHis3Doc diagnostics

#ifdef _DEBUG
void CHis3Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHis3Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHis3Doc commands
