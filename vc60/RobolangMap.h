#if !defined(AFX_ROBOLANGMAP_H__F54358C2_5B21_4E73_9B78_14BB9215B2DA__INCLUDED_)
#define AFX_ROBOLANGMAP_H__F54358C2_5B21_4E73_9B78_14BB9215B2DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RobolangMap.h : header file
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
// CRobolangMap window

class CRobolangMap : public CView , public IRoboMapWindow
{
// Construction
public:
	CRobolangMap();
	DECLARE_DYNCREATE( CRobolangMap );

// Attributes
public:
private:
	
	CPoint startPoint;
	CSize wallH; // horizontal
	CSize wallV; // vertical
	CSize wallC; // wall in corner
	CSize cell;
	CString capturedRobot;
// Operations
public:
	void identificatePoint( CPoint point, Location &resLoc, LocationType &resType );

	virtual void updateMap();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRobolangMap)
	virtual void OnDraw( CDC *dc );
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRobolangMap();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRobolangMap)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROBOLANGMAP_H__F54358C2_5B21_4E73_9B78_14BB9215B2DA__INCLUDED_)
