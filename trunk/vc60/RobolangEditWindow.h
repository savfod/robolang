#if !defined(AFX_ROBOLANGEDITWINDOW_H__5848CC7C_CCB0_4541_93B6_9DD6140B7F5C__INCLUDED_)
#define AFX_ROBOLANGEDITWINDOW_H__5848CC7C_CCB0_4541_93B6_9DD6140B7F5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RobolangEditWindow.h : header file
//
#include "../Program/Command.h"

/////////////////////////////////////////////////////////////////////////////
// CRobolangEditWindow window

class CRobolangEditWindow : public CListView
{
// Construction
public:
	CRobolangEditWindow();
	DECLARE_DYNCREATE( CRobolangEditWindow );

// Attributes
public:

// Operations
public:


	void ShowCommand(CCommand* command);
	void RemoveAllCommands();
	static CRobolangEditWindow* GetPointer();

private:


	void ShowCommand(CCommand* command, int tabulationCount);
	CString AddTabulations(CString string, int tabulationCount);
	static CRobolangEditWindow* _pointer;

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
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROBOLANGEDITWINDOW_H__5848CC7C_CCB0_4541_93B6_9DD6140B7F5C__INCLUDED_)
