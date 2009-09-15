// Interpreter.cpp: implementation of the CInterpreter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Interpreter.h"
#include <ctime>

#define WAIT( X ) { clock_t endwait; endwait = clock () + CLOCKS_PER_SEC * X; while (clock() < endwait) {} } //not finished// for alpha version only!

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInterpreter::CInterpreter( IControl *p_ic )
:	ic( p_ic )
{
	wasStopped = true;
	pauseTime = 0.02;
}

CInterpreter::~CInterpreter()
{
}

void CInterpreter::startOrStopInterpretating(void*)
{
	//not finished. Start and Stop should be different functions
	CInterpreter* interpreter = IControl::getInstance() -> getCInterpreter();
	
	//if is on - stop
	if(!interpreter -> wasStopped) // = if is on
	{
		interpreter -> wasStopped = true;
		return;
	}

	interpreter -> wasStopped = false;
	CProgram* program = IControl::getInstance() -> getCProgram();
	interpreter -> interpretProcedure( program -> getMainProcedure() );
	interpreter -> wasStopped = true;
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
	

	CRoboMap* map = IControl::getInstance() -> getCRoboMap();
	switch( cmd -> getType() )
	{
		case CMDTYPE_PAINT:
		{
			WAIT( pauseTime );
			map -> robotPaint( cmd -> getRobotName(), cmd -> color );		
			break;
		}
		case CMDTYPE_MOVE:
		{
			WAIT( pauseTime );
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
				map -> getRobotLocation( cmd -> getRobotName(), loc );
			}
			break;
		}
		case CMDTYPE_CALL:
		{
			CProgram* program = IControl::getInstance() -> getCProgram();
			CString procName = cmd -> callingProcedureName;
			CProcedure* proc =  program -> getProcedureByName( procName );
			
			if( proc == NULL )
			{
				CString error = (CString)"Ошибка. Недействительное имя процедуры (" + procName + (CString)")";
				IControl::getInstance() -> messageBox(error);
				wasStopped = true;
			}
			else	
				interpretProcedure( proc );
			
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



void CInterpreter::SpeedUp()
{
	pauseTime /= 2;
}

void CInterpreter::SpeedDown()
{
	pauseTime *= 2;
}
