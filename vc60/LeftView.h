// LeftView.h : interface of the CLeftView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEFTVIEW_H__336327CB_1B7B_4BF4_A449_8AD5653D9F7C__INCLUDED_)
#define AFX_LEFTVIEW_H__336327CB_1B7B_4BF4_A449_8AD5653D9F7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRobolangDoc;

class CLeftView : public CTreeView
{
protected: // create from serialization only
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

// Attributes
public:
	CRobolangDoc* GetDocument();

// Operations
public:
	void removeProcedures();
	void addProcedure( CProcedure *p );

private:
	HTREEITEM addItem( HTREEITEM parent , CString name , int type );
	HTREEITEM getProceduresItem();
	int getItemType( HTREEITEM item );
	HTREEITEM getCurrentItem();
	CProcedure *getProcedure( HTREEITEM item );

public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeftView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLeftView)
	afx_msg void OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCmdprocAdd();
	afx_msg void OnUpdateCmdprocAdd(CCmdUI* pCmdUI);
	afx_msg void OnCmdprocChange();
	afx_msg void OnUpdateCmdprocChange(CCmdUI* pCmdUI);
	afx_msg void OnCmdprocDelete();
	afx_msg void OnUpdateCmdprocDelete(CCmdUI* pCmdUI);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in LeftView.cpp
inline CRobolangDoc* CLeftView::GetDocument()
   { return (CRobolangDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEFTVIEW_H__336327CB_1B7B_4BF4_A449_8AD5653D9F7C__INCLUDED_)
