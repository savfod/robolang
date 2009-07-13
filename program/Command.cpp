// Command.cpp: implementation of the CCommand class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "program.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommand::CCommand()
{
	robot = 0;
	type = CMDTYPE_UNKNOWN;
	color = 0;
	direction = 'U';
	condition = CMDCOND_UNKNOWN;
}

CCommand::~CCommand()
{
	CCommandArray& cmdList1 = childCommands;
	for( int i = 0; i < cmdList1.GetSize(); i++ )
		delete cmdList1[i];

	cmdList1.RemoveAll();
}

CommandType CCommand::getType()
{
	return( type );
}

bool CCommand::isCompound()
{
	return( type == CMDTYPE_IF || type == CMDTYPE_WHILE );
}

CString CCommand::getRobotName()
{
	CString s;
	s.Format( "����� %d" , robot );
	return( s );
}

CString CCommand::getCommandName()
{
	switch( type )
		{
			case CMDTYPE_PAINT : return( "���������" );
			case CMDTYPE_MOVE : return( "�������" );
			case CMDTYPE_IF : return( "����" );
		}
	return( "?" );
}

CString CCommand::getCommandString()
{
	return( getCommandName() );
}

CString CCommand::getElseName()
{
	return( "�����" );
}

CString CCommand::getEndifName()
{
	return( "����� ����" );
}

CString CCommand::getEndName()
{
	if( type == CMDTYPE_IF )
		return( "����� ����" );
	if( type == CMDTYPE_WHILE )
		return( "����� �����" );

	ASSERT( FALSE );
	return( "" );
}

void CCommand::setPaint( COLORREF p_color )
{
	type = CMDTYPE_PAINT;
	color = p_color;
}

void CCommand::setMove( char p_direction )
{
	type = CMDTYPE_MOVE;
	direction = p_direction;
}

void CCommand::setIf( CommandCondition p_condition )
{
	type = CMDTYPE_IF;
	condition = p_condition;
}

void CCommand::setWhile( CommandCondition p_condition )
{
	type = CMDTYPE_WHILE;
	condition = p_condition;
}

