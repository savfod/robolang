// ProgramUI.cpp: implementation of the CProgramUI class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ProgramUI.h"

#include "../Program/Program.h"
#include "..\control\Control.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction

CProgramUI::CProgramUI( IEditWindow *p_iw )
:	iw( p_iw )
{
	procedure = NULL;
	isProcessUpdates = true;
}

CProgramUI::~CProgramUI()
{
}

void CProgramUI::skipUpdates()
{
	isProcessUpdates = false;
}

void CProgramUI::restoreUpdates()
{
	isProcessUpdates = true;
}

/*#########################################################################*/
/*#########################################################################*/

void CProgramUI::onControlProcActivated( CString name )
{
	procName = name;
	
	//finding CProgram, "singleton"
	CProgram *program = IControl::getInstance() -> getCProgram();
	
	// refresh view
	iw -> removeAllCommands();
	procedure = program -> getProcedureByName( procName );
	iw -> setProcedure( procedure );
}

/*#########################################################################*/
/*#########################################################################*/

void CProgramUI::onProgramNew()
{
	if( !isProcessUpdates )
		return;

	//finding CProgram, "singleton"
	CProgram *program = IControl::getInstance() -> getCProgram();

	// refresh view	
	iw -> removeAllCommands();
	procedure = program -> getMainProcedure(); 
	iw -> setProcedure( procedure );
}

void CProgramUI::onProgramChanged()
{
	if( !isProcessUpdates )
		return;

	//finding CProgram, "singleton"
	CProgram *program = IControl::getInstance() -> getCProgram();

	// refresh view	
	iw -> removeAllCommands();
	procedure = program -> getMainProcedure(); 
	iw -> setProcedure( procedure );

	//notify Doc
	onSmthChanged();
}

void CProgramUI::onProgramProcRenamed( CProcedure *p )
{
	if( !isProcessUpdates )
		return;

	if( procedure == p )
	{
		procName = p -> name;
		iw -> notifyProcRenamed( p );
	}

	//notify Doc
	onSmthChanged();
}

void CProgramUI::onProgramProcDeleted( CString name )
{
	if(name == procName)
	{
		CProgram *program = IControl::getInstance() -> getCProgram();
		procedure = program -> getMainProcedure(); 
		procName = procedure -> name;

		iw -> removeAllCommands();
		iw -> setProcedure( procedure );
	}

	//notify Doc
	onSmthChanged();
}

/*#########################################################################*/
/*#########################################################################*/

void CProgramUI::onEditAdd( CCommand *cmd , CCommand *parent , CCommand *before )
{
	skipUpdates();
	procedure -> addCommand( cmd , parent , before );
	restoreUpdates();

	iw -> setProcedure( procedure );

	//notify Doc
	onSmthChanged();
}

void CProgramUI::onEditUpdate( CCommand *cmd , CCommand *cmdData )
{
	// cannot update compound to simple if have childs
	if( cmd -> isCompound() && cmdData -> isCompound() == false && cmd -> childCommands.GetSize() > 0 )
		{
			IControl::getInstance() -> messageBox( "������ �������� ��������� �������� �� �������, ���� ������� ��������� �������" );
			return;
		}

	// copy props
	skipUpdates();
	cmd -> setProps( cmdData );
	restoreUpdates();

	// refresh view
	iw -> setProcedure( procedure );

	//notify Doc
	onSmthChanged();
}

void CProgramUI::onEditDelete( CCommand *cmd )
{
	skipUpdates();
	procedure -> deleteCommand( cmd );
	restoreUpdates();

	// refresh view
	iw -> setProcedure( procedure );

	//notify Doc
	onSmthChanged();
}

/*#########################################################################*/
/*#########################################################################*/

void CProgramUI::onProgramOpened(bool successful)
{
	CControl* control = IControl::getInstance() -> getCControl();
	if(successful)
		control -> onProgNewProgram();
	else
	{
		IControl::getInstance() -> messageBox( "������. �� ������� �������� ����." );
		control -> onAppNewProgram();
	}
	onProgramChanged();
}

void CProgramUI::onSmthChanged() 
{
	IControl::getInstance() -> onSmthChanged();
}
