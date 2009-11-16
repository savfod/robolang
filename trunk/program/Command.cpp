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
	condition.type =  CONDTYPE_UNKNOWN;
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
	callingProcedureName = cmdData -> callingProcedureName;
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
			case CMDTYPE_CALL : return( "ВЫЗВАТЬ" );
		}
	return( "?" );
}

CString CommandCondition::getConditionName()
{
	switch( type )
	{
		case CONDTYPE_WALLLEFT : return( " слева стена " );
		case CONDTYPE_WALLRIGHT : return( " справа стена " );
		case CONDTYPE_WALLUP : return( " сверху стена " );
		case CONDTYPE_WALLDOWN : return( " снизу стена " );
		case CONDTYPE_PAINTED : return( " поле закрашено " );
		case CONDTYPE_OR: return( " (" + cond1->getConditionName() + ")" + " или " + "(" + cond2->getConditionName() + " )" );
		case CONDTYPE_AND: return( " (" + cond1->getConditionName() + ")" + " и " + "(" + cond2->getConditionName() + " )" );
		
		case CONDTYPE_NOT: 
		{
			switch( cond1 -> type )
			{
				case CONDTYPE_WALLLEFT : return( " слева свободно " );
				case CONDTYPE_WALLRIGHT : return( " справа свободно " );
				case CONDTYPE_WALLUP : return( " сверху свободно " );
				case CONDTYPE_WALLDOWN : return( " снизу свободно " );
				case CONDTYPE_PAINTED : return( " поле не закрашено " );

				case CONDTYPE_NOT : return cond1 -> cond1 -> getConditionName();
			}
			return (" не " + (CString)"(" + cond1->getConditionName() + ") ");
		}
	}
	return( " условие отсутствует " );
}

CommandCondition CommandCondition::getCopy()
{
	CommandCondition res;
	res.type = type;
	switch( type )
	{
		
		case CONDTYPE_OR: 
		case CONDTYPE_AND:
		{
			//will be here in cases: Or/And
			res.cond2 = new CommandCondition;
			*(res.cond2) = cond2 -> getCopy(); 
		}
		case CONDTYPE_NOT:
		{
			//will be here in cases: Or/And/Not
			res.cond1 = new CommandCondition;
			*(res.cond1) = cond1 -> getCopy(); 
		}
	}

	return( res );
}

CommandCondition::CommandCondition()
{
	type = CONDTYPE_UNKNOWN;
	cond1 = cond2 = NULL;
}

CommandCondition::~CommandCondition()
{
/*	if(cond1)	
		delete cond1;
	if(cond2)
		delete cond2;*/
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
					case ( RGB( 255 , 255 , 0 ) ) : return( "Красить в жёлтый" );
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
				return CString("Если ") + condition.getConditionName();
			}
			case CMDTYPE_WHILE : 
			{
				return CString("Пока ") + condition.getConditionName();
			}
			case CMDTYPE_CALL : 
			{
				CString s = "Вызвать продедуру: ";
				s += callingProcedureName;
				return( s );
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

void CCommand::setCall( CString name )
{
	type = CMDTYPE_CALL;
	callingProcedureName = name;
}

void CCommand::setIf( CommandConditionType p_condition )
{
	type = CMDTYPE_IF;
	condition.type = p_condition;
}

void CCommand::setIfC( CommandCondition p_condition )
{
	type = CMDTYPE_IF;
	condition = p_condition;
}

void CCommand::setIfNot( CommandConditionType p_condition )
{
	type = CMDTYPE_IF;
	condition.type = CONDTYPE_NOT;
	condition.cond1 = new CommandCondition;
	condition.cond1 -> type = p_condition;
}

void CCommand::setWhile( CommandConditionType p_condition )
{
	type = CMDTYPE_WHILE;
	condition.type = p_condition;
}

void CCommand::setWhileC( CommandCondition p_condition )
{
	type = CMDTYPE_WHILE;
	condition = p_condition;
}

void CCommand::setWhileNot( CommandConditionType p_condition )
{
	type = CMDTYPE_WHILE;
	condition.type = CONDTYPE_NOT;
	condition.cond1 = new CommandCondition;
	condition.cond1 -> type = p_condition;
}

void CCommand::onProcRenamed( CString oldName, CString newName )
{
	if( type == CMDTYPE_CALL && callingProcedureName == oldName )
		callingProcedureName = newName;

	if( isCompound() )
		for(int i = 0; i < childCommands.GetSize() ; i++ )
			childCommands.GetAt(i) -> onProcRenamed( oldName, newName );
}

