#if !defined(AFX_ROBOLANGMAP_H__F54358C2_5B21_4E73_9B78_14BB9215B2DA__INCLUDED_)
#define AFX_ROBOLANGMAP_H__F54358C2_5B21_4E73_9B78_14BB9215B2DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RobolangMap.h : header file
//

#include "..\mapui\RoboMapUI.h"

/////////////////////////////////////////////////////////////////////////////
// CRobolangMap window

class CRobolangMap : public CView , public IRoboMapWindow
{
// Construction
public:
	CRobolangMap();
	DECLARE_DYNCREATE( CRobolangMap );

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRobolangMap)
	void OnDraw( CDC *dc );
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRobolangMap();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRobolangMap)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROBOLANGMAP_H__F54358C2_5B21_4E73_9B78_14BB9215B2DA__INCLUDED_)
