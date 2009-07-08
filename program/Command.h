// Command.h: interface for the CCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMAND_H__36DD0D80_1E8D_4CA5_BFF4_D65E19CF461B__INCLUDED_)
#define AFX_COMMAND_H__36DD0D80_1E8D_4CA5_BFF4_D65E19CF461B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>

/*#########################################################################*/
/*#########################################################################*/

class CCommand;

typedef CArray<CCommand*, CCommand*> CCommandArray;
typedef enum {
	CMDTYPE_PAINT = 1 ,
	CMDTYPE_MOVE = 2 ,
	CMDTYPE_IF = 3 ,
	CMDTYPE_PROCEDURE = 4
} CommandType;

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

// data
public:
	int robot;
	CommandType type;
	CCommandArray primaryChildCommands;
	CCommandArray secondaryChildCommands;
};

/*#########################################################################*/
/*#########################################################################*/

#endif // !defined(AFX_COMMAND_H__36DD0D80_1E8D_4CA5_BFF4_D65E19CF461B__INCLUDED_)
