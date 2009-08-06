// RobolangMap.cpp : implementation file
//

#include "stdafx.h"
#include "robolang.h"
#include "RobolangMap.h"
#include "..\map\RoboMap.h"

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
	startPoint = CPoint( 0, 0 );
	cell = CSize( 20, 20 );
	wallC = CSize( 5, 5 );
	wallH = CSize( cell.cx, wallC.cy );
	wallV = CSize( wallC.cx, cell.cy );
}

CRobolangMap::~CRobolangMap()
{
}

BEGIN_MESSAGE_MAP(CRobolangMap, CView)
	//{{AFX_MSG_MAP(CRobolangMap)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRobolangMap message handlers

void CRobolangMap::OnDraw( CDC *dc ) 
{
	// not finished
	// TODO: Add your message handler code here
	//CRect rc;
	//GetUpdateRect( rc , TRUE );

	CRoboMap* map = IControl::getInstance() -> getCRoboMap();
	
	//ASSERT( map != NULL );
	if(map == NULL)
		return;
	
	RoboMapSize size = map -> getSize();
	int numberY = size.sizeY;
	int numberX = size.sizeX;
	int iY, iX; 

	//cells
	for( iY = 0; iY < numberY; iY++ )
	{	
		for( iX = 0; iX < numberX; iX++ )
		{
			int startX = startPoint.x + ( iX * cell.cx + ( iX + 1 ) * wallV.cx );
			int startY = startPoint.y + ( iY * cell.cy + ( iY + 1 ) * wallH.cy );
			dc -> FillSolidRect( startX, startY, cell.cx, cell.cy, map ->getCellColor( iX, iY ) );
		}
	}
	
	//wallH
	for( iY = 0; iY < numberY + 1; iY++ )
	{
		for( iX = 0; iX < numberX; iX++ )
		{
			int startX = startPoint.x + ( iX * cell.cx + ( iX + 1 ) * wallV.cx );
			int startY = startPoint.y + ( iY * cell.cy + iY * wallH.cy );
			COLORREF color = ( map -> getExistenceWallH( iX, iY ) ) ? RGB( 255, 0, 0) : RGB( 100, 100, 100 );
 			dc ->FillSolidRect( startX, startY, wallH.cx, wallH.cy, color ); 
		}
	}
	
	//wallV
	for( iY = 0; iY < numberY; iY++ )
	{
		for( iX = 0; iX < numberX + 1; iX++ )
		{
			int startX = startPoint.x + ( iX * cell.cx + iX * wallV.cx );
			int startY = startPoint.y + ( iY * cell.cy + ( iY + 1 ) * wallH.cy );
			COLORREF color = ( map -> getExistenceWallV( iX, iY ) ) ? RGB( 255, 0, 0) : RGB( 100, 100, 100 );
 			dc ->FillSolidRect( startX, startY, wallV.cx, wallV.cy, color ); 
		}
	}
	//edge
	for( iY = 0; iY < numberY + 1; iY++ )
	{
		for( iX = 0; iX < numberX + 1; iX++ )
		{
			if( iY == 0 || iY == numberY || iX == 0 || iX == numberX )
			{
				int startX = startPoint.x + ( iX * cell.cx + iX * wallV.cx );
				int startY = startPoint.y + ( iY * cell.cy + iY * wallH.cy );
				COLORREF color = RGB( 255, 0, 0) ;
 				dc ->FillSolidRect( startX, startY, wallC.cx, wallC.cy, color );
			}
		}
	}

	//robots
	HICON robot = (HICON)LoadIcon( GetModuleHandle( NULL ) , MAKEINTRESOURCE( IDI_ICON1) );
	//map -> robots
	CString key;
	Location loc;
	for( POSITION pos = map -> robots.GetStartPosition(); pos != NULL; )
	{
		map -> robots.GetNextAssoc( pos, key, loc );
		int startX = cell.cx * loc.CrdX + wallC.cx * ( loc.CrdX + 1 );
		int startY = cell.cy * loc.CrdY + wallC.cy * ( loc.CrdY + 1 );

		dc -> DrawIcon( startX, startY, robot);
	}
	DestroyIcon( robot );
}

BOOL CRobolangMap::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CDC *dc = GetDC();
	
	// TODO: Add your message handler code here
	CRect rc;
	GetClientRect( rc );
	
	dc -> FillSolidRect( rc , RGB( 134 , 238 , 195 ) );

	ReleaseDC(dc);
	return TRUE;
}

void CRobolangMap::updateMap()
{
	CDC *dc = GetDC();
	OnDraw(dc);
	capturedRobot.Empty();
	ReleaseDC(dc);
}

void CRobolangMap::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CRoboMapUI *mapUI = IControl::getInstance() -> getCRoboMapUI();
	Location loc;
	LocationType type;
	identificatePoint( point, loc, type ); 

	switch( type )
	{
		case TYPE_INWALLH:
		{
			mapUI -> onViewWallHChanged( loc.CrdX, loc.CrdY );
			break;
		}
		case TYPE_INWALLV:
		{
			mapUI -> onViewWallVChanged( loc.CrdX, loc.CrdY );
			break;
		}
		case TYPE_INCELL:
		{
			CRoboMap *map = IControl::getInstance() -> getCRoboMap();
			Location robotLoc; 
			if( !capturedRobot.IsEmpty() && map -> getRobotLocation( capturedRobot, robotLoc ) )
			{
				if( robotLoc.CrdX != loc.CrdX || robotLoc.CrdY != loc.CrdY )
				{
					map -> setRobotLocation( capturedRobot, loc );
					break;
				}
			}
			mapUI -> onViewCellChanged( loc.CrdX, loc.CrdY );
			break;
		}
	}
	capturedRobot.Empty();

	CView::OnLButtonUp(nFlags, point);
}
void CRobolangMap::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	Location loc;
	LocationType type;
	identificatePoint( point, loc, type );
	
	if( type == TYPE_INCELL )
	{
		CRoboMap *map = IControl::getInstance() -> getCRoboMap();
		CString key;
		Location robotLoc;
		for( POSITION pos = map -> robots.GetStartPosition(); pos != NULL; )
		{
			map -> robots.GetNextAssoc( pos, key, robotLoc );
			if( robotLoc.CrdX == loc.CrdX && robotLoc.CrdY == loc.CrdY )
			{
				capturedRobot = key;
				break;
			}
		}
	}
	
	CView::OnLButtonDown(nFlags, point);
}

void CRobolangMap::identificatePoint( CPoint point, Location &resLoc, LocationType &resType )
{
	//map starts at startPoint
	point.x -= startPoint.x;
	point.y -= startPoint.y;
	
	//test if point is out of map
	CRoboMap* map = IControl::getInstance() -> getCRoboMap();
	if(map == NULL)
	{
		resType = TYPE_UNKNOWN;
		return;
	}
	RoboMapSize size = map -> getSize();	
	int maxX = cell.cx * size.sizeX + wallC.cx * ( size.sizeX + 1 );
	int maxY = cell.cy * size.sizeY + wallC.cy * ( size.sizeY + 1 );
	if( point.x > maxX  || 0 > point.x || 
		point.y > maxY  || 0 > point.y    )
	{
		resType = TYPE_OUTOFMAP;
		return;
	}
	
	
	resLoc.CrdX = 0;
	resLoc.CrdY = 0;
	int stepX = cell.cx + wallC.cx;
	int stepY = cell.cy + wallC.cy;
	
	
	while( point.x > stepX )
	{
		resLoc.CrdX++;
		point.x -= stepX;
	}
	while( point.y > stepY )
	{
		resLoc.CrdY++;
		point.y -= stepY;
	}

	if( 0 < point.y && point.y <= wallC.cy )
	{
 		if( 0 < point.x && point.x <= wallC.cx )
		{
			resType = TYPE_INWALLC;
		
		}
		else if( wallC.cx < point.x && point.x <= stepX )
		{
			resType = TYPE_INWALLH;
		}
	}
	else if( wallC.cy < point.y && point.y <= stepY )
	{
		if( 0 < point.x && point.x <= wallC.cx )
		{
			resType = TYPE_INWALLV;
		}
		else if( wallC.cx < point.x && point.x <= stepX )
		{
			resType = TYPE_INCELL;
		}
	}
}






