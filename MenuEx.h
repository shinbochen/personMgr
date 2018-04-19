// MenuEx.h: interface for the CMenuEx class.
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// CONSTANTS declare
#if !defined(AFX_MENUEX_H__F7737CE2_6F2F_4798_BC3D_4581964C65ED__INCLUDED_)
#define AFX_MENUEX_H__F7737CE2_6F2F_4798_BC3D_4581964C65ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 

#ifndef	PUBLICAREA
#define PUBLICAREA	20
#endif

//////////////////////////////////////////////////////////////////////
// enum structor declare
enum{
	TOPITEM = -2,
	POPITEM = -1,
	SEPAITEM = 0
};
class CMenuItem{
public:
	int		m_nType;
	UINT	m_nImage;
	CString	m_strText;
};

class CMenuEx : public CMenu {
// constructor /deconstructor
public:
	CMenuEx();
	virtual ~CMenuEx();
// methods
public:
	int GetIconIndexByID(UINT uID);
	virtual void DrawItem(LPDRAWITEMSTRUCT  lpDIS);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMIS);
	void DrawText(CDC* pDC, CRect rect, CString sText, BOOL bEnable);
	void DrawIcon(CDC* pDC, CRect rect, UINT uIndex, BOOL IsEnabled);
	void DrawBestRect(CDC *pDC, CRect rect, COLORREF cr1,COLORREF cr2, BOOL bHor);
	void DrawBGColor(CDC* pDC, CRect rect, BOOL bSelected);
	void DrawTop(CDC *pDC,CRect rect,BOOL bSelected);
	int GetImageFromToolBar(CToolBar* pToolBar, CSize sz, CImageList *pImageList,  CUIntArray *pIDArray);
	BOOL ChangeMenuStyle( HMENU hMenu, BOOL bTop );
	void AttachMenu(HMENU hMenu, CToolBar* pToolBar,CSize sz);

// property
protected:
	CUIntArray		m_arrMenuID;
	CImageList		m_ImageList;   

};

#endif // !defined(AFX_MENUEX_H__F7737CE2_6F2F_4798_BC3D_4581964C65ED__INCLUDED_)
