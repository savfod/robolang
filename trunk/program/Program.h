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
	CMDCOND_PAINTED = 5
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
	void setProps( CCommand *cmdData );
	void setPaint( COLORREF color );
	void setMove( char direction );
	void setIf( CommandCondition condition );
	void setWhile( CommandCondition condition );
	void setCall( CString name );

// data
public:
	int robot;
	CommandType type;
	COLORREF color;
	char direction; // LRUD
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
	void deleteCommand( CCommand *cmd );

	int findCommand( CCommandArray *cmdList , CCommand *cmd );
	CCommand *findParent( CCommand *cmdListOwner , CCommandArray *cmdList , CCommand *cmd );
	bool isMain();
	static bool checkValidProcName( CString name );

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
	int getProcedureCount();
	CProcedure *getProcedureByIndex( int index );
	void renameProcedure( CProcedure *p , CString newName );
	bool deleteProcedure( CString name );

	CString getProgramText(); //procedures -> text
	void setProgram( CString program ); // text -> procedures
	
private:
	void clear();
	
	CString getProcedureText(CProcedure* proc);
	CString getCommandText(CCommand *cmd);
	CString getBlockOfCommandsText(CCommandArray *commands);

	bool isLetter(TCHAR c);

private:
	IControl *ic;
	CProcedureMap procedures;
};

/*#########################################################################*/
/*#########################################################################*/

#endif // !defined(AFX_PROGRAM_H__54E717C0_BF26_45B6_BEFF_3EE9C65FE0E9__INCLUDED_)
