// ProgramUI.cpp: implementation of the CProgramUI class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ProgramUI.h"

#include "../Program/Program.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction

CProgramUI::CProgramUI( IEditWindow *p_iw )
:	iw( p_iw )
{
}

CProgramUI::~CProgramUI()
{
}

/*#########################################################################*/
/*#########################################################################*/

void CProgramUI::onProgramChanged()
{
	//finding CProgram, "singleton"
	CProgram *program = IControl::getInstance() -> getCProgram();

	iw -> removeAllCommands();
	iw -> addCommand( program -> GetMainCommand() );
}

/*#########################################################################*/
/*#########################################################################*/

void CProgramUI::onEditAdd( CCommand *cmd , CCommand *whereToAdd )
{
}

void CProgramUI::onEditUpdate( CCommand *cmd )
{
}

void CProgramUI::onEditDelete( CCommand *cmd )
{
}

/*#########################################################################*/
/*#########################################################################*/
