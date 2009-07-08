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
	s.Format( "–Œ¡Œ“ %d" , robot );
	return( s );
}

CString CCommand::getCommandName()
{
	switch( type )
		{
			case CMDTYPE_PAINT : return( "«¿ –¿—»“‹" );
			case CMDTYPE_MOVE : return( "œ≈–≈…“»" );
			case CMDTYPE_IF : return( "≈—À»" );
		}
	return( "?" );
}

CString CCommand::getCommandString()
{
	return( getCommandName() );
}

CString CCommand::getElseName()
{
	return( "»Õ¿◊≈" );
}

CString CCommand::getEndifName()
{
	return( " ŒÕ≈÷ ≈—À»" );
}
