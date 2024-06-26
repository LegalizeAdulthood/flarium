/// Flarium24.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Flarium24.h"

#include "MainFrm.h"
#include "Flarium24Doc.h"
#include "Flarium24View.h"
#include "external.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////
// Global variables
 
BOOL			bStretchToFit;
BOOL			bFitToPage;
BOOL			bNewView, bNewViewSave, bZoomingMode, bJuliaMode;
BOOL			bAutoTile;
BOOL			bGlobalDraw;

int				global_width;
int				global_height;

CString		szTempFileName = "Flarium.tmp";
CString		szFluFileName = "Flarium.flu";
CString		szColorFileName = "Flarium.clr";

/////////////////////////////////////////////////////////////////////////////
// CFlarium24App

BEGIN_MESSAGE_MAP(CFlarium24App, CWinApp)
	//{{AFX_MSG_MAP(CFlarium24App)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlarium24App construction

CFlarium24App::CFlarium24App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CFlarium24App object

CFlarium24App theApp;

/////////////////////////////////////////////////////////////////////////////
// CFlarium24App initialization

BOOL CFlarium24App::InitInstance()
{
  CStdioFile    outFile;

	bAutoTile = FALSE;
	bNewView = TRUE;
	global_width	= 320;   // 320
	global_height = 240;	 // 240
	
	bFitToPage = FALSE;
	bStretchToFit = FALSE;

  if (!outFile.Open( szTempFileName, 
     		CFile::modeWrite | CFile::modeCreate))
  {
    AfxMessageBox ( "Error, Opening File:" + szTempFileName );
		outFile.Close();
		return FALSE;
	}	
	else
	{
		szTempFileName = outFile.GetFilePath();	
	}
	outFile.Close();

  if (outFile.Open( szColorFileName, CFile::modeRead))
	{
		szColorFileName = outFile.GetFilePath();	
		outFile.Close();
	}

  if (outFile.Open( szFluFileName, CFile::modeRead))	
	{
		szFluFileName = outFile.GetFilePath();	
		outFile.Close();
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_FLARIUTYPE,
		RUNTIME_CLASS(CFlarium24Doc),
		RUNTIME_CLASS(CMDIChildWnd),
		RUNTIME_CLASS(CFlarium24View));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pMainFrame->UpdateWindow();

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
void CFlarium24App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CFlarium24App commands

BOOL CFlarium24App::OnIdle(LONG lCount) 
{
	BOOL Result = CWinApp::OnIdle(lCount);
 	m_pMainWnd->SendMessage(WM_COMMAND, ID_APPLICATION_IDLE);

	if (bGlobalDraw)
		return TRUE;
	else
		return FALSE;
}

int CFlarium24App::ExitInstance() 
{
	TRY
	{
	  CFile::Remove( szTempFileName );
	}
	CATCH( CFileException, e )
	{
    AfxMessageBox("File: " + szTempFileName + " cannot be removed");
	}
	END_CATCH
 
	return CWinApp::ExitInstance();
}
