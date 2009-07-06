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

/////////////////////////////////////////////////////////////////////////////
// CRobolangEditWindow
IMPLEMENT_DYNCREATE( CRobolangEditWindow , CListView )

CRobolangEditWindow::CRobolangEditWindow()
{
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
	
	// Insert columns
	CListCtrl& lc = GetListCtrl();
	if( lc.GetHeaderCtrl() -> GetItemCount() > 0 )
		return;
	
 	//get width
	CRect rect;
	GetClientRect( rect );

	lc.SetRedraw( false );
	lc.InsertColumn( 0, "Робот", LVCFMT_LEFT, 100);
	lc.InsertColumn( 1, "Команда", LVCFMT_LEFT, 100);
	lc.InsertColumn( 2, "Параметры", LVCFMT_LEFT);
	lc.SetRedraw( true );

	lc.SetExtendedStyle( LVS_EX_GRIDLINES | LVS_EX_FLATSB );
	AdjustLastColumnWidth();
}

BOOL CRobolangEditWindow::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	//Set listCtrl style (Report)
	cs.style |= LVS_REPORT | LVS_NOSORTHEADER | LVS_SINGLESEL | LVS_SHOWSELALWAYS;
	
	return CListView::PreCreateWindow(cs);
}

void CRobolangEditWindow::OnSize(UINT nType, int cx, int cy) 
{
	CListView::OnSize(nType, cx, cy);

	AdjustLastColumnWidth();
}

void CRobolangEditWindow::AdjustLastColumnWidth()
{
	CListCtrl& lc = GetListCtrl();
	CHeaderCtrl *hc = lc.GetHeaderCtrl();
	if( hc -> GetItemCount() == 0 )
		return;

	int width = 0;
	for( int k = hc -> GetItemCount() - 2; k >= 0; k-- )
		{
			CRect hrc;
			hc -> GetItemRect( k , hrc );
			width += hrc.Width();
		}

	CRect rc;
	GetClientRect( rc );

	if( rc.Width() > width )
		{
			HDITEM item;
			item.mask = HDI_WIDTH;
			item.cxy = rc.Width() - width;
			hc -> SetItem( hc -> GetItemCount() - 1 , &item );
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

CString CRobolangEditWindow::AddTabulations(const CString string, int tabulationCount)
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
