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
		map -> setCellColor( RGB( 250 , 162 , 14 ) , indexX, indexY);
	else if( oldValue != RGB( 0, 0, 0 ) )
		map -> setCellColor( RGB( 0, 0 , 0 ) , indexX, indexY);
}

void CRoboMapUI::onViewClearCell()
{
	CRoboMap* map = IControl::getInstance() -> getCRoboMap();
	
	RoboMapSize size  = map -> getSize();
	COLORREF black = RGB(0,0,0);

	for( unsigned int i_x = 0; i_x < size.sizeX; i_x++ )
		for( unsigned int i_y = 0; i_y < size.sizeY; i_y++ )
			map -> setCellColor( black, i_x, i_y);
}

void CRoboMapUI::onViewRandomCell()
{
	srand( time( NULL ) );
	
	CRoboMap* map = IControl::getInstance() -> getCRoboMap();
	
	RoboMapSize  size     = map -> getSize();
	COLORREF     stdColor = map -> stdCellColor;
	COLORREF     black    = RGB(0,0,0);

	for( unsigned int i_x = 0; i_x < size.sizeX; i_x++ )
	{
		for( unsigned int i_y = 0; i_y < size.sizeY; i_y++ )
		{
			COLORREF color = ( rand()%2 )? stdColor : black; 
			map -> setCellColor( color , i_x, i_y);
		}
	}
}

void CRoboMapUI::onViewClearWall()
{
	CRoboMap* map = IControl::getInstance() -> getCRoboMap();
	
	RoboMapSize size  = map -> getSize();
	unsigned int i_x, i_y;

	for( i_x = 0; i_x < size.sizeX + 1; i_x++ )
		for( i_y = 0; i_y < size.sizeY; i_y++ )
			map -> setExistenceWallV( false, i_x, i_y );
	
	for( i_x = 0; i_x < size.sizeX; i_x++ )
		for( i_y = 0; i_y < size.sizeY + 1; i_y++ )
			map -> setExistenceWallH( false, i_x, i_y );
	

}

void CRoboMapUI::onViewRandomWall()
{
	srand( time( NULL ) );
	
	CRoboMap* map = IControl::getInstance() -> getCRoboMap();
	
	RoboMapSize size  = map -> getSize();
	unsigned int i_x, i_y;

	for( i_x = 0; i_x < size.sizeX + 1; i_x++ )
		for( i_y = 0; i_y < size.sizeY; i_y++ )
			map -> setExistenceWallV( rand()%2 , i_x, i_y );
	
	for( i_x = 0; i_x < size.sizeX; i_x++ )
		for( i_y = 0; i_y < size.sizeY + 1; i_y++ )
			map -> setExistenceWallH( rand()%2 , i_x, i_y );
	

}
