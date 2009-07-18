#if !defined(AFX_ROBOLANGEDITWINDOW_H__5848CC7C_CCB0_4541_93B6_9DD6140B7F5C__INCLUDED_)
#define AFX_ROBOLANGEDITWINDOW_H__5848CC7C_CCB0_4541_93B6_9DD6140B7F5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RobolangEditWindow.h : header file
//

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
	virtual void setProcedure( CProcedure *proc );
	virtual void removeAllCommands();
	virtual void notifyProcNamed( CProcedure *program );

private:
	void addCommand( CCommand *command );
	int addCommand( int pos , CCommand *command, int depth );
	void adjustLastColumnWidth();
	CCommand *getCurrentCommand();

	void addItem( int pos , CString robot , CString command , int depth , short type , void *data );
	short getItemType( int pos );
	int hitTest( int& subItem );
	CString addTabulations( const CString string, int tabulationCount );

	void startSelectRobot( int item );
	CCommand *getCommand( int item );
	int getCurrentItem();

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
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnUpdateCmdnew(CCmdUI* pCmdUI);
	afx_msg void OnCmdnew();
	afx_msg void OnCmdchange();
	afx_msg void OnUpdateCmdchange(CCmdUI* pCmdUI);
	afx_msg void OnCmddelete();
	afx_msg void OnUpdateCmddelete(CCmdUI* pCmdUI);
	//}}AFX_MSG
	void OnCmdRange( UINT nCmd );
	void OnUpdateCmdRange( CCmdUI* pCmdUI );

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROBOLANGEDITWINDOW_H__5848CC7C_CCB0_4541_93B6_9DD6140B7F5C__INCLUDED_)
