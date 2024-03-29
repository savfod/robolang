// Program.cpp: implementation of the CProgram class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Program.h"
#include "..\programui\ProgramUI.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProgram::CProgram( IControl *p_ic )
:	ic( p_ic )
{
}

CProgram::~CProgram()
{
	clear();
}

void CProgram::clear()
{
	CString key;
	CProcedure *proc;
	for( POSITION pos = procedures.GetStartPosition(); pos != NULL; )
	{
		procedures.GetNextAssoc( pos , key , proc );
		delete proc;
	}
	procedures.RemoveAll();
}

/////////////////////////////////////////////////////////////////////
// Other

void CProgram::createNew()
{
	clear();

	// create empty program
	addProcedure( "main" );

}

CProcedure *CProgram::addProcedure( CString name )
{
	CProcedure *proc;
	if( procedures.Lookup( name , proc ) )
		ASSERT( FALSE );

	// create empty program
	proc = new CProcedure( name );
	procedures.SetAt( name , proc );

	// notify ui
	if( name != "main") //if it is reaction on "create new", the programm didn't chandged
	{
		CProgramUI *ui = ic -> getCProgramUI();
		ui -> onProgramChanged();
	}
	else
	{
		CProgramUI *ui = ic -> getCProgramUI();
		ui -> onProgramNew();
	}
	
	return( proc );
}

CProcedure *CProgram::getMainProcedure()
{
	return( getProcedureByName( "main" ) );
}

CProcedure *CProgram::getProcedureByName( CString name )
{
	CProcedure *proc;
	if( procedures.Lookup( name , proc ) )
		return( proc );
	return( NULL );
}


/////////////////////////////////////////////////////////////////////

int CProgram::getProcedureCount()
{
	return( procedures.GetCount() );
}

CProcedure *CProgram::getProcedureByIndex( int index )
{
	POSITION pos = procedures.GetStartPosition();
	if( pos == NULL )
		return( NULL );

	CString key;
	CProcedure *proc;
	for( int k = 0; k <= index; k++ )
		procedures.GetNextAssoc( pos , key , proc );

	return( proc );			
}

void CProgram::renameProcedure( CProcedure *p , CString newName )
{
	procedures.RemoveKey( p -> name );
	p -> name = newName;
	procedures.SetAt( p -> name , p );

	//not finished ( procedure calls must rename )
	CString key;
	CProcedure *proc;

	// notify
	CProgramUI *ui = ic -> getCProgramUI();
	ui -> onProgramProcRenamed( p );
}

bool CProgram::deleteProcedure( CString name )
{
		//not finished ( procedure calls must be changed )
	CProcedure* p;
	BOOL wasFound = procedures.Lookup( name , p );
	ASSERT( wasFound );
	delete p;
	procedures.RemoveKey( name );

	CProgramUI *ui = ic -> getCProgramUI();
	ui -> onProgramProcDeleted( name );
	
	return( true );
}

/////////////////////////////////////////////////////////////////////
// open/save

CString CProgram::getProgramText()
{
	CString result;

	CString key;
	CProcedure* value;
	POSITION pos = procedures.GetStartPosition();
	while(pos != NULL)
	{
		procedures.GetNextAssoc(pos, key, value);
		
		result += getProcedureText( value );
		if( pos != NULL )
			result += "\r\n";
	}
	stylize( result );
	return result;
}

CString CProgram::getProcedureText(CProcedure *proc)
{
	//procedure
	CString result( "���������" );
	result += ' ';
	result += proc -> name;
	result += "\r\n";

	//commands
	result += getBlockOfCommandsText( &(proc -> commands) );

	return result;
}

CString CProgram::getCommandText( CCommand *cmd )
{
	CString result = cmd -> getCommandString();
	result += "\r\n";

	if( cmd -> isCompound() )
		result += getBlockOfCommandsText( &( cmd -> childCommands ) );
	
	return result;
}

CString CProgram::getBlockOfCommandsText(CCommandArray *commands)
{
	CString result;
	
	result += "{\r\n";
	
	for( int i = 0; i < commands -> GetSize(); i++ )
		result += getCommandText( commands -> GetAt(i) );

	result += "}\r\n";

	return result;
}

void CProgram::setProgram( CString program )
{
	procedures.RemoveAll();
	bool successful = true;
	while( !program.IsEmpty() )
	{
		CProcedure *proc = new CProcedure("NoName");
		if( !readFirstProcedure(*proc, program) )
			successful = false;

		procedures.SetAt( proc -> name, proc);
		skipEmptySymbols( program );
	}
	

	CProgramUI *ui = ic -> getCProgramUI();
	ui -> onProgramOpened( successful );
}

bool CProgram::isLetter(TCHAR c)
{
	return		(
		(( 'a' <= c ) && ( c <= 'z' )) ||
		(( 'A' <= c ) && ( c <= 'Z' )) ||
		(( '�' <= c ) && ( c <= '�' )) ||
		(( '�' <= c ) && ( c <= '�' )) ||
		(c == '_')                     ||
		(c == '�')                     ||
		(c == '�')                     
				);
}

bool CProgram::isValid(TCHAR c)
{
	bool isEmpty = ( c == ' ' || c == '\n' || c == '\t' ); 
	return( !isEmpty );
}


void CProgram::skipEmptySymbols(CString &string)
{
	if( string.IsEmpty() )
		return;
	while( ( !string.IsEmpty() ) && ( !isValid( string.GetAt(0) ) ) )
		string.Delete(0);
}

bool CProgram::readFirstProcedure(CProcedure &proc, CString& string)
{
	skipEmptySymbols( string );
	if( readFirstWord( string ) != (CString)"���������" )
	{
		return false;
	}
	proc.name = readFirstWord( string );
	bool successful = readBlockOfCommands( proc.commands, string );
	return successful;
}

CString CProgram::readFirstWord(CString &string)
{
	skipEmptySymbols( string );
	CString word;
	while( !string.IsEmpty() && isValid( string.GetAt(0) ) && ( word.IsEmpty() || isLetter( string.GetAt(0) ) ) )
	{
		word += string.GetAt(0);
		string.Delete(0);
	} 
	return word;
}

bool CProgram::readBlockOfCommands(CCommandArray &commands, CString &string)
{
	if( readFirstWord( string ) != (CString)'{')
	{
		return false;
	}

	skipEmptySymbols( string );
	
	while( ( !string.IsEmpty() ) && ( string.GetAt(0) != '}' ) )
	{
		CCommand* cmd = new CCommand;
		bool successful = readFirstCommand(*cmd, string);
		skipEmptySymbols( string );
		if( successful )
		{
			commands.Add( cmd );
		}
		else
		{
			if( string.GetAt(0) != '}' )
				return false;
		}
	}
	if( string.GetAt(0) == '}' )
	{
		string.Delete(0);
		return true;
	}
	
	return false;
}

bool CProgram::readFirstCommand(CCommand &cmd, CString &string)
{
	CString word = readFirstWord( string );
	
	//instead of switch
	if( word == CString("����") )
	{
		cmd.type = CMDTYPE_MOVE;

		CString direction = readFirstWord( string );
		if( direction == CString("������") )
			cmd.direction = 'L';
		else if( direction == CString("�������") )
			cmd.direction = 'R';
		else if( direction == CString("�����") )
			cmd.direction = 'U';
		else if( direction == CString("����") )
			cmd.direction = 'D';
		return true;
	}
	else if( word == CString("�������") )
	{
		cmd.type = CMDTYPE_PAINT;

		readFirstWord( string ); // "�"
		CString color = readFirstWord( string );
		
		if( color == CString("�����") )
			cmd.color = RGB(255, 255, 255);
		else if( color == CString("������") || color == CString("������") )// �/�
			cmd.color = RGB(0, 0, 0);
		else if( color == CString("�������") )
			cmd.color = RGB(255, 0, 0);
		else if( color == CString("������") )
			cmd.color = RGB(0, 255, 0);
		else
			cmd.color = RGB(255, 255, 0);
		return true;
	}
	else if( word == CString("�������") )
	{
		cmd.type = CMDTYPE_CALL;
		readFirstWord( string ); // "���������"
		skipSymbol(':', string);
		cmd.callingProcedureName = readFirstWord( string );
		return true;
	}
	else if( word == CString("����") )
	{
		cmd.type = CMDTYPE_WHILE;
		bool successful = readCondition(cmd.condition, string) && readBlockOfCommands( cmd.childCommands, string );
		if(successful)
			return true;
		else 
			return false;
	}	
	else if( word == CString("����") )
	{
		cmd.type = CMDTYPE_IF;
		bool successful = readCondition(cmd.condition, string) && readBlockOfCommands( cmd.childCommands, string );
		if(successful)
			return true;
		else 
			return false;
	}

	return false;
}		

bool CProgram::readCondition(CommandCondition &condition, CString &string)
{
	skipEmptySymbols( string );
	if(string.IsEmpty())
		return false;

	//compose condition or/and
	if( string.GetAt( 0 ) == '(' )
	{
		condition.cond1 = new CommandCondition;
		condition.cond2 = new CommandCondition;
		bool result = true;

		result = result && skipSymbol( '(', string );
		result = result && readCondition( *condition.cond1, string );
		result = result && skipSymbol( ')', string );

		CString word = readFirstWord(string);
		if( word == (CString)"�" )
			condition.type = CONDTYPE_AND;
		else if( word == (CString)"���" )
			condition.type = CONDTYPE_OR;
		else 
			return false;
		
		result = result && skipSymbol( '(', string );
		result = result && readCondition( *condition.cond2, string );
		result = result && skipSymbol( ')', string );

		return result;

	}
	//not ...
	
	if( string.GetAt( 0 ) == '�' )
	{
		readFirstWord( string );

		condition.type = CONDTYPE_NOT;
		bool result = true;
		condition.cond1 = new CommandCondition;
		
		result = result && skipSymbol( '(', string );
		result = result && readCondition( *condition.cond1, string );
		result = result && skipSymbol( ')', string );

		return result;
	}

	//easy conditions
	CString firstWord = readFirstWord( string );
	CString secondWord = readFirstWord( string );
	
	if( secondWord == (CString)"�����" )
	{
		if( firstWord == CString("�����") )
			condition.type = CONDTYPE_WALLLEFT;
		else if( firstWord == CString("������") )
			condition.type = CONDTYPE_WALLRIGHT;
		else if( firstWord == CString("������") )
			condition.type = CONDTYPE_WALLUP;
		else if( firstWord == CString("�����") )
			condition.type = CONDTYPE_WALLDOWN;
		else
			return false;
		return true;	
	}
	else if ( secondWord == (CString)"��������" )
	{
		condition.type = CONDTYPE_NOT;
		
		condition.cond1 = new CommandCondition;


		if( firstWord == CString("�����") )
			condition.cond1 -> type = CONDTYPE_WALLLEFT;
		else if( firstWord == CString("������") )
			condition.cond1 -> type = CONDTYPE_WALLRIGHT;
		else if( firstWord == CString("������") )
			condition.cond1 -> type = CONDTYPE_WALLUP;
		else if( firstWord == CString("�����") )
			condition.cond1 -> type = CONDTYPE_WALLDOWN;
		else
			return false;
		return true;	
	}
	else if ( secondWord == (CString)"���������" )
	{
		condition.type = CONDTYPE_PAINTED;
		
		if( firstWord == CString("����") )
			return true;
		return false;
	}
	else if ( secondWord == (CString)"��" )
	{
		secondWord = readFirstWord( string );
		if( secondWord == (CString)"���������" && firstWord == (CString)"����" )
		{
			condition.cond1 = new CommandCondition;
			condition.type = CONDTYPE_NOT;
			condition.cond1 -> type = CONDTYPE_PAINTED;
			return true;
		}

		return false;
	}

	return false;
}

bool CProgram::skipSymbol(char symbol, CString &string)
{
	skipEmptySymbols( string );
	if(string.IsEmpty())
		return false;
	if(string.GetAt(0) != symbol ) 
	{
		string.Delete(0);
		return false;
	}
	string.Delete(0);
	return true;
}

void CProgram::stylize(CString &string)
{
	int depth = 0;
	int index = 0;
	while( index < string.GetLength() )
	{
		if( string.GetAt( index ) == '\n' )
		{
			//adding tabulations
			for( int i = 0; i < depth; i++ )
			{
				string.Insert( index + 1 , '\t' ); //add \t after \n, 
				index++;
			}
		}
		else if( string.GetAt( index ) == '{' )
			depth++;
		else if( string.GetAt( index ) == '}' )
		{
			depth--;
			
			// for string with }
			if( string.GetAt( index - 1 ) == '\t' ) 
			{
				string.Delete( index - 1 );
				continue;
			}
		}
		index++;
	}
}