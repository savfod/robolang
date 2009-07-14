// Program.cpp: implementation of the CProgram class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Program.h"

CProcedure::CProcedure( CString p_name )
{
	name = p_name;
}

CProcedure::~CProcedure()
{
	CCommandArray& cmdList = commands;
	for( int i = 0; i < cmdList.GetSize(); i++)
		{
			CCommand *cmd = cmdList[i];
			delete cmd;
		}

	cmdList.RemoveAll();
}

CString CProcedure::getProcLine()
{
	return( CString( "опнжедспю " ) + name );
}

void CProcedure::addCommand( CCommand *cmd , CCommand *parent , CCommand *before )
{
	CCommandArray& list = ( parent == NULL )? commands : parent -> childCommands;

	// find before if any
	if( before != NULL )
		{
			int pos = findCommand( &list , before );
			if( pos < 0 )
				ASSERT( FALSE );

			// add in position
			list.InsertAt( pos , cmd );
		}
	else
		list.Add( cmd );
}

int CProcedure::findCommand( CCommandArray *cmdList , CCommand *cmd )
{
	for( int k = 0; k < cmdList -> GetSize(); k++ )
		if( cmdList -> GetAt( k ) == cmd )
			return( k );

	return( -1 );
}

