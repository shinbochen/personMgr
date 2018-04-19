// DateDlg.cpp : implementation file
//
/////////////////////////////////////////////////////////////////////////////
// include file declare
#include "stdafx.h"
#include "PersonMgr.h"
#include "DateDlg.h"

#include "TimeDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CONSTANTS declare
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDateDlg dialog


CDateDlg::CDateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDateDlg)
	m_strTime = _T("");
	//}}AFX_DATA_INIT
}


void CDateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDateDlg)
	DDX_Control(pDX, IDC_SETTIME, m_btSetTime);
	DDX_Control(pDX, IDOK, m_ctrOK);
	DDX_Control(pDX, IDCANCEL, m_ctrCancel);
	DDX_Text(pDX, IDC_TIME, m_strTime);
	DDX_Control(pDX, IDC_CALENDAR1, m_ctrCalendar);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDateDlg, CDialogEx)
	//{{AFX_MSG_MAP(CDateDlg)
	ON_BN_CLICKED(IDC_SETTIME, OnSetTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDateDlg message handlers
BOOL CDateDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();

	m_strTime.Empty();

	m_ctrCalendar.Today();
	UpdateData( FALSE );
	
	return TRUE;  
}
/////////////////////////////////////////////////////////////////////////////
// CDateDlg message handlers
void CDateDlg::OnSetTime() {

	UpdateData( );
	CTimeDlg			timeDlg( m_strTime );

	if( timeDlg.DoModal() == IDOK ){
		GetDlgItem(IDC_TIME)->SetWindowText( timeDlg.GetTimeString() );
	}
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CDateDlg message handlers
CString CDateDlg::GetDateString(){

	return m_strDate;
}
/////////////////////////////////////////////////////////////////////////////
// CDateDlg message handlers
void CDateDlg::OnOK() {
	UpdateData();
	if( m_ctrCalendar.GetDay() == 0 ){
		MessageBox( "Please select a day First!" );
		return;
	}
	m_strDate.Format( "%d-%d-%d ",
					  m_ctrCalendar.GetYear(),
					  m_ctrCalendar.GetMonth(),
					  m_ctrCalendar.GetDay() );
	m_strDate += m_strTime;
	CDialogEx::OnOK();
}

BEGIN_EVENTSINK_MAP(CDateDlg, CDialogEx)
    //{{AFX_EVENTSINK_MAP(CDateDlg)
	ON_EVENT(CDateDlg, IDC_CALENDAR1, -601 /* DblClick */, OnDblClickCalendar1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CDateDlg::OnDblClickCalendar1() {

	OnOK();
	return;
}
