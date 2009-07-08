// RobolangMap.cpp : implementation file
//

#include "stdafx.h"
#include "robolang.h"
#include "RobolangMap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRobolangMap
IMPLEMENT_DYNCREATE( CRobolangMap , CView )

CRobolangMap::CRobolangMap()
{
}

CRobolangMap::~CRobolangMap()
{
}

BEGIN_MESSAGE_MAP(CRobolangMap, CView)
	//{{AFX_MSG_MAP(CRobolangMap)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRobolangMap message handlers

void CRobolangMap::OnDraw( CDC *dc ) 
{
	// TODO: Add your message handler code here
	CRect rc;
	GetUpdateRect( rc , TRUE );

	dc -> SelectStockObject( ANSI_FIXED_FONT );
	
	GetClientRect( rc );
	dc -> DrawText( CString( "MAP SHOULD BE DRAWN HERE" ) , rc ,  DT_CENTER | DT_VCENTER | DT_SINGLELINE );
	
	// Do not call CWnd::OnPaint() for painting messages
}

BOOL CRobolangMap::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CDC *dc = GetDC();
	
	// TODO: Add your message handler code here
	CRect rc;
	GetClientRect( rc );
	
	dc -> FillSolidRect( rc , RGB( 134 , 238 , 195 ) );

	return TRUE;
}
