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
	if( before != NULL )
		parent = findParent( NULL , &commands , before );
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

bool CProcedure::isMain()
{
	return( name.Compare( "main" ) == 0 );
}

int CProcedure::findCommand( CCommandArray *cmdList , CCommand *cmd )
{
	for( int k = 0; k < cmdList -> GetSize(); k++ )
		if( cmdList -> GetAt( k ) == cmd )
			return( k );

	return( -1 );
}

CCommand *CProcedure::findParent( CCommand *cmdListOwner , CCommandArray *cmdList , CCommand *cmdFind )
{
	for( int k = 0; k < cmdList -> GetSize(); k++ )
		{
			CCommand *cmd = cmdList -> GetAt( k );

			// find in owned commands
			if( cmd == cmdFind )
				return( cmdListOwner );

			// find in childs
			cmd = findParent( cmd , &cmd -> childCommands , cmdFind );
			if( cmd != NULL )
				return( cmd );
		}

	return( NULL );
}

void CProcedure::deleteCommand( CCommand *cmd )
{
	CCommand *parent = findParent( NULL , &commands , cmd );
	CCommandArray& list = ( parent == NULL )? commands : parent -> childCommands;
	int pos = findCommand( &list , cmd );
	if( pos < 0 )
		ASSERT( FALSE );

	list.RemoveAt( pos );
	delete cmd;
}
