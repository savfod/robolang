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

