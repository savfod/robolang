// robolangDoc.h : interface of the CRobolangDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROBOLANGDOC_H__B8F42106_519E_485C_8940_2A0F6AF42D00__INCLUDED_)
#define AFX_ROBOLANGDOC_H__B8F42106_519E_485C_8940_2A0F6AF42D00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CRobolangDoc : public CDocument
{
protected: // create from serialization only
	CRobolangDoc();
	DECLARE_DYNCREATE(CRobolangDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRobolangDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRobolangDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRobolangDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROBOLANGDOC_H__B8F42106_519E_485C_8940_2A0F6AF42D00__INCLUDED_)
