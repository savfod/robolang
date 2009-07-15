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
	s.Format( "РОБОТ %d" , robot );
	return( s );
}

CString CCommand::getCommandName()
{
	switch( type )
		{
			case CMDTYPE_PAINT : return( "ЗАКРАСИТЬ" );
			case CMDTYPE_MOVE : return( "ПЕРЕЙТИ" );
			case CMDTYPE_IF : return( "ЕСЛИ" );
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
					case ( RGB( 0 , 0 , 0 ) ) : return( "Красить в чёрный" );
					case ( RGB( 255 , 255 , 255  ) ) : return( "Красить в белый" );
					case ( RGB( 255 , 0 , 0 ) ) : return( "Красить в красный" );
					case ( RGB( 255 , 0 , 255 ) ) : return( "Красить в жёлтый" );
					case ( RGB( 0 , 255 , 0 ) ) : return( "Красить в зелёный" );
				}
				return("Красить в необычный цвет");
			}

			case CMDTYPE_MOVE : 
			{
				switch( direction )
				{
					case 'L' : return( "Идти налево" );
					case 'R' : return( "Идти направо" );
					case 'U' : return( "Идти вверх" );
					case 'D' : return( "Идти вниз" );
				}
				return( "идти в неизвестном направлении" );
			}							
			case CMDTYPE_IF : 
			{
				switch( condition )
				{
					case CMDCOND_WALLLEFT : return( "Если слева стена" );
					case CMDCOND_WALLRIGHT : return( "Если справа стена" );
					case CMDCOND_WALLUP : return( "Если сверху стена" );
					case CMDCOND_WALLDOWN : return( "Если снизу стена" );
				}
				return( "Если не пойми что" );
			}
			case CMDTYPE_WHILE : 
			{
				switch( condition )
				{
					case CMDCOND_WALLLEFT : return( "Пока слева стена" );
					case CMDCOND_WALLRIGHT : return( "Пока справа стена" );
					case CMDCOND_WALLUP : return( "Пока сверху стена" );
					case CMDCOND_WALLDOWN : return( "Пока снизу стена" );
				}
				return( "Пока не пойми что" );
			}
	}
	return( "?" );
}

CString CCommand::getElseName()
{
	return( "Иначе" );
}

CString CCommand::getEndifName()
{
	return( "Конец если" );
}

CString CCommand::getEndName()
{
	if( type == CMDTYPE_IF )
		return( "Конец если" );
	if( type == CMDTYPE_WHILE )
		return( "Конец цикла" );

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

