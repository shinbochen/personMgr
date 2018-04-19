// SplitterWndEx.cpp: implementation of the CSplitterWndEx class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PersonMgr.h"
#include "SplitterWndEx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSplitterWndEx::CSplitterWndEx()
{

}

CSplitterWndEx::~CSplitterWndEx()
{

}

BEGIN_MESSAGE_MAP(CSplitterWndEx, CSplitterWnd)
	//{{AFX_MSG_MAP(CDialogEx)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplitterWndEx message handlers

int CSplitterWndEx::OnCreate(LPCREATESTRUCT lpCreateStruct){
	if (CSplitterWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 1;
}

/////////////////////////////////////////////////////////////////////////////
// CSplitterWndEx message handlers
void CSplitterWndEx::OnDrawSplitter( CDC* pDC, 
									ESplitType nType, const CRect& rect ){
	
	CSplitterWnd::OnDrawSplitter( pDC, nType, rect);

	if( pDC != NULL ){
		CBitmap			bitmap;
		CBrush			brush;

		bitmap.LoadBitmap( IDB_PATTERN );
		brush.CreatePatternBrush( &bitmap );
		bitmap.Detach( );

		switch( nType ){
		case splitBorder:
			pDC->FrameRect( &rect, &CBrush( RGB( BKRCOLOR,BKGCOLOR,BKBCOLOR ) ) );
			break;
		case splitBar:
			pDC->FillRect( &rect, &brush );
			break;
		case splitIntersection :
		case splitBox:
		default:
			break;
		}
	}
	return;
}
