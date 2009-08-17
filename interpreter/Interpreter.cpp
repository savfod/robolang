// Interpreter.cpp: implementation of the CInterpreter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Interpreter.h"
#include <ctime>


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
	wasStopped = false;
	CProgram* program = IControl::getInstance() -> getCProgram();
	interpretProcedure( program -> getMainProcedure() );
}

void CInterpreter::interpretProcedure(CProcedure* proc)
{
	if(wasStopped) 
		return;

	interpretCommandArray( &(proc -> commands) );
}

void CInterpreter::interpretCommand(CCommand *cmd)
{
	if(wasStopped) 
		return;

	//not finished // wait must be in robolangMapWindow
	clock_t endwait;
	endwait = clock () + CLOCKS_PER_SEC/3 ;
	while (clock() < endwait) {}
	
	

	CRoboMap* map = IControl::getInstance() -> getCRoboMap();
	switch( cmd -> getType() )
	{
		case CMDTYPE_PAINT:
		{
			map -> robotPaint( cmd -> getRobotName(), cmd -> color );		
			break;
		}
		case CMDTYPE_MOVE:
		{
			bool successful = map -> robotMoved( cmd -> getRobotName(), cmd -> direction );
			if( !successful ) 
				wasStopped = true;
			
			break;
		}
		case CMDTYPE_IF:
		{
			Location loc;
			map -> getRobotLocation( cmd -> getRobotName(), loc );
						
			if( map ->checkCondition( loc, cmd -> condition ) )
				interpretCommandArray( &( cmd -> childCommands ) );
			
			break;
		}
		case CMDTYPE_WHILE:
		{
			Location loc;
			map -> getRobotLocation( cmd -> getRobotName(), loc );
			
			while( map ->checkCondition( loc, cmd -> condition ) )
			{
				if(wasStopped) 
					break;
				interpretCommandArray( &( cmd -> childCommands ) );
			}
			break;
		}
		case CMDTYPE_CALL:
		{
			CProgram* program = IControl::getInstance() -> getCProgram();
			CString procName = cmd -> callingProcedureName;
			interpretProcedure( program -> getProcedureByName( procName ) );
			
			break;
		}
	}

}


void CInterpreter::interpretCommandArray( CCommandArray *cmdArray )
{
	if(wasStopped) 
		return;
	
	for(int i = 0; i < cmdArray -> GetSize() ; i++ )
	{
		interpretCommand( cmdArray -> GetAt( i ) );
	}
}


