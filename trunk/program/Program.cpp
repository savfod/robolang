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
	program->Name = "ןנמדנאללא"; //"program"
}

CProgram::~CProgram()
{
	Close();
	if(program)
	{
		delete program;
	}
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
}
void CProgram::DeleteCommand(CCommand* command)
{
	for (int i = 0; i < (command->Commands).GetSize(); i++)
	{
		DeleteCommand((command->Commands)[i]);
	}
	delete command;
}


