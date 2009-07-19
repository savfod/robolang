// robolangDoc.cpp : implementation of the CRobolangDoc class
//

#include "stdafx.h"
#include "robolang.h"

#include "robolangDoc.h"
#include "..\program\program.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRobolangDoc

IMPLEMENT_DYNCREATE(CRobolangDoc, CDocument)

BEGIN_MESSAGE_MAP(CRobolangDoc, CDocument)
	//{{AFX_MSG_MAP(CRobolangDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRobolangDoc construction/destruction

CRobolangDoc::CRobolangDoc()
{
	// TODO: add one-time construction code here

}

CRobolangDoc::~CRobolangDoc()
{
}

BOOL CRobolangDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CRobolangDoc serialization

void CRobolangDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		CProgram *prog = IControl::getInstance() -> getCProgram();
		CString text = prog -> getProgramText();
		ar.WriteString( text );
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRobolangDoc diagnostics

#ifdef _DEBUG
void CRobolangDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRobolangDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRobolangDoc commands


