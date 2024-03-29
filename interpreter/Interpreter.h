// Interpreter.h: interface for the CInterpreter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INTERPRETER_H__673DB5B2_FFE6_44E0_9D87_76FC75C9ACD1__INCLUDED_)
#define AFX_INTERPRETER_H__673DB5B2_FFE6_44E0_9D87_76FC75C9ACD1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\program\Program.h"
#include "..\map\RoboMap.h"

class CCommand;
class CProcedure;
class IControl;

class CInterpreter  
{
public:
	void SpeedDown();
	void SpeedUp();
	CInterpreter( IControl *ic );
	virtual ~CInterpreter();
	static void startOrStopInterpretating(void*);
	
private:
	void interpretCommand( CCommand* cmd );
	void interpretProcedure( CProcedure* proc );
	void interpretCommandArray( CCommandArray *cmdArray );
	
	bool wasStopped;
	double pauseTime;
	IControl *ic;
};

#endif // !defined(AFX_INTERPRETER_H__673DB5B2_FFE6_44E0_9D87_76FC75C9ACD1__INCLUDED_)
