// his3View.h : interface of the CHis3View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HIS3VIEW_H__2C742D76_F114_441E_9446_DF88CD60E7FA__INCLUDED_)
#define AFX_HIS3VIEW_H__2C742D76_F114_441E_9446_DF88CD60E7FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHis3View : public CView
{
protected: // create from serialization only
	CHis3View();
	DECLARE_DYNCREATE(CHis3View)

// Attributes
public:
	CHis3Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHis3View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHis3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHis3View)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in his3View.cpp
inline CHis3Doc* CHis3View::GetDocument()
   { return (CHis3Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HIS3VIEW_H__2C742D76_F114_441E_9446_DF88CD60E7FA__INCLUDED_)
