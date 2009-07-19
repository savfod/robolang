// Control.cpp: implementation of the CControl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Control.h"
#include "..\program\program.h"
#include "..\programui\programUI.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CControl::CControl( IControl *p_ic )
:	ic( p_ic )
{
}

CControl::~CControl()
{
}

void CControl::onAppNewProgram()
{
	CProgram *prog = ic -> getCProgram();
	CRoboMap *map = ic -> getCRoboMap();

	prog -> createNew();

	ic -> removeProcedures();
	
	int n = prog -> getProcedureCount();
	for( int k = 0; k < n; k++ )
		{
			CProcedure *p = prog -> getProcedureByIndex( k );
			ic -> addProcedure( p );
		}
}

CProcedure *CControl::onAppCreateProcedure()
{
	CProgram *prog = ic -> getCProgram();
	
	CString name = "Новая";
	CProcedure *p = prog -> getProcedureByName ( name );
	if( p != NULL)
	{
		int i = 2;
		CString nameEnd;
		nameEnd.Format("%d", i);
		while( prog -> getProcedureByName (name + nameEnd) != NULL)
		{
			i++;
			nameEnd.Format("%d", i);
		}
		name += nameEnd;
	}
	return( prog -> addProcedure( name ) );
}

bool CControl::onAppRenameProcedure( CProcedure *p , CString newName )
{
	CProgram *prog = ic -> getCProgram();
	CProcedure *pOther = prog -> getProcedureByName( newName );
	if( pOther != NULL && pOther != p )
		{
			ic -> messageBox( "Уже существует процедура с таким именем" );
			return( false );
		}

	// check name is valid
	if( !CProcedure::checkValidProcName( newName ) )
		{
			ic -> messageBox( "Процедура должна состоять из букв, цифр, знаков подчеркивания и не начинаться с цифры" );
			return( false );
		}
	
	prog -> renameProcedure( p , newName );

	return( true );
}

void CControl::onAppProcActivated( CString name )
{
	CProgramUI* ui = IControl::getInstance() -> getCProgramUI();
	ui -> onControlProcActivated( name );
}

bool CControl::onAppDeleteProc( CString name )
{
	CProgram* prog = IControl::getInstance() -> getCProgram();
	return( prog -> deleteProcedure( name ) );
}

