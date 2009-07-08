#if !defined(AFX_ROBOLANGEDITWINDOW_H__5848CC7C_CCB0_4541_93B6_9DD6140B7F5C__INCLUDED_)
#define AFX_ROBOLANGEDITWINDOW_H__5848CC7C_CCB0_4541_93B6_9DD6140B7F5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RobolangEditWindow.h : header file
//

#include "..\Program\Command.h"
#include "..\ProgramUI\ProgramUI.h"

/////////////////////////////////////////////////////////////////////////////
// CRobolangEditWindow window

class CRobolangEditWindow : public CListView , public IEditWindow
{
// Construction
public:
	CRobolangEditWindow();
	DECLARE_DYNCREATE( CRobolangEditWindow );

// Operations
public:
	void addCommand( CCommand *command );
	void removeAllCommands();

private:
	int addCommand( int pos , CCommand *command, int depth );
	void adjustLastColumnWidth();

	void addItem( int pos , CString robot , CString command , int depth , void *data );
	int hitTest( int& subItem );
	CString addTabulations( const CString string, int tabulationCount );

	void startSelectRobot( int item );

	CCommand *getCommand( int item );
	CCommand *insertCommand( int item );

// windows stuff
private:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRobolangEditWindow)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRobolangEditWindow();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRobolangEditWindow)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROBOLANGEDITWINDOW_H__5848CC7C_CCB0_4541_93B6_9DD6140B7F5C__INCLUDED_)
