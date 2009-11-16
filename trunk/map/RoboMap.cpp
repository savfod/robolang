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
	stdCellColor = RGB( 250 , 162 , 14 );
	cells = new CArray< CColorArrayPointer, CColorArrayPointer >;
	wallH = new CArray< CBoolArrayPointer, CBoolArrayPointer >;
	wallV = new CArray< CBoolArrayPointer, CBoolArrayPointer >;
}

CRoboMap::~CRoboMap()
{
	deleteCells();
	deleteWallH();
	deleteWallV();
}


bool CRoboMap::robotMoved( CString name, char direction ) //LRUD 
{
	Location loc;
	BOOL wasFound =  robots.Lookup( name , loc );
	if( !wasFound )
		return false;
	
	switch( direction )
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
		case 'U':
		case 'u':
		{
			if( getExistenceWallH( loc.CrdX , loc.CrdY ) )
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
		case 'D':
		case 'd':
		{
			if( getExistenceWallH( loc.CrdX , loc.CrdY + 1 ) )
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
	return false;
}
void CRoboMap::robotPaint( CString name, COLORREF color )
{
	Location loc;
	getRobotLocation( name, loc );

	setCellColor( color, loc.CrdX, loc.CrdY );
}

bool CRoboMap::checkCondition( Location loc, CommandCondition condition)
{ 
	switch( condition.type )
	{
		case CONDTYPE_UNKNOWN:
		{
			TRACE(" CMDCOND_UNKNOWN in CRoboMap::checkCondition ");
			IControl::getInstance() -> messageBox ("Пустое условие!");
			return false;
		}
		case CONDTYPE_WALLLEFT:
		{
			return( getExistenceWallV( loc.CrdX, loc.CrdY ) );
		}
		case CONDTYPE_WALLRIGHT:
		{
			return( getExistenceWallV( loc.CrdX + 1, loc.CrdY ) );
		}
		case CONDTYPE_WALLUP:
		{
			return( getExistenceWallH( loc.CrdX, loc.CrdY ) );
		}
		case CONDTYPE_WALLDOWN:
		{
			return( getExistenceWallH( loc.CrdX, loc.CrdY + 1 ) );
		}
		case CONDTYPE_PAINTED:
		{
			COLORREF color = getCellColor( loc.CrdX, loc.CrdY );
			return( color != RGB( 0, 0, 0) );
		}
		case CONDTYPE_NOT:
		{
			return ( !checkCondition(loc, *condition.cond1) );
		}
		case CONDTYPE_OR:
		{
			return ( checkCondition(loc, *condition.cond1) || checkCondition(loc, *condition.cond2) );
		}
		case CONDTYPE_AND:
		{
			return ( checkCondition(loc, *condition.cond1) && checkCondition(loc, *condition.cond2) );
		}

	}

	return false;
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
	COLORREF color = stdCellColor;
	cells -> GetAt(3) -> SetAt(1, color);
	cells -> GetAt(3) -> SetAt(2, color);
	cells -> GetAt(3) -> SetAt(3, color);
	cells -> GetAt(3) -> SetAt(6, color);
	cells -> GetAt(3) -> SetAt(9, color);
	cells -> GetAt(3) -> SetAt(10, color);
	cells -> GetAt(3) -> SetAt(11, color);
	cells -> GetAt(3) -> SetAt(14, color);
	cells -> GetAt(3) -> SetAt(16, color);
	cells -> GetAt(3) -> SetAt(17, color);
	cells -> GetAt(3) -> SetAt(18, color);

	cells -> GetAt(4) -> SetAt(1, color);
	//cells -> GetAt(4) -> SetAt(2, color);
	cells -> GetAt(4) -> SetAt(3, color);
	cells -> GetAt(4) -> SetAt(5, color);
	cells -> GetAt(4) -> SetAt(7, color);
	cells -> GetAt(4) -> SetAt(9, color);
	//cells -> GetAt(4) -> SetAt(10, color);
	cells -> GetAt(4) -> SetAt(11, color);
	cells -> GetAt(4) -> SetAt(13, color);
	cells -> GetAt(4) -> SetAt(15, color);
	cells -> GetAt(4) -> SetAt(17, color);
	//cells -> GetAt(4) -> SetAt(18, color);

	cells -> GetAt(5) -> SetAt(1, color);
	cells -> GetAt(5) -> SetAt(2, color);
	//cells -> GetAt(5) -> SetAt(3, color);
	cells -> GetAt(5) -> SetAt(5, color);
	cells -> GetAt(5) -> SetAt(7, color);
	cells -> GetAt(5) -> SetAt(9, color);
	cells -> GetAt(5) -> SetAt(10, color);
	//cells -> GetAt(5) -> SetAt(11, color);
	cells -> GetAt(5) -> SetAt(13, color);
	cells -> GetAt(5) -> SetAt(15, color);
	cells -> GetAt(5) -> SetAt(17, color);
	//cells -> GetAt(5) -> SetAt(18, color);

	cells -> GetAt(6) -> SetAt(1, color);
	//cells -> GetAt(6) -> SetAt(2, color);
	cells -> GetAt(6) -> SetAt(3, color);
	cells -> GetAt(6) -> SetAt(5, color);
	cells -> GetAt(6) -> SetAt(7, color);
	cells -> GetAt(6) -> SetAt(9, color);
	//cells -> GetAt(6) -> SetAt(10, color);
	cells -> GetAt(6) -> SetAt(11, color);
	cells -> GetAt(6) -> SetAt(13, color);
	cells -> GetAt(6) -> SetAt(15, color);
	cells -> GetAt(6) -> SetAt(17, color);
	//cells -> GetAt(6) -> SetAt(18, color);

	cells -> GetAt(7) -> SetAt(1, color);
	//cells -> GetAt(7) -> SetAt(2, color);
	cells -> GetAt(7) -> SetAt(3, color);
	cells -> GetAt(7) -> SetAt(6, color);
	//cells -> GetAt(7) -> SetAt(7, color);
	cells -> GetAt(7) -> SetAt(9, color);
	cells -> GetAt(7) -> SetAt(10, color);
	cells -> GetAt(7) -> SetAt(11, color);
	cells -> GetAt(7) -> SetAt(14, color);
	//cells -> GetAt(7) -> SetAt(15, color);
	cells -> GetAt(7) -> SetAt(17, color);
	//cells -> GetAt(7) -> SetAt(18, color);


		
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
	for( int i = 0; i < cells -> GetSize(); i++ )
		delete cells -> GetAt( i );
	delete cells;
}

void CRoboMap::deleteWallH()
{
	for( int i = 0; i < wallH -> GetSize(); i++ )
		delete wallH -> GetAt( i );
	delete wallH;
}

void CRoboMap::deleteWallV()
{
	for( int i = 0; i < wallV -> GetSize(); i++ )
		delete wallV -> GetAt( i );
	delete wallV;
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

