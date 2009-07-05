// Command.h: interface for the CCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMAND_H__36DD0D80_1E8D_4CA5_BFF4_D65E19CF461B__INCLUDED_)
#define AFX_COMMAND_H__36DD0D80_1E8D_4CA5_BFF4_D65E19CF461B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <afxtempl.h>


class CCommand  
{
public:
	CCommand();
	virtual ~CCommand();
	
	CString Name;
	CArray<CCommand*, CCommand*> Commands;
};

#endif // !defined(AFX_COMMAND_H__36DD0D80_1E8D_4CA5_BFF4_D65E19CF461B__INCLUDED_)
