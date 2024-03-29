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
	virtual void setProcedure( CProcedure *p ) = 0;
	virtual void removeAllCommands() = 0;
	virtual void notifyProcRenamed( CProcedure *p ) = 0;
};

/*#########################################################################*/
/*#########################################################################*/

class CProgramUI  
{
public:
	void onProgramOpened(bool successful);
	CProgramUI( IEditWindow *iw );
	virtual ~CProgramUI();

//CControl
	void onControlProcActivated( CString name );

// CRobolangEditWindow
	void onEditAdd( CCommand *cmd , CCommand *parent , CCommand *before );
	void onEditUpdate( CCommand *cmd , CCommand *cmdData );
	void onEditDelete( CCommand *cmd );

// CProgram
	void onProgramChanged();
	void onProgramNew();
	void onProgramProcRenamed( CProcedure *p );
	void onProgramProcDeleted( CString name );

private:
	void skipUpdates();
	void restoreUpdates();
	void onSmthChanged(); // notify other parts of the programm, that smth was changed

private:	
	IEditWindow *iw;
	CProcedure *procedure;
	CString procName;
	bool isProcessUpdates;
};

/*#########################################################################*/
/*#########################################################################*/

#endif // !defined(AFX_PROGRAMUI_H__428B1B90_3CEF_4E31_B454_D2494C1D3A7E__INCLUDED_)
