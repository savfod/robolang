// Program.cpp: implementation of the CProgram class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Program.h"
#include "..\programui\ProgramUI.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProgram::CProgram( IControl *p_ic )
:	ic( p_ic )
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
}

CProgram::~CProgram()
{
	clear();
}

void CProgram::clear()
{
	CString key;
	CProcedure *proc;
	for( POSITION pos = procedures.GetStartPosition(); pos != NULL; )
		{
			procedures.GetNextAssoc( pos , key , ( CProcedure *& ) proc );
			delete proc;
		}
	procedures.RemoveAll();
}

/////////////////////////////////////////////////////////////////////
// Other

void CProgram::createNew()
{
	// create empty program
	addProcedure( "main" );

	// notify ui
	CProgramUI *ui = ic -> getCProgramUI();
	ui -> onProgramChanged();
}

CProcedure *CProgram::addProcedure( CString name )
{
	CProcedure *proc;
	if( procedures.Lookup( name , proc ) )
		ASSERT( FALSE );

	// create empty program
	proc = new CProcedure( name );
	procedures.SetAt( name , proc );
	return( proc );
}

CProcedure *CProgram::getMainProcedure()
{
	return( getProcedureByName( "main" ) );
}

CString CProgram::getProgramText()
{
	// debug
	CString res;
	return res;
}

void CProgram::setProgram( CString program )
{
	// debug
	createNew();
}

CProcedure *CProgram::getProcedureByName( CString name )
{
	CProcedure *proc;
	if( procedures.Lookup( name , proc ) )
		return( proc );
	return( NULL );
}
