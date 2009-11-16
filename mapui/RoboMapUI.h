// MapUI.h: interface for the CMapUI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPUI_H__0B3F765C_1712_4B73_BB42_05887E40ADBE__INCLUDED_)
#define AFX_MAPUI_H__0B3F765C_1712_4B73_BB42_05887E40ADBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class IRoboMapWindow
{
public:
	// interface for map window
	virtual void updateMap() = 0;
};

typedef enum { 
	CHANGETYPE_UNKNOWN = 0,
	TYPE_FILL = 1,
	TYPE_ERASE = 2,
	TYPE_INVERT = 3
} ChangeType;

class CRoboMapUI  
{
public:

	COLORREF stdColor;
	COLORREF black;

	CRoboMapUI( IRoboMapWindow *mw );
	virtual ~CRoboMapUI();

	void onViewCellChanged( int indexX, int indexY, ChangeType change );
	void onViewWallVChanged( int indexX, int indexY, ChangeType change );
	void onViewWallHChanged( int indexX, int indexY, ChangeType change );

	void onViewClearCell(); //fill all cells if all are cleared
	void onViewClearWall(); //set all walls if all are removed 
	void onViewRandomCell();
	void onViewRandomWall();

	void onMapChanged();
private:
	IRoboMapWindow *iw;
};

#endif // !defined(AFX_MAPUI_H__0B3F765C_1712_4B73_BB42_05887E40ADBE__INCLUDED_)
