// LoginDlg.cpp : implementation file
//
/////////////////////////////////////////////////////////////////////////////
// include file declare
#include "stdafx.h"
#include "PersonMgr.h"
#include "LoginDlg.h"
#include "picture.h"
#include "MainFrm.h"

/////////////////////////////////////////////////////////////////////////////
// CONSTANTS declare
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog
CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent){
	//{{AFX_DATA_INIT(CLoginDlg)
	m_strPSD = _T("");
	m_strUser = _T("");
	//}}AFX_DATA_INIT
	m_pMapUserPSD = NULL;
}

CLoginDlg::CLoginDlg(CMapStringToString* pMap, CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent){

	m_pMapUserPSD = pMap;
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX){
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDlg)
	DDX_Control(pDX, IDC_LOGINBMP, m_ctrLogBmp);
	DDX_Control(pDX, IDC_HELPINFO, m_btHelp);
	DDX_Control(pDX, IDOK, m_ctrOK);
	DDX_Control(pDX, IDCANCEL, m_ctrCancel);
	DDX_Control(pDX, IDC_USERCOMBO, m_ctrCombo);
	DDX_Text(pDX, IDC_PSDEDIT, m_strPSD);
	DDX_CBString(pDX, IDC_USERCOMBO, m_strUser);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	//{{AFX_MSG_MAP(CLoginDlg)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_HELPINFO, OnHelp)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg message handlers
BOOL CLoginDlg::OnInitDialog(){

	CDialog::OnInitDialog();

	m_bkCr = RGB( BKRCOLOR,BKGCOLOR,BKBCOLOR );

	if( m_pMapUserPSD != NULL ){

		CString			strKey;
		CString			strValue;
		POSITION		pos;
		int				nCnt = 0;

		pos = m_pMapUserPSD->GetStartPosition();
		while( pos != NULL ){
			m_pMapUserPSD->GetNextAssoc( pos, strKey, strValue );
			m_ctrCombo.AddString( strKey );
			if( nCnt == 0 ){
				m_strUser = strKey;
				nCnt = 1;
			}
		}
	}	
	m_bkBrush.DeleteObject();
	m_bkBrush.CreateSolidBrush( m_bkCr );
	UpdateData( FALSE );
	GetDlgItem( IDC_PSDEDIT )->SetFocus();

	CString			strData;
	CMainFrame*		pFrame = (CMainFrame*)AfxGetMainWnd( );

	GetDlgItem(IDC_S_USER)->GetWindowText( strData );
	strData = pFrame->GetDispPhrase( strData );
	GetDlgItem(IDC_S_USER)->SetWindowText( strData );

	GetDlgItem(IDC_S_PASSWORD)->GetWindowText( strData );
	strData = pFrame->GetDispPhrase( strData );
	GetDlgItem(IDC_S_PASSWORD)->SetWindowText( strData );

	
	GetDlgItem(IDC_S_DEFAULTPASSWORD)->GetWindowText( strData );
	strData = pFrame->GetDispPhrase( strData );
	GetDlgItem(IDC_S_DEFAULTPASSWORD)->SetWindowText( strData );

	GetWindowText( strData );
	strData = pFrame->GetDispPhrase( strData );
	SetWindowText( strData );
	return FALSE;	              
}

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg message handlers
void CLoginDlg::OnOK() {
	
	UpdateData( TRUE );
	CDialog::OnOK();
}
/////////////////////////////////////////////////////////////////////////////
// CLoginDlg message handlers
void CLoginDlg::OnPaint() {

	//CPaintDC			dc(this); 
	CDialog::OnPaint();


	CPicture			pic;
	CString				strPath;
	CRect				rect;
	CDC*				pDC = m_ctrLogBmp.GetDC();

	m_ctrLogBmp.GetClientRect( &rect );
	m_ctrLogBmp.RedrawWindow();


	strPath = GetModulePath() + "\\login.jpg";

	if( pic.Load(strPath) == TRUE ){
		pic.Render( pDC, &rect );
	}
	ReleaseDC( pDC );
	return;	
}
/////////////////////////////////////////////////////////////////////////////
// CLoginDlg message handlers
HBRUSH CLoginDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
	UINT				nID;

	pDC->SetBkMode( TRANSPARENT );
	nID = pWnd->GetDlgCtrlID();
	switch( nID ){
	case IDC_STATIC:
		pDC->SetTextColor( RGB( 0,0,0 ) );
		break;
	default:
		pDC->SetTextColor( RGB( 0,0,255 ) );
		break;
	}
	return m_bkBrush;
}
/////////////////////////////////////////////////////////////////////////////
// CLoginDlg message handlers
void CLoginDlg::OnHelp() {
	CString			strPath;

	strPath = GetModulePath( ) +"\\PersonMgrHelp.chm";
	/*if( HtmlHelp(NULL,
		(LPCSTR)strPath, 
		HH_DISPLAY_TOPIC, 
		NULL) == NULL ){
		AfxMessageBox( "Can't find PersonMgrHelp.chm!" );
	
	}*/
	return;
}

