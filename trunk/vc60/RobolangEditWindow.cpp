// RobolangEditWindow.cpp : implementation file
//

#include "stdafx.h"
#include "robolang.h"
#include "RobolangEditWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRobolangEditWindow
IMPLEMENT_DYNCREATE( CRobolangEditWindow , CListView )

CRobolangEditWindow::CRobolangEditWindow()
{
}

CRobolangEditWindow::~CRobolangEditWindow()
{
}


BEGIN_MESSAGE_MAP(CRobolangEditWindow, CListView)
	//{{AFX_MSG_MAP(CRobolangEditWindow)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRobolangEditWindow message handlers
