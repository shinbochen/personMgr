// SDSetupDlg.cpp : implementation file
//
/////////////////////////////////////////////////////////////////////////////
// include file declare
#include "stdafx.h"
#include "PersonMgr.h"
#include "SDSetupDlg.h"
#include "MainFrm.h"

#include "TimeDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CONSTANTS declare
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSDSetupDlg dialog


CSDSetupDlg::CSDSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSDSetupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSDSetupDlg)
	m_nEnable = 0;
	m_strTime = _T("");
	//}}AFX_DATA_INIT
}

CSDSetupDlg::CSDSetupDlg(CString strTime, BOOL bON, CWnd* pParent /*=NULL*/)
	: CDialog(CSDSetupDlg::IDD, pParent){

	m_strTime = strTime;
	if( bON == TRUE ){
		m_nEnable = 0;
	}
	else{
		m_nEnable = 1;
	}
}


void CSDSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSDSetupDlg)
	DDX_Control(pDX, IDC_COMBO_ONOFF, m_ctrComBox);
	DDX_Control(pDX, IDC_EDITTIME, m_ctrEdit);
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_SETTIME, m_btSetTime);
	DDX_CBIndex(pDX, IDC_COMBO_ONOFF, m_nEnable);
	DDX_Text(pDX, IDC_EDITTIME, m_strTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSDSetupDlg, CDialog)
	//{{AFX_MSG_MAP(CSDSetupDlg)
	ON_EN_KILLFOCUS(IDC_EDITTIME, OnKillfocusEdittime)
	ON_BN_CLICKED(IDC_SETTIME, OnSettime)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSDSetupDlg message handlers

BOOL CSDSetupDlg::OnInitDialog() {

	CDialog::OnInitDialog();

	CMainFrame*			pFrame = (CMainFrame*)AfxGetMainWnd( );
	CString				strData;

	m_ctrEdit.SetEditType( "SIMPLETIME" );
	m_ctrComBox.SetCurSel( m_nEnable );
	UpdateData( FALSE );
	
	m_bkCr = RGB( BKRCOLOR,BKGCOLOR,BKBCOLOR );
	m_bkBrush.CreateSolidBrush( m_bkCr );
	
	GetDlgItem(IDC_S_AUTOONOFF)->GetWindowText( strData );
	strData = pFrame->GetDispPhrase( strData );	
	GetDlgItem(IDC_S_AUTOONOFF)->SetWindowText( strData );

	GetDlgItem(IDC_S_AUTOTIME)->GetWindowText( strData );
	strData = pFrame->GetDispPhrase( strData );	
	GetDlgItem(IDC_S_AUTOTIME)->SetWindowText( strData );

	GetWindowText( strData );
	strData = pFrame->GetDispPhrase( strData );
	SetWindowText( strData );
	return TRUE;  
}
/////////////////////////////////////////////////////////////////////////////
// CSDSetupDlg message handlers
void CSDSetupDlg::OnKillfocusEdittime() {
	CString			strValue;

	if( m_ctrEdit.GetValue( strValue ) == FALSE ){
		m_ctrEdit.SetFocus();
	}
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CSDSetupDlg message handlers
void CSDSetupDlg::OnSettime() {

	UpdateData();

	CTimeDlg			timeDlg( m_strTime );
	if( timeDlg.DoModal() == IDOK ){
		m_strTime = timeDlg.GetTimeString();
		UpdateData( FALSE );
	}
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CSDSetupDlg message handlers
HBRUSH CSDSetupDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor){

	if( pWnd->GetDlgCtrlID() != IDC_EDITTIME ){
		pDC->SetBkMode( TRANSPARENT );
		if( pWnd->GetDlgCtrlID() == IDC_STATIC ){
			pDC->SetTextColor( RGB( 255, 0, 0 ) );
		}
		else{
			pDC->SetTextColor( RGB( 0, 0, 255 ) );
		}
		return m_bkBrush;
	}
	else{
		HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);	
		return hbr;
	}
}
/////////////////////////////////////////////////////////////////////////////
// CSDSetupDlg message handlers
void CSDSetupDlg::OnOK() {

	if( m_ctrEdit.GetValue( m_strTime ) == FALSE ){
		return;
	}
	UpdateData();
	CDialog::OnOK();
}
