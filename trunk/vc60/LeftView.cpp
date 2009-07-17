// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "robolang.h"

#include "robolangDoc.h"
#include "LeftView.h"
#include "..\program\program.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	//{{AFX_MSG_MAP(CLeftView)
	ON_NOTIFY_REFLECT(TVN_BEGINLABELEDIT, OnBeginlabeledit)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CTreeView::OnFilePrintPreview)
END_MESSAGE_MAP()

#define TREEITEMTYPE_PROCHEADING	1
#define TREEITEMTYPE_PROC			2
#define TREEITEMTYPE_PROCMAIN		3
#define TREEITEMTYPE_HISTORYHEADING	4
#define TREEITEMTYPE_HISTORY		5

/////////////////////////////////////////////////////////////////////////////
// CLeftView construction/destruction

/*#########################################################################*/
/*#########################################################################*/

CLeftView::CLeftView()
{
	// TODO: add construction code here

}

CLeftView::~CLeftView()
{
}

void CLeftView::removeProcedures()
{
	CTreeCtrl& tc = GetTreeCtrl();
	HTREEITEM item = getProceduresItem();
	if( item == NULL )
		return;
	
	while( true )
		{
			HTREEITEM ci = tc.GetChildItem( item );
			if( ci == NULL )
				break;

			tc.DeleteItem( ci );
		}
}

void CLeftView::addProcedure( CProcedure *p )
{
	HTREEITEM parent = getProceduresItem();

	CString name = p -> name;
	int type = ( p -> isMain() )? TREEITEMTYPE_PROCMAIN : TREEITEMTYPE_PROC;
	addItem( parent , name , type );

	CTreeCtrl& tc = GetTreeCtrl();
	tc.SortChildren( parent );
}

/*#########################################################################*/
/*#########################################################################*/

HTREEITEM CLeftView::addItem( HTREEITEM parent , CString name , int type )
{
	CTreeCtrl& tc = GetTreeCtrl();

	HTREEITEM item = tc.InsertItem( name , parent );
	tc.SetItemData( item , ( DWORD )type );

	return( item );
}

HTREEITEM CLeftView::getProceduresItem()
{
	CTreeCtrl& tc = GetTreeCtrl();
	HTREEITEM item = tc.GetRootItem();

	while( item != NULL )
		{
			int type = getItemType( item );
			if( type == TREEITEMTYPE_PROCHEADING )
				return( item );

			item = tc.GetNextSiblingItem( item );
		}

	return( NULL );
}

int CLeftView::getItemType( HTREEITEM item )
{
	CTreeCtrl& tc = GetTreeCtrl();
	return( ( int )tc.GetItemData( item ) );
}

/*#########################################################################*/
/*#########################################################################*/

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= TVS_DISABLEDRAGDROP | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_EDITLABELS; 

	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView drawing

void CLeftView::OnDraw(CDC* pDC)
{
	CRobolangDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView printing

BOOL CLeftView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLeftView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLeftView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: You may populate your TreeView with items by directly accessing
	//  its tree control through a call to GetTreeCtrl().
	addItem( NULL , "Процедуры текущей программы" , TREEITEMTYPE_PROCHEADING );
	addItem( NULL , "Известные программы" , TREEITEMTYPE_HISTORYHEADING );
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CRobolangDoc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRobolangDoc)));
	return (CRobolangDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftView message handlers

void CLeftView::OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here

	int type = getItemType( pTVDispInfo -> item.hItem );
	*pResult = ( type == TREEITEMTYPE_PROC )? 0 : 1;
}
