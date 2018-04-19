// StatusBarEx.cpp: implementation of the CStatusBarEx class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PersonMgr.h"
#include "StatusBarEx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CStatusBarEx, CStatusBar)

BEGIN_MESSAGE_MAP(CStatusBarEx, CStatusBar)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CStatusBarEx::CStatusBarEx(){

	m_BKCr = RGB( BKRCOLOR,BKGCOLOR,BKBCOLOR );
	m_BKBrush.CreateSolidBrush( m_BKCr );
}

CStatusBarEx::~CStatusBarEx()
{

}

/////////////////////////////////////////////////////////////////////////////
// CStatusBarEx message handlers
BOOL CStatusBarEx::OnEraseBkgnd(CDC* pDC){

	CRect			nRect;
	GetClientRect( &nRect );
	pDC->FillSolidRect( &nRect, m_BKCr );
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CStatusBarEx message handlers

HBRUSH CStatusBarEx::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor){
	//HBRUSH hbr = CStatusBar::OnCtlColor(pDC, pWnd, nCtlColor);
	
	pDC->SetBkMode( TRANSPARENT );
	if( pWnd->GetDlgCtrlID() == ID_INDICATOR_AUTO ){
		pDC->SetTextColor( RGB(255,0,0) );
	}
	return m_BKBrush;
	//return hbr;
}

/////////////////////////////////////////////////////////////////////////////
// CStatusBarEx message handlers
int CStatusBarEx::OnCreate(LPCREATESTRUCT lpCreateStruct) {

	if (CStatusBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CStatusBarCtrl&		statusCtrl = GetStatusBarCtrl();

	statusCtrl.SetBkColor( m_BKCr );
	return 0;
}