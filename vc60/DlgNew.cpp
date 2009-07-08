// DlgNew.cpp : implementation file
//

#include "stdafx.h"
#include "robolang.h"
#include "DlgNew.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNew dialog


CDlgNew::CDlgNew(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNew::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNew)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CCommand *CDlgNew::createCommand()
{
	CDlgNew l_dlg;
	l_dlg.DoModal();

	return( NULL );
}

void CDlgNew::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNew)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgNew, CDialog)
	//{{AFX_MSG_MAP(CDlgNew)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNew message handlers
