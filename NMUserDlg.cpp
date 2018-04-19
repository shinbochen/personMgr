// NMUserDlg.cpp : implementation file
//
/////////////////////////////////////////////////////////////////////////////
// include file declare
#include "stdafx.h"
#include "PersonMgr.h"
#include "NMUserDlg.h"
#include "MainFrm.h"

/////////////////////////////////////////////////////////////////////////////
// CONSTANTS declare
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNMUserDlg dialog
CNMUserDlg::CNMUserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNMUserDlg::IDD, pParent){

	//{{AFX_DATA_INIT(CNMUserDlg)
	m_strNewPSD = _T("");
	m_strCfmPSD = _T("");
	m_strOldPSD = _T("");
	m_strUser = _T("");
	//}}AFX_DATA_INIT
	m_strTitle.Empty();
}
/////////////////////////////////////////////////////////////////////////////
// CNMUserDlg dialog
CNMUserDlg::CNMUserDlg( CMapStringToString* pMap,
					    int nType,
						CWnd* pWnd )
	: CDialog(CNMUserDlg::IDD, pWnd){

	m_pMapUserPSD = pMap;
	m_nType = nType;
	if( m_nType == NEWUSER ){
		m_strTitle = "New User...";
	}
	else if( m_nType == CHGPSD ){
		m_strTitle = "Change User Password...";
	}
	else if( m_nType == DELETEUSER ){
		m_strTitle = "Delete User...";
	}
}
/////////////////////////////////////////////////////////////////////////////
// CNMUserDlg dialog
void CNMUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNMUserDlg)
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_USERVALUE, m_ctrCombo);
	DDX_Text(pDX, IDC_NEWPSDVALUE, m_strNewPSD);
	DDX_Text(pDX, IDC_CFMPSDVALUE, m_strCfmPSD);
	DDX_Text(pDX, IDC_OLDPSDVALUE, m_strOldPSD);
	DDX_CBString(pDX, IDC_USERVALUE, m_strUser);
	//}}AFX_DATA_MAP
}
/////////////////////////////////////////////////////////////////////////////
// CNMUserDlg dialog
BEGIN_MESSAGE_MAP(CNMUserDlg, CDialog)
	//{{AFX_MSG_MAP(CNMUserDlg)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNMUserDlg message handlers
BOOL CNMUserDlg::OnInitDialog(){

	CMainFrame*			pFrame = (CMainFrame*)AfxGetMainWnd( );

	CDialog::OnInitDialog();

	
	m_bkCr = RGB( BKRCOLOR,BKGCOLOR,BKBCOLOR );
	m_bBrush.CreateSolidBrush( m_bkCr );

	if( m_pMapUserPSD != NULL ){

		CString			strKey;
		CString			strValue;
		POSITION		pos;

		pos = m_pMapUserPSD->GetStartPosition();
		while( pos != NULL ){
			m_pMapUserPSD->GetNextAssoc( pos, strKey, strValue );
			m_ctrCombo.AddString( strKey );
		}
		
		GetDlgItem(IDC_USERNAME)->GetWindowText(strKey); 
		strKey = pFrame->GetDispPhrase( strKey );
		GetDlgItem(IDC_USERNAME)->SetWindowText(strKey);
	
		GetDlgItem(IDC_OLDPSDNAME)->GetWindowText(strKey); 
		strKey = pFrame->GetDispPhrase( strKey );
		GetDlgItem(IDC_OLDPSDNAME)->SetWindowText(strKey);
	
		GetDlgItem(IDC_NEWPSDNAME)->GetWindowText(strKey); 
		strKey = pFrame->GetDispPhrase( strKey );
		GetDlgItem(IDC_NEWPSDNAME)->SetWindowText(strKey);
	
		GetDlgItem(IDC_CFMPSDNAME)->GetWindowText(strKey); 
		strKey = pFrame->GetDispPhrase( strKey );
		GetDlgItem(IDC_CFMPSDNAME)->SetWindowText(strKey);

		if( m_nType == NEWUSER ){
			GetDlgItem( IDC_OLDPSDNAME )->ShowWindow( SW_HIDE );			
			GetDlgItem( IDC_OLDPSDVALUE )->ShowWindow( SW_HIDE );
		}
		else if( m_nType == DELETEUSER ){
			GetDlgItem( IDC_NEWPSDNAME )->ShowWindow( SW_HIDE );			
			GetDlgItem( IDC_NEWPSDVALUE )->ShowWindow( SW_HIDE );
			GetDlgItem( IDC_CFMPSDNAME )->ShowWindow( SW_HIDE );			
			GetDlgItem( IDC_CFMPSDVALUE )->ShowWindow( SW_HIDE );
		}
	}	
	SetWindowText( pFrame->GetDispPhrase(m_strTitle) );
	UpdateData( FALSE );
	
	return TRUE;  
}
/////////////////////////////////////////////////////////////////////////////
// CNMUserDlg message handlers
BOOL CNMUserDlg::ChkDataValid(){

	UpdateData();

	if( m_strUser.IsEmpty() ){
		MessageBox( "User Name Can't be Empty!" );
		GetDlgItem( IDC_USERVALUE )->SetFocus();
		return FALSE;
	}

	if( m_nType != DELETEUSER ){
		if( m_strCfmPSD != m_strNewPSD ){
			MessageBox( "The Confirmation Password is not correct" );
			GetDlgItem( IDC_CFMPSDVALUE )->SetFocus();
			return FALSE;
		}
	}

	// ÐÂÓÃ»§
	if( IsNewUser( m_strUser ) ) {
		if( m_nType != NEWUSER ){
			MessageBox( "This User not exists! Please select another!" );
			GetDlgItem( IDC_USERVALUE )->SetFocus();
			return FALSE;
		}
	}
	else{
		if( m_nType == NEWUSER ){
			MessageBox( "This User already exists! please input new! " );
			GetDlgItem( IDC_USERVALUE )->SetFocus();
			return FALSE;
		}
		else if( m_nType == DELETEUSER ){
			if( m_strUser == "Admin" ){
				MessageBox( "This User(Admin) Can't be delete! " );
				GetDlgItem( IDC_USERVALUE )->SetFocus();
				return FALSE;
			}
		}
	}
	
	// change Password
	if( m_nType == CHGPSD || m_nType == DELETEUSER ){
		CString			strOldPSD;

		m_pMapUserPSD->Lookup( m_strUser, strOldPSD );
		if( strOldPSD != m_strOldPSD ){
			GetDlgItem( IDC_OLDPSDVALUE )->SetFocus();
			MessageBox( "The Old Password is not correct" );
			return FALSE;
		}
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CNMUserDlg message handlers
BOOL CNMUserDlg::IsNewUser( CString strUser ){
	
	POSITION			pos;
	CString				strKey;
	CString				strValue;

	pos = m_pMapUserPSD->GetStartPosition();
	while( pos != NULL ){
		
		m_pMapUserPSD->GetNextAssoc( pos, strKey, strValue );
		if( strKey == strUser ){
			return FALSE;		
		}
	}
	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
// CNMUserDlg message handlers
void CNMUserDlg::OnOK() {
	if( ChkDataValid() == FALSE ){
		return;
	}
	CDialog::OnOK();
}
/////////////////////////////////////////////////////////////////////////////
// CNMUserDlg message handlers
// redraw the window
HBRUSH CNMUserDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {

	pDC->SetBkMode( TRANSPARENT );
	return m_bBrush;
}
