// MenuEx.cpp: implementation of the CMenuEx class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PersonMgr.h"
#include "MenuEx.h"
#include "Mainfrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMenuEx::CMenuEx(){

}

CMenuEx::~CMenuEx(){

}

//////////////////////////////////////////////////////////////////////
// Initall the Menu
void CMenuEx::AttachMenu(HMENU hMenu, CToolBar* pToolBar, CSize sz){

	Attach( hMenu );
	ChangeMenuStyle( hMenu, TRUE );
	GetImageFromToolBar( pToolBar, sz, &m_ImageList, &m_arrMenuID);
	return;
}

//////////////////////////////////////////////////////////////////////
// change the menu to owner draw
BOOL CMenuEx::ChangeMenuStyle(HMENU hMenu, BOOL bTop){

	CMenu			*pMenu;

	pMenu = CMenu::FromHandle(hMenu);
	if( pMenu == NULL ){
		return FALSE;
	}
	for( UINT nCnt = 0; nCnt < pMenu->GetMenuItemCount(); nCnt++ ){

		CMenuItem*		pMenuItem = new CMenuItem();
		CMenu			*pSubMenu = NULL;

		pMenuItem->m_nType = pMenu->GetMenuItemID( nCnt );

		// is TOP MenuItem
		if( pMenuItem->m_nType < 0 && bTop ){
			pMenuItem->m_nType = (int)TOPITEM;
		}	

		pMenu->GetMenuString(nCnt, pMenuItem->m_strText, MF_BYPOSITION);
		pMenu->ModifyMenu(	nCnt, MF_BYPOSITION | MF_OWNERDRAW,
							pMenuItem->m_nType, LPCTSTR(pMenuItem) );

		pSubMenu = pMenu->GetSubMenu( nCnt );
		if(pSubMenu && pMenuItem->m_nType != -2 && !bTop){
			pMenuItem->m_nType = -1;
		}
		if( pSubMenu ){
			ChangeMenuStyle( pSubMenu->GetSafeHmenu(), FALSE );
		} 
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// Get the imageList and approite MenuID
int CMenuEx::GetImageFromToolBar(CToolBar* pToolBar, CSize sz, 
								 CImageList *pImageList, CUIntArray *pIDArray){
	
	CImageList*			pILTmp;
	CToolBarCtrl&		toolBarCtl = pToolBar->GetToolBarCtrl();

	if(pImageList == NULL || pIDArray == NULL){
		return -1;
	}

	int nCount = pToolBar->GetCount();
	if(nCount <= 0){
		return -1;
	}
	pILTmp = toolBarCtl.GetImageList();
	pImageList->Create( pILTmp );

	int nImageCount = pImageList->GetImageCount();
	for(int i = 0; i < nCount; i ++){

		UINT uID = pToolBar->GetItemID(i);
		if(uID != ID_SEPARATOR){
			pIDArray->Add(uID);
		}
	}
	int nSize = pIDArray->GetSize();
	ASSERT(nSize == nImageCount);
	return nSize;
}

//////////////////////////////////////////////////////////////////////
// Draw the top item
void CMenuEx::DrawTop(CDC *pDC, CRect rect, BOOL bSelected){

	if(bSelected){		
		pDC->SelectStockObject(BLACK_PEN);
		pDC->Rectangle(&rect);
		rect.DeflateRect(1, 1);
		pDC->FillSolidRect( &rect, RGB(176, 176, 224) );
	}
	else{
		pDC->FillSolidRect( &rect, GetSysColor(0) );
	}
	return;
}

//////////////////////////////////////////////////////////////////////
// Draw the item backgroud color
void CMenuEx::DrawBGColor(CDC *pDC, CRect rect, BOOL bSelected){

	if(bSelected){
		pDC->SelectStockObject( NULL_BRUSH );
		pDC->SelectStockObject( BLACK_PEN );
		pDC->Rectangle(&rect);
		rect.DeflateRect(1, 1);
		DrawBestRect(pDC, rect,  RGB(176, 176, 224),RGB(146, 146, 224), TRUE);
	}
	else{

		CRect rcGray(rect);
		rcGray.right = rcGray.left + PUBLICAREA;

		pDC->FillSolidRect( &rcGray, RGB(216, 216, 209) );

		CRect rcWhite(rect);
		rcWhite.left = rcGray.right;
		pDC->FillSolidRect( &rcWhite, RGB(240, 240, 240) );
	}
	return;
}

//////////////////////////////////////////////////////////////////////
// use the cr1 and cr2 to draw the shadow 
void CMenuEx::DrawBestRect(CDC *pDC, CRect rect, 
						   COLORREF cr1, COLORREF cr2, BOOL bHor){

	int r1 = GetRValue(cr1);//Red color1
	int g1 = GetGValue(cr1);//Green color1
	int b1 = GetBValue(cr1);//blue color1
	int r2 = GetRValue(cr2);//red color2
	int g2 = GetGValue(cr2);//green color2
	int b2 = GetBValue(cr2);//blue color2
	if(bHor){
		float dr = ((float)(r2 - r1))/(float)(rect.Width());
		float dg = ((float)(g2 - g1))/(float)(rect.Width());
		float db = ((float)(b2 - b1))/(float)(rect.Width());
		for(int i = rect.left; i < rect.right; i ++){
			int r = r1 + (int)(dr*((float)(i - rect.left)));
			int g = g1 + (int)(dg*((float)(i - rect.left)));
			int b = b1 + (int)(db*((float)(i - rect.left)));
			CPen pen(PS_SOLID, 1, RGB(r, g, b));
			CPen *old = pDC->SelectObject(&pen);
			pDC->MoveTo(i, rect.top);
			pDC->LineTo(i, rect.bottom);
			pDC->SelectObject(old);
		}
	}
	else{
		float dr = ((float)(r2 - r1))/(float)(rect.Height());
		float dg = ((float)(g2 - g1))/(float)(rect.Height());
		float db = ((float)(b2 - b1))/(float)(rect.Height());
		for(int i = rect.top; i < rect.bottom; i ++){
			int r = r1 + (int)(dr*((float)(i - rect.top)));
			int g = g1 + (int)(dg*((float)(i - rect.top)));
			int b = b1 + (int)(db*((float)(i - rect.top)));
			CPen pen(PS_SOLID, 1, RGB(r, g, b));
			CPen *old = pDC->SelectObject(&pen);
			pDC->MoveTo(rect.left, i);
			pDC->LineTo(rect.right, i);
			pDC->SelectObject(old);
		}
	}
	return;
}

//////////////////////////////////////////////////////////////////////
// draw the icon
void CMenuEx::DrawIcon(CDC *pDC, CRect rect, UINT uIndex, BOOL IsEnabled){

	rect.DeflateRect(3, 3, 3, 3);

	UINT	uStyle =ILD_TRANSPARENT;
	if(IsEnabled){
		uStyle |=ILD_BLEND50;
		m_ImageList.Draw(pDC, uIndex, CPoint(rect.left, rect.top), uStyle);
	}
	else{
		m_ImageList.Draw(pDC, uIndex, CPoint(rect.left-1, rect.top-1), uStyle);
	}
	return;
}

//////////////////////////////////////////////////////////////////////
// draw the Text
void CMenuEx::DrawText(CDC *pDC, CRect rect, 
					   CString sText, BOOL bEnable){
	rect.DeflateRect(8, 0, 0, 0);

	if( bEnable ){
		pDC->DrawText(sText, &rect, DT_LEFT|DT_SINGLELINE|DT_EXPANDTABS|DT_VCENTER );
	}
	else{
		pDC->SetBkMode( TRANSPARENT );
		pDC->SetTextColor( RGB( 160, 160, 160 ) );
		pDC->DrawText(sText, &rect, DT_EXPANDTABS|DT_LEFT|DT_SINGLELINE|DT_VCENTER );
	}
	return;
}
//////////////////////////////////////////////////////////////////////
// Measure the Item Rect
void CMenuEx::MeasureItem(LPMEASUREITEMSTRUCT lpMIS){

	CString			strText;
	CMainFrame*		pFrame;
	CSize			size;
	CDC*			pDC = NULL;

	lpMIS->itemWidth = 180;
	lpMIS->itemHeight = 24;
	strText = ((CMenuItem*)(lpMIS->itemData))->m_strText;
	pFrame = (CMainFrame*)AfxGetMainWnd( );
	pDC = pFrame->GetDC( );
	

	strText = pFrame->GetDispPhrase( strText );

	size = pDC->GetTextExtent( strText );
	lpMIS->itemWidth = size.cx;
	pFrame->ReleaseDC( pDC );


	UINT nMenuID = ((CMenuItem*)(lpMIS->itemData))->m_nType;
	switch(nMenuID){
	// 顶层菜单条  
	case TOPITEM:			
		//lpMIS->itemWidth =((CMenuItem*)(lpMIS->itemData))->m_strText.GetLength()*5;
		lpMIS->itemWidth -= 5;
		break;
	// 弹出菜单  
	case POPITEM:		
		//lpMIS->itemWidth =((CMenuItem*)(lpMIS->itemData))->m_strText.GetLength()*10;
		lpMIS->itemWidth += 25;
		break;
	// 分隔条
	case SEPAITEM:		
		lpMIS->itemHeight = 5;
		break;
	// 一般的菜单
	default:				
		//	lpMIS->itemWidth =((CItemInfo*)(lpMIS->itemData))->strText.GetLength()*10;
		lpMIS->itemWidth += 20;
		break;	
	}
	return;
}

//////////////////////////////////////////////////////////////////////
// Draw the Item 
void CMenuEx::DrawItem(LPDRAWITEMSTRUCT lpDIS){

	CRect		rcItem;
	UINT		uState;
	CString		strText;
	UINT		nMenuID;
	CDC*		pDC = CDC::FromHandle( lpDIS->hDC );
	CMainFrame*	pFrame;

	pFrame = (CMainFrame*)AfxGetMainWnd();


	VERIFY(pDC);
	pDC->SetBkMode(TRANSPARENT);
	rcItem = lpDIS->rcItem;
	uState = lpDIS->itemState;	
	if(lpDIS->itemData == NULL){
		return;
	}
	strText = ((CMenuItem*)(lpDIS->itemData))->m_strText;
	nMenuID = ((CMenuItem*)(lpDIS->itemData))->m_nType;

	strText = pFrame->GetDispPhrase( strText );

	CRect		rcIcon(rcItem);
	rcIcon.right = rcIcon.left + PUBLICAREA;
	CRect		rcText(rcItem);
	rcText.left  = rcIcon.right;
	switch(nMenuID){
	// 顶层菜单条 
	case TOPITEM:  
		if( uState&ODS_SELECTED ){
			DrawTop( pDC, rcItem, TRUE );
		}
		else{
			DrawTop( pDC, rcItem, FALSE );
		}
		DrawText( pDC, rcItem, strText, TRUE) ;
		break;

	// 弹出菜单  
	case POPITEM:
		if( uState&ODS_SELECTED ){			
			pDC->Rectangle( &rcItem );
			rcItem.DeflateRect(1, 1);
			DrawBestRect( pDC, rcItem, RGB(200,255,200), RGB(100,255,100), TRUE );
		}
		else{
			DrawBGColor( pDC, rcItem, FALSE );
		}
		DrawText( pDC, rcText, strText, TRUE);
		break;
	// 分隔条  
	case SEPAITEM:
		DrawBGColor(pDC,rcItem,FALSE);
		rcText.top =rcText.Height()/2+rcText.top ;
		rcText.bottom =rcText.top +2;
		rcText.left +=2;
		rcText.right -=2;
		pDC->Draw3dRect(rcText,RGB(64,0,128),RGB(255,255,255));
		break;
	// 一般的菜单	
	default:		
		int nIndex = GetIconIndexByID( nMenuID );
		// 画背景
		if( uState&ODS_SELECTED ){
			if( uState&ODS_GRAYED ){
				DrawBGColor( pDC, rcItem, FALSE );
			} 
			else{
				DrawBGColor( pDC, rcItem, TRUE );
			}
		}
		else{
			DrawBGColor( pDC, rcItem, FALSE );
		}

		// 画ICON
		if ( nIndex >= 0 ){
			if( uState&ODS_GRAYED ){
				DrawIcon(pDC,rcItem,nIndex,TRUE);
			}
			else{
				//if( uState&ODS_SELECTED )
				DrawIcon(pDC,rcItem,nIndex, FALSE);
			}
		}
		// draw Text
		if( uState&ODS_GRAYED ){
			DrawText(pDC, rcText, strText, FALSE);
		}
		else{		
			if( uState&ODS_CHECKED ){			
				DrawText(pDC, rcText, "√"+strText, TRUE);
				break;
			}
			else{
				DrawText(pDC, rcText, strText, TRUE);
				break;
			}	
		}
		break;
	}
	return;
}

//////////////////////////////////////////////////////////////////////
// get imageId
int CMenuEx::GetIconIndexByID(UINT uID){

	for(int i = 0; i < m_arrMenuID.GetSize(); i ++){
		if( uID == m_arrMenuID[i] )	{
			ASSERT(i < m_ImageList.GetImageCount());
			return i;
		}
	}
	return -1;
}
