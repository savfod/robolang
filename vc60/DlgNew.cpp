// DlgNew.cpp : implementation file
//

#include "stdafx.h"
#include "robolang.h"

#include "..\programui\programui.h"
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

bool CDlgNew::setCommand( CCommand *cmd , int nCmd )
{
	CCommand cmdCopy;
	CDlgNew::setCommandTo( &cmdCopy , nCmd );

	CProgramUI *ui = IControl::getInstance() -> getCProgramUI();
	
	ui -> onEditUpdate( cmd , &cmdCopy );
	return( true );
}

bool CDlgNew::createCommand( int nCmd , CCommand *parent , CCommand *before )
{
	CCommand *cmd = new CCommand;
	CDlgNew::setCommandTo( cmd , nCmd );

	CProgramUI *ui = IControl::getInstance() -> getCProgramUI();
	ui -> onEditAdd( cmd , parent , before );
	return( true );
}

void CDlgNew::setCommandTo( CCommand *cmd , int nCmd )
{
	switch( nCmd )
		{
			case IDC_CMDPAINT_BLACK              :	cmd -> setPaint( RGB( 0 , 0 , 0 ) ); break;
			case IDC_CMDPAINT_WHITE              :	cmd -> setPaint( RGB( 255 , 255 , 255 ) ); break;
			case IDC_CMDPAINT_RED                :	cmd -> setPaint( RGB( 255 , 0 , 0 ) ); break;
			case IDC_CMDPAINT_YELLOW             :	cmd -> setPaint( RGB( 255 , 255 , 0 ) ); break;
			case IDC_CMDPAINT_GREEN              :	cmd -> setPaint( RGB( 0 , 255 , 0 ) ); break;
			case IDC_CMDMOVE_LEFT                :	cmd -> setMove( 'L' ); break;
			case IDC_CMDMOVE_RIGHT               :	cmd -> setMove( 'R' ); break;
			case IDC_CMDMOVE_UP                  :	cmd -> setMove( 'U' ); break;
			case IDC_CMDMOVE_DOWN                :	cmd -> setMove( 'D' ); break;
			case IDC_CMDIF_WALLLEFT              :	cmd -> setIf( CMDCOND_WALLLEFT ); break;
			case IDC_CMDIF_WALLRIGHT             :	cmd -> setIf( CMDCOND_WALLRIGHT ); break;
			case IDC_CMDIF_WALLUP                :	cmd -> setIf( CMDCOND_WALLUP ); break;
			case IDC_CMDIF_WALLDOWN              :	cmd -> setIf( CMDCOND_WALLDOWN ); break;
			case IDC_CMDIF_PAINTED               :	cmd -> setIf( CMDCOND_PAINTED ); break;
			case IDC_CMDWHILE_WALLLEFT           :	cmd -> setWhile( CMDCOND_WALLLEFT ); break;
			case IDC_CMDWHILE_WALLRIGHT          :	cmd -> setWhile( CMDCOND_WALLRIGHT ); break;
			case IDC_CMDWHILE_WALLUP             :	cmd -> setWhile( CMDCOND_WALLUP ); break;
			case IDC_CMDWHILE_WALLDOWN           :	cmd -> setWhile( CMDCOND_WALLDOWN ); break;
			case IDC_CMDWHILE_PAINTED            :	cmd -> setWhile( CMDCOND_PAINTED ); break;

			default :
				if( nCmd >= IDC_CMDPROC_CALLFIRST )
					{
						// get procedure by corresponding index
						CProgram *prog = IControl::getInstance() -> getCProgram();
						CProcedure *p = prog -> getProcedureByIndex( nCmd - IDC_CMDPROC_CALLFIRST );
						cmd -> setCall( p -> name );
						break;
					}

				AfxMessageBox( "Unknown command" );
				break;
		}
}

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
