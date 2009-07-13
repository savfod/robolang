// Program.h: interface for the CProgram class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROGRAM_H__54E717C0_BF26_45B6_BEFF_3EE9C65FE0E9__INCLUDED_)
#define AFX_PROGRAM_H__54E717C0_BF26_45B6_BEFF_3EE9C65FE0E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "..\control\control.h"

/*#########################################################################*/
/*#########################################################################*/

class CProgram;
class CCommand;
class CProcedure;


typedef CArray<CCommand *, CCommand *> CCommandArray;
typedef CArray<CProcedure *, CProcedure *> CProcedureArray;

typedef enum {
	CMDTYPE_UNKNOWN = 0 ,
	CMDTYPE_PAINT = 1 ,
	CMDTYPE_MOVE = 2 ,
	CMDTYPE_IF = 3 ,
	CMDTYPE_WHILE = 4 ,
	CMDTYPE_CALL = 5
} CommandType;

typedef enum {
	CMDCOND_UNKNOWN = 0 ,
	CMDCOND_WALLLEFT = 1 ,
	CMDCOND_WALLRIGHT = 2 ,
	CMDCOND_WALLUP = 3 ,
	CMDCOND_WALLDOWN = 4 ,
} CommandCondition;

class CCommand  
{
public:
	CCommand();
	virtual ~CCommand();

	// primary command attributes
	CommandType getType();
	CString getRobotName();
	CString getCommandName();

	// command representations
	CString getCommandString();
	CString getElseName();
	CString getEndifName();

	// sets
	void setPaint( COLORREF color );
	void setMove( char direction );
	void setIf( CommandCondition condition );
	void setWhile( CommandCondition condition );

// data
public:
	int robot;
	CommandType type;
	COLORREF color;
	char direction; // LRTB
	CommandCondition condition;

	CString callingProcedureName;
	CCommandArray primaryChildCommands;
	CCommandArray secondaryChildCommands;
};
class CProcedure
{
public:
	CCommandArray childCommands;
	CString Name;
};
	
/*#########################################################################*/
/*#########################################################################*/

class CProgram  
{
public:
	CProgram( IControl *ic );
	virtual ~CProgram();

	const CProcedureArray* GetProgram();
	CString GetProgramText(); //procedures -> text
	void SetProgram(CString program); // text -> procedure
	
	
	
private:
	IControl *ic;
	CProcedureArray program;
	void DeleteCommand(CCommand* command);
	void DeleteProcedure(CProcedure* procedure);
};

/*#########################################################################*/
/*#########################################################################*/

#endif // !defined(AFX_PROGRAM_H__54E717C0_BF26_45B6_BEFF_3EE9C65FE0E9__INCLUDED_)
