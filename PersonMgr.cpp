// PersonMgr.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "PersonMgr.h"

#include "MainFrm.h"
#include "PersonMgrDoc.h"
#include "PersonMgrTreeView.h"
#include "PersonMgrListView.h"

#include "buttonex.h"
#include "superlink.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrApp

BEGIN_MESSAGE_MAP(CPersonMgrApp, CWinApp)
	//{{AFX_MSG_MAP(CPersonMgrApp)
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
// CPersonMgrApp construction

CPersonMgrApp::CPersonMgrApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPersonMgrApp object

CPersonMgrApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrApp initialization

BOOL CPersonMgrApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// ³õÊ¼»¯COM
	// AfxOleInit();
	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Lanna Tech Studio"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CPersonMgrDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CPersonMgrTreeView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_HIDE);
	m_pMainWnd->UpdateWindow();

	POSITION			pos = NULL;
	CPersonMgrDoc*		pDoc = NULL;

	pos = pDocTemplate->GetFirstDocPosition( );
	pDoc = (CPersonMgrDoc*)pDocTemplate->GetNextDoc( pos );
	if( pDoc->Login() == FALSE ){
		return FALSE;
	}
	
	pDoc->m_bLogin = TRUE;
	
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();

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
	CButtonEx	m_btOK;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
public:
	
	CSuperLink			m_ctrWebsite;
	CSuperLink			m_ctrEmail;
	COLORREF			m_bkCr;
	CBrush				m_bkBrush;

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
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
	DDX_Control(pDX, IDOK, m_btOK);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CPersonMgrApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CPersonMgrApp message handlers
BOOL CAboutDlg::OnInitDialog() {

	CString			strInfo;

	CDialog::OnInitDialog();
	m_ctrWebsite.SubclassDlgItem( IDC_WEBSITE, this );
	m_ctrWebsite.SetSuperLink( TRUE );
	m_ctrWebsite.SetLinkCursor(AfxGetApp()->LoadCursor(IDC_HAND));
	m_ctrWebsite.GetWindowText( strInfo );
	m_ctrWebsite.SetLinkAddress( strInfo );

	m_ctrEmail.SubclassDlgItem( IDC_EMAIL, this );
	m_ctrEmail.SetSuperLink(TRUE );
	m_ctrEmail.SetLinkCursor(AfxGetApp()->LoadCursor(IDC_HAND));
	m_ctrEmail.GetWindowText( strInfo );
	m_ctrEmail.SetLinkAddress(strInfo);

	strInfo.LoadString( IDS_VERSION );
	GetDlgItem(IDC_VERSION)->SetWindowText( strInfo );

	m_bkCr = RGB( BKRCOLOR,BKGCOLOR,BKBCOLOR );
	m_bkBrush.CreateSolidBrush( m_bkCr );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
/////////////////////////////////////////////////////////////////////////////
// CPersonMgrApp message handlers
HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {

	pDC->SetBkMode( TRANSPARENT );
	if( pWnd->GetDlgCtrlID() == IDC_HELPINFO ){
		pDC->SetTextColor( RGB(0,0,255) );
	}
	else if (pWnd->GetDlgCtrlID() == IDC_WEBSITE ){
		m_ctrWebsite.CtlColor( pDC, nCtlColor );
	}
	else if (pWnd->GetDlgCtrlID() == IDC_EMAIL ){
		m_ctrEmail.CtlColor( pDC, nCtlColor );
	}
	return m_bkBrush;
}
