// ButtonEx.cpp : implementation file
//

/////////////////////////////////////////////////////////////////////////////
// include file declare
#include "stdafx.h"
#include "PersonMgr.h"
#include "ButtonEx.h"

/////////////////////////////////////////////////////////////////////////////
// CONSTANTS declare
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CButtonEx

CButtonEx::CButtonEx()
{
	m_nTimer = 0;
}

CButtonEx::~CButtonEx(){

}


BEGIN_MESSAGE_MAP(CButtonEx, CButton)
	//{{AFX_MSG_MAP(CButtonEx)
	ON_WM_MOVE()
	ON_WM_NCHITTEST()
	ON_WM_TIMER()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CButtonEx message handlers
//ODS_DISABLED   This bit is set if the item is to be drawn as disabled. 
//ODS_FOCUS   This bit is set if the item has input focus. 
//ODS_GRAYED   This bit is set if the item is to be dimmed. This bit is used only in a menu. 
//ODS_SELECTED 
void CButtonEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) {

	CDC*		pDC;
	CRect		rcItem;
	CString		strText;   
	UINT		itemAction;
	UINT		itemState;
	CPoint		point;

	GetCursorPos( &point );
	ScreenToClient ( &point );


	pDC = CDC::FromHandle( lpDrawItemStruct->hDC );
	rcItem = lpDrawItemStruct->rcItem;
	itemAction = lpDrawItemStruct->itemAction;
	itemState = lpDrawItemStruct->itemState;

	GetWindowText( strText );

	pDC->RoundRect(rcItem, CPoint(4, 4));

	if ( itemState & ODS_FOCUS || itemState & ODS_SELECTED){
		DrawButton( RGB( 128, 128, 192), RGB(0, 0, 255) );
	}
	else{
		DrawButton( GetSysColor(0), RGB(0, 0, 0) );
	}

	return;
}


void CButtonEx::OnMove(int x, int y) 
{
	CButton::OnMove(x, y);
}

UINT CButtonEx::OnNcHitTest(CPoint point){

	if ( GetState() & 0x0004 ){
		DrawButton( RGB( 128, 128, 192), RGB(0, 0, 255) );
	}
	else{
		DrawButton( RGB( 255, 255, 255), RGB(0,0,0) );
	}
	if ( m_nTimer ){
		KillTimer( m_nTimer );
	}
	m_nTimer = SetTimer( IDC_TIMERBUTTON, 200, NULL );
	return CButton::OnNcHitTest(point);
}

void CButtonEx::OnTimer(UINT nIDEvent){


	CRect			nRect;
	CPoint			point;

	GetCursorPos ( &point );
	ScreenToClient( &point );
	GetClientRect( &nRect );

	if ( nIDEvent == IDC_TIMERBUTTON ){
		if ( !nRect.PtInRect( point ) ){

			if ( GetState() & 0x0008 ){
				DrawButton( RGB( 128, 128, 192), RGB(0, 0, 255) );
			}
			else{
				DrawButton( GetSysColor(0), RGB(0,0,0) );
			}
			KillTimer( m_nTimer );
			m_nTimer = 0;
		}
	}
	
	CButton::OnTimer(nIDEvent);
}

void CButtonEx::DrawButton(COLORREF crBack, COLORREF crText){

	CRect		nRect;
	CDC*		pDC;
	CString		strText;

	GetClientRect( &nRect );
	nRect.DeflateRect( 2, 2, 2, 2);
	pDC = GetDC();
	pDC->FillSolidRect( &nRect, crBack );
	GetWindowText( strText );
	pDC->SetTextColor ( crText );
	pDC->DrawText( strText, &nRect, DT_CENTER|DT_SINGLELINE|DT_VCENTER );

	ReleaseDC( pDC );
	return;
}


BOOL CButtonEx::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) {
	// TODO: Add your message handler code here and/or call default
	::SetCursor( ::LoadCursor( NULL, IDC_ARROW ) );
	return TRUE;	
}
