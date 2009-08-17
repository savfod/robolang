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
		procedures.GetNextAssoc( pos , key , proc );
		delete proc;
	}
	procedures.RemoveAll();
}

/////////////////////////////////////////////////////////////////////
// Other

void CProgram::createNew()
{
	clear();

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

CProcedure *CProgram::getProcedureByName( CString name )
{
	CProcedure *proc;
	if( procedures.Lookup( name , proc ) )
		return( proc );
	return( NULL );
}

/////////////////////////////////////////////////////////////////////
// open/save

CString CProgram::getProgramText()
{
	CString result;

	CString key;
	CProcedure* value;
	POSITION pos = procedures.GetStartPosition();
	while(pos != NULL)
	{
		procedures.GetNextAssoc(pos, key, value);
		
		result += getProcedureText( value );
		if( pos != NULL )
			result += "\r\n";
	}
	return result;
}

CString CProgram::getProcedureText(CProcedure *proc)
{
	//procedure
	CString result( "Процедура" );
	result += ' ';
	result += proc -> name;
	result += "\r\n";

	//commands
	result += getBlockOfCommandsText( &(proc -> commands) );

	return result;
}

CString CProgram::getCommandText( CCommand *cmd )
{
	CString result = cmd -> getCommandString();
	result += "\r\n";

	if( cmd -> isCompound() )
		result += getBlockOfCommandsText( &( cmd -> childCommands ) );
	
	return result;
}

CString CProgram::getBlockOfCommandsText(CCommandArray *commands)
{
	CString result;
	
	result += "{\r\n";
	
	for( int i = 0; i < commands -> GetSize(); i++ )
		result += getCommandText( commands -> GetAt(i) );

	result += "}\r\n";

	return result;

}

void CProgram::setProgram( CString program )
{
	/*while( program.size() )
	{
		while( !isLetter( program.GetAt(0) ) )
			program.Delete(0);	
	}*/
}

bool CProgram::isLetter(TCHAR c)
{
	return		(
		(( 'a' <= c ) && ( c <= 'z' )) ||
		(( 'A' <= c ) && ( c <= 'Z' )) ||
		(( 'а' <= c ) && ( c <= 'я' )) ||
		(( 'А' <= c ) && ( c <= 'Я' ))
				);
}

int CProgram::getProcedureCount()
{
	return( procedures.GetCount() );
}

CProcedure *CProgram::getProcedureByIndex( int index )
{
	POSITION pos = procedures.GetStartPosition();
	if( pos == NULL )
		return( NULL );

	CString key;
	CProcedure *proc;
	for( int k = 0; k <= index; k++ )
		procedures.GetNextAssoc( pos , key , proc );

	return( proc );			
}

void CProgram::renameProcedure( CProcedure *p , CString newName )
{
	procedures.RemoveKey( p -> name );
	p -> name = newName;
	procedures.SetAt( p -> name , p );

	// notify
	CProgramUI *ui = ic -> getCProgramUI();
	ui -> onProgramProcRenamed( p );
}

bool CProgram::deleteProcedure( CString name )
{
	CProcedure* p;
	BOOL wasFound = procedures.Lookup( name , p );
	ASSERT( wasFound );
	delete p;
	procedures.RemoveKey( name );

	CProgramUI *ui = ic -> getCProgramUI();
	ui -> onProgramProcDeleted( name );
	
	return( true );
}
