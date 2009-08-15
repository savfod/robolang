// Map.cpp: implementation of the CMap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RoboMap.h"
#include "..\mapUI\RoboMapUI.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const int STARTWIDTH = 20;
const int STARTHEIGHT = 10;

CRoboMap::CRoboMap( IControl *p_ic )
:	ic( p_ic )
{
}

CRoboMap::~CRoboMap()
{
	deleteCells();
	deleteWallH();
	deleteWallV();
}


bool CRoboMap::executeCommand( CCommand *cmd )
{
	Location loc;
	CString name = cmd -> getRobotName();
	BOOL wasFound = robots.Lookup( name , loc);
	if( !wasFound )
	{
		TRACE("in CRoboMap::executeCommand robot not found");
		return false;
	}

	if( cmd -> getType() == CMDTYPE_PAINT)
	{
		setCellColor( cmd -> color, loc.CrdX, loc.CrdY );
		return true;
	}
	if( cmd -> getType() == CMDTYPE_MOVE)
	{
		switch( cmd -> direction)
		{
			case 'L':
			case 'l':
			{
				if( getExistenceWallV( loc.CrdX, loc.CrdY ) )
				{
					MessageBox(NULL, "Робот не может пройти сквозь стену", NULL, IDOK);
					return false;
				}
				else
				{
					loc.CrdX--;
					setRobotLocation( name, loc );
					return true;
				}
			}
			case 'R':
			case 'r':
			{
				if( getExistenceWallV( loc.CrdX + 1, loc.CrdY ) )
				{
					MessageBox(NULL, "Робот не может пройти сквозь стену", NULL, IDOK);
					return false;
				}
				else
				{
					loc.CrdX++;
					setRobotLocation( name, loc );
					return true;
				}
			}
			case 'T':
			case 't':
			{
				if( getExistenceWallV( loc.CrdX , loc.CrdY ) )
				{
					MessageBox(NULL, "Робот не может пройти сквозь стену", NULL, IDOK);
					return false;
				}
				else
				{
					loc.CrdY--;
					setRobotLocation( name, loc );
					return true;
				}
			}
			case 'B':
			case 'b':
			{
				if( getExistenceWallV( loc.CrdX , loc.CrdY + 1 ) )
				{ 
					MessageBox(NULL, "Робот не может пройти сквозь стену", NULL, IDOK);
					return false;
				}
				else
				{
					loc.CrdY++;
					setRobotLocation( name, loc );
					return true;
				}
			}

		}
	}
	TRACE("in CRoboMap::executeCommand unexpected command");
	return false;
}

bool checkCondition( Location loc, CommandCondition condition)
{ 
	//not finished
	return true;
}

void CRoboMap::setSize( RoboMapSize size )
{
	//not finished
}

RoboMapSize CRoboMap::getSize()
{
	RoboMapSize a;
	a.sizeY = cells -> GetSize();
	ASSERT( a.sizeY > 0 );
	a.sizeX = cells -> GetAt(0) -> GetSize();
	return a;
}

void CRoboMap::addRobot(CString name)
{
	Location a;
	a.CrdX = 1;
	a.CrdY = 1;
	robots.SetAt( name, a );
}
void CRoboMap::removeRobot(CString name)
{
	Location loc;
	BOOL wasFound = robots.Lookup( name , loc );
	ASSERT( wasFound );
	robots.RemoveKey( name );
}

void CRoboMap::createNew()
{
	deleteCells();
	deleteWallH();
	deleteWallV();

	int i;
	int j;

	//cells
	cells = new CArray< CColorArrayPointer, CColorArrayPointer >;
	for( i = 0; i < STARTHEIGHT; i++)
	{
		cells -> Add( new CArray< COLORREF, COLORREF> );
		for( j = 0; j < STARTWIDTH; j++)
			cells -> GetAt(i) -> Add( RGB( 0 , 0 , 0 ) );
	}
	
	//wallsV
	wallV = new CArray< CBoolArrayPointer, CBoolArrayPointer >;
	for( i = 0; i < STARTHEIGHT; i++)
	{
		wallV -> Add( new CArray< bool, bool> );
		for( j = 0; j < STARTWIDTH + 1; j++)
		{
			if( j == 0 || j == STARTWIDTH )
				wallV -> GetAt( i ) -> Add( true );
			else
				wallV -> GetAt( i ) -> Add( false );
		}
	}
	
	//wallH
	wallH = new CArray< CBoolArrayPointer, CBoolArrayPointer >;
	for( i = 0; i < STARTHEIGHT + 1; i++)
	{
		wallH -> Add( new CArray< bool, bool> );
		for( j = 0; j < STARTWIDTH; j++)
		{
			if( i == 0 || i == STARTHEIGHT )
				wallH -> GetAt( i ) -> Add( true );
			else
				wallH -> GetAt( i ) -> Add( false );
		}
	}

	//robot
	Location loc;
	loc.CrdX = 0;
	loc.CrdY = 0;
	robots.SetAt( "РОБОТ 0", loc );

	//for fun (first picture)
	COLORREF green = RGB( 0, 255, 0 );
	cells -> GetAt(3) -> SetAt(1, green);
	cells -> GetAt(3) -> SetAt(2, green);
	cells -> GetAt(3) -> SetAt(3, green);
	cells -> GetAt(3) -> SetAt(6, green);
	cells -> GetAt(3) -> SetAt(9, green);
	cells -> GetAt(3) -> SetAt(10, green);
	cells -> GetAt(3) -> SetAt(11, green);
	cells -> GetAt(3) -> SetAt(14, green);
	cells -> GetAt(3) -> SetAt(16, green);
	cells -> GetAt(3) -> SetAt(17, green);
	cells -> GetAt(3) -> SetAt(18, green);

	cells -> GetAt(4) -> SetAt(1, green);
	//cells -> GetAt(4) -> SetAt(2, green);
	cells -> GetAt(4) -> SetAt(3, green);
	cells -> GetAt(4) -> SetAt(5, green);
	cells -> GetAt(4) -> SetAt(7, green);
	cells -> GetAt(4) -> SetAt(9, green);
	//cells -> GetAt(4) -> SetAt(10, green);
	cells -> GetAt(4) -> SetAt(11, green);
	cells -> GetAt(4) -> SetAt(13, green);
	cells -> GetAt(4) -> SetAt(15, green);
	cells -> GetAt(4) -> SetAt(17, green);
	//cells -> GetAt(4) -> SetAt(18, green);

	cells -> GetAt(5) -> SetAt(1, green);
	cells -> GetAt(5) -> SetAt(2, green);
	//cells -> GetAt(5) -> SetAt(3, green);
	cells -> GetAt(5) -> SetAt(5, green);
	cells -> GetAt(5) -> SetAt(7, green);
	cells -> GetAt(5) -> SetAt(9, green);
	cells -> GetAt(5) -> SetAt(10, green);
	//cells -> GetAt(5) -> SetAt(11, green);
	cells -> GetAt(5) -> SetAt(13, green);
	cells -> GetAt(5) -> SetAt(15, green);
	cells -> GetAt(5) -> SetAt(17, green);
	//cells -> GetAt(5) -> SetAt(18, green);

	cells -> GetAt(6) -> SetAt(1, green);
	//cells -> GetAt(6) -> SetAt(2, green);
	cells -> GetAt(6) -> SetAt(3, green);
	cells -> GetAt(6) -> SetAt(5, green);
	cells -> GetAt(6) -> SetAt(7, green);
	cells -> GetAt(6) -> SetAt(9, green);
	//cells -> GetAt(6) -> SetAt(10, green);
	cells -> GetAt(6) -> SetAt(11, green);
	cells -> GetAt(6) -> SetAt(13, green);
	cells -> GetAt(6) -> SetAt(15, green);
	cells -> GetAt(6) -> SetAt(17, green);
	//cells -> GetAt(6) -> SetAt(18, green);

	cells -> GetAt(7) -> SetAt(1, green);
	//cells -> GetAt(7) -> SetAt(2, green);
	cells -> GetAt(7) -> SetAt(3, green);
	cells -> GetAt(7) -> SetAt(6, green);
	//cells -> GetAt(7) -> SetAt(7, green);
	cells -> GetAt(7) -> SetAt(9, green);
	cells -> GetAt(7) -> SetAt(10, green);
	cells -> GetAt(7) -> SetAt(11, green);
	cells -> GetAt(7) -> SetAt(14, green);
	//cells -> GetAt(7) -> SetAt(15, green);
	cells -> GetAt(7) -> SetAt(17, green);
	//cells -> GetAt(7) -> SetAt(18, green);


		
	CRoboMapUI *ui = ic -> getCRoboMapUI();
	ui -> onMapChanged();
}

void CRoboMap::deleteOldObjects()
{
	robots.RemoveAll();
	deleteCells();
	deleteWallH();
	deleteWallV();
}

void CRoboMap::deleteCells()
{
	//not finished

}

void CRoboMap::deleteWallH()
{
	//not finished

}

void CRoboMap::deleteWallV()
{
	//not finished

}


//###############################################################
//###############################################################
//access to members

COLORREF CRoboMap::getCellColor(int countX, int countY)
{
	int sizeY = cells -> GetSize();
	ASSERT( countY < sizeY );
	int sizeX = cells -> GetAt( countY ) -> GetSize();
	ASSERT( countX < sizeX );

	COLORREF res = cells -> GetAt( countY ) -> GetAt( countX );
	return res;
}

bool CRoboMap::getExistenceWallH(int countX, int countY)
{
	int sizeY = wallH -> GetSize();
	ASSERT( countY < sizeY );
	int sizeX = wallH -> GetAt( countY ) -> GetSize();
	ASSERT( countX < sizeX );

	bool res = wallH -> GetAt( countY ) -> GetAt( countX );
	return res;
}

bool CRoboMap::getExistenceWallV(int countX, int countY)
{
	int sizeY = wallV -> GetSize();
	ASSERT( countY < sizeY );
	int sizeX = wallV -> GetAt( countY ) -> GetSize();
	ASSERT( countX < sizeX );

	bool res = wallV -> GetAt( countY ) -> GetAt( countX );
	return res;
}


void CRoboMap::setCellColor( COLORREF value, int countX, int countY )
{
	int sizeY = cells -> GetSize();
	ASSERT( countY < sizeY );
	int sizeX = cells -> GetAt( countY ) -> GetSize();
	ASSERT( countX < sizeX );

	cells -> GetAt( countY ) -> SetAt( countX, value );

	CRoboMapUI *ui = ic -> getCRoboMapUI();
	ui -> onMapChanged();
}

void CRoboMap::setExistenceWallH( bool value, int countX, int countY )
{
	int sizeY = wallH -> GetSize();
	ASSERT( countY < sizeY );
	int sizeX = wallH -> GetAt( countY ) -> GetSize();
	ASSERT( countX < sizeX );

	//edge can't be changed
	if( countY == 0 || countY == sizeY - 1 )
		return; 

	wallH -> GetAt( countY ) ->SetAt( countX , value );

	CRoboMapUI *ui = ic -> getCRoboMapUI();
	ui -> onMapChanged();
}

void CRoboMap::setExistenceWallV( bool value, int countX, int countY )
{
	int sizeY = wallV -> GetSize();
	ASSERT( countY < sizeY );
	int sizeX = wallV -> GetAt( countY ) -> GetSize();
	ASSERT( countX < sizeX );

	//edge can't be changed
	if( countX == 0 || countX == sizeX - 1 )
		return;

	wallV -> GetAt( countY ) ->SetAt( countX , value );

	CRoboMapUI *ui = ic -> getCRoboMapUI();
	ui -> onMapChanged();
}

void CRoboMap::setRobotLocation( CString name, Location loc )
{
	Location getLoc;
	BOOL wasFound = robots.Lookup( name, getLoc );
	ASSERT( wasFound );
	robots.SetAt( name , loc );

	CRoboMapUI *ui = ic -> getCRoboMapUI();
	ui -> onMapChanged();
}

BOOL CRoboMap::getRobotLocation( CString name, Location &loc )
{
	return( robots.Lookup( name, loc ) );
}

