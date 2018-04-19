/////////////////////////////////////////////////////////////////////////////
// AlarmDlg.cpp : implementation file
// include file declare
#include "stdafx.h"
#include "PersonMgr.h"
#include "AlarmDlg.h"
#include "MainFrm.h"

/////////////////////////////////////////////////////////////////////////////
// CAlarmDlg dialog
// CONSTANTS declare
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlarmDlg dialog


CAlarmDlg::CAlarmDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAlarmDlg::IDD, pParent){
	//{{AFX_DATA_INIT(CAlarmDlg)
	m_strAlarmType = _T("");
	m_strNote = _T("");
	m_strTime = _T("");
	//}}AFX_DATA_INIT
	m_bkCr = RGB( 122,200,122 );
}
CAlarmDlg::CAlarmDlg(CString strType, 
					 CString strNote, 
					 CString strMelody,
					 CWnd* pParent )
	: CDialogEx(CAlarmDlg::IDD, pParent){
	m_strAlarmType = strType;
	m_strNote = strNote;
	m_strMelody = strMelody;
	m_bkCr = RGB( 122,200,122 );
	return;
}

void CAlarmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAlarmDlg)
	DDX_Control(pDX, IDCANCEL, m_ctrCancel);
	DDX_Text(pDX, IDC_ALARMTYPE, m_strAlarmType);
	DDX_Text(pDX, IDC_NOTE, m_strNote);
	DDX_Text(pDX, IDC_TIME, m_strTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAlarmDlg, CDialogEx)
	//{{AFX_MSG_MAP(CAlarmDlg)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlarmDlg message handlers

BOOL CAlarmDlg::OnInitDialog(){

	CDialogEx::OnInitDialog();

	CTime		time = CTime::GetCurrentTime();
	CWnd*		pWnd = GetDesktopWindow();
	CMainFrame*	pFrame = (CMainFrame*)AfxGetMainWnd( );
	CString		strTime;
	CRect		rect;
	CRect		rectWindow;
	int			nLeft;
	int			nTop;
	int			nCnt;
	CString		strData;

	nCnt = s_nCnt++;
	
	strTime = time.Format( "%Y/%m/%d %H:%M:%S %A" );
	m_strTime = strTime;

	CenterWindow( );
	GetClientRect( &rect );	
	pWnd->GetClientRect( &rectWindow );

	nLeft = rectWindow.right - rect.Width();
	nTop = rectWindow.bottom- rect.Height() - nCnt*12;

	SetWindowPos( &wndTopMost, nLeft, nTop, 0, 0, /*SWP_NOMOVE|*/SWP_NOSIZE );
	UpdateData( FALSE );
	
	GetDlgItem(IDC_S_ALARMTIME)->GetWindowText(strData);
	strData = pFrame->GetDispPhrase( strData );
	GetDlgItem(IDC_S_ALARMTIME)->SetWindowText(strData);

	GetDlgItem(IDC_S_NOTE)->GetWindowText(strData);
	strData = pFrame->GetDispPhrase( strData );
	GetDlgItem(IDC_S_NOTE)->SetWindowText(strData);

	m_bkBrush.DeleteObject();
	m_bkBrush.CreateSolidBrush( m_bkCr );
	Beep(2000, 200);	
	sndPlaySound(m_strMelody, SND_ASYNC|SND_LOOP);
	return TRUE;  
}

/////////////////////////////////////////////////////////////////////////////
// CAlarmDlg message handlers
void CAlarmDlg::OnCancel() {

	s_nCnt--;	
	sndPlaySound(NULL, SND_ASYNC);
	CDialog::OnCancel();
}
/////////////////////////////////////////////////////////////////////////////
// CAlarmDlg message handlers
HBRUSH CAlarmDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {

	UINT				nID;

	pDC->SetBkMode( TRANSPARENT );
	nID = pWnd->GetDlgCtrlID();
	switch( nID ){
	case IDC_ALARMTYPE:
		pDC->SetTextColor( RGB( 0,0,255 ) );
		break;
	case IDC_NOTE:
		pDC->SetTextColor( RGB( 255,0,0 ) );
		break;
	}
	return m_bkBrush;
}
