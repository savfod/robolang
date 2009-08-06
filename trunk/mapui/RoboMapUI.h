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

class CRoboMapUI  
{
public:
	CRoboMapUI( IRoboMapWindow *mw );
	virtual ~CRoboMapUI();

	void onViewCellChanged( int indexX, int indexY);
	void onViewWallVChanged( int indexX, int indexY);
	void onViewWallHChanged( int indexX, int indexY);

	void onMapChanged();
private:
	IRoboMapWindow *iw;
};

#endif // !defined(AFX_MAPUI_H__0B3F765C_1712_4B73_BB42_05887E40ADBE__INCLUDED_)
