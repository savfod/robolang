// Map.h: interface for the CMap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAP_H__99A05FF9_B630_4808_A98C_3459904AD4E6__INCLUDED_)
#define AFX_MAP_H__99A05FF9_B630_4808_A98C_3459904AD4E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
 
#include <afxtempl.h>
#include "..\control\control.h"
#include "..\program\Program.h"
class CCommand;

typedef enum {
	WLLDRCT_UNKNOWN = 0 ,
	WLLDRCT_WALLLEFT = 1 ,
	WLLDRCT_WALLRIGHT = 2 ,
	WLLDRCT_WALLUP = 3 ,
	WLLDRCT_WALLDOWN = 4 
} WallDirection;

struct RoboMapSize
{
	unsigned int sizeX;
	unsigned int sizeY;
};

struct Location
{
	unsigned int CrdX; // CrdX >= 0
	unsigned int CrdY; // CrdY >= 0
	WallDirection wallDrct; // for walls only
};

typedef CMap<CString, LPCSTR, Location, Location> CLocationMap;
typedef CArray< COLORREF, COLORREF > *CColorArrayPointer;
typedef CArray< CColorArrayPointer , CColorArrayPointer > *CColorSquareArrayPointer;
typedef CArray< bool, bool > *CBoolArrayPointer;
typedef CArray< CBoolArrayPointer, CBoolArrayPointer >* CBoolSquareArrayPointer;

class CRoboMap  
{
public:
	CRoboMap( IControl *ic );
	virtual ~CRoboMap();
	void createNew();


	bool checkCondition( Location loc, CommandCondition condition);
	bool robotMoved( CString name, char direction ); //LRUD //if successful return true
	void robotPaint( CString name	, COLORREF color );

	void setSize( RoboMapSize size );
	RoboMapSize getSize();

	void addRobot(CString name);
	void removeRobot(CString name);
	
	//access
	bool getExistenceWallV( int countX, int countY );
	bool getExistenceWallH( int countX, int countY );
	COLORREF getCellColor( int countX, int countY );
	BOOL getRobotLocation( CString name, Location &loc );
	
	void setRobotLocation( CString name, Location loc );
	void setExistenceWallV( bool value, int countX, int countY );
	void setExistenceWallH( bool value, int countX, int countY );
	void setCellColor( COLORREF value, int countX, int countY );
	
//public data
	CLocationMap robots;
	COLORREF stdCellColor;

	CColorSquareArrayPointer cells;
	CBoolSquareArrayPointer wallH; //horizontal
	CBoolSquareArrayPointer wallV; //vertical


private:
	void deleteOldObjects();
	void deleteWallV();
	void deleteWallH();
	void deleteCells();

	IControl *ic;
};

#endif // !defined(AFX_MAP_H__99A05FF9_B630_4808_A98C_3459904AD4E6__INCLUDED_)
