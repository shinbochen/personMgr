// RegDlg.cpp : implementation file
//
/////////////////////////////////////////////////////////////////////////////
// include file declare
#include "stdafx.h"
#include "PersonMgr.h"
#include "RegDlg.h"


/////////////////////////////////////////////////////////////////////////////
// CONSTANTS declare
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



//extern BOOL WINAPI GetIDESerial( CString& strText );
//extern CString WINAPI GetRegisterCode( CString strSN );
//extern BOOL  GetIDESeriala( CString& strText );
//extern CString  GetRegisterCodea( CString strSN );
/////////////////////////////////////////////////////////////////////////////
// CRegDlg dialog


CRegDlg::CRegDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRegDlg::IDD, pParent){

	//{{AFX_DATA_INIT(CRegDlg)
	m_strRegCode = _T("");
	//}}AFX_DATA_INIT
}


void CRegDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegDlg)
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Text(pDX, IDC_REGISTERCODE, m_strRegCode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRegDlg, CDialogEx)
	//{{AFX_MSG_MAP(CRegDlg)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegDlg message handlers
BOOL CRegDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();
	
	CString				strSN;
	CString				strInfo;

	// GetIDESeriala( strSN );
	GetDlgItem( IDC_MACHINECODE )->SetWindowText( strSN );
	
	m_bkCr = RGB( BKRCOLOR,BKGCOLOR,BKBCOLOR );
	m_bkBrush.CreateSolidBrush( m_bkCr );

	
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

	return TRUE;  
}
/////////////////////////////////////////////////////////////////////////////
// CRegDlg message handlers
HBRUSH CRegDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
	
	pDC->SetBkMode( TRANSPARENT );
	if (pWnd->GetDlgCtrlID() == IDC_WEBSITE ){
		m_ctrWebsite.CtlColor( pDC, nCtlColor );
	}
	else if (pWnd->GetDlgCtrlID() == IDC_EMAIL ){
		m_ctrEmail.CtlColor( pDC, nCtlColor );
	}
	return m_bkBrush;
}
/////////////////////////////////////////////////////////////////////////////
// CRegDlg message handlers
void CRegDlg::OnOK() {

	UpdateData();	
	CDialogEx::OnOK();
}
