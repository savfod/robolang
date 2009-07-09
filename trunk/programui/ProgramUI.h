// ProgramUI.h: interface for the CProgramUI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROGRAMUI_H__428B1B90_3CEF_4E31_B454_D2494C1D3A7E__INCLUDED_)
#define AFX_PROGRAMUI_H__428B1B90_3CEF_4E31_B454_D2494C1D3A7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\program\program.h"

/*#########################################################################*/
/*#########################################################################*/

class IEditWindow
{
public:
	// interface to program edit window
	virtual void addCommand( CCommand *command ) = 0;
	virtual void removeAllCommands() = 0;
};

/*#########################################################################*/
/*#########################################################################*/

class CProgramUI  
{
public:
	CProgramUI( IEditWindow *iw );
	virtual ~CProgramUI();

// CRobolangEditWindow
	void onEditAdd( CCommand *cmd , CCommand *whereToAdd );
	void onEditUpdate( CCommand *cmd );
	void onEditDelete( CCommand *cmd );

// CProgram
	void onProgramChanged();

private:
	IEditWindow *iw;
};

/*#########################################################################*/
/*#########################################################################*/

#endif // !defined(AFX_PROGRAMUI_H__428B1B90_3CEF_4E31_B454_D2494C1D3A7E__INCLUDED_)
