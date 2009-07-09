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

/*#########################################################################*/
/*#########################################################################*/

CDlgNew::CDlgNew(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNew::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNew)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	cmd = NULL;
	currentColor = RGB( 200 , 200 , 180 );
}

CCommand *CDlgNew::createCommand()
{
	CDlgNew l_dlg;
	l_dlg.DoModal();

	return( l_dlg.cmd );
}

bool CDlgNew::updateCommand( CCommand *cmd )
{
	CDlgNew dlg;
	dlg.cmd = cmd;

	return( dlg.DoModal() == IDOK );
}

/*#########################################################################*/
/*#########################################################################*/

void CDlgNew::enableControls( CommandType type )
{
}

/*#########################################################################*/
/*#########################################################################*/

void CDlgNew::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNew)
	DDX_Control(pDX, IDC_RECT, m_wndColor);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgNew, CDialog)
	//{{AFX_MSG_MAP(CDlgNew)
	ON_BN_CLICKED(IDC_CMDTYPEIF, OnCmdtypeif)
	ON_BN_CLICKED(IDC_CMDTYPEMOVE, OnCmdtypemove)
	ON_BN_CLICKED(IDC_CMDTYPEPAINT, OnCmdtypepaint)
	ON_BN_CLICKED(IDC_COLOR, OnColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNew message handlers

void CDlgNew::OnCmdtypeif() 
{
	// TODO: Add your control notification handler code here
	enableControls( CMDTYPE_IF );
}

void CDlgNew::OnCmdtypemove() 
{
	// TODO: Add your control notification handler code here
	enableControls( CMDTYPE_MOVE );
}

void CDlgNew::OnCmdtypepaint() 
{
	// TODO: Add your control notification handler code here
	enableControls( CMDTYPE_PAINT );
}

void CDlgNew::OnColor() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgNew::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

BOOL CDlgNew::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CheckRadioButton( IDC_CMDTYPEPAINT , IDC_CMDTYPEIF , IDC_CMDTYPEPAINT );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
