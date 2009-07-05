// ProgramUI.cpp: implementation of the CProgramUI class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ProgramUI.h"

#include "../vc60/RobolangEditWindow.h"
#include "../Program/Program.h"
CProgramUI* CProgramUI::_instance = NULL;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProgramUI::CProgramUI()
{
	_instance = this;
}

CProgramUI::~CProgramUI()
{

}

void CProgramUI::ReUploadProgramm()
{
	//finding CRobolangEditWindow, "singleton"
	CRobolangEditWindow* robolang = CRobolangEditWindow::GetPointer();
	
	//finding CProgram, "singleton"
	CProgram* program = CProgram::Instance();

	//
	robolang->RemoveAllCommands();
	robolang->ShowCommand(program->GetMainCommand());
}
CProgramUI* CProgramUI::Instance()
{
	if(!_instance)
	{
		CProgramUI();
	}

	return _instance;
}
