// Program.h: interface for the CProgram class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROGRAM_H__54E717C0_BF26_45B6_BEFF_3EE9C65FE0E9__INCLUDED_)
#define AFX_PROGRAM_H__54E717C0_BF26_45B6_BEFF_3EE9C65FE0E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\control\control.h"
#include "Command.h"

class CProgram  
{
public:
	CProgram( IControl *ic );
	virtual ~CProgram();

	CCommand* GetMainCommand();
	void Open();//parameters?
	void Save();//parameters?
	void Close();
	
	
private:
	IControl *ic;
	CCommand* program;
	void DeleteCommand(CCommand* command);
};

#endif // !defined(AFX_PROGRAM_H__54E717C0_BF26_45B6_BEFF_3EE9C65FE0E9__INCLUDED_)
