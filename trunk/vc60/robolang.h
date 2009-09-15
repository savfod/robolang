// robolang.h : main header file for the ROBOLANG application
//

#if !defined(AFX_ROBOLANG_H__9C0353F5_A643_4EDF_8329_DD78AF494D7B__INCLUDED_)
#define AFX_ROBOLANG_H__9C0353F5_A643_4EDF_8329_DD78AF494D7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "..\control\control.h"       // control

/////////////////////////////////////////////////////////////////////////////
// CRobolangApp:
// See robolang.cpp for the implementation of this class
//

class CLeftView;

class CRobolangApp : public CWinApp, public IControl
{
public:
	CRobolangApp();

public:
	virtual void messageBox( CString msg );
	virtual void removeProcedures();
	virtual void addProcedure( CProcedure *p );
	virtual void onSmthChanged();

public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRobolangApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CRobolangApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	afx_msg void OnStartInterpreter();
	afx_msg void OnMapClearCell();
	afx_msg void OnMapRandomCell();
	afx_msg void OnMapClearWall();
	afx_msg void OnMapRandomWall();
	afx_msg void OnViewInterpreterSpeedDown();
	afx_msg void OnViewInterpreterSpeedUp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void createClasses();
	CLeftView *getControlWindow();

private:
	// data
	bool initMode;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROBOLANG_H__9C0353F5_A643_4EDF_8329_DD78AF494D7B__INCLUDED_)
