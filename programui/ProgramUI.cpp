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
	procedure = NULL;
	isProcessUpdates = true;
}

CProgramUI::~CProgramUI()
{
}

void CProgramUI::skipUpdates()
{
	isProcessUpdates = false;
}

void CProgramUI::restoreUpdates()
{
	isProcessUpdates = true;
}

/*#########################################################################*/
/*#########################################################################*/

void CProgramUI::onProgramChanged()
{
	if( !isProcessUpdates )
		return;

	//finding CProgram, "singleton"
	CProgram *program = IControl::getInstance() -> getCProgram();

	iw -> removeAllCommands();

	procedure = program -> getMainProcedure();
	iw -> setProcedure( procedure );
}

/*#########################################################################*/
/*#########################################################################*/

void CProgramUI::onEditAdd( CCommand *cmd , CCommand *parent , CCommand *before )
{
	skipUpdates();
	procedure -> addCommand( cmd , parent , before );
	restoreUpdates();

	iw -> setProcedure( procedure );
}

void CProgramUI::onEditUpdate( CCommand *cmd )
{
}

void CProgramUI::onEditDelete( CCommand *cmd )
{
}

/*#########################################################################*/
/*#########################################################################*/
