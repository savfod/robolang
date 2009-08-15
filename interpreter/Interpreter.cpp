// Interpreter.cpp: implementation of the CInterpreter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Interpreter.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInterpreter::CInterpreter( IControl *p_ic )
:	ic( p_ic )
{
}

CInterpreter::~CInterpreter()
{
}

void CInterpreter::startInterpretating()
{

}

void CInterpreter::interpretProcedure(CProcedure* proc)
{
	interpretCommandArray( &(proc -> commands) );
}

void CInterpreter::interpretCommand(CCommand *cmd)
{
	switch( cmd -> getType() )
	{
		case CMDTYPE_PAINT:
		{

		}
		case CMDTYPE_MOVE:
		{

		}
		case CMDTYPE_IF:
		{
			
		}
		case CMDTYPE_WHILE:
		{
		}
		case CMDTYPE_CALL:
		{
		}
	}

}

void CInterpreter::interpretCommandArray( CCommandArray *cmdArray )
{
	for(int i = 0; i < cmdArray -> GetSize() ; i++ )
	{
		interpretCommand( cmdArray -> GetAt( i ) );
	}
}


