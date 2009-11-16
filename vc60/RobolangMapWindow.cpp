// RobolangMapWindow.cpp : implementation file
//

#include "stdafx.h"
#include "robolang.h"
#include "RobolangMapWindow.h"
#include "..\map\RoboMap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRobolangMapWindow
IMPLEMENT_DYNCREATE( CRobolangMapWindow , CView )

CRobolangMapWindow::CRobolangMapWindow()
{
	startPoint = CPoint( 0, 0 );
	cell = CSize( 20, 20 );
	wallC = CSize( 5, 5 );
	wallH = CSize( cell.cx, wallC.cy );
	wallV = CSize( wallC.cx, cell.cy );
}

CRobolangMapWindow::~CRobolangMapWindow()
{
}

BEGIN_MESSAGE_MAP(CRobolangMapWindow, CView)
	//{{AFX_MSG_MAP(CRobolangMapWindow)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRobolangMapWindow message handlers

void CRobolangMapWindow::OnDraw( CDC *dc ) 
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
			COLORREF color = ( map -> getExistenceWallH( iX, iY ) ) ? RGB( 255, 0, 0) : RGB( 50, 50, 50 );
 			dc -> FillSolidRect( startX, startY, wallH.cx, wallH.cy, color ); 
		}
	}
	
	//wallV
	for( iY = 0; iY < numberY; iY++ )
	{
		for( iX = 0; iX < numberX + 1; iX++ )
		{
			int startX = startPoint.x + ( iX * cell.cx + iX * wallV.cx );
			int startY = startPoint.y + ( iY * cell.cy + ( iY + 1 ) * wallH.cy );
			COLORREF color = ( map -> getExistenceWallV( iX, iY ) ) ? RGB( 255, 0, 0) : RGB( 50, 50, 50 );
 			dc -> FillSolidRect( startX, startY, wallV.cx, wallV.cy, color ); 
		}
	}

	//WallC
	for( iY = 1; iY < numberY ; iY++ ) //walls on edge are skipped
	{
		for( iX = 1; iX < numberX ; iX++ ) //walls on edge are skipped
		{
			int startX = startPoint.x + ( iX * cell.cx + iX * wallV.cx );
			int startY = startPoint.y + ( iY * cell.cy + iY * wallH.cy );
			
			bool isWallUp = map -> getExistenceWallV( iX , iY - 1 ); 
			bool isWallTop = map -> getExistenceWallV( iX, iY ); 
			bool isWallLeft = map -> getExistenceWallH( iX - 1, iY ); 
			bool isWallRight = map -> getExistenceWallH( iX, iY  ); 
			bool isAnyWallNear = isWallUp || isWallTop || isWallLeft || isWallRight;
			
			COLORREF color = ( isAnyWallNear ) ? RGB( 255, 0, 0) : RGB( 50, 50, 50 );
 			dc ->FillSolidRect( startX, startY, wallC.cx, wallC.cy, color ); 
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

	//set map rectangular
	rcMap.left = startPoint.x;
	rcMap.top = startPoint.y;
	rcMap.right = startPoint.x + numberX * cell.cx + ( numberX + 1 ) * wallV.cx;
	rcMap.bottom = startPoint.y + numberY * cell.cy + ( numberY + 1 ) * wallH.cy;

}

BOOL CRobolangMapWindow::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CDC *dc = GetDC();
	
	// TODO: Add your message handler code here
	CRect rc;
	GetClientRect( rc );
	
	//painting everything but map
	CRect rcTop;
	CRect rcBottom;
	CRect rcLeft;
	CRect rcRight;

	rcTop.top = rcLeft.top = rcRight.top = rc.top;
	rcBottom.top = rcMap.bottom;
	
	rcBottom.bottom = rcLeft.bottom = rcRight.bottom = rc.bottom;
	rcTop.bottom = rcMap.top;

	rcTop.left = rcBottom.left = rcLeft.left = rc.left;
	rcRight.left = rcMap.right;

	rcTop.right = rcBottom.right = rcRight.right = rc.right;
	rcLeft.right = rcMap.left;

	COLORREF color = RGB( 134 , 238 , 195 );
	dc -> FillSolidRect( rcTop , color );
	dc -> FillSolidRect( rcBottom , color );
	dc -> FillSolidRect( rcLeft , color );
	dc -> FillSolidRect( rcRight , color );

	OnDraw(dc);

	ReleaseDC(dc);
	capturedRobot.Empty();
	return TRUE;
}

void CRobolangMapWindow::updateMap()
{
	CDC *dc = GetDC();
	OnDraw(dc);
//	capturedRobot.Empty();
	ReleaseDC(dc);
}

void CRobolangMapWindow::OnLButtonUp(UINT nFlags, CPoint point) 
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
			mapUI -> onViewWallHChanged( loc.CrdX, loc.CrdY,TYPE_INVERT );
			break;
		}
		case TYPE_INWALLV:
		{
			mapUI -> onViewWallVChanged( loc.CrdX, loc.CrdY, TYPE_INVERT );
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
			if( currentElement.type != TYPE_INCELL || currentElement.loc.CrdX != loc.CrdX || currentElement.loc.CrdY != loc.CrdY )
				mapUI -> onViewCellChanged( loc.CrdX, loc.CrdY, TYPE_INVERT );
			break;
		}
	}
	capturedRobot.Empty();

	CView::OnLButtonUp(nFlags, point);
}
void CRobolangMapWindow::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	Location loc;
	LocationType type;
	identificatePoint( point, loc, type );
	
	currentElement.type = LOCATIONTYPE_UNKNOWN; //stops this system.
	
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

void CRobolangMapWindow::identificatePoint( CPoint point, Location &resLoc, LocationType &resType )
{
	//map starts at startPoint
	point.x -= startPoint.x;
	point.y -= startPoint.y;
	
	//test if point is out of map
	CRoboMap* map = IControl::getInstance() -> getCRoboMap();
	if(map == NULL)
	{
		resType = LOCATIONTYPE_UNKNOWN;
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


Element CRobolangMapWindow::identificatePoint( CPoint point ){
	Element el;
	identificatePoint( point, ( el.loc ), ( el.type ) );
	return el;
}




BOOL CRobolangMapWindow::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CRobolangMapWindow::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	//SetWindowPos(NULL, 0, 0, 1000, 1000, 0);	// TODO: Add your message handler code here
	
}

void CRobolangMapWindow::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	Location loc;
	LocationType type;
	identificatePoint( point, loc, type );
	CRoboMap* map = IControl::getInstance() -> getCRoboMap();

	if( type == TYPE_INCELL )
	{
		map -> setRobotLocation( "пнанр 0", loc );
	//	mapUI -> onViewCellChanged( loc.CrdX, loc.CrdY );
	}
	
	CView::OnLButtonDblClk(nFlags, point);
}

void CRobolangMapWindow::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	Element newElement = identificatePoint( point );
	CRoboMapUI *mapUI = IControl::getInstance() -> getCRoboMapUI();
	
	//if(currentElement != newElement )
	if( currentElement.loc.CrdX !=  newElement.loc.CrdX || currentElement.loc.CrdY !=  newElement.loc.CrdY || currentElement.type !=  newElement.type )
	{
		ChangeType type = ( nFlags & MK_SHIFT ) ? TYPE_ERASE : TYPE_FILL;
			
		if( (newElement.type == TYPE_INCELL) && (nFlags & MK_LBUTTON) )
			makeChange( newElement, type );
				
		if( (newElement.type == TYPE_INWALLH) && ( nFlags & MK_RBUTTON ) )
			makeChange( newElement, type );
		
		if( ( newElement.type == TYPE_INWALLV ) && ( nFlags & MK_RBUTTON ) )
			makeChange( newElement, type );
	}
	
	currentElement = newElement;
	CView::OnMouseMove(nFlags, point);	
}

void CRobolangMapWindow::makeChange(Element el, ChangeType change)
{
	CRoboMapUI *mapUI = IControl::getInstance() -> getCRoboMapUI();
	switch( el.type ) 
	{	
		case TYPE_INCELL:	mapUI -> onViewCellChanged( el.loc.CrdX, el.loc.CrdY, change);	break;
		case TYPE_INWALLV:	mapUI -> onViewWallVChanged( el.loc.CrdX, el.loc.CrdY, change); break;
		case TYPE_INWALLH:	mapUI -> onViewWallHChanged( el.loc.CrdX, el.loc.CrdY, change); break;
	}
}
