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

class CProgram;
class CCommand;
class CProcedure;

/*#########################################################################*/
/*#########################################################################*/

typedef CArray<CCommand *, CCommand *> CCommandArray;
typedef CMap<CString, LPCSTR, CProcedure *, CProcedure *> CProcedureMap;

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
	CString getEndName();

	// command types
	bool isCompound();

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
	CCommandArray childCommands;
};

/*#########################################################################*/
/*#########################################################################*/

class CProcedure
{
public:
	CProcedure( CString name );
	~CProcedure();

	CString getProcLine();
	void addCommand( CCommand *cmd , CCommand *parent , CCommand *before );
	int findCommand( CCommandArray *cmdList , CCommand *cmd );

	CCommandArray commands;
	CString name;
};
	
/*#########################################################################*/
/*#########################################################################*/

class CProgram  
{
public:
	CProgram( IControl *ic );
	virtual ~CProgram();

	void createNew();

	CProcedure *addProcedure( CString name );
	CProcedure *getMainProcedure();
	CProcedure *getProcedureByName( CString name );

	CString getProgramText(); //procedures -> text
	void setProgram( CString program ); // text -> procedure
	
private:
	void clear();
	void deleteCommand( CCommand *command );
	void deleteProcedure( CProcedure *procedure );

private:
	IControl *ic;
	CProcedureMap procedures;
};

/*#########################################################################*/
/*#########################################################################*/

#endif // !defined(AFX_PROGRAM_H__54E717C0_BF26_45B6_BEFF_3EE9C65FE0E9__INCLUDED_)