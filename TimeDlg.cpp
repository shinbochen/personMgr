// TimeDlg.cpp : implementation file
//
/////////////////////////////////////////////////////////////////////////////
// include file declare
#include "stdafx.h"
#include "PersonMgr.h"
#include "TimeDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CONSTANTS declare
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTimeDlg dialog


CTimeDlg::CTimeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTimeDlg::IDD, pParent){
	//{{AFX_DATA_INIT(CTimeDlg)
	m_nHour = 0;
	m_nMinute = 0;
	m_nSecond = 0;
	//}}AFX_DATA_INIT
	m_nFocus = 0;
	m_bHaveTime = FALSE;
}


CTimeDlg::CTimeDlg(CString strTime, CWnd* pParent /*=NULL*/)
	: CDialog(CTimeDlg::IDD, pParent){

	m_nHour = 0;
	m_nMinute = 0;
	m_nSecond = 0;
	m_nFocus = 0;

	if( strTime.IsEmpty() ){
		m_bHaveTime = FALSE;
	}
	else{
		int			nCnt;
		CString		strTmp;

		nCnt = strTime.Find( ":" );
		if( nCnt != -1 ){
			strTmp = strTime.Left( nCnt );
			strTime = strTime.Mid( nCnt + 1 );
			m_nHour = atoi( strTmp.GetBuffer( 0 ) );
			if( m_nHour > 23 ){
				m_nHour = 23;
			}
			else if( m_nHour < 0 ){
				m_nHour = 0;
			}
			strTmp.ReleaseBuffer();
		}
		nCnt = strTime.Find( ":" );
		if( nCnt != -1 ){
			strTmp = strTime.Left( nCnt );
			strTime = strTime.Mid( nCnt + 1 );
			m_nMinute = atoi( strTmp.GetBuffer( 0 ) );
			if( m_nMinute > 59 ){
				m_nMinute = 59;
			}
			else if( m_nMinute < 0 ){
				m_nMinute = 0;
			}
			strTmp.ReleaseBuffer();
		}
		m_nSecond = atoi( strTime.GetBuffer( 0 ) );
		if( m_nSecond > 59 ){
			m_nSecond = 59;
		}
		else if( m_nMinute < 0 ){
			m_nSecond = 0;
		}
		strTime.ReleaseBuffer();
		m_bHaveTime = TRUE;
	}

}

void CTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTimeDlg)
	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_UP, m_btUp);
	DDX_Control(pDX, IDC_DOWN, m_btDown);
	DDX_Text(pDX, IDC_EDITHOUR, m_nHour);
	DDV_MinMaxUInt(pDX, m_nHour, 0, 23);
	DDX_Text(pDX, IDC_EDITMINUTE, m_nMinute);
	DDV_MinMaxUInt(pDX, m_nMinute, 0, 59);
	DDX_Text(pDX, IDC_EDITSECOND, m_nSecond);
	DDV_MinMaxUInt(pDX, m_nSecond, 0, 59);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTimeDlg, CDialog)
	//{{AFX_MSG_MAP(CTimeDlg)
	ON_EN_CHANGE(IDC_EDITHOUR, OnChangeEdit)
	ON_EN_SETFOCUS(IDC_EDITHOUR, OnSetfocusEditHour)
	ON_EN_SETFOCUS(IDC_EDITMINUTE, OnSetfocusEditMinute)
	ON_EN_SETFOCUS(IDC_EDITSECOND, OnSetfocusEditSecond)
	ON_EN_KILLFOCUS(IDC_EDITHOUR, OnKillfocusEditHour)
	ON_EN_KILLFOCUS(IDC_EDITMINUTE, OnKillfocusEditMinute)
	ON_EN_KILLFOCUS(IDC_EDITSECOND, OnKillfocusEditSecond)
	ON_BN_CLICKED(IDC_DOWN, OnDown)
	ON_BN_CLICKED(IDC_UP, OnUp)
	ON_EN_CHANGE(IDC_EDITMINUTE, OnChangeEdit)
	ON_EN_CHANGE(IDC_EDITSECOND, OnChangeEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimeDlg message handlers
// initall dialog
BOOL CTimeDlg::OnInitDialog() {
	CDialog::OnInitDialog();

	CEdit*			pEdit;
	CTime			time = CTime::GetCurrentTime();

	m_btUp.LoadBitmaps( IDB_UP, IDB_UP1 );
	m_btDown.LoadBitmaps( IDB_DOWN, IDB_DOWN1 );
	
	pEdit = (CEdit *)GetDlgItem(IDC_EDITHOUR);
	pEdit->SetLimitText( 2 );
	
	pEdit = (CEdit *)GetDlgItem(IDC_EDITMINUTE);
	pEdit->SetLimitText( 2 );
	
	pEdit = (CEdit *)GetDlgItem(IDC_EDITSECOND);
	pEdit->SetLimitText( 2 );

	if( m_bHaveTime == FALSE ){
		m_nHour = time.GetHour();
		m_nMinute = time.GetMinute();
		m_nSecond = time.GetSecond();
	}
	UpdateData( FALSE );

	return TRUE;  
}
/////////////////////////////////////////////////////////////////////////////
// CTimeDlg message handlers
// 
void CTimeDlg::OnChangeEdit() {

	UpdateData( TRUE );
	if( m_nHour > 23 ){
		m_nHour = 23;
	}
	if( m_nMinute > 59 ){
		m_nMinute = 59;
	}
	if( m_nSecond > 59 ){
		m_nSecond = 59;
	}
	UpdateData( FALSE );
	return;	
}
/////////////////////////////////////////////////////////////////////////////
// CTimeDlg message handlers
// 
void CTimeDlg::OnSetfocusEditHour() {
	m_nFocus = HOUR_FOCUS;
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CTimeDlg message handlers
// 
void CTimeDlg::OnSetfocusEditMinute(){
	m_nFocus = MINUTE_FOCUS;
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CTimeDlg message handlers
// 
void CTimeDlg::OnSetfocusEditSecond() {
	m_nFocus = SECOND_FOCUS;
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CTimeDlg message handlers
// 
void CTimeDlg::OnKillfocusEditHour() {
	//m_nFocus &= ~HOUR_FOCUS;
	return;	
}
/////////////////////////////////////////////////////////////////////////////
// CTimeDlg message handlers
// 
void CTimeDlg::OnKillfocusEditMinute() {
	//m_nFocus &= ~MINUTE_FOCUS;
	return;	
}
/////////////////////////////////////////////////////////////////////////////
// CTimeDlg message handlers
// 
void CTimeDlg::OnKillfocusEditSecond() {
	//m_nFocus &= ~SECOND_FOCUS;
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CTimeDlg message handlers
// 
void CTimeDlg::OnUp() {

	CWnd*		pWnd;

	UpdateData();
	if( m_nFocus & HOUR_FOCUS ){
		m_nHour++;
		if( m_nHour > 23 ){
			m_nHour = 0;
		}
		pWnd = GetDlgItem( IDC_EDITHOUR );
		pWnd->SetFocus();
	}
	else if( m_nFocus & MINUTE_FOCUS ){
		m_nMinute++;
		if( m_nMinute > 59 ){
			m_nMinute = 0;
		}
		pWnd = GetDlgItem( IDC_EDITMINUTE );
		pWnd->SetFocus();
	}
	else if( m_nFocus & SECOND_FOCUS ){
		m_nSecond++;
		if( m_nSecond > 59 ){
			m_nSecond = 0;
		}
		pWnd = GetDlgItem( IDC_EDITSECOND );
		pWnd->SetFocus();
	}
	UpdateData(FALSE);
	return;	
}
/////////////////////////////////////////////////////////////////////////////
// CTimeDlg message handlers
// 
void CTimeDlg::OnDown() {

	CWnd*		pWnd;

	UpdateData();
	if( m_nFocus & HOUR_FOCUS ){
		if( m_nHour == 0 ){
			m_nHour = 23;
		}
		else{
			m_nHour--;
		}
		pWnd = GetDlgItem( IDC_EDITHOUR );
		pWnd->SetFocus();
	}
	else if( m_nFocus & MINUTE_FOCUS ){
		if( m_nMinute ==0 ){
			m_nMinute = 59;
		}
		else{
			m_nMinute--;
		}
		pWnd = GetDlgItem( IDC_EDITMINUTE );
		pWnd->SetFocus();
	}
	else if( m_nFocus & SECOND_FOCUS ){
		if( m_nSecond == 0 ){
			m_nSecond = 59;
		}
		else{
			m_nSecond--;
		}
		pWnd = GetDlgItem( IDC_EDITSECOND );
		pWnd->SetFocus();
	}
	UpdateData(FALSE);
	return;		
}
/////////////////////////////////////////////////////////////////////////////
// CTimeDlg message handlers
// 
void CTimeDlg::OnOK() {

	UpdateData();
	CDialog::OnOK();
}
/////////////////////////////////////////////////////////////////////////////
// CTimeDlg message handlers
// function
CString CTimeDlg::GetTimeString(){

	CString			strTime;

	strTime.Format( "%2d:%2d:%2d", m_nHour, m_nMinute, m_nSecond );
	return strTime;
}
