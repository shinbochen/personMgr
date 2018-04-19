// ToolBarEx.cpp : implementation file
//

#include "stdafx.h"
#include "PersonMgr.h"
#include "ToolBarEx.h"
#include "picture.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolBarEx

CToolBarEx::CToolBarEx(){
	m_nTimer = 0;
}

CToolBarEx::~CToolBarEx(){

}


BEGIN_MESSAGE_MAP(CToolBarEx, CToolBar)
	//{{AFX_MSG_MAP(CToolBarEx)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolBarEx message handlers

int CToolBarEx::OnCreate(LPCREATESTRUCT lpCreateStruct) {
		
	if (CToolBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}
/////////////////////////////////////////////////////////////////////////////
// CToolBarEx message handlers onsize
void CToolBarEx::OnSize(UINT nType, int cx, int cy) {

	CToolBar::OnSize(nType, cx, cy);
	m_nX = cx;
	m_nY = cy;
	m_nX0 = GetItemWidth();
	OnPaint();
	//if( m_nTimer == 0 ){
	//	m_nTimer = SetTimer( IDC_TOOLBARTIMER, 1000, NULL );
	//}
	return;
}

/////////////////////////////////////////////////////////////////////////////
// CToolBarEx message handlers onsize
BOOL CToolBarEx::OnEraseBkgnd(CDC* pDC){

	CRect			nRect;
	CRect			rect2;

	GetClientRect ( &nRect );

	rect2 = nRect;

	nRect.right = nRect.left + m_nX0;
	pDC->FillSolidRect( &nRect, RGB(BKRCOLOR,BKGCOLOR,BKBCOLOR) );

	rect2.left+=m_nX0;

	
	CPicture		pic;
	CString			strPath;

	strPath = GetModulePath( )+"\\board.jpg";
	if( pic.Load( strPath ) == TRUE ){
		pic.Render( pDC, &rect2 );
	}		
	else{
		pDC->FillRect(&rect2,&CBrush(RGB(BKRCOLOR,BKGCOLOR,BKBCOLOR)) );
	}	
	
	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////
// CToolBarEx message handlers onsize
void CToolBarEx::OnPaint(){

	CToolBarCtrl&		toolBarCtrl = GetToolBarCtrl();
	CPoint				nPoint;
	CRect				nRect;

	GetClientRect( &nRect );
	CPaintDC			dc(this);

	CToolBar::OnPaint();

	GetCursorPos( &nPoint );
	ScreenToClient( &nPoint );
	//if ( !nRect.PtInRect( nPoint )  ){
	//	return;
	//}


	int					nSelCnt;
	int					nCnt;
	int					nLen;
	int					nID;
	int					nIID = 0;

	nSelCnt = toolBarCtrl.HitTest( &nPoint );

	nLen = toolBarCtrl.GetButtonCount();
	for( nCnt = 0; nCnt < nLen; nCnt++ ){

		nID = GetItemID( nCnt );
		if( !toolBarCtrl.IsButtonEnabled(nID) ){
			//OnDrawNormalD( pDC, nCnt, nIID );
			OnDrawNormalD( &dc, nCnt, nIID );
		}
		else{
			if ( nID == ID_SEPARATOR ){
				//DrawSeparator( pDC, nCnt );
				DrawSeparator( &dc, nCnt );
				//DrawSeparator( &dc, nCnt );
				continue;
			}
			if( nCnt == nSelCnt ){
				//OnDrawSelect( pDC, nCnt, nIID );
				OnDrawSelect( &dc, nCnt, nIID );
				//OnDrawSelect( &dc, nCnt, nIID );
			}
			else{
				//OnDrawNormal( pDC, nCnt, nIID );
				OnDrawNormal( &dc, nCnt, nIID );
				//OnDrawNormal( &dc, nCnt, nIID );
			}
		}
		nIID++;
	}
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CToolBarEx message handlers onsize
/*void CToolBarEx::OnDrawSelect(CDC* pDC, int nCnt){

	CToolBarCtrl&		toolBarCtrl = GetToolBarCtrl();
	CImageList*			pImageList;
	CRect				nRect;
	UINT				nID;
	int					nImageID = 0;

	
	nID = GetItemID( nCnt );
	if ( nID == ID_SEPARATOR || !toolBarCtrl.IsButtonEnabled(nID) ){
		return;
	}

	pImageList = toolBarCtrl.GetImageList();
	toolBarCtrl.GetItemRect( nCnt, &nRect );

	nRect.DeflateRect( 0, 0, 1, 1);		
	pDC->FrameRect ( &nRect, &CBrush( RGB(0, 0, 0) ) );
	nRect.DeflateRect( 1, 1, 1, 1);
	pDC->FillSolidRect( &nRect, RGB(176, 176, 224) ); 

	for ( int i = 0; i <= nCnt; i++ ){
		if ( GetItemID(i) == ID_SEPARATOR ){
			nImageID++;
		}
	}
	nImageID = nCnt - nImageID;

	pImageList->Draw( pDC, nImageID, 
		CPoint( nRect.left + (nRect.Width() - 16)/2, nRect.top+1 ),
		ILD_TRANSPARENT );

	CFont			nFont;
	CString			strText;

	strText = GetButtonText( nCnt );
	if ( strText.IsEmpty() == FALSE ){
		nFont.CreatePointFont( 90, "Arail", pDC);
		pDC->SelectObject ( &nFont );
		nRect.top += 19;
		pDC->SetTextColor( RGB( 0, 0, 255 ) );
		pDC->DrawText(	strText, 
						&nRect, 
						DT_EXPANDTABS|DT_CENTER|DT_SINGLELINE|DT_VCENTER );
	}
	return;	
}*/

/////////////////////////////////////////////////////////////////////////////
// CToolBarEx message handlers onsize
void CToolBarEx::OnDrawSelect(CDC* pDC, int nCnt, int nIID){

	CToolBarCtrl&		toolBarCtrl = GetToolBarCtrl();
	CImageList*			pImageList;
	CRect				rect;
	

	pImageList = toolBarCtrl.GetImageList();
	toolBarCtrl.GetItemRect( nCnt, &rect );
	
	pDC->FrameRect ( &rect, &CBrush( RGB(0, 0, 0) ) );
	rect.DeflateRect( 1, 1, 1, 1);
	pDC->FillSolidRect( &rect, RGB(176, 176, 224) ); 


	pImageList->Draw( pDC,
					  nIID, 
					  CPoint( rect.left + (rect.Width() - 16)/2, rect.top+2 ),
					  ILD_TRANSPARENT );

	CFont			font;
	CString			strText;

	strText = GetButtonText( nCnt );
	if ( strText.IsEmpty() == FALSE ){
		font.CreatePointFont( 90, "Arail", pDC);
		pDC->SelectObject ( &font );
		rect.top += 19;
		pDC->SetTextColor( RGB( 0, 0, 255 ) );
		pDC->DrawText(	strText, 
						&rect, 
						DT_EXPANDTABS|DT_CENTER|DT_SINGLELINE|DT_VCENTER );
	}
	return;	
}

/////////////////////////////////////////////////////////////////////////////
// CToolBarEx message handlers onsize
void CToolBarEx::OnDrawNormal( CDC* pDC, int nCnt, int nIID ){

	CToolBarCtrl&		toolBarCtrl = GetToolBarCtrl();
	CImageList*			pImageList;
	CRect				rect;
	

	pImageList = toolBarCtrl.GetImageList();
	toolBarCtrl.GetItemRect( nCnt, &rect );
	pDC->FillSolidRect( &rect, RGB(BKRCOLOR,BKGCOLOR,BKBCOLOR) ); 


	pImageList->Draw( pDC,
					  nIID, 
					  CPoint( rect.left + (rect.Width() - 16)/2, rect.top+4 ),
					  ILD_TRANSPARENT );

	CFont			font;
	CString			strText;

	strText = GetButtonText( nCnt );
	if ( strText.IsEmpty() == FALSE ){
		font.CreatePointFont( 90, "Arail", pDC);
		pDC->SelectObject ( &font );
		rect.top += 19;
		pDC->SetTextColor( RGB( 0, 0, 255 ) );
		pDC->DrawText(	strText, 
						&rect, 
						DT_EXPANDTABS|DT_CENTER|DT_SINGLELINE|DT_VCENTER );
	}
	return;	
}
/////////////////////////////////////////////////////////////////////////////
// CToolBarEx message handlers onsize
void CToolBarEx::OnDrawNormalD( CDC* pDC, int nCnt, int nIID ){

	CToolBarCtrl&		toolBarCtrl = GetToolBarCtrl();
	CImageList*			pImageList;
	CRect				rect;
	

	pImageList = toolBarCtrl.GetImageList();
	toolBarCtrl.GetItemRect( nCnt, &rect );
	pDC->FillSolidRect( &rect, RGB(BKRCOLOR,BKGCOLOR,BKBCOLOR) ); 


	pImageList->Draw( pDC,
					  nIID, 
					  CPoint( rect.left + (rect.Width() - 16)/2, rect.top+4 ),
					  ILD_TRANSPARENT |ILD_BLEND50);

	CFont			font;
	CString			strText;

	strText = GetButtonText( nCnt );
	if ( strText.IsEmpty() == FALSE ){
		font.CreatePointFont( 90, "Arail", pDC);
		pDC->SelectObject ( &font );
		rect.top += 19;
		pDC->SetTextColor( RGB( 0, 0, 255 ) );
		pDC->DrawText(	strText, 
						&rect, 
						DT_EXPANDTABS|DT_CENTER|DT_SINGLELINE|DT_VCENTER );
	}
	return;	
}
/////////////////////////////////////////////////////////////////////////////
// CToolBarEx message handlers onsize
void CToolBarEx::DrawSeparator( CDC* pDC, int nCnt ){

	CToolBarCtrl&		toolBarCtrl = GetToolBarCtrl();
	CRect				rect;

	
	toolBarCtrl.GetItemRect( nCnt, &rect );
	pDC->FillSolidRect( &rect, RGB(BKRCOLOR,BKGCOLOR,BKBCOLOR) );
	pDC->MoveTo( rect.left + rect.Width()/2, rect.top + 2 );
	pDC->LineTo( rect.left + rect.Width()/2, rect.bottom - 2 );
	return;
}
/////////////////////////////////////////////////////////////////////////////
// CToolBarEx message handlers onsize
void CToolBarEx::OnTimer(UINT nIDEvent) {

	if( nIDEvent == IDC_TOOLBARTIMER ){
		MoveText( );
	}	
	CToolBar::OnTimer(nIDEvent);
}
/////////////////////////////////////////////////////////////////////////////
// CToolBarEx message handlers onsize
void CToolBarEx::MoveText(){

	static int	nX = 0;
	static int	nStep = 5;
	CSize		size;
	int			nWidth;

	CDC*		pDC = GetDC();
	CRect		rect2( m_nX0, 0+1, m_nX-2, m_nY );
	CString		strText;

	pDC->SetBkMode( TRANSPARENT );

	pDC->SetTextColor( RGB(BKRCOLOR,BKGCOLOR,BKBCOLOR) );
	pDC->TextOut( m_nX0 + nX, 2, m_strPrev );

	//pDC->FillSolidRect( &rect2, RGB( BKRCOLOR,BKGCOLOR,BKBCOLOR ) );
	
	CBrush			brush;
	CBrush*			pBrush;
	
	brush.CreateSolidBrush( RGB(240,160,250) );

	pBrush = pDC->SelectObject( &brush );
	//pDC->RoundRect( &rect2, CPoint(8,8) );
	pDC->DrawFocusRect( &rect2 );
	pDC->SelectObject( pBrush );

	
	pDC->SetTextColor( RGB(BKRCOLOR	,BKGCOLOR,BKBCOLOR) );
	pDC->DrawText(m_strPrev, &rect2, DT_SINGLELINE|DT_CENTER|DT_VCENTER );

	strText = GetString();
	m_strPrev = strText;

	size = pDC->GetTextExtent( strText );
	nWidth = size.cx;
	if( nWidth > rect2.Width() ){
		return;
	}

	nX += nStep;
	if( nX + nWidth + m_nX0 >= m_nX ){
		nStep = -1;
	}
	if( nX <= 0 ){
		nStep = 1;
	}

	pDC->SetTextColor( RGB(220, 220, 220) );
	pDC->DrawText(strText, &rect2, DT_SINGLELINE|DT_CENTER|DT_VCENTER );
	//pDC->TextOut( m_nX0 + nX, 4, strText );
	ReleaseDC( pDC );
	//pDC->DeleteDC();
	return;
}

/////////////////////////////////////////////////////////////////////////////
// CToolBarEx message handlers onsize
int CToolBarEx::GetItemWidth( ){
	
	int				nLen;
	int				nCnt;
	int				nWidth = 0;
	CRect			rect;
	
	CToolBarCtrl&	toolCtrl = GetToolBarCtrl();	

	nLen = toolCtrl.GetButtonCount();
	for( nCnt = 0; nCnt < nLen; nCnt++ ){
		toolCtrl.GetItemRect( nCnt, &rect );
		nWidth += rect.Width();
	}
	return nWidth;	
}
/////////////////////////////////////////////////////////////////////////////
// CToolBarEx message handlers onsize
CString CToolBarEx::GetString( ){

	CString			strText;
	CTime			time;
	CString			strTime;

	time = CTime::GetCurrentTime();

	if( m_strUser.IsEmpty() ){
		strText.Empty();
	}
	else{
		strText = m_strUser+": ";
	}
	//strText = "Dear "+m_strUser+"! ";

	if( time.GetHour() <= 12 ){
		strText += " Good Morning!";
	}
	else if (time.GetHour() < 18 ){
		strText += "Good Afternoon!";
	}
	else{
		strText += "Good Evening!";
	}
	strTime = time.Format( "  %Y-%m-%d %H:%M:%S %A" );
	strText += strTime;
	return strText;
}
