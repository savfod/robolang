// robolangView.h : interface of the CRobolangView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROBOLANGVIEW_H__1DFBC0A7_4636_4379_BFC3_5B65A5B53E3A__INCLUDED_)
#define AFX_ROBOLANGVIEW_H__1DFBC0A7_4636_4379_BFC3_5B65A5B53E3A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CRobolangView : public CView
{
protected: // create from serialization only
	CRobolangView();
	DECLARE_DYNCREATE(CRobolangView)

// Attributes
public:
	CRobolangDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRobolangView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRobolangView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	CRobolangSplitter splitter;

// Generated message map functions
protected:
	//{{AFX_MSG(CRobolangView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in robolangView.cpp
inline CRobolangDoc* CRobolangView::GetDocument()
   { return (CRobolangDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROBOLANGVIEW_H__1DFBC0A7_4636_4379_BFC3_5B65A5B53E3A__INCLUDED_)
