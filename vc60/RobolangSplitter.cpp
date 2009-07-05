// RobolangSplitter.cpp : implementation file
//

#include "stdafx.h"
#include "robolang.h"
#include "RobolangEditWindow.h"
#include "RobolangMap.h"
#include "RobolangSplitter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRobolangSplitter

CRobolangSplitter::CRobolangSplitter()
{
	editPane = NULL;
	mapPane = NULL;
}

CRobolangSplitter::~CRobolangSplitter()
{
}

BOOL CRobolangSplitter::Create( CWnd *parent , LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
{
	if( !CSplitterWnd::CreateStatic( parent, 2, 1 ) )
		return( FALSE );

	if( !CSplitterWnd::CreateView( 0 , 0 , RUNTIME_CLASS( CRobolangEditWindow ) , CSize( 20 , 20 ) , pContext ) )
		return( FALSE );

	if( !CSplitterWnd::CreateView( 1 , 0 , RUNTIME_CLASS( CRobolangMap ) , CSize( 20 , 20 ) , pContext ) )
		return( FALSE );

	editPane = ( CRobolangEditWindow * )CSplitterWnd::GetPane( 0 , 0 );
	mapPane = ( CRobolangMap * )CSplitterWnd::GetPane( 1 , 0 );

	return( TRUE );
}

BEGIN_MESSAGE_MAP(CRobolangSplitter, CSplitterWnd)
	//{{AFX_MSG_MAP(CRobolangSplitter)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRobolangSplitter message handlers
