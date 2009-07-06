// ProgramUI.h: interface for the CProgramUI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROGRAMUI_H__428B1B90_3CEF_4E31_B454_D2494C1D3A7E__INCLUDED_)
#define AFX_PROGRAMUI_H__428B1B90_3CEF_4E31_B454_D2494C1D3A7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\program\program.h"

class IEditWindow
{
public:
	// interface to program edit window
	virtual void ShowCommand(const CCommand *command ) = 0;
	virtual void RemoveAllCommands() = 0;
};

class CProgramUI  
{
public:
	CProgramUI( IEditWindow *iw );
	virtual ~CProgramUI();

	void ReUploadProgram();

//CRobolangEditWindow
	void onEditAdd(CCommand* whereToAdd, CString commandName); 
	void onEditDelete(CCommand* command);
	void onEditSave();//what parameters?
	void onEditOpen();//what parameters?
	void onEditClose();
	void onEditNew();
//CProgram
	void onProgramSmthChanged();

private:
	IEditWindow *iw;
};

#endif // !defined(AFX_PROGRAMUI_H__428B1B90_3CEF_4E31_B454_D2494C1D3A7E__INCLUDED_)
