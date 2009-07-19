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

#define LINETYPE_PROCEDURE			1
#define LINETYPE_ONELINECOMMAND		2
#define LINETYPE_COMMANDSTART		3
#define LINETYPE_COMMANDSTOP		4

/*#########################################################################*/
/*#########################################################################*/

CRobolangEditWindow::CRobolangEditWindow()
{
}

CRobolangEditWindow::~CRobolangEditWindow()
{
}

void CRobolangEditWindow::setProcedure( CProcedure *proc )
{
	CListCtrl &lc = CListView::GetListCtrl();

	removeAllCommands();

	// procedure
	CString cmdLine = proc -> getProcLine();
	CString robot( "" );
	int pos = lc.GetItemCount(); 
	addItem( pos++ , robot , cmdLine , 0 , LINETYPE_PROCEDURE , proc ); //itemData - Procedure*!

	// Commands inside command
	CCommandArray& cmdList = proc -> commands;
	for( int i = 0; i < cmdList.GetSize(); i++ )
		pos = addCommand( pos , cmdList.GetAt(i), 1 );
}

void CRobolangEditWindow::removeAllCommands()
{
	CListCtrl &lc = CListView::GetListCtrl();
	lc.DeleteAllItems();
}

void CRobolangEditWindow::notifyProcRenamed( CProcedure *p )
{
	int item = getProcedureItem( p );
	CString line = p -> getProcLine();
	
	CListCtrl &lc = CListView::GetListCtrl();
	lc.SetItemText( item, 1, line );
}

/*#########################################################################*/
/*#########################################################################*/

void CRobolangEditWindow::addCommand( CCommand *command )
{
	CListCtrl &lc = CListView::GetListCtrl();
	addCommand( lc.GetItemCount() , command , 0 );
}

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

	int opType = ( command -> isCompound() )? LINETYPE_COMMANDSTART : LINETYPE_ONELINECOMMAND;
	addItem( pos++ , robot , cmdLine , depth , opType , command );

	// secondary list - for if
	if( command -> isCompound() )
		{
			// check has else section
			CCommandArray& cmdList = command -> childCommands;
			for( int i = 0; i < cmdList.GetSize(); i++ )
				pos = addCommand( pos , cmdList.GetAt(i), depth + 1 );

			// compound termination
			addItem( pos++ , robot , command -> getEndName() , depth , LINETYPE_COMMANDSTOP , command );
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

void CRobolangEditWindow::addItem( int pos , CString robot , CString command , int depth , short type , void *data )
{
	CListCtrl &lc = CListView::GetListCtrl();

	CString tabbedCommand = addTabulations( command , depth );

	int item = lc.InsertItem( pos , robot );
	lc.SetItemData( item , ( unsigned long )data );
	lc.SetItemText( item , 1 , tabbedCommand );

	LVITEM lvi;
	lvi.iItem = pos;
	lvi.iSubItem = 0;
	lvi.mask = LVIF_IMAGE;
	lvi.iImage = type;
	lc.SetItem( &lvi );
}

short CRobolangEditWindow::getItemType( int pos )
{
	CListCtrl &lc = CListView::GetListCtrl();

	LVITEM lvi;
	lvi.iItem = pos;
	lvi.iSubItem = 0;
	lvi.mask = LVIF_IMAGE;
	if( lc.GetItem( &lvi ) < 0 )
		return( 0 );

	return( ( short )lvi.iImage );
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
		return;

	short type = getItemType( item );
}

CCommand *CRobolangEditWindow::getCommand( int item )
{
	CListCtrl &lc = CListView::GetListCtrl();

	short type = getItemType( item );
	if( type == LINETYPE_PROCEDURE )
		return( NULL );

	return( ( CCommand * )lc.GetItemData( item ) );
}

CCommand *CRobolangEditWindow::getCurrentCommand()
{
	int item = getCurrentItem();
	if( item < 0 )
		return( NULL );

	return( getCommand( item ) );
}

int CRobolangEditWindow::getCurrentItem()
{
	CListCtrl &lc = CListView::GetListCtrl();
	int item = lc.GetNextItem( -1 , LVNI_SELECTED );

	return( item );
}

int CRobolangEditWindow::getProcedureItem( CProcedure *p )
{
	CListCtrl &lc = CListView::GetListCtrl();
	int n = lc.GetItemCount();
	for( int i = 0; i < n; i++ )
	{
		int type = getItemType( i );
		if( type == LINETYPE_PROCEDURE )
		{
			CProcedure* pLine = ( CProcedure* ) lc.GetItemData( i );
			if( pLine == p )
				return i;
		}
	}
	return -1;
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
	ON_COMMAND(IDC_CMDCHANGE, OnCmdchange)
	ON_UPDATE_COMMAND_UI(IDC_CMDCHANGE, OnUpdateCmdchange)
	ON_COMMAND(IDC_CMDDELETE, OnCmddelete)
	ON_UPDATE_COMMAND_UI(IDC_CMDDELETE, OnUpdateCmddelete)
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE( IDC_CMDRANGE_FIRST , IDC_CMDRANGE_LAST , OnCmdRange )
	ON_UPDATE_COMMAND_UI_RANGE( IDC_CMDRANGE_FIRST , IDC_CMDRANGE_LAST , OnUpdateCmdRange )
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

	mp -> TrackPopupMenu( TPM_LEFTALIGN | TPM_LEFTBUTTON , point.x , point.y , AfxGetMainWnd() );
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

void CRobolangEditWindow::OnCmdchange() 
{
	// TODO: Add your command handler code here
	CCommand *cmd = getCurrentCommand();
	if( cmd == NULL )
		return;

	CDlgNew::updateCommand( cmd );
}

void CRobolangEditWindow::OnUpdateCmdchange(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CCommand *cmd = getCurrentCommand();
	pCmdUI -> Enable( cmd != NULL );
}

void CRobolangEditWindow::OnCmddelete() 
{
	// TODO: Add your command handler code here
	CCommand *cmd = getCurrentCommand();
	if( cmd == NULL )
		return;

	CProgramUI *ui = IControl::getInstance() -> getCProgramUI();
	ui -> onEditDelete( cmd );
}

void CRobolangEditWindow::OnUpdateCmddelete(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CCommand *cmd = getCurrentCommand();
	pCmdUI -> Enable( cmd != NULL );
}

void CRobolangEditWindow::OnCmdRange( UINT nCmd )
{
	int item = getCurrentItem();
	CCommand *cmd = NULL;
	if( item >= 0 )
		cmd = getCommand( item );

	// change command - if shift pressed
	bool change = ( ::GetKeyState( VK_SHIFT ) & 0x8000 )? true : false;
	if( change == true && cmd != NULL )
		{
			CDlgNew::setCommand( cmd , nCmd );
			return;
		}

	// find parent - if current command != NULL, for compound operator on LINETYPE_COMMANDSTOP (then before is NULL), otherwise it is "before" command
	CCommand *parent = NULL;
	CCommand *before = NULL;
	if( cmd != NULL )
		if( cmd -> isCompound() && getItemType( item ) == LINETYPE_COMMANDSTOP )
			parent = cmd;
		else
			before = cmd;

	CDlgNew::createCommand( nCmd , parent , before );
}

void CRobolangEditWindow::OnUpdateCmdRange(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CCommand *cmd = getCurrentCommand();
	pCmdUI -> Enable( TRUE );
}
