// RobolangEditWindow.cpp : implementation file
//

#include "stdafx.h"
#include "robolang.h"
#include "RobolangEditWindow.h"
#include "../ProgramUI/ProgramUI.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CRobolangEditWindow* CRobolangEditWindow::_pointer = NULL;

/////////////////////////////////////////////////////////////////////////////
// CRobolangEditWindow
IMPLEMENT_DYNCREATE( CRobolangEditWindow , CListView )

CRobolangEditWindow::CRobolangEditWindow()
{
	_pointer = this;
}

CRobolangEditWindow::~CRobolangEditWindow()
{
}


BEGIN_MESSAGE_MAP(CRobolangEditWindow, CListView)
	//{{AFX_MSG_MAP(CRobolangEditWindow)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




/////////////////////////////////////////////////////////////////////////////
// CRobolangEditWindow message handlers

void CRobolangEditWindow::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();
	
	// Insert a column. 
	LVCOLUMN col;
	col.mask = LVCF_WIDTH;
	if(!GetListCtrl().GetColumn(0, &col)) 
	{
 		//get width
		RECT rect;
		CRobolangEditWindow::GetWindowRect(&rect);
		int width = rect.right - rect.left;
		TRACE("%d", width);

		ASSERT(GetStyle() & LVS_REPORT);
		GetListCtrl().InsertColumn(0, "", LVCFMT_LEFT, 100);
	}

	//Upload initial test
	(CProgramUI::Instance()) -> ReUploadProgramm();

	

}

BOOL CRobolangEditWindow::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	//Set listCtrl style (Report)
	cs.style = (cs.style | LVS_REPORT);
	
	return CListView::PreCreateWindow(cs);
}

void CRobolangEditWindow::OnSize(UINT nType, int cx, int cy) 
{
	CListView::OnSize(nType, cx, cy);
	
	LVCOLUMN col;
	col.mask = LVCF_WIDTH;
	if(GetListCtrl().GetColumn(0, &col)) 
	{
		col.cx = cx;
		GetListCtrl().SetColumn(0, &col);
	}
}




/////////////////////////////////////////////////////////////////////////////
// Other

void CRobolangEditWindow::ShowCommand( CCommand* command )
{
	ShowCommand(command, 0);
}

void CRobolangEditWindow::ShowCommand( CCommand* command, int tabulationCount)
{
	//command
	int itemCount = GetListCtrl().GetItemCount();
	int currentItem = GetListCtrl().InsertItem(itemCount, AddTabulations((command->Name), tabulationCount));
	GetListCtrl().SetItemData(currentItem, (DWORD)command);

	//Commands inside command
	for (int i = 0; i < (command->Commands).GetSize(); i++)
	{
		ShowCommand( (command->Commands).GetAt(i), tabulationCount + 1);
	}

}

CString CRobolangEditWindow::AddTabulations(CString string, int tabulationCount)
{
	CString result = string;
	for(int i = 0; i < tabulationCount; i++)
	{
		result.Insert(0, "    "); //  4 spaces
	}
	return result;
}

void CRobolangEditWindow::RemoveAllCommands()
{
	GetListCtrl().DeleteAllItems();
}

CRobolangEditWindow* CRobolangEditWindow::GetPointer()
{
	return _pointer;
}