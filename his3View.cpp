// his3View.cpp : implementation of the CHis3View class
//

#include "stdafx.h"
#include "his3.h"

#include "his3Doc.h"
#include "his3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHis3View

IMPLEMENT_DYNCREATE(CHis3View, CView)

BEGIN_MESSAGE_MAP(CHis3View, CView)
	//{{AFX_MSG_MAP(CHis3View)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHis3View construction/destruction

CHis3View::CHis3View()
{
	// TODO: add construction code here

}

CHis3View::~CHis3View()
{
}

BOOL CHis3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CHis3View drawing

void CHis3View::OnDraw(CDC* pDC)
{
	CHis3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CHis3View printing

BOOL CHis3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CHis3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CHis3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CHis3View diagnostics

#ifdef _DEBUG
void CHis3View::AssertValid() const
{
	CView::AssertValid();
}

void CHis3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHis3Doc* CHis3View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHis3Doc)));
	return (CHis3Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHis3View message handlers
