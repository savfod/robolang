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

void CCommand::setProps( CCommand *cmdData )
{
	robot = cmdData -> robot;
	type = cmdData -> type;
	color = cmdData -> color;
	direction = cmdData -> direction;
	condition = cmdData -> condition;
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
	switch( type )
		{
			case CMDTYPE_PAINT : 
			{
				switch( color )
				{
					case ( RGB( 0 , 0 , 0 ) ) : return( "������� � ������" );
					case ( RGB( 255 , 255 , 255  ) ) : return( "������� � �����" );
					case ( RGB( 255 , 0 , 0 ) ) : return( "������� � �������" );
					case ( RGB( 255 , 0 , 255 ) ) : return( "������� � �����" );
					case ( RGB( 0 , 255 , 0 ) ) : return( "������� � ������" );
				}
				return("������� � ��������� ����");
			}

			case CMDTYPE_MOVE : 
			{
				switch( direction )
				{
					case 'L' : return( "���� ������" );
					case 'R' : return( "���� �������" );
					case 'U' : return( "���� �����" );
					case 'D' : return( "���� ����" );
				}
				return( "���� � ����������� �����������" );
			}							
			case CMDTYPE_IF : 
			{
				switch( condition )
				{
					case CMDCOND_WALLLEFT : return( "���� ����� �����" );
					case CMDCOND_WALLRIGHT : return( "���� ������ �����" );
					case CMDCOND_WALLUP : return( "���� ������ �����" );
					case CMDCOND_WALLDOWN : return( "���� ����� �����" );
				}
				return( "���� �� ����� ���" );
			}
			case CMDTYPE_WHILE : 
			{
				switch( condition )
				{
					case CMDCOND_WALLLEFT : return( "���� ����� �����" );
					case CMDCOND_WALLRIGHT : return( "���� ������ �����" );
					case CMDCOND_WALLUP : return( "���� ������ �����" );
					case CMDCOND_WALLDOWN : return( "���� ����� �����" );
				}
				return( "���� �� ����� ���" );
			}
	}
	return( "?" );
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

