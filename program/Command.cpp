// Command.cpp: implementation of the CCommand class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Command.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommand::CCommand()
{
}

CCommand::~CCommand()
{
}

CommandType CCommand::getType()
{
	return( type );
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
