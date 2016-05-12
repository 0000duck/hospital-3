// his3Doc.h : interface of the CHis3Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HIS3DOC_H__74BD71A0_6F46_47F7_9C27_266DBCEC4DF5__INCLUDED_)
#define AFX_HIS3DOC_H__74BD71A0_6F46_47F7_9C27_266DBCEC4DF5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHis3Doc : public CDocument
{
protected: // create from serialization only
	CHis3Doc();
	DECLARE_DYNCREATE(CHis3Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHis3Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHis3Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHis3Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HIS3DOC_H__74BD71A0_6F46_47F7_9C27_266DBCEC4DF5__INCLUDED_)
