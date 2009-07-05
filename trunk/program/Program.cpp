// Program.cpp: implementation of the CProgram class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Program.h"
CProgram* CProgram::_instance = NULL;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProgram::CProgram()
{
	_instance = this;
}

CProgram::~CProgram()
{

}
/////////////////////////////////////////////////////////////////////
// Other

CCommand* CProgram::GetMainCommand()
{
	//for debug only
	CCommand* result = new CCommand();
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
	result->Commands[2]->Commands[0]->Name = "here";

	return result;
}
CProgram* CProgram::Instance()
{
	if(!_instance)
	{
		CProgram();
	}

	return _instance;
}
