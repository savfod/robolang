// robolang.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "robolang.h"

#include "MainFrm.h"
#include "robolangDoc.h"
#include "LeftView.h"
#include "RobolangSplitter.h"
#include "RobolangEditWindow.h"
#include "RobolangView.h"
#include "RobolangMapWindow.h"

#include "..\interpreter\interpreter.h"
#include "..\program\program.h"
#include "..\programui\programui.h"
#include "..\map\RoboMap.h"
#include "..\mapui\RoboMapUI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRobolangApp

BEGIN_MESSAGE_MAP(CRobolangApp, CWinApp)
	//{{AFX_MSG_MAP(CRobolangApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRobolangApp construction

/*#########################################################################*/
/*#########################################################################*/

CRobolangApp::CRobolangApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	initMode = true;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CRobolangApp object

CRobolangApp theApp;

IControl *IControl::getInstance()
{
	return( &theApp );
}

// operations
void CRobolangApp::messageBox( CString msg )
{
	AfxMessageBox( msg );
}

void CRobolangApp::removeProcedures()
{
	CLeftView *lv = getControlWindow();
	lv -> removeProcedures();
}

void CRobolangApp::addProcedure( CProcedure *p )
{
	CLeftView *lv = getControlWindow();
	lv -> addProcedure( p );
}

/*#########################################################################*/
/*#########################################################################*/

void CRobolangApp::createClasses()
{
	CMainFrame *mainframe = ( CMainFrame * )AfxGetMainWnd();
	CLeftView *controlWindow = ( CLeftView * )mainframe -> m_wndSplitter.GetPane( 0 , 0 );
	CRobolangView *rightView = mainframe -> GetRightPane();
	CRobolangEditWindow *editWindow = ( CRobolangEditWindow * )rightView -> splitter.GetPane( 0 , 0 );
	CRobolangMapWindow *mapWindow = ( CRobolangMapWindow * )rightView -> splitter.GetPane( 1 , 0 );

	IControl::vCInterpreter = new CInterpreter( this );
	IControl::vCProgram = new CProgram( this );
	IControl::vCRoboMap = new CRoboMap( this );
	IControl::vCControl = new CControl( this );
	IControl::vCProgramUI = new CProgramUI( editWindow );
	IControl::vCRoboMapUI = new CRoboMapUI( mapWindow );
}

CLeftView *CRobolangApp::getControlWindow()
{
	CMainFrame *mainframe = ( CMainFrame * )AfxGetMainWnd();
	CLeftView *controlWindow = ( CLeftView * )mainframe -> m_wndSplitter.GetPane( 0 , 0 );

	return( controlWindow );
}

/*#########################################################################*/
/*#########################################################################*/

/////////////////////////////////////////////////////////////////////////////
// CRobolangApp initialization

BOOL CRobolangApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CRobolangDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CLeftView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	( ( CMainFrame * )m_pMainWnd ) -> resizeSplitters();
	m_pMainWnd->UpdateWindow();

	createClasses();
	initMode = false;
	OnFileNew();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CRobolangApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CRobolangApp message handlers

void CRobolangApp::OnFileNew() 
{
	// TODO: Add your command handler code here
	if( initMode )
		{
			CWinApp::OnFileNew();
			return;
		}

	IControl::vCControl -> onAppNewProgram();
}

int CRobolangApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete IControl::vCInterpreter;
	delete IControl::vCProgram;
	delete IControl::vCRoboMap;
	delete IControl::vCRoboMapUI;
	delete IControl::vCProgramUI;
	delete IControl::vCControl;
	
	return CWinApp::ExitInstance();
}
