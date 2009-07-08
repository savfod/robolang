// RobolangEditWindow.cpp : implementation file
//

#include "stdafx.h"
#include "robolang.h"
#include "RobolangEditWindow.h"
#include "../ProgramUI/ProgramUI.h"
#include "DlgNew.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRobolangEditWindow
IMPLEMENT_DYNCREATE( CRobolangEditWindow , CListView )

/*#########################################################################*/
/*#########################################################################*/

CRobolangEditWindow::CRobolangEditWindow()
{
}

CRobolangEditWindow::~CRobolangEditWindow()
{
}

void CRobolangEditWindow::addCommand( CCommand *command )
{
	CListCtrl &lc = CListView::GetListCtrl();
	addCommand( lc.GetItemCount() , command , 0 );
}

void CRobolangEditWindow::removeAllCommands()
{
	CListCtrl &lc = CListView::GetListCtrl();
	lc.DeleteAllItems();
}

/*#########################################################################*/
/*#########################################################################*/

void CRobolangEditWindow::adjustLastColumnWidth()
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

int CRobolangEditWindow::addCommand( int pos , CCommand *command , int depth )
{
	CListCtrl &lc = CListView::GetListCtrl();

	// command
	CString robot = command -> getRobotName();
	CString cmdLine = command -> getCommandString();
	addItem( pos++ , robot , cmdLine , depth , command );

	// Commands inside command
	CCommandArray& cmdList = command -> primaryChildCommands;
	for( int i = 0; i < cmdList.GetSize(); i++ )
		pos = addCommand( pos , cmdList.GetAt(i), depth + 1 );

	// secondary list - for if/else
	CommandType cmdType = command -> getType();
	if( cmdType == CMDTYPE_IF )
		{
			// check has else section
			CCommandArray& cmdList = command -> secondaryChildCommands;
			if( cmdList.GetSize() > 0 )
				addItem( pos++ , robot , command -> getElseName() , depth , command );

			for( int i = 0; i < cmdList.GetSize(); i++ )
				pos = addCommand( pos , cmdList.GetAt(i), depth + 1 );

			// if termination
			addItem( pos++ , robot , command -> getEndifName() , depth , command );
		}

	return( pos );
}

int CRobolangEditWindow::hitTest( int& subItem ) 
{
	// TODO: Add your message handler code here and/or call default
	CListCtrl &lc = CListView::GetListCtrl();

	CPoint pt;
	::GetCursorPos( &pt );
	ScreenToClient( &pt );

	LVHITTESTINFO ht;
	ht.pt = pt;
	ht.flags = LVHT_ONITEM | LVHT_TORIGHT;
	int item = lc.SubItemHitTest( &ht );
	subItem = ht.iSubItem;

	return( item );
}

void CRobolangEditWindow::addItem( int pos , CString robot , CString command , int depth , void *data )
{
	CListCtrl &lc = CListView::GetListCtrl();

	CString tabbedCommand = addTabulations( command , depth );

	int item = lc.InsertItem( pos , robot );
	lc.SetItemText( item , 1 , tabbedCommand );
	lc.SetItemData( item , ( unsigned long )data );
}

CString CRobolangEditWindow::addTabulations( const CString string , int tabulationCount )
{
	CString result = string;
	for( int i = 0; i < tabulationCount; i++ )
		result.Insert( 0 , "    " ); //  4 spaces

	return result;
}

void CRobolangEditWindow::startSelectRobot( int item )
{
	CCommand *cmd = getCommand( item );
	if( cmd == NULL )
		cmd = insertCommand( item );
}

CCommand *CRobolangEditWindow::getCommand( int item )
{
	CListCtrl &lc = CListView::GetListCtrl();
	return( ( CCommand * )lc.GetItemData( item ) );
}

CCommand *CRobolangEditWindow::insertCommand( int item )
{
	return( NULL );
}

/*#########################################################################*/
/*#########################################################################*/

BEGIN_MESSAGE_MAP(CRobolangEditWindow, CListView)
	//{{AFX_MSG_MAP(CRobolangEditWindow)
	ON_WM_SIZE()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_CONTEXTMENU()
	ON_UPDATE_COMMAND_UI(IDC_CMDNEW, OnUpdateCmdnew)
	ON_COMMAND(IDC_CMDNEW, OnCmdnew)
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
	lc.SetRedraw( true );

	lc.SetExtendedStyle( LVS_EX_GRIDLINES | LVS_EX_FLATSB | LVS_EX_FULLROWSELECT );
	adjustLastColumnWidth();

	lc.SetBkColor( COLORREF( RGB( 255 , 255 , 180 ) ) );
}

BOOL CRobolangEditWindow::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	//Set listCtrl style (Report)
	cs.style |= LVS_REPORT | LVS_NOSORTHEADER | LVS_SINGLESEL;
	
	return CListView::PreCreateWindow(cs);
}

void CRobolangEditWindow::OnSize(UINT nType, int cx, int cy) 
{
	CListView::OnSize(nType, cx, cy);

	adjustLastColumnWidth();
}

/////////////////////////////////////////////////////////////////////////////
// Other

BOOL CRobolangEditWindow::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	if( nHitTest == HTCLIENT )
		{
			int subItem;
			int item = hitTest( subItem );

			if( item >= 0 )
				{
					if( subItem == 0 )
						{
							char *l_IDC_HAND = MAKEINTRESOURCE(32649);
							::SetCursor( ::LoadCursor( NULL , l_IDC_HAND ) );
							return( TRUE );
						}
				}
		}
	
	return CListView::OnSetCursor(pWnd, nHitTest, message);
}

void CRobolangEditWindow::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int subItem;
	int item = hitTest( subItem );

	if( item >= 0 )
		{
			if( subItem == 0 )
				startSelectRobot( item );
		}
	
	CListView::OnLButtonDown(nFlags, point);
}

void CRobolangEditWindow::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	CMenu menu;
	menu.LoadMenu( IDR_MAINFRAME );
	CMenu *mp = menu.GetSubMenu( 2 );

	mp -> TrackPopupMenu( TPM_LEFTALIGN | TPM_LEFTBUTTON , point.x , point.y , this );
}

void CRobolangEditWindow::OnUpdateCmdnew(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CRobolangEditWindow::OnCmdnew() 
{
	// TODO: Add your command handler code here
	CDlgNew::createCommand();
}
