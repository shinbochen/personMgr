// DialogEx.cpp : implementation file
//

#include "stdafx.h"
#include "PersonMgr.h"
#include "DialogEx.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define		OFFSET		6

/////////////////////////////////////////////////////////////////////////////
// CDialogEx dialog


CDialogEx::CDialogEx(UINT nID, CWnd* pParent /*=NULL*/)
	: CDialog(nID, pParent){
	//{{AFX_DATA_INIT(CDialogEx)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

}


void CDialogEx::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogEx)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogEx, CDialog)
	//{{AFX_MSG_MAP(CDialogEx)
	ON_WM_CREATE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogEx message handlers

int CDialogEx::OnCreate(LPCREATESTRUCT lpCreateStruct){

	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	CenterWindow();

	if( ((CMainFrame*)AfxGetMainWnd())->IsDynamicDlg() == FALSE ){
		return 0;
	}

	srand( (unsigned)time( NULL ) );
	m_nType = rand() % 5;

	SetTimer(IDC_TIMER, 10, NULL);

	GetClientRect(&m_nRect);
	m_nRect.bottom += 20;
	ClientToScreen(&m_nRect);

	if ( m_nType == 0 ){
		m_nX = m_nRect.left + m_nRect.Width()/2;
		m_nY = m_nRect.top + m_nRect.Height()/2;
		m_nX2 = m_nX + 2;
		m_nY2 = m_nY + 2;
	}
	else if ( m_nType == 1 ){
		m_nX = m_nRect.left + m_nRect.Width()/2;
		m_nY = m_nRect.top;
		m_nX2 = m_nX + 2;
		m_nY2 = m_nRect.bottom;
	}
	else if ( m_nType == 2 ){
		m_nX = m_nRect.left;
		m_nY = m_nRect.top + m_nRect.Height()/2;
		m_nX2 = m_nRect.right;
		m_nY2 = m_nY + 2;
	}
	else if ( m_nType == 3 ){
		m_nX = m_nRect.left;
		m_nY = m_nRect.top ;
		m_nX2 = m_nX + 2;
		m_nY2 = m_nRect.bottom ;
	}
	else {
		m_nX = m_nRect.right-2;
		m_nY = m_nRect.top;
		m_nX2 = m_nX + 2;
		m_nY2 = m_nRect.bottom;
	}
	MoveWindow(m_nX, m_nY, m_nX2-m_nX, m_nY2-m_nY);
	
	return 0;
}
/////////////////////////////////////////////////////////////////////////////
// CDialogEx 时间信息

void CDialogEx::OnTimer(UINT nIDEvent) {

	int			nFlag = 0;

	if ( nIDEvent == IDC_TIMER ){
		if ( m_nX > m_nRect.left ){
			m_nX -= OFFSET;
		}
		else{
			m_nX = m_nRect.left;
			nFlag |= 0x01;
		}		
		if ( m_nY > m_nRect.top ){
			m_nY -= OFFSET;
		}
		else{
			m_nY = m_nRect.top;
			nFlag |= 0x02;
		}

		if ( m_nX2 < m_nRect.right ){
			m_nX2 += OFFSET;
		}
		else{
			m_nX2 = m_nRect.right;
			nFlag |= 0x04;
		}		
		if ( m_nY2 < m_nRect.bottom ){
			m_nY2 += OFFSET;
		}
		else{
			m_nY2 = m_nRect.bottom;
			nFlag |= 0x08;
		}

	
		if( nFlag == 0x0f ){
			KillTimer(IDC_TIMER);
		}
		else{
			MoveWindow(m_nX, m_nY, m_nX2-m_nX, m_nY2-m_nY);
		}
	}	
	CDialog::OnTimer(nIDEvent);
}
