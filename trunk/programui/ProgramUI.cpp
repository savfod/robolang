// ProgramUI.cpp: implementation of the CProgramUI class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ProgramUI.h"

#include "../Program/Program.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProgramUI::CProgramUI( IEditWindow *p_iw )
:	iw( p_iw )
{
}

CProgramUI::~CProgramUI()
{
}

void CProgramUI::ReUploadProgram()
{
	//finding CProgram, "singleton"
	CProgram *program = IControl::getInstance() -> getCProgram();

	iw -> RemoveAllCommands();
	iw -> ShowCommand( program -> GetMainCommand() );
}

