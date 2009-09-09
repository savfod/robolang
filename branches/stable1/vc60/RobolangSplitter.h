#if !defined(AFX_ROBOLANGSPLITTER_H__39FD6FE3_D63E_4707_AB7A_910E26EFBBDF__INCLUDED_)
#define AFX_ROBOLANGSPLITTER_H__39FD6FE3_D63E_4707_AB7A_910E26EFBBDF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RobolangSplitter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRobolangSplitter frame with splitter

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CRobolangEditWindow;
class CRobolangMapWindow;

class CRobolangSplitter : public CSplitterWnd
{
public:
	CRobolangSplitter();           // protected constructor used by dynamic creation

// Attributes
protected:
	CRobolangEditWindow *editPane;
	CRobolangMapWindow *mapPane;

// Operations
public:
	BOOL Create( CWnd *parent , LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRobolangSplitter)
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRobolangSplitter();

	// Generated message map functions
	//{{AFX_MSG(CRobolangSplitter)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROBOLANGSPLITTER_H__39FD6FE3_D63E_4707_AB7A_910E26EFBBDF__INCLUDED_)
