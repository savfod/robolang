// Control.h: interface for the CControl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTROL_H__A5996464_A2C1_4ABB_A5B5_EEAA5382D49C__INCLUDED_)
#define AFX_CONTROL_H__A5996464_A2C1_4ABB_A5B5_EEAA5382D49C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CControl;
class CProgram;
class CProcedure;
class CProgramUI;
class CRoboMap;
class CRoboMapUI;
class CInterpreter;

/*#########################################################################*/
/*#########################################################################*/

// application interface
class IControl
{
public:
	static IControl *getInstance();

	CControl *getCControl() { return( vCControl ); };
	CProgram *getCProgram() { return( vCProgram ); };
	CProgramUI *getCProgramUI() { return( vCProgramUI ); };
	CRoboMap *getCRoboMap() { return( vCRoboMap ); };
	CRoboMapUI *getCRoboMapUI() { return( vCRoboMapUI ); };
	CInterpreter *getCInterpreter() { return( vCInterpreter ); };

public:
	// generic functions
	virtual void messageBox( CString msg ) = 0;
	virtual void removeProcedures() = 0;
	virtual void addProcedure( CProcedure *p ) = 0;

protected:
	// core classes - singletons
	CControl *vCControl;
	CProgram *vCProgram;
	CProgramUI *vCProgramUI;
	CRoboMap *vCRoboMap;
	CRoboMapUI *vCRoboMapUI;
	CInterpreter *vCInterpreter;
};

/*#########################################################################*/
/*#########################################################################*/

// controller class
class CControl  
{
public:
	CControl( IControl *ic );
	virtual ~CControl();

	void onAppProcActivated( CString name );
	bool onAppDeleteProc( CString name );
	CProcedure *onAppCreateProcedure();
	bool onAppRenameProcedure( CProcedure *p , CString newName );
	
	void onAppNewProgram();
	void onProgNewProgram();
private:
	IControl *ic;
};

/*#########################################################################*/
/*#########################################################################*/

#endif // !defined(AFX_CONTROL_H__A5996464_A2C1_4ABB_A5B5_EEAA5382D49C__INCLUDED_)
