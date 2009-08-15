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
	CInterpreter( IControl *ic );
	virtual ~CInterpreter();
	void startInterpretating();
	
private:
	void interpretCommand( CCommand* cmd );
	void interpretProcedure( CProcedure* proc );
	void interpretCommandArray( CCommandArray *cmdArray );
	

	IControl *ic;
};

#endif // !defined(AFX_INTERPRETER_H__673DB5B2_FFE6_44E0_9D87_76FC75C9ACD1__INCLUDED_)
