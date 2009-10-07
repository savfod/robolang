#if !defined(AFX_RobolangMapWindow_H__F54358C2_5B21_4E73_9B78_14BB9215B2DA__INCLUDED_)
#define AFX_RobolangMapWindow_H__F54358C2_5B21_4E73_9B78_14BB9215B2DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RobolangMapWindow.h : header file
//

#include "..\mapui\RoboMapUI.h"
#include "..\map\RoboMap.h"

typedef enum {
	TYPE_UNKNOWN = 0 ,
	TYPE_INWALLC = 1 ,
	TYPE_INWALLH = 2 ,
	TYPE_INWALLV = 3 ,
	TYPE_INCELL = 4 ,
	TYPE_OUTOFMAP = 5
} LocationType;

/////////////////////////////////////////////////////////////////////////////
// CRobolangMapWindow window

class CRobolangMapWindow : public CView , public IRoboMapWindow
{
// Construction
public:
	CRobolangMapWindow();
	DECLARE_DYNCREATE( CRobolangMapWindow );

// Attributes
public:
private:
	
	CPoint startPoint;
	CSize wallH; // horizontal
	CSize wallV; // vertical
	CSize wallC; // wall in corner
	CSize cell;
	CRect rcMap;
	CString capturedRobot;
// Operations
public:
	void identificatePoint( CPoint point, Location &resLoc, LocationType &resType );

	virtual void updateMap();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRobolangMapWindow)
	public:
	virtual void OnDraw( CDC *dc );
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRobolangMapWindow();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRobolangMapWindow)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RobolangMapWindow_H__F54358C2_5B21_4E73_9B78_14BB9215B2DA__INCLUDED_)
