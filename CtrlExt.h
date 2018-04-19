#if !defined(AFX_CTRLEXT_H__73174776_BFB9_4C45_AEBF_1190C75ACB31__INCLUDED_)
#define AFX_CTRLEXT_H__73174776_BFB9_4C45_AEBF_1190C75ACB31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class	CTreeCtrlEx;
/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx window
/////////////////////////////////////////////////////////////////////////////
// 用于控制List 与 Tree View的 超类

class CListCtrlEx : public CListCtrl
{
// Construction
public:
	CListCtrlEx();

// Attributes
public:

// Operations
public:
	// Assigns an image list to a list view control.
	CImageList*	SetImageList( CImageList *pImageList,	
							  int nImageListType = TVSIL_NORMAL);
	// 向此listView类加一 "列" 项目 
	BOOL AddColumn(	LPCTSTR strItem, 
					int nItem, 
					int nSubItem = -1,
					int nMask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM,
					int nFmt = LVCFMT_LEFT );

	BOOL AddItem (	int nItem, 
					int nSubItem,
					LPCTSTR strItem,
					int nImageIndex = -1 );
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlEx)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListCtrlEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListCtrlEx)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
class CTreeCursor  
{
public:
	CTreeCursor();
	virtual ~CTreeCursor();

// Attributes
protected:
	HTREEITEM		m_hTreeItem;
	CTreeCtrlEx		*m_pTree;

// Implementation
protected:
	CTreeCursor CTreeCursor::_Insert(LPCTSTR strItem, 
									 int nImageIndex,
									 HTREEITEM hAfter);

// Operations
public:	
	

	CTreeCursor( HTREEITEM hTreeItem, CTreeCtrlEx* pTree );
	CTreeCursor( const CTreeCursor& posSrc );
	const CTreeCursor& operator =( const CTreeCursor& posSrc );
	operator HTREEITEM();

	CTreeCursor InsertAfter(LPCTSTR strItem, 
							HTREEITEM hAfter,
							int nImageIndex = -1);
							
	CTreeCursor AddHead(LPCTSTR strItem, int nImageIndex = -1);
	CTreeCursor AddTail(LPCTSTR strItem, int nImageIndex = -1);

	int GetImageID();

	BOOL GetRect(LPRECT lpRect, BOOL bTextOnly);
	
	CTreeCursor GetNext(UINT nCode);
	CTreeCursor GetChild();
	CTreeCursor GetNextSibling();
	CTreeCursor GetPrevSibling();
	CTreeCursor GetParent();
	CTreeCursor GetFirstVisible();
	CTreeCursor GetNextVisible();
	CTreeCursor GetPrevVisible();
	CTreeCursor GetSelected();
	CTreeCursor GetDropHilight();
	CTreeCursor GetRoot();
	CString 	GetText();
	BOOL 		GetImage(int& nImage, int& nSelectedImage);
	UINT 		GetState(UINT nStateMask);
	DWORD 		GetData();
	BOOL 		Set(UINT nMask, LPCTSTR lpszItem, int nImage,
					int nSelectedImage, UINT nState, UINT nStateMask, LPARAM lParam);
	BOOL 		SetText(LPCTSTR lpszItem);
	BOOL 		SetImage(int nImage, int nSelectedImage);
	BOOL 		SetState(UINT nState, UINT nStateMask);
	BOOL 		SetData(DWORD dwData);
	BOOL 		HasChildren();
	
	BOOL 		Delete();
	BOOL 		Expand(UINT nCode = TVE_EXPAND);
	CTreeCursor Select(UINT nCode);
	CTreeCursor Select();
	CTreeCursor SelectDropTarget();
	CTreeCursor SelectSetFirstVisible();
	CEdit* 		EditLabel();
	CImageList* CreateDragImage();
	BOOL 		SortChildren();
	BOOL 		EnsureVisible();
};
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlEx window

class CTreeCtrlEx : public CTreeCtrl
{
// Construction
public:
	CTreeCtrlEx();

// Attributes
public:

// Operations
public:	
	// Assigns an image list to a list view control.
	CImageList* SetImageList( CImageList* pImageList, 
							  int nImageListType = TVSIL_NORMAL);

	
	CTreeCursor GetNextItem(HTREEITEM hItem, UINT nCode);
	CTreeCursor GetChildItem(HTREEITEM hItem);
	CTreeCursor GetNextSiblingItem(HTREEITEM hItem);
	CTreeCursor GetPrevSiblingItem(HTREEITEM hItem);
	CTreeCursor GetParentItem(HTREEITEM hItem);
	CTreeCursor GetFirstVisibleItem();
	CTreeCursor GetNextVisibleItem(HTREEITEM hItem);
	CTreeCursor GetPrevVisibleItem(HTREEITEM hItem);
	CTreeCursor GetSelectedItem();
	CTreeCursor GetDropHilightItem();
	CTreeCursor GetRootItem();
	CTreeCursor InsertItem(LPTV_INSERTSTRUCT lpInsertStruct);
	
	CTreeCursor InsertItem( UINT nMask, 
							LPCTSTR lpszItem,
							int nImage,
							int nSelectedImage, 
							UINT nState, 
							UINT nStateMask, 
							LPARAM lParam,
							HTREEITEM hParent, 
							HTREEITEM hInsertAfter);
	CTreeCursor InsertItem(	LPCTSTR lpszItem, 
							HTREEITEM hParent = TVI_ROOT,
							HTREEITEM hInsertAfter = TVI_LAST);
	CTreeCursor InsertItem(	LPCTSTR lpszItem, 
							int nImage, 
							int nSelectedImage,
							HTREEITEM hParent = TVI_ROOT, 
							HTREEITEM hInsertAfter = TVI_LAST);
							
	CTreeCursor Select(HTREEITEM hItem, UINT nCode);
	CTreeCursor SelectItem(HTREEITEM hItem);
	CTreeCursor SelectDropTarget(HTREEITEM hItem);
	CTreeCursor SelectSetFirstVisible(HTREEITEM hItem);
	CTreeCursor HitTest(CPoint pt, UINT* pFlags = NULL);
	CTreeCursor HitTest(TV_HITTESTINFO* pHitTestInfo);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeCtrlEx)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTreeCtrlEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTreeCtrlEx)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#include "CtrlExt.inl"
#endif // !defined(AFX_CTRLEXT_H__73174776_BFB9_4C45_AEBF_1190C75ACB31__INCLUDED_)
