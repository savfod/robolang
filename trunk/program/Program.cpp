// Program.cpp: implementation of the CProgram class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Program.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProgram::CProgram( IControl *p_ic )
:	ic( p_ic )
{
	program = new CCommand;
	program -> type = CMDTYPE_UNKNOWN;
}

CProgram::~CProgram()
{
	Close();
}

/////////////////////////////////////////////////////////////////////
// Other

CCommand* CProgram::GetMainCommand()
{
	//for debug only
	/*CCommand* result = new CCommand();
	result->Name = "now";
	result->Commands.Add(new CCommand());
	result->Commands.Add(new CCommand());
	result->Commands.Add(new CCommand());

	result->Commands[0]->Name = "commands";
	result->Commands[1]->Name = "can";
	result->Commands[2]->Name = "displayed";

	result->Commands[1]->Commands.Add(new CCommand());
	result->Commands[1]->Commands[0]->Name = "be";

	result->Commands[2]->Commands.Add(new CCommand());
	result->Commands[2]->Commands[0]->Name = "here";*/

	return program;
}

void CProgram::Close()
{
	DeleteCommand(program);
	program = NULL;
}

void CProgram::DeleteCommand( CCommand* command )
{
	CCommandArray& cmdList1 = command -> primaryChildCommands;
	for( int i = 0; i < cmdList1.GetSize(); i++ )
		DeleteCommand( cmdList1[i] );

	CCommandArray& cmdList2 = command -> secondaryChildCommands;
	for( i = 0; i < cmdList2.GetSize(); i++ )
		DeleteCommand( cmdList2[i] );

	delete command;
}
