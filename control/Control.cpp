// Control.cpp: implementation of the CControl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Control.h"
#include "..\program\program.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CControl::CControl( IControl *p_ic )
:	ic( p_ic )
{
}

CControl::~CControl()
{
}

void CControl::newProgram()
{
	CProgram *prog = ic -> getCProgram();
	CRoboMap *map = ic -> getCRoboMap();

	prog -> createNew();
}
