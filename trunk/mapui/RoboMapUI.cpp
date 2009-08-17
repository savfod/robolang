// MapUI.cpp: implementation of the CMapUI class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RoboMapUI.h"
#include "..\map\RoboMap.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRoboMapUI::CRoboMapUI( IRoboMapWindow *p_iw )
:	iw( p_iw )
{
}

CRoboMapUI::~CRoboMapUI()
{
}

void CRoboMapUI::onMapChanged()
{
	iw -> updateMap();
}

void CRoboMapUI::onViewWallHChanged(int indexX, int indexY)
{
	CRoboMap* map = IControl::getInstance() -> getCRoboMap();
	bool oldValue = map -> getExistenceWallH( indexX, indexY );
	map -> setExistenceWallH( !oldValue, indexX, indexY);
}

void CRoboMapUI::onViewWallVChanged(int indexX, int indexY)
{
	CRoboMap* map = IControl::getInstance() -> getCRoboMap();
	bool oldValue = map -> getExistenceWallV( indexX, indexY );
	map -> setExistenceWallV( !oldValue, indexX, indexY);
}

void CRoboMapUI::onViewCellChanged(int indexX, int indexY)
{
	CRoboMap* map = IControl::getInstance() -> getCRoboMap();
	COLORREF oldValue = map -> getCellColor( indexX, indexY );
	if( oldValue == RGB( 0, 0, 0 ) )
		map -> setCellColor( RGB( 0, 255, 0 ) , indexX, indexY);
	else if( oldValue != RGB( 0, 0, 0 ) )
		map -> setCellColor( RGB( 0, 0 , 0 ) , indexX, indexY);
}
