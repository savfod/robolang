// robolangView.cpp : implementation of the CRobolangView class
//

#include "stdafx.h"
#include "robolang.h"

#include "robolangDoc.h"
#include "robolangSplitter.h"
#include "robolangView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRobolangView

IMPLEMENT_DYNCREATE(CRobolangView, CView)

BEGIN_MESSAGE_MAP(CRobolangView, CView)
	//{{AFX_MSG_MAP(CRobolangView)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/*#########################################################################*/
/*#########################################################################*/

/////////////////////////////////////////////////////////////////////////////
// CRobolangView construction/destruction

CRobolangView::CRobolangView()
{
	// TODO: add construction code here
}

CRobolangView::~CRobolangView()
{
}

void CRobolangView::createViews( CCreateContext* pContext )
{
	splitter.Create( this , NULL , pContext );
}

/*#########################################################################*/
/*#########################################################################*/

BOOL CRobolangView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CRobolangView drawing

void CRobolangView::OnDraw(CDC* pDC)
{
}

void CRobolangView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// CRobolangView printing

BOOL CRobolangView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRobolangView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRobolangView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CRobolangView diagnostics

#ifdef _DEBUG
void CRobolangView::AssertValid() const
{
	CView::AssertValid();
}

void CRobolangView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRobolangDoc* CRobolangView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRobolangDoc)));
	return (CRobolangDoc*)m_pDocument;
}
#endif //_DEBUG

BOOL CRobolangView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return TRUE;
}

void CRobolangView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if( splitter.m_hWnd != NULL )
		{
			CRect rc;
			GetClientRect( rc );
			splitter.MoveWindow( rc );
		}
}
