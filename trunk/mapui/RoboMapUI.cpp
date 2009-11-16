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
	CRoboMap* map = IControl::getInstance() -> getCRoboMap();
	stdColor = map -> stdCellColor;
	black = RGB( 0, 0, 0 );
}

CRoboMapUI::~CRoboMapUI()
{
}

void CRoboMapUI::onMapChanged()
{
	iw -> updateMap();
}

void CRoboMapUI::onViewWallHChanged(int indexX, int indexY, ChangeType change)
{
	
	CRoboMap* map = IControl::getInstance() -> getCRoboMap();
	bool oldValue = map -> getExistenceWallH( indexX, indexY );
	bool newValue;
	
	switch( change )
	{
		case TYPE_FILL:		newValue = 1; break;
		case TYPE_ERASE:	newValue = 0; break;
		case TYPE_INVERT:	newValue = !oldValue; break;
	}

	map -> setExistenceWallH( newValue, indexX, indexY);
}

void CRoboMapUI::onViewWallVChanged(int indexX, int indexY, ChangeType change)
{
	CRoboMap* map = IControl::getInstance() -> getCRoboMap();
	bool oldValue = map -> getExistenceWallV( indexX, indexY );
	bool newValue;
	
	switch( change )
	{
		case TYPE_FILL:		newValue = 1; break;
		case TYPE_ERASE:	newValue = 0; break;
		case TYPE_INVERT:	newValue = !oldValue; break;
	}

	map -> setExistenceWallV( newValue, indexX, indexY);
}

void CRoboMapUI::onViewCellChanged(int indexX, int indexY, ChangeType change)
{
	CRoboMap* map = IControl::getInstance() -> getCRoboMap();
	COLORREF oldValue = map -> getCellColor( indexX, indexY );
	COLORREF newValue;

	switch( change )
	{
		case TYPE_FILL:		newValue = stdColor; break;
		case TYPE_ERASE:	newValue = black; break;
		case TYPE_INVERT:	newValue = ( oldValue == black ) ? stdColor : black; break;
	}

	map -> setCellColor( newValue, indexX, indexY);
}

void CRoboMapUI::onViewClearCell()
{
	//fill all cells if all are cleared
	CRoboMap* map = IControl::getInstance() -> getCRoboMap();
	RoboMapSize size  = map -> getSize();
	
	//learn if cells are all black;
	unsigned int i_x, i_y;
	
	bool res = true;
	for( i_x = 0; i_x < size.sizeX; i_x++ )
		for( i_y = 0; i_y < size.sizeY; i_y++ )
			if( map -> getCellColor( i_x, i_y ) )
				res = false;
	COLORREF newColor = (res) ? stdColor : black;
	

	for( i_x = 0; i_x < size.sizeX; i_x++ )
		for( i_y = 0; i_y < size.sizeY; i_y++ )
			map -> setCellColor( newColor, i_x, i_y );
}

void CRoboMapUI::onViewRandomCell()
{
	srand( time( NULL ) );
	
	CRoboMap* map = IControl::getInstance() -> getCRoboMap();
	
	RoboMapSize  size     = map -> getSize();
	
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
	//set all walls if all are removed 
	CRoboMap* map = IControl::getInstance() -> getCRoboMap();
	RoboMapSize size  = map -> getSize();
	unsigned int i_x, i_y;
	
	 //learn if all walls are removed 
	bool res = true;

	for( i_x = 1; i_x < size.sizeX; i_x++ )
		for( i_y = 1; i_y < size.sizeY - 1; i_y++ )
			if( map -> getExistenceWallV( i_x, i_y ) )
				res = false; 
	
	for( i_x = 1; i_x < size.sizeX - 1; i_x++ )
		for( i_y = 1; i_y < size.sizeY; i_y++ )
			if( map -> getExistenceWallH( i_x, i_y ) )
				res = false;
	
	bool value = res;

	for( i_x = 0; i_x < size.sizeX + 1; i_x++ )
		for( i_y = 0; i_y < size.sizeY; i_y++ )
			map -> setExistenceWallV( value, i_x, i_y );
	
	for( i_x = 0; i_x < size.sizeX; i_x++ )
		for( i_y = 0; i_y < size.sizeY + 1; i_y++ )
			map -> setExistenceWallH( value, i_x, i_y );
	

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
